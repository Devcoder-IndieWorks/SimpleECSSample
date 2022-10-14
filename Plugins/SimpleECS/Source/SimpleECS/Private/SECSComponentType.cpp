#include "SECSComponentType.h"
#include "SimpleECSPCH.h"
#include "SECSManager.h"
#include "SECSRegistry.h"
#include "SECSComponentWrapper.h"

FSECSActorReference::FSECSActorReference( AActor* InOwner )
{
    Owner = InOwner;
}

FSECSActorTransform::FSECSActorTransform( FTransform InTransform )
    : Transform( InTransform )
{
}

//-----------------------------------------------------------------------------

USECSLinker::USECSLinker()
{
    TransformSync = ESECSTransformSyncType::TS_BothWays;
    EntityID = -1;

    PrimaryComponentTick.bCanEverTick = false;
}

void USECSLinker::BeginPlay()
{
    Super::BeginPlay();

    auto world = GetOwner()->GetWorld();
    if ( ensure( world != nullptr ) ) {
        for ( TActorIterator<ASECSManager> iter( world ); iter; ++iter ) {
            if ( IsValid( *iter ) ) {
                ECSManager = *iter;
                break;
            }
        }

        if ( !ECSManager.IsValid() )
            ECSManager = world->SpawnActor<ASECSManager>();

        if ( ECSManager.IsValid() ) {
            auto registry = ECSManager->GetRegistry();
            if ( ensure( registry != nullptr ) )
                EntityID = registry->CreateEntity();
        }
    }

    RegisterWithECS();
}

void USECSLinker::RegisterWithECS()
{
    if ( ECSManager.IsValid() ) {
        auto registry = ECSManager->GetRegistry();
        registry->AddComponent( EntityID, FSECSActorReference( GetOwner() ) );

        if ( TransformSync == ESECSTransformSyncType::TS_ActorToEcs || TransformSync == ESECSTransformSyncType::TS_BothWays )
            registry->AddComponent( EntityID, FSECSCopyTransformToECS() );

        if ( TransformSync == ESECSTransformSyncType::TS_EcsToActor || TransformSync == ESECSTransformSyncType::TS_BothWays )
            registry->AddComponent( EntityID, FSECSCopyTransformToActor() );

        for ( auto comp : GetOwner()->GetComponents() ) {
            auto compWrapper = Cast<ISECSComponentWrapper>( comp );
            if ( compWrapper != nullptr )
                compWrapper->AddToEntity( registry, EntityID );
        }
    }
}
