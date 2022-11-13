#include "SteerComponent.h"

SteerComponent::SteerComponent(float turnRate, int updateOrder) : Component(updateOrder), turnRate(turnRate)
{
	componentType = MOVE;
}

void SteerComponent::update(const float& deltaTime)
{
	vec4 fwd = vec4(owningGameObject->getFowardDirection(), 0.0f);

	vec3 newFwd = fwd.xyz;

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT)) {
		//cout << "right" << endl;
		newFwd = (glm::rotate(glm::radians(-turnRate) * deltaTime, UNIT_Y_V3) * fwd).xyz;

	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT)) {
		//cout << "left" << endl;
		newFwd = (glm::rotate(glm::radians(turnRate) * deltaTime, UNIT_Y_V3) * fwd).xyz;

	}

	owningGameObject->rotateTo(newFwd);
}
