// Copyright Devcoder.
#pragma once
#include <SECSComponentWrapper.h>
#include "SampleMoverComponentWrapper.generated.h"

USTRUCT( BlueprintType ) 
struct FSampleMoverComponent
{
    GENERATED_BODY()
    FSampleMoverComponent() = default;
};

//-----------------------------------------------------------------------------

UCLASS( ClassGroup=(ECS), meta=(BlueprintSpawnableComponent) )
class USampleMoverComponentWrapper : 
    public UActorComponent, 
    public ISECSComponentWrapper
{
    GENERATED_UCLASS_BODY()
protected:
    void AddToEntity( class FSECSRegistry* InRegistry, int32 InEntityID ) final;
};
