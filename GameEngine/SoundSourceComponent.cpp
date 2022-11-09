#include "SoundSourceComponent.h"

SoundSourceComponent::SoundSourceComponent(std::string soundFileName, float refDistance,
	float rollOffFactor, float maxDistance, int updateOrder) : SoundBaseComponent(updateOrder),
	refDistance(refDistance), rollOffFactor(rollOffFactor), maxDistance(maxDistance)
{
	// Load the sound file into a buffer.
	buffer = alutCreateBufferFromFile(soundFileName.c_str());
	SoundEngine::check_alut_errors();

	// Create a source
	alGenSources((ALuint)1, &source);
	SoundEngine::check_al_errors();
	// Associate the buffer with the source
	alSourcei(source, AL_BUFFER, buffer);
	// Set the reference distance
	setReferenceDistance(this->refDistance);
	// Set the roll off factor
	setRollOffFactor(this->rollOffFactor);
	// Set the max distance
	setMaxDistance(this->maxDistance);
	SoundEngine::check_al_errors();
	// Play the source of preInitPlay is enabled
	if (preInitPlay) {
		play();
	}
}

SoundSourceComponent::~SoundSourceComponent()
{
	// Unbind the buffer from the source
	alSourcei(source, AL_BUFFER, NULL);
	// Delete the buffer
	alDeleteBuffers(1, &buffer);
	// Delete the source
	alDeleteSources(1, &source);
}

void SoundSourceComponent::update(const float& deltaTime)
{
	SoundBaseComponent::update(deltaTime);
	// Set source position
	alSource3f(source, AL_POSITION, soundPosition.x, soundPosition.y, soundPosition.z);
	// Set source velocity
	alSource3f(source, AL_VELOCITY, soundVelocity.x, soundVelocity.y, soundVelocity.z);
	// Set source direction
	alSource3f(source, AL_DIRECTION, soundForward.x, soundForward.y, soundForward.z);
	// Set source orientation
	float orientation[6];
	orientation[0] = this->soundForward.x; //forward vector x value
	orientation[1] = this->soundForward.y; //forward vector y value
	orientation[2] = this->soundForward.z; //forward vector z value
	orientation[3] = this->soundUp.x; //up vector x value
	orientation[4] = this->soundUp.y; //up vector y value
	orientation[5] = this->soundUp.z; //up vector z value
	alSourcefv(source, AL_ORIENTATION, orientation);
	SoundEngine::check_al_errors();
}

void SoundSourceComponent::play()
{
	// Play the source
	alSourcePlay(source);
}

void SoundSourceComponent::stop()
{
	// Stop playing the source
	alSourceStop(source);
}

void SoundSourceComponent::pause()
{
	// Pause the source
	if (this->isPlaying()) {
		alSourcePause(source);
	}
}

void SoundSourceComponent::continuePlaying()
{
	// Continue playing the paused source
	if (this->isPaused()) {
		alSourcePlay(source);
	}
}

bool SoundSourceComponent::isPlaying()
{
	ALint isPlaying;
	alGetSourcei(this->source, AL_SOURCE_STATE, &isPlaying);
	return isPlaying == AL_PLAYING;
}

void SoundSourceComponent::setGain(float volume)
{
	// Set the gain value for the source
	alSourcef(this->source, AL_GAIN, volume);
}

float SoundSourceComponent::getGain()
{
	// Get the gain value for the source
	float gain;
	alGetSourcef(this->source, AL_GAIN, &gain);
	return gain;
}

bool SoundSourceComponent::isPaused()
{
	ALint isPaused;
	alGetSourcei(this->source, AL_SOURCE_STATE, &isPaused);
	return isPaused == AL_PAUSED;
}

void SoundSourceComponent::setLooping(bool loopingOn)
{
	alSourcei(this->source, AL_LOOPING, loopingOn);
}

void SoundSourceComponent::setReferenceDistance(float refDistance)
{
	this->refDistance = refDistance;
	alSourcef(this->source, AL_REFERENCE_DISTANCE, this->refDistance);
}

void SoundSourceComponent::initialize()
{
	SoundBaseComponent::initialize();
	// Set the initial source position
	alSource3f(source, AL_POSITION, lastPosition.x, lastPosition.y, lastPosition.z);
}

void SoundSourceComponent::setRollOffFactor(float rollOffFactor)
{
	this->rollOffFactor = rollOffFactor;
	alSourcef(this->source, AL_ROLLOFF_FACTOR, this->rollOffFactor);
}

void SoundSourceComponent::setMaxDistance(float maxDistance)
{
	this->maxDistance = maxDistance;
	alSourcef(this->source, AL_MAX_DISTANCE, this->maxDistance);
}
