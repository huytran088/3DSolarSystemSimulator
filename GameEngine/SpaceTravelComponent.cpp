#include "SpaceTravelComponent.h"

#define VERBOSE false


SpaceTravelComponent::SpaceTravelComponent(std::vector<GameObject*> planets, vec3 velocity)
	: velocity(velocity), speed(glm::length(velocity)), planets(planets),
	targetPlanetIndex(static_cast<int>(planets.size()) - 1)
{
	componentType = MOVE;
	targetPlanetIndex = 0;
}

void SpaceTravelComponent::update(const float& deltaTime)
{
	float radius = 6.0;

	if (isMoving) {
		// Check if next planet has been reached
		checkIfPlanetReached(deltaTime, radius);

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

		// Update the position based on the newDirection
		position = position + newDirection * speed * deltaTime;

		// Set the position of the GameObject
		owningGameObject->setPosition(position, WORLD);
	}
}

vec3 SpaceTravelComponent::getDirectionToNextPlanet() {
	return glm::normalize((planets[targetPlanetIndex]->getPosition() - owningGameObject->getPosition(WORLD)));
}

GLfloat SpaceTravelComponent::distanceToTargetPlanet() {
	GLfloat dist = glm::distance(planets[targetPlanetIndex]->getPosition(), owningGameObject->getPosition(WORLD));

	if (VERBOSE) cout << dist << endl;

	return dist;
}

void SpaceTravelComponent::checkIfPlanetReached(const float& deltaTime, const float& radius)
{
	if (distanceToTargetPlanet() < (speed * deltaTime + radius)) {
		switch (targetPlanetIndex) {
		case 0:	// Sun
			if (VERBOSE) cout << "Sun reached" << endl;
			isMoving = false;
			speed = 0.0f;
			break;
		case 1:	// Earth
			if (VERBOSE) cout << "Earth reached" << endl;
			speed = 3.0f;
			break;
		case 2:	// Mars
			if (VERBOSE) cout << "Mars reached" << endl;
			speed = 5.0f;
			break;
		case 3:	// Venus
			if (VERBOSE) cout << "Venus reached" << endl;
			speed = 6.5f;
			break;
		default:
			speed = 0.0f;
		}
	}
	else {
		speed = 7.0f;
	}
}

void SpaceTravelComponent::processInput()
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_0)) {
		// Go to the sun
		isMoving = true;
		targetPlanetIndex = 0;
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_1)) {
		// Go to Earth
		isMoving = true;
		targetPlanetIndex = 1;
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_2)) {
		// Go to Mars
		isMoving = true;
		targetPlanetIndex = 2;
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_3)) {
		// Go to venus
		isMoving = true;
		targetPlanetIndex = 3;
	}
}
