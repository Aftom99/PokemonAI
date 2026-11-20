
#pragma once

#include <cstdint>

namespace pokemon
{
    // All elemental Pokémon types.
    enum class Type : std::uint8_t
    {
        Normal,
        Fire,
        Water,
        Electric,
        Grass,
        Ice,
        Fighting,
        Poison,
        Ground,
        Flying,
        Psychic,
        Bug,
        Rock,
        Ghost,
        Dragon,
        Dark,
        Steel,
        Fairy
    };

    // Physical and special move categories.
    enum class MoveCategory : std::uint8_t
    {
        Physical,
        Special,
        Status
    };

    // Gender representation.
    enum class Gender : std::uint8_t
    {
        Male,
        Female,
        Genderless
    };
}
