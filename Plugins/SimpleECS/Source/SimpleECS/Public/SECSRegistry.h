// Copyright Devcoder.
#pragma once
#include "SECSComponentPool.h"

class SIMPLEECS_API FSECSArcheType
{
public:
    ~FSECSArcheType();

    const TArray<int32>& GetEntityList();
    const bool IsEmpty() const;

    void MoveToSmaller( FSECSArcheType* InTo, int32 InEntityID );

public:
    template< typename TComp > 
    TSECSComponentPool<TComp>* GetPool() const
    {
        auto typeToFind = SECS_TypeToTypeID<TComp>();
        check( TypeIDToPool.Contains( typeToFind ) );
        auto pool = static_cast<TSECSComponentPool<TComp>*>( TypeIDToPool[ typeToFind ]->Pool );
        if ( EntityIDs.Num() != pool->Components.Num() )
            Log( TEXT( "EntityIDs != Pool->Components" ) );
        return pool;
    }

    template< typename TComp > 
    TComp* GetComponent( int32 InEntityID ) const
    {
        auto index = EntityIDToIndex[ InEntityID ];
        auto pool = GetPool<TComp>();
        return &(pool->Components[ index ]);
    }

    template< typename... TComps > 
    static FSECSArcheType* Create()
    {
        auto newArcheType = new FSECSArcheType();
        newArcheType->TypeIDToPool = { {SECS_TypeToTypeID<TComps>(), FSECSPoolData::Create<TComps>()}... };
        newArcheType->TypeIDs = { SECS_TypeToTypeID<TComps>()... };
        return newArcheType;
    }

    template< typename TNewComp > 
    static FSECSArcheType* CreateExtension( FSECSArcheType* InOriginal )
    {
        auto newArcheType = new FSECSArcheType();
        for ( const auto& pair : InOriginal->TypeIDToPool ) {
            auto typeID = pair.Key;
            auto data = InOriginal->TypeIDToPool[ typeID ];
            auto newData = data->CreateEmptyClone();
            newArcheType->TypeIDToPool.Add( typeID, newData );
        }

        auto newCompTypeID = SECS_TypeToTypeID<TNewComp>();
        newArcheType->TypeIDToPool.Add( newCompTypeID, FSECSPoolData::Create<TNewComp>() );
        TSet<FString> newKey = { newCompTypeID };
        newKey.Append( InOriginal->TypeIDs );
        newArcheType->TypeIDs = newKey;
        return newArcheType;
    }

    template< typename TNewComp > 
    void AddComponent( int32 InEntityID, TNewComp&& InComponent )
    {
        if ( !EntityIDs.Contains( InEntityID ) )
            AddEntity( InEntityID );

        auto& comps = GetPool<TNewComp>()->Components;
        check( comps.Num() == EntityIDToIndex[ InEntityID ] );
        comps.Push( MoveTemp( InComponent ) );
    }

    template< typename TComp > 
    void MoveToBigger( FSECSArcheType* InTo, int32 InEntityID, TComp&& InComponent )
    {
        MoveToSmaller( InTo, InEntityID );
        InTo->AddComponent( InEntityID, MoveTemp( InComponent ) );
        if ( InTo->GetPool<TComp>()->Components.Num() != InTo->EntityIDs.Num() )
            Log( TEXT( "InTo->EntityIDs != InTo->GetPool()->Components" ) );
    }

private:
    void AddEntity( int32 InEntityID );
    void RemoveEntity( int32 InIndexToMove, int32 InEntityID );
    void Log( const TCHAR* InMessage ) const;

public:
    TSet<FString> TypeIDs;

private:
    TArray<int32> EntityIDs;
    TMap<int32, int32> EntityIDToIndex;
    TMap<FString, FSECSPoolData*> TypeIDToPool;
};

//-----------------------------------------------------------------------------

class SIMPLEECS_API FSECSRegistry
{
public:
    ~FSECSRegistry();

    int32 CreateEntity();
    FSECSArcheType* GetExactArcheType( TSet<FString> InKey );

public:
    template< typename TComp > 
    void AddComponent( int32 InEntityID, TComp&& InComponent )
    {
        typedef typename TRemoveReference<TComp>::Type T;
        auto typeID = SECS_TypeToTypeID<T>();
        if ( EntityToArcheTypes.Contains( InEntityID ) ) {
            auto container = EntityToArcheTypes[ InEntityID ];
            TSet<FString> biggerKey = { typeID };
            biggerKey.Append( container->TypeIDs );

            auto biggerContainer = GetExactArcheType( biggerKey );
            if ( biggerContainer == nullptr ) {
                biggerContainer = FSECSArcheType::CreateExtension<T>( container );
                ArcheTypes.Add( biggerContainer );
            }

            container->MoveToBigger<T>( biggerContainer, InEntityID, MoveTemp( InComponent ) );
            EntityToArcheTypes[ InEntityID ] = biggerContainer;
        }
        else {
            auto container = GetExactArcheType( TSet<FString>{ typeID } );
            if ( container == nullptr ) {
                container = FSECSArcheType::Create<T>();
                ArcheTypes.Add( container );
            }

            container->AddComponent( InEntityID, MoveTemp( InComponent ) );
            EntityToArcheTypes.Add( InEntityID, container );
        }
    }

    template< typename TComp > 
    TComp* GetComponent( int32 InEntityID ) const
    {
        check( EntityToArcheTypes.Contains( InEntityID ) );
        return EntityToArcheTypes[ InEntityID ]->GetComponent<TComp>( InEntityID );
    }

    template< typename... TComps, typename... TExcludes > 
    TArray<FSECSArcheType*> GetArcheTypes( const TSECSExclude<TExcludes...>& InExclude = {} ) const
    {
        TArray<FSECSArcheType*> matchingArcheTypes;
        TSet<FString> keySetToInclude = { SECS_TypeToTypeID<TComps>()... };
        TSet<FString> keySetToExclude = { SECS_TypeToTypeID<TExcludes>()... };

        for ( auto archeType : ArcheTypes ) {
            if ( archeType->TypeIDs.Includes( keySetToInclude ) && archeType->TypeIDs.Intersect( keySetToExclude ).Num() == 0 )
                matchingArcheTypes.Add( archeType );
        }

        return matchingArcheTypes;
    }

    template< typename... TComps > 
    TArray<FSECSArcheType*> GetArcheTypes() const
    {
        TArray<FSECSArcheType*> matchingArcheTypes;
        TSet<FString> keySetToInclude = { SECS_TypeToTypeID<TComps>()... };
        for ( auto archeType : ArcheTypes ) {
            if ( archeType->TypeIDs.Includes( keySetToInclude ) )
                matchingArcheTypes.Add( archeType );
        }

        return matchingArcheTypes;
    }

private:
    int32 NextEntity = 0;
    TArray<FSECSArcheType*> ArcheTypes;
    TMap<int32, FSECSArcheType*> EntityToArcheTypes;
};
