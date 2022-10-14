#include "SECSRegistry.h"
#include "SimpleECSPCH.h"

FSECSArcheType::~FSECSArcheType()
{
    for ( auto& pair : TypeIDToPool )
        delete pair.Value;
}

const TArray<int32>& FSECSArcheType::GetEntityList()
{
    return EntityIDs;
}

const bool FSECSArcheType::IsEmpty() const
{
    return EntityIDs.Num() == 0;
}

void FSECSArcheType::MoveToSmaller( FSECSArcheType* InTo, int32 InEntityID )
{
    auto indexToMove = EntityIDToIndex[ InEntityID ];
    RemoveEntity( indexToMove, InEntityID );
    InTo->AddEntity( InEntityID );

    for ( auto& pair : TypeIDToPool ) {
        auto typeID = pair.Key;
        auto from = pair.Value;
        from->MoveTo( indexToMove, InTo->TypeIDToPool[ typeID ] );
    }
}

void FSECSArcheType::AddEntity( int32 InEntityID )
{
    auto newIndex = EntityIDs.Add( InEntityID );
    EntityIDToIndex.Add( InEntityID, newIndex );
}

void FSECSArcheType::RemoveEntity( int32 InIndexToMove, int32 InEntityID )
{
    auto lastEntityID = EntityIDs[ EntityIDs.Num() - 1 ];
    EntityIDs[ InIndexToMove ] = lastEntityID;
    EntityIDToIndex[ lastEntityID ] = InIndexToMove;
    EntityIDs.RemoveAt( EntityIDs.Num() - 1 );
    EntityIDToIndex.Remove( InEntityID );
}

void FSECSArcheType::Log( const TCHAR* InMessage ) const
{
    UE_LOG( LogTemp, Log, TEXT( "#### [%s] ####" ), InMessage );
}

//-----------------------------------------------------------------------------

FSECSRegistry::~FSECSRegistry()
{
    for ( auto archeType : ArcheTypes )
        delete archeType;
}

int32 FSECSRegistry::CreateEntity()
{
    return NextEntity++;
}

FSECSArcheType* FSECSRegistry::GetExactArcheType( TSet<FString> InKey )
{
    for ( auto archeType : ArcheTypes ) {
        if ( archeType->TypeIDs.Difference( InKey ).Num() == 0 && InKey.Difference( archeType->TypeIDs ).Num() == 0 )
            return archeType;
    }

    return nullptr;
}
