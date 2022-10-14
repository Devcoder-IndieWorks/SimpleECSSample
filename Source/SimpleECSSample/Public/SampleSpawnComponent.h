// Copyright Devcoder.
#pragma once
#include <Components/ActorComponent.h>
#include "SampleSpawnComponent.generated.h"

UCLASS( ClassGroup=(ECSSample), meta=(BlueprintSpawnableComponent) ) 
class USampleSpawnComponent : public UActorComponent
{
    GENERATED_UCLASS_BODY()
protected:
    void BeginPlay() override;

private:
    UPROPERTY( EditAnywhere, Category="Spawner|Settings" )
    TSubclassOf<AActor> SampleMoverClass;
    UPROPERTY( EditAnywhere, Category="Spawner|Settings" )
    TSubclassOf<AActor> SampleDoorClass;
    UPROPERTY( EditAnywhere, Category="Spawner|Settings" )
    int32 PoolSize;
};
