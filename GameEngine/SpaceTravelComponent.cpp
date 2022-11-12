#include "SpaceTravelComponent.h"

#define VERBOSE true


SpaceTravelComponent::SpaceTravelComponent(std::vector<GameObject*> planets, vec3 velocity)
	: velocity(velocity), speed(glm::length(velocity)), planets(planets),
	targetPlanetIndex(static_cast<int>(planets.size()) - 1)
{
	targetPlanetIndex = 0;
}

void SpaceTravelComponent::update(const float& deltaTime)
{
	float radius = 1.0;

	// Get current facing directions
	vec3 current = owningGameObject->getFowardDirection(WORLD);

	// Get direction to the next waypoint
	vec3 desiredDirection = getDirectionToNextPlanet();

	// Incrementally update current direction to face the next waypoint
	vec3 newDirection = glm::lerp(current, desiredDirection, deltaTime);

	// Rotate to face the new direction
	owningGameObject->rotateTo(newDirection, WORLD);

	// Get the current position
	vec3 position = owningGameObject->getPosition(WORLD);

	// Check if next waypoint has been reached
	if (distanceToTargetPlanet() >= (speed * deltaTime + radius)) {
		// Update the position based on the newDirection
		position = position + newDirection * speed * deltaTime;
	}
	else {

	}

	// Set the position of the GameObject
	owningGameObject->setPosition(position, WORLD);
}

vec3 SpaceTravelComponent::getDirectionToNextPlanet() {
	return glm::normalize((planets[targetPlanetIndex]->getPosition() - owningGameObject->getPosition(WORLD)));
}

GLfloat SpaceTravelComponent::distanceToTargetPlanet() {
	GLfloat dist = glm::distance(planets[targetPlanetIndex]->getPosition(), owningGameObject->getPosition(WORLD));

	if (VERBOSE) cout << dist << endl;

	return dist;
}

void SpaceTravelComponent::processInput()
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_0)) {
		// Go to the sun
		targetPlanetIndex = 1;
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_1)) {
		// Go to Earth
		targetPlanetIndex = 2;
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_2)) {
		// Go to Mars
		targetPlanetIndex = 3;
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_3)) {
		// Go to venus
		targetPlanetIndex = 4;
	}
}
