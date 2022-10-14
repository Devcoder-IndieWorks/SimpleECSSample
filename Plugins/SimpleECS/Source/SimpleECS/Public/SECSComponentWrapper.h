// Copyright Devcoder.
#pragma once
#include <CoreMinimal.h>
#include <UObject/Interface.h>
#include "SECSComponentWrapper.generated.h"

UINTERFACE() 
class SIMPLEECS_API USECSComponentWrapper : public UInterface
{
    GENERATED_BODY()
};

class SIMPLEECS_API ISECSComponentWrapper
{
    GENERATED_BODY()
public:
    virtual void AddToEntity( class FSECSRegistry* InRegistry, int32 InEntityID ) = 0;
};
