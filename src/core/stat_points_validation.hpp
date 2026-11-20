
#pragma once

#include "stat_points.hpp"

namespace pokemon
{
    constexpr bool isValidStatPoints(const StatPoints &points)
    {
        const unsigned int total =
            points.hp +
            points.attack +
            points.defense +
            points.specialAttack +
            points.specialDefense +
            points.speed;

        return total <= 66 &&
               points.hp <= 32 &&
               points.attack <= 32 &&
               points.defense <= 32 &&
               points.specialAttack <= 32 &&
               points.specialDefense <= 32 &&
               points.speed <= 32;
    }
}
