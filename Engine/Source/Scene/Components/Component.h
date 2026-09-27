#pragma once

#include <string_view>

namespace DarrJorge
{
class Entity;

using ComponentTypeId = size_t;

class ComponentTypeIdGenerator
{
public:
    template <class T>
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

    virtual void update(float deltaTime) {}

    [[nodiscard]] virtual ComponentTypeId typeId() const = 0;
    [[nodiscard]] virtual std::string_view typeName() const = 0;
    [[nodiscard]] Entity* owner() const { return m_owner; }

private:
    friend class Entity;

    Entity* m_owner = nullptr;
};

template <typename Derived>
class ComponentBase : public Component
{
public:
    [[nodiscard]]
    ComponentTypeId typeId() const override { return ComponentTypeIdGenerator::get<Derived>(); }
};
}
