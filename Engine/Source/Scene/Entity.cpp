#include "Entity.h"
#include "Components/Component.h"

using namespace DarrJorge;

void Entity::update(float deltaTime)
{
    for (auto& [id, component] : m_components)
    {
        component->update(deltaTime);
    }
}
