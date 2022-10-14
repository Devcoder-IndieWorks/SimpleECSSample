// Copyright Devcoder.
#pragma once
#include "SECSRegistry.h"

template< typename... TComps > 
class TSECSQuery
{
public:
    template< typename TPoolComp > 
    using TCompPoolPtr = TSECSComponentPool<TPoolComp>*;

    template< typename TFunc > 
    void Each( const FSECSRegistry& InRegistry, TFunc InFunc )
    {
        auto archeTypes = InRegistry.GetArcheTypes<TComps...>();
        for ( auto archeType : archeTypes ) {
            const auto entityOrder = archeType->GetEntityList();
            auto pools = MakeTuple<TCompPoolPtr<TComps>...>( archeType->GetPool<TComps>()... );

            for ( int32 index = 0; index < entityOrder.Num(); index++ ) {
                auto entityID = entityOrder[ index ];
                InFunc( entityID, pools.Get<TCompPoolPtr<TComps>>()->Components[ index ]... );
            }
        }
    }
};

template< typename... TComps, typename... TExcludes > 
class TSECSQuery<TSECSExclude<TExcludes...>, TComps...>
{
public:
    template< typename TPoolComp > 
    using TCompPoolPtr = TSECSComponentPool<TPoolComp>*;

    template< typename TFunc >
    void Each( const FSECSRegistry& InRegistry, TFunc InFunc )
    {
        auto archeTypes = InRegistry.GetArcheTypes<TComps...>( TSECSExclude<TExcludes...>() );
        for ( auto archeType : archeTypes ) {
            auto entityOrder = archeType->GetEntityList();

            for ( int32 index = 0; index < entityOrder.Num(); index++ ) {
                auto entityID = entityOrder[ index ];
                if ( InFunc( entityID, *InRegistry.GetComponent<TComps>( entityID )... ) == false )
                    return;
            }
        }
    }
};
