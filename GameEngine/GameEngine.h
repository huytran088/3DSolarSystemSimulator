#pragma once

// Base Classes
#include "GameObject.h"

// Shader program building
#include "BuildShaderProgram.h"
#include "Texture.h"

// Shared Uniform Blocks
#include "SharedMaterials.h"
#include "SharedTransformations.h"
#include "SharedLighting.h"

// Meshes
#include "BoxMeshComponent.h"
#include "ModelMeshComponent.h"
#include "SphereMeshComponent.h"
#include "CylinderMeshCompnent.h"

// Movement
#include "ArrowRotateComponent.h"
#include "MakeVisableComponent.h"
#include "TranslateComponent.h"
#include "ContinuousRotateComponent.h"
#include "SteerComponent.h"
#include "WaypointComponent.h"
#include "SteeringComponent.h"
#include "SpinComponent.h"
#include "SpaceTravelComponent.h"

// Lighting
#include "PositionalLightComponent.h"
#include "DirectionalLightComponent.h"
#include "SpotLightComponent.h"

// Camera
#include "CameraComponent.h"

// Sound
#include "SoundEngine.h"
#include "SoundListenerComponent.h"
#include "SoundSourceComponent.h"

