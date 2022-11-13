#include "ContinuousRotateComponent.h"

ContinuousRotateComponent::ContinuousRotateComponent(float rotationRate, vec3 axis, int updateOrder) :
	Component(updateOrder), rotationRate(rotationRate), axis(axis)
{
	componentType = MOVE;
}

void ContinuousRotateComponent::update(const float& deltaTime)
{
	mat4 rot = owningGameObject->getRotation();

	rot *= glm::rotate(glm::radians(rotationRate) * deltaTime, axis);
	owningGameObject->setRotation(rot);
}
