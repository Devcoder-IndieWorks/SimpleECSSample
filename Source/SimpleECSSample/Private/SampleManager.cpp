#include "SampleManager.h"
#include "SampleTestSystem.h"

ASampleManager::ASampleManager( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
}

void ASampleManager::SetupSystems( TArray<TSharedPtr<FSECSSystemBase>>& InSystem )
{
    TSharedPtr<FSECSSystemBase> system = MakeShared<FSampleTestSystem>();
    InSystem.Add( system );
}
