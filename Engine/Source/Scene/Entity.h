#pragma once

#include <memory>
#include <Core/Utility.h>

namespace DarrJorge
{
class Mesh;
class MeshRendererComponent;
class Component;

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
        m_components.emplace_back(std::move(component));
        return result;
    }

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

    template <typename T>
    const T* getComponent() const
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

    template <typename T>
    [[nodiscard]] bool hasComponent() const
    {
        return getComponent<T>() != nullptr;
    }

    template <typename T>
    void removeComponent()
    {
        static_assert(std::is_base_of_v<Component, T>);

        m_components.erase(std::remove_if(m_components.begin(), m_components.end(),
            [](const auto& component){
                return dynamic_cast<T*>(component.get()) != nullptr;
            }),
            m_components.end());
    }

    void update(float deltaTime);

private:
    std::vector<std::unique_ptr<Component>> m_components;
};
}