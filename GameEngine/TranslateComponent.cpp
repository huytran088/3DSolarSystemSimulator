#include "TranslateComponent.h"

TranslateComponent::TranslateComponent(vec3 velocity, int updateOrder)
	: Component(updateOrder), velocity(velocity)
{
	componentType = MOVE;
}

void TranslateComponent::initialize()
{
	cout << "TranslateRotateComponent initialized" << endl;

	owningGameObject->setPosition(vec3(0.0f, 0.0f, -5.0f));
}



void TranslateComponent::update(const float& deltaTime)
{
	/*if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP)) {
		vec3 position = owningGameObject->getPosition();

		position += velocity * deltaTime;

		owningGameObject->setPosition(position);
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN)) {
		vec3 position = owningGameObject->getPosition();

		position -= velocity * deltaTime;

		owningGameObject->setPosition(position);
	}*/
	vec3 position = owningGameObject->getPosition();

	position += velocity * deltaTime;

	owningGameObject->setPosition(position);
}
