
#pragma once

#include <cstdint>

namespace pokemon
{
    struct Stats
    {
        std::uint16_t hp = 0;
        std::uint16_t attack = 0;
        std::uint16_t defense = 0;
        std::uint16_t specialAttack = 0;
        std::uint16_t specialDefense = 0;
        std::uint16_t speed = 0;
    };
}
