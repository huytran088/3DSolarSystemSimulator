#include "SoundSourceComponent.h"

SoundSourceComponent::SoundSourceComponent(std::string soundFileName, float refDistance,
	float rollOffFactor, float maxDistance, int updateOrder)
{
	// Load the sound file into a buffer.
	buffer = alutCreateBufferFromFile(soundFileName.c_str());
	SoundEngine::check_alut_errors();

	// Create a source
	alGenSources((ALuint)1, &source);
	SoundEngine::check_al_errors();
	// Associate the buffer with the source
	alSourcei(source, AL_BUFFER, buffer);
	SoundEngine::check_al_errors();
}

SoundSourceComponent::~SoundSourceComponent()
{
}

void SoundSourceComponent::update(const float& deltaTime)
{
	SoundBaseComponent::update(deltaTime);
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
	alSourcePause(source);
}

void SoundSourceComponent::continuePlaying()
{
	// Continue playing the source
	alSourcePlay(source);
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
	alSourcef(this->source, AL_REFERENCE_DISTANCE, refDistance);
}

void SoundSourceComponent::initialize()
{
	// Set source position
	alSource3f(source, AL_POSITION, soundPosition.x, soundPosition.y, soundPosition.z);
	// Set source velocity
	alSource3f(source, AL_VELOCITY, soundVelocity.x, soundVelocity.y, soundVelocity.z);
	// Set source direction
	alSource3f(source, AL_DIRECTION, soundForward.x, soundForward.y, soundForward.z);
}

void SoundSourceComponent::setRollOffFactor(float rollOffFactor)
{
	alSourcef(this->source, AL_ROLLOFF_FACTOR, rollOffFactor);
}

void SoundSourceComponent::setMaxDistance(float maxDistance)
{
	alSourcef(this->source, AL_MAX_DISTANCE, maxDistance);
}
