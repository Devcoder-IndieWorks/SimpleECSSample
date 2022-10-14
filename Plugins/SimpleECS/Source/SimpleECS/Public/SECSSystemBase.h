// Copyright Devcoder.
#pragma once
#include <CoreMinimal.h>

class SIMPLEECS_API FSECSSystemBase
{
public:
    virtual ~FSECSSystemBase() = default;
    virtual void Update( float InDeltaTime, class FSECSRegistry* InRegistry ) = 0;
};
