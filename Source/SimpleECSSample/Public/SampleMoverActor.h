// Copyright Devcoder.
#pragma once
#include <GameFramework/Actor.h>
#include "SampleMoverActor.generated.h"

UCLASS() 
class ASampleMoverActor : public AActor
{
    GENERATED_UCLASS_BODY()
public:
    void Tick( float InDeltaTime ) override;

private:
    UPROPERTY( EditAnywhere, Category=ECS )
    bool EnableTick;
};
