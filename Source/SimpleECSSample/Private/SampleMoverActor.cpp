#include "SampleMoverActor.h"
#include <Math/UnrealMathUtility.h>

ASampleMoverActor::ASampleMoverActor( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASampleMoverActor::Tick( float InDeltaTime )
{
    Super::Tick( InDeltaTime );

    if ( !EnableTick )
        return;

    auto location = GetActorLocation();
    auto newLocation = location + 1000.0f * InDeltaTime * 
        FVector( FMath::RandRange( -1.0f, 1.0f ), 
            FMath::RandRange( -1.0f, 1.0f ),
            FMath::RandRange( -1.0f, 1.0f ) );

    SetActorLocation( newLocation );
}
