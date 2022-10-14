// Copyright Devcoder.
#pragma once
#include <GameFramework/Actor.h>
#include "SampleDoorActor.generated.h"

UCLASS() 
class ASampleDoorActor : public AActor
{
    GENERATED_UCLASS_BODY()
public:
    void Tick( float InDeltaTime ) override;

public:
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category=ECS )
    bool IsOpen;

private:
    UPROPERTY( EditAnywhere, Category=ECS )
    bool EnableTick;
};
