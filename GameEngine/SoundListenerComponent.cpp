#include "SoundListenerComponent.h"

SoundListenerComponent::SoundListenerComponent(int updateOrder) : SoundBaseComponent(updateOrder)
{
}

void SoundListenerComponent::initialize()
{
	SoundBaseComponent::initialize();
	// Set the initial listener position
	alListener3f(AL_POSITION, lastPosition.x, lastPosition.y, lastPosition.z);
}

void SoundListenerComponent::update(const float& deltaTime)
{
	SoundBaseComponent::update(deltaTime);
	// Set current listener position
	alListener3f(AL_POSITION, soundPosition.x, soundPosition.y, soundPosition.z);
	// Set current listener velocity
	alListener3f(AL_VELOCITY, soundVelocity.x, soundVelocity.y, soundVelocity.z);
	float orientation[6];
	orientation[0] = this->soundForward.x; //forward vector x value
	orientation[1] = this->soundForward.y; //forward vector y value
	orientation[2] = this->soundForward.z; //forward vector z value
	orientation[3] = this->soundUp.x; //up vector x value
	orientation[4] = this->soundUp.y; //up vector y value
	orientation[5] = this->soundUp.z; //up vector z value
	// Set current listener orientation
	alListenerfv(AL_ORIENTATION, orientation);
	SoundEngine::check_al_errors();
}
