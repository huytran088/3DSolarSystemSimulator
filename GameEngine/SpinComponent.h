#pragma once
#include "Component.h"
class SpinComponent :
    public Component
{
public:
    SpinComponent(float rotRateDegrees = 5.0f, vec3 axis = UNIT_Y_V3, int updateOrder = 100);

    virtual void update(const float& deltaTime) override;
protected:
    // Axis of rotation
    vec3 axis;
    // Rotation rate in radians per second
    float rotRate;
};

