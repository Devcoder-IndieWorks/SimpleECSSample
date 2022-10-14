#include "SampleTestSystem.h"
#include "SampleMoverActor.h"
#include "SampleDoorActor.h"
#include "SampleMoverComponentWrapper.h"
#include "SampleDoorComponentWrapper.h"
#include <SECSComponentType.h>
#include <SECSRegistry.h>
#include <SECSQuery.h>

void FSampleTestSystem::Update( float InDeltaTime, FSECSRegistry* InRegistry )
{
    // FSECSActorTransform 컴포넌트를 가지고 있는 Entities에 FSECSActorTransform 컴포넌트를 추가 함.
    TSECSQuery<TSECSExclude<FSECSActorTransform>, FSECSCopyTransformToECS> queryAddTransform;
    queryAddTransform.Each( *InRegistry, [InRegistry]( int32 InEntityID, FSECSCopyTransformToECS& ) {
        InRegistry->AddComponent( InEntityID, FSECSActorTransform() );
        return true;
    } );

    // FSECSActorReference, FSECSActorTransform 컴포넌트를 가지고 있는 Entities에서 Actor의 Transform 정보를 복사 함.
    TSECSQuery<FSECSActorReference, FSECSActorTransform> queryCopyTransform;
    queryCopyTransform.Each( *InRegistry, []( int32, const FSECSActorReference& InActor, FSECSActorTransform& InTrans ){
        const auto& actorTransform = InActor.Owner->GetActorTransform();
        InTrans.Transform = actorTransform;
        return true;
    } );

    // FSampleMoverComponent, FSECSActorTransform 컴포넌트를 가지고 있는 Entities에 랜덤하게 계산된 Transform으로 변경 함.
    TSECSQuery<FSampleMoverComponent, FSECSActorTransform> queryMoveMover;
    queryMoveMover.Each( *InRegistry, [InDeltaTime]( int32, FSampleMoverComponent&, FSECSActorTransform& InTrans ){
        const auto& location = InTrans.Transform.GetLocation();
        auto newPos = location + 1000.0f * InDeltaTime * 
            FVector( FMath::RandRange( -1.0f, 1.0f ), 
                FMath::RandRange( -1.0f, 1.0f ), 
                FMath::RandRange( -1.0f, 1.0f ) );

        InTrans.Transform.SetLocation( newPos );
        return true;
    } );

    // FSampleDoorComponent, FSECSActorTransform 컴포넌트를 가지고 있는 Entities에 door open 상태를 체크 함.
    TSECSQuery<FSampleDoorComponent, FSECSActorTransform> queryCheckDoorOpen;
    queryCheckDoorOpen.Each( *InRegistry, [InRegistry]( int32, FSampleDoorComponent& InDoorComp, FSECSActorTransform& InDoorTrans ){
        InDoorComp.IsOpen = false;
        auto doorLocation = InDoorTrans.Transform.GetLocation();
        auto doorCompPtr = &InDoorComp;

        TSECSQuery<FSampleMoverComponent, FSECSActorTransform> queryMovers;
        queryMovers.Each( *InRegistry, [doorLocation, doorCompPtr]( int32, FSampleMoverComponent&, FSECSActorTransform& InMoverTrans ){
            auto moverLocation = InMoverTrans.Transform.GetLocation();
            if ( FVector::Distance( doorLocation, moverLocation ) <= 100.0f ) {
                doorCompPtr->IsOpen = true;
                return false;
            }
            return true;
        } );

        return true;
    } );

    // FSampleDoorComponent의 IsOpen 상태를 ASampleDoorActor의 IsOpen에 적용 함.
    TSECSQuery<FSampleDoorComponent, FSECSActorReference> queryCopyDoorCompToDoor;
    queryCopyDoorCompToDoor.Each( *InRegistry, []( int32 InEntityID, FSampleDoorComponent& InDoorComp, FSECSActorReference& InActor ){
        auto door = Cast<ASampleDoorActor>( InActor.Owner );
        if ( door != nullptr )
            door->IsOpen = InDoorComp.IsOpen;
        return true;
    } );

    // FSECSActorTransform에 저장된 Transform 정보들을 Actor들의 Transform에 적용 함.
    TSECSQuery<FSECSCopyTransformToActor, FSECSActorReference, FSECSActorTransform> queryCopyTransformToActor;
    queryCopyTransformToActor.Each( *InRegistry, []( int32, FSECSCopyTransformToActor&, FSECSActorReference& InActor, FSECSActorTransform& InTrans ){
        InActor.Owner->SetActorTransform( InTrans.Transform );
        return true;
    } );
}
