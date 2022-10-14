#include "SampleDoorActor.h"
#include "SampleMoverActor.h"
#include <EngineUtils.h>

ASampleDoorActor::ASampleDoorActor( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
}

void ASampleDoorActor::Tick( float InDeltaTime )
{
    Super::Tick( InDeltaTime );

    if ( !EnableTick )
        return;

    auto location = GetActorLocation();
    IsOpen = false;

    for ( const auto mover : TActorRange<ASampleMoverActor>( GetWorld() ) ) {
        auto moverLocation = mover->GetActorLocation();
        if ( FVector::Distance( location, moverLocation ) <= 100.0f ) {
            IsOpen = true;
            return;
        }
    }
}
