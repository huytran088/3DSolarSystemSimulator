#pragma once
#include "Component.h"
class MakeVisibleComponent : public Component
{
public:
    MakeVisibleComponent(int controlKey, int updateOrder = 100);

    virtual void initialize() override;

    virtual void processInput() override;

protected:
    int controlKey;

    bool KeyDown = false;
};

