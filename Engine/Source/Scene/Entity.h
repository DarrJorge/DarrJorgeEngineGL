#pragma once

#include <memory>
#include <unordered_map>

#include "Components/Component.h"
#include <Core/Utility.h>

namespace DarrJorge
{
class Mesh;
class MeshRendererComponent;

class Entity
{
public:
    Entity() = default;
    ~Entity() = default;

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    Entity(Entity&&) = default;
    Entity& operator=(Entity&&) = default;

public:
    template<typename T, typename ... Args>
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
    const T* getComponent() const
    {
        static_assert(std::is_base_of_v<Component, T>);

        const auto it = m_components.find(ComponentTypeIdGenerator::get<T>());
        return it != m_components.end() ? static_cast<T*>(it->second.get()) : nullptr;
    }

    template <typename T>
    [[nodiscard]] bool hasComponent() const
    {
        return getComponent<T>() != nullptr;
    }

    template <typename T>
    void removeComponent()
    {
        static_assert(std::is_base_of_v<Component, T>);

        m_components.erase(ComponentTypeIdGenerator::get<T>());
    }

    void update(float deltaTime);

private:
    std::unordered_map<ComponentTypeId, std::unique_ptr<Component>> m_components;
};
}