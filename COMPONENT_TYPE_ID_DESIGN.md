# Component type lookup without `dynamic_cast`

## Problem

`Entity::getComponent<T>()`/`removeComponent<T>()` (`Engine/Source/Scene/Entity.h`) currently
find a component by scanning `m_components` and calling `dynamic_cast<T*>` on every element:

```cpp
template <typename T>
T* getComponent()
{
    static_assert(std::is_base_of_v<Component, T>);

    for (auto& component : m_components)
    {
        if (auto ptr = dynamic_cast<T*>(component.get()))
        {
            return ptr;
        }
    }
    return nullptr;
}
```

This is called every frame (`RotatorComponent::update`, `CameraControllerComponent::update`, etc.
all call `owner()->getComponent<T>()`), and `dynamic_cast` pays for RTTI's general
multiple/virtual-inheritance-aware algorithm on every call, even though every concrete component
in this engine (`TransformComponent`, `MeshRendererComponent`, `CameraComponent`,
`RotatorComponent`, `CameraControllerComponent`, ...) derives directly and only from `Component` —
there is no deeper hierarchy and lookups are always for an *exact* type, never "any subclass of".

## Option B — custom compile-time-assigned type ID, no RTTI

Same idea as Unreal's `Cast<T>()`, scaled down: Unreal walks a `UClass*` parent-chain built by its
reflection system (UHT-generated, needed for serialization/GC/Blueprints); this engine has no
reflection system and no need for one, so a flat integer ID per concrete type is enough — no
macros, no code generation.

### `Component.h`

```cpp
#pragma once

#include <cstddef>

namespace DarrJorge
{
class Entity;

using ComponentTypeId = size_t;

class ComponentTypeIdGenerator
{
public:
    template <typename T>
    static ComponentTypeId get()
    {
        static const ComponentTypeId id = next();
        return id;
    }

private:
    static ComponentTypeId next()
    {
        static ComponentTypeId counter = 0;
        return counter++;
    }
};

class Component
{
public:
    virtual ~Component() = default;

    [[nodiscard]] virtual ComponentTypeId typeId() const = 0;

    [[nodiscard]] Entity* owner() const { return m_owner; }

private:
    friend class Entity;

    Entity* m_owner = nullptr;
};

template <typename Derived>
class ComponentBase : public Component
{
public:
    ComponentTypeId typeId() const override { return ComponentTypeIdGenerator::get<Derived>(); }
};
}  // namespace DarrJorge
```

### Every concrete component — one-line base class change

```cpp
// before: class TransformComponent : public Component
class TransformComponent : public ComponentBase<TransformComponent>
{
    ...
};
```
Same for `MeshRendererComponent`, `CameraComponent`, `RotatorComponent`,
`CameraControllerComponent` — nothing else in those classes changes.

### `Entity.h`

```cpp
template <typename T>
T* getComponent()
{
    static_assert(std::is_base_of_v<Component, T>);

    const ComponentTypeId id = ComponentTypeIdGenerator::get<T>();
    for (auto& component : m_components)
    {
        if (component->typeId() == id)
        {
            return static_cast<T*>(component.get());
        }
    }
    return nullptr;
}

// const overload: identical body, `static_cast<const T*>`

template <typename T>
void removeComponent()
{
    static_assert(std::is_base_of_v<Component, T>);

    const ComponentTypeId id = ComponentTypeIdGenerator::get<T>();
    m_components.erase(
        std::remove_if(m_components.begin(), m_components.end(),
            [id](const auto& component) { return component->typeId() == id; }),
        m_components.end());
}
```

No `dynamic_cast`, no `typeid`, no RTTI dependency at all — `typeId()` is a single virtual call
returning a `size_t` compared with `==`, then an unchecked `static_cast` (safe here because the ID
match already proves the concrete type).

## Option B+C — also replace the linear scan with O(1) lookup

Option B still scans `m_components` linearly (cheap per-element check, but still O(n)). Once components
carry a `typeId()`, storage can move from `std::vector<std::unique_ptr<Component>>` to a map keyed by
that same ID:

### `Entity.h`

```cpp
private:
    std::unordered_map<ComponentTypeId, std::unique_ptr<Component>> m_components;
```

```cpp
template <typename T, typename... Args>
T& addComponent(Args&&... args)
{
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    component->m_owner = this;
    T& result = *component;
    m_components[ComponentTypeIdGenerator::get<T>()] = std::move(component);
    return result;
}

template <typename T>
T* getComponent()
{
    static_assert(std::is_base_of_v<Component, T>);

    const auto it = m_components.find(ComponentTypeIdGenerator::get<T>());
    return it != m_components.end() ? static_cast<T*>(it->second.get()) : nullptr;
}

template <typename T>
void removeComponent()
{
    static_assert(std::is_base_of_v<Component, T>);
    m_components.erase(ComponentTypeIdGenerator::get<T>());
}
```

`getComponent`/`removeComponent` become a single hash lookup instead of a scan-and-compare loop.

### Trade-off to accept explicitly

`Entity::update(deltaTime)` iterates `m_components` to call `update()` on each — with a `vector` this
runs in insertion order (the order `addComponent` calls were made in `SceneFactory`); with
`unordered_map` the iteration order is unspecified and may change between runs. No component in this
codebase currently depends on another sibling component's update order within the same frame
(`RotatorComponent`, `CameraControllerComponent` each only touch a *different* entity's components via
`owner()->getComponent<T>()`, never a same-entity sibling's freshly-updated-this-frame state), so this
is safe today — but it is a real, deliberate change in guarantee, not a free upgrade. If a future
component ever needs "run after sibling X", `unordered_map` storage would need revisiting (e.g. an
explicit priority/order field) before that dependency could be expressed.

Also implicitly changes semantics from "first component whose type matches" to "at most one component
per concrete type per entity" (`addComponent<T>` called twice now replaces the previous instance
instead of appending a second one) — matches how every component is used in this codebase today, but is
a behavior change worth knowing about if that's ever relied on.

## Recommendation

Adopt **B** first — it's a pure lookup-mechanism swap (`Component.h`, `Entity.h`, and one base-class
line per concrete component file), fully backward compatible with existing call sites
(`getComponent<T>()`/`removeComponent<T>()` keep their exact signatures), and removes `dynamic_cast`/RTTI
entirely. Layer **C** on top only when the linear scan is actually shown to matter (this engine has a
handful of components per entity today), since C also changes the update-order guarantee and the
one-component-per-type semantics, which are worth deciding on deliberately rather than picking up as a
side effect.
