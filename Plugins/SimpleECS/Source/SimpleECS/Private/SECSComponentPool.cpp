#include "SECSComponentPool.h"
#include "SimpleECSPCH.h"

FSECSPoolData* FSECSPoolData::CreateEmptyClone()
{
    return new FSECSPoolData {
        TypeID,
        Pool->CreateEmpty()
    };
}

void FSECSPoolData::MoveTo( int32 InIndex, FSECSPoolData* InTo )
{
    Pool->MoveTo( InIndex, InTo->Pool );
}
