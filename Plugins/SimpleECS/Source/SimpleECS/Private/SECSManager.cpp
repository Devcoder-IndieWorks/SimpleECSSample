#include "SECSManager.h"
#include "SimpleECSPCH.h"
#include "SECSSystemBase.h"
#include "SECSRegistry.h"

ASECSManager::ASECSManager( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    EnableTick = false;
    Registry = MakeShared<FSECSRegistry>();

    PrimaryActorTick.bCanEverTick = true;
}

void ASECSManager::BeginPlay()
{
    Super::BeginPlay();
    SetupSystems( Systems );
}

void ASECSManager::SetupSystems( TArray<TSharedPtr<FSECSSystemBase>>& InSystems )
{
}

void ASECSManager::Tick( float InDeltaTime )
{
    Super::Tick( InDeltaTime );

    if ( !EnableTick )
        return;

    for ( auto& system : Systems )
        system->Update( InDeltaTime, Registry.Get() );
}

FSECSRegistry* ASECSManager::GetRegistry() const
{
    return Registry.Get();
}
