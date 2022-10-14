// Copyright Devcoder.
#pragma once
#include <SECSManager.h>
#include "SampleManager.generated.h"

UCLASS() 
class ASampleManager : public ASECSManager
{
    GENERATED_UCLASS_BODY()
protected:
    void SetupSystems( TArray<TSharedPtr<class FSECSSystemBase>>& InSystem ) override;
};
