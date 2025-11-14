#include "MakeVisibleComponent.h"


MakeVisibleComponent::MakeVisibleComponent(int controlKey, int updateOrder)
	: Component(updateOrder), controlKey(controlKey)
{

}

void MakeVisibleComponent::initialize()
{
	owningGameObject->setState(ACTIVE);

}
void MakeVisibleComponent::processInput()
{
	if (glfwGetKey(glfwGetCurrentContext(), controlKey) && KeyDown == false) {

		owningGameObject->setState(owningGameObject->getState() == ACTIVE ? PAUSED : ACTIVE);

		KeyDown = true;

	}
	else if (!glfwGetKey(glfwGetCurrentContext(), controlKey)) {
		KeyDown = false;
	}


}
