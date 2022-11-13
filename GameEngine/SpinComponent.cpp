#include "SpinComponent.h"

// Constructor
SpinComponent::SpinComponent(float rotRateDegrees, vec3 axis, int updateOrder) :
	Component(updateOrder), rotRate(glm::radians(rotRateDegrees)), axis(axis)
{
	componentType = MOVE;
}

// Update
void SpinComponent::update(const float& deltaTime)
{
	mat4 rot = owningGameObject->getRotation(LOCAL);

	rot *= glm::rotate(rotRate * deltaTime, axis);
	owningGameObject->setRotation(rot, LOCAL);
}
