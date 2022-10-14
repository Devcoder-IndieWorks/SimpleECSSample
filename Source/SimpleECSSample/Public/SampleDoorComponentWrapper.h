// Copyright Devcoder.
#pragma once
#include <SECSComponentWrapper.h>
#include "SampleDoorComponentWrapper.generated.h"

USTRUCT( BlueprintType ) 
struct FSampleDoorComponent
{
    GENERATED_BODY()
    FSampleDoorComponent() { IsOpen = false; }

    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    bool IsOpen;
};

//-----------------------------------------------------------------------------

UCLASS( ClassGroup=(ECS), meta=(BlueprintSpawnableComponent) ) 
class USampleDoorComponentWrapper : 
    public UActorComponent, 
    public ISECSComponentWrapper
{
    GENERATED_UCLASS_BODY()
protected:
    void AddToEntity( class FSECSRegistry* InRegistry, int32 InEntityID ) final;
};
