
#pragma once

#include <cstdint>

namespace pokemon
{
    enum class MoveTarget : std::uint8_t
    {
        SingleOpponent,
        AllOpponents,
        AllAdjacent,
        AllAdjacentExceptUser,
        User,
        UserSide,
        Ally,
        AllAllies,
        Field,
        RandomOpponent
    };
}
