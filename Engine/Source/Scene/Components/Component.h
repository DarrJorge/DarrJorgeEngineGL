#pragma once

namespace DarrJorge
{
class Entity;

class Component
{
public:
    virtual ~Component() = default;

    virtual void update(float deltaTime) {}

    [[nodiscard]] Entity* owner() const { return m_owner; }

private:
    friend class Entity;

    Entity* m_owner = nullptr;
};
}
