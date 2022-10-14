// Copyright Devcoder.
#pragma once
#include <CoreMinimal.h>
#include <Components/ActorComponent.h>
#include "SECSComponentType.generated.h"

USTRUCT( BlueprintType ) 
struct SIMPLEECS_API FSECSActorReference
{
    GENERATED_BODY()
    FSECSActorReference( class AActor* InOwner = nullptr );

    TWeakObjectPtr<class AActor> Owner;
};

USTRUCT( BlueprintType ) 
struct SIMPLEECS_API FSECSActorTransform
{
    GENERATED_BODY()
    FSECSActorTransform() = default;
    FSECSActorTransform( FTransform InTransform );

    UPROPERTY( EditAnywhere, Category=ECS )
    FTransform Transform;
};

USTRUCT( BlueprintType ) 
struct SIMPLEECS_API FSECSCopyTransformToECS
{
    GENERATED_BODY()
};

USTRUCT( BlueprintType ) 
struct SIMPLEECS_API FSECSCopyTransformToActor
{
    GENERATED_BODY()
};

//-----------------------------------------------------------------------------

UENUM( BlueprintType ) 
enum class ESECSTransformSyncType : uint8
{
    TS_EcsToActor,
    TS_ActorToEcs,
    TS_BothWays,
    TS_Disabled
};

UCLASS( ClassGroup=(ECS), meta=(BlueprintSpawnableComponent) ) 
class SIMPLEECS_API USECSLinker : public UActorComponent
{
    GENERATED_BODY()
public:
    USECSLinker();

protected:
    virtual void BeginPlay() override;
    void RegisterWithECS();

protected:
    UPROPERTY( EditAnywhere, Category=ECS )
    ESECSTransformSyncType TransformSync;

private:
    int32 EntityID;
    TWeakObjectPtr<class ASECSManager> ECSManager;
};
