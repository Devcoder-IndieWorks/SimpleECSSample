// Copyright Devcoder.
#pragma once
#include <GameFramework/Actor.h>
#include "SECSManager.generated.h"

UCLASS() 
class SIMPLEECS_API ASECSManager : public AActor
{
    GENERATED_UCLASS_BODY()
public:
    void BeginPlay() override;
    void Tick( float InDeltaTime ) override;

    class FSECSRegistry* GetRegistry() const;

protected:
    virtual void SetupSystems( TArray<TSharedPtr<class FSECSSystemBase>>& InSystems );

protected:
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="SimpleECSManager|Settings", meta=(AllowPrivateAccess="true") )
    bool EnableTick;

private:
    TSharedPtr<class FSECSRegistry> Registry;
    TArray<TSharedPtr<class FSECSSystemBase>> Systems;
};
