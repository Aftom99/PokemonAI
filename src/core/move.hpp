
#pragma once

#include <cstdint>
#include <string>

#include "types.hpp"
#include "move_target.hpp"

namespace pokemon
{
    struct Move
    {
        std::string id;
        std::string name;

        Type type = Type::Normal;
        MoveCategory category = MoveCategory::Status;

        std::uint16_t power = 0;
        std::uint8_t accuracy = 0;

        std::int8_t priority = 0;

        MoveTarget target = MoveTarget::SingleOpponent;
    };
}
