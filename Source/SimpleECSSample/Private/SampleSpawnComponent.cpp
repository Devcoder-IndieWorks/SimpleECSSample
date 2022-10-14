#include "SampleSpawnComponent.h"
#include <EngineUtils.h>

USampleSpawnComponent::USampleSpawnComponent( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USampleSpawnComponent::BeginPlay()
{
    Super::BeginPlay();

    for ( int32 i = 0; i < PoolSize; ++i ) {
        for ( int32 j = 0; j < PoolSize; ++j ) {
            GetWorld()->SpawnActor<AActor>( SampleMoverClass, 100.0f * FVector(i - PoolSize/2.0f, j - PoolSize/2.0f, 0.0f), FRotator::ZeroRotator );
            GetWorld()->SpawnActor<AActor>( SampleDoorClass, 100.0f * FVector(i - PoolSize/2.0f, j - PoolSize/2.0f, 0.0f), FRotator::ZeroRotator );
        }
    }
}
