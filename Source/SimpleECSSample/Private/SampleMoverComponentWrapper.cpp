#include "SampleMoverComponentWrapper.h"
#include <SECSRegistry.h>

USampleMoverComponentWrapper::USampleMoverComponentWrapper( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USampleMoverComponentWrapper::AddToEntity( FSECSRegistry* InRegistry, int32 InEntityID )
{
    if ( ensure( InRegistry != nullptr ) )
        InRegistry->AddComponent( InEntityID, FSampleMoverComponent() );
}
