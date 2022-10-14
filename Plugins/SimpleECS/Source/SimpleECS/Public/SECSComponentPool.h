// Copyright Devcoder.
#pragma once
#include <CoreMinimal.h>

template< typename Type > 
FString SECS_TypeToTypeID()
{
    return typeid(Type).name();
}

template< typename... > 
class TSECSTypeList
{
};

template< typename... Type > 
class TSECSExclude : public TSECSTypeList<Type...>
{
};

//-----------------------------------------------------------------------------

class SIMPLEECS_API ISECSComponentPool
{
public:
    virtual ~ISECSComponentPool() = default;
    virtual ISECSComponentPool* CreateEmpty() = 0;
    virtual void MoveTo( int32, ISECSComponentPool* ) = 0;
};

template< typename TComp > 
class TSECSComponentPool : public ISECSComponentPool
{
public:
    ~TSECSComponentPool() final = default;

    ISECSComponentPool* CreateEmpty() final 
    {
        return new TSECSComponentPool<TComp>();
    }

    void MoveTo( int32 InIndex, ISECSComponentPool* InTo ) final
    {
        int32 lastIdx = Components.Num() - 1;
        check( lastIdx >= InIndex );
        auto realTo = static_cast<TSECSComponentPool<TComp>*>( InTo );
        realTo->Components.Add( MoveTemp( Components[ InIndex ] ) );
        Components[ InIndex ] = Components[ lastIdx ];
        Components.RemoveAt( lastIdx );
    }

public:
    TArray<TComp> Components;
};

//-----------------------------------------------------------------------------

class SIMPLEECS_API FSECSPoolData
{
public:
    template< typename TComp > 
    static FSECSPoolData* Create()
    {
        auto poolData = new FSECSPoolData();
        poolData->TypeID = SECS_TypeToTypeID<TComp>();
        poolData->Pool = new TSECSComponentPool<TComp>();
        return poolData;
    }

    FSECSPoolData* CreateEmptyClone();
    void MoveTo( int32 InIndex, FSECSPoolData* InTo );

private:
    FSECSPoolData() = default;

public:
    FString TypeID;
    ISECSComponentPool* Pool;
};
