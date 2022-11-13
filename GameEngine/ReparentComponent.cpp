#include "ReparentComponent.h"

// Constructor
ReparentComponent::ReparentComponent(GameObject* newParent, float radius, int updateOrder) :
	Component(updateOrder), newParent(newParent), radius(radius)
{} // end Constructor

void ReparentComponent::update(const float& deltaTime)
{
	// Check whether the spaceship is "in range"
	auto distanceToNewParent = glm::distance(newParent->getPosition(), owningGameObject->getPosition());
	if (distanceToNewParent <= radius) {
		reparent();
	}
}


void ReparentComponent::reparent()
{
	// Vector storing all move components of the moon
	std::vector<Component*> components = owningGameObject->getComponents();

	for (Component* component : components) {
		if (component->getComponentType() == MOVE) {
			// Remove all move component of the old parent
			owningGameObject->removeComponent(component);
		}
	}
	// Reparent to the new parent
	newParent->reparent(owningGameObject);
	// Place the stolen moon "under" the ship
	owningGameObject->setPosition(vec3(0.0f, -1.0f, 0.0f), LOCAL);

	// Reattach move components to the moon after reparenting
	for (Component* component : components) {
		if (component->getComponentType() == MOVE) {
			// Remove all move component of the old parent
			owningGameObject->addComponent(component);
		}
	}
}
