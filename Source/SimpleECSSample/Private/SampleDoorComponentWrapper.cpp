#include "SampleDoorComponentWrapper.h"
#include <SECSRegistry.h>

USampleDoorComponentWrapper::USampleDoorComponentWrapper( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USampleDoorComponentWrapper::AddToEntity( FSECSRegistry* InRegistry, int32 InEntityID )
{
    if ( ensure( InRegistry != nullptr ) )
        InRegistry->AddComponent( InEntityID, FSampleDoorComponent() );
}
