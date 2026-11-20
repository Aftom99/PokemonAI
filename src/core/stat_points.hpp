
#pragma once

#include <cstdint>

namespace pokemon
{
    struct StatPoints
    {
        std::uint8_t hp = 0;
        std::uint8_t attack = 0;
        std::uint8_t defense = 0;
        std::uint8_t specialAttack = 0;
        std::uint8_t specialDefense = 0;
        std::uint8_t speed = 0;
    };
}
