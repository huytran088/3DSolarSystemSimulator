#pragma once
#include "Component.h"
class SpaceTravelComponent :
    public Component
{
public:
	/**
	 * @fn	SpaceTravelComponent(std::vector< glm::vec3> planetLocs, vec3 velocity = vec3(20, 0, 0));
	 *
	 * @brief	Constructor
	 *
	 * @param	planetLocs	The planets in solar system.
	 * @param	velocity 	(Optional) The velocity.
	 */
	SpaceTravelComponent(std::vector<GameObject*> planets, vec3 velocity = vec3(20, 0, 0));

	virtual void update(const float& deltaTime) override;

	virtual void processInput() override;

	float currentRoll = 0;

protected:

	vec3 getDirectionToNextPlanet();
	GLfloat distanceToTargetPlanet();

	/**
	 * @fn	void checkIfPlanetReached(const float& deltaTime, const float& radius);
	 * 
	 * @brief	A helper method to check whether the ship has reached the planet, and adjust the
	 *			speed accordingly.
	 * 
	 * @param	deltaTime	The time in seconds since the component was
	 * 						last updated.
	 * @param	radius	The radius of the range to check
	 */
	void checkIfPlanetReached(const float& deltaTime, const float& radius);

	std::vector<GameObject*> planets;

	vec3 velocity;
	float speed;

	int targetPlanetIndex = 0;
	bool isMoving = false;

};

