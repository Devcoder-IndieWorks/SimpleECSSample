// Copyright Devcoder.
#pragma once
#include <SECSSystemBase.h>

class FSampleTestSystem : public FSECSSystemBase
{
public:
    void Update( float InDeltaTime, class FSECSRegistry* InRegistry ) override;
};
