
#pragma once

#include <cstdint>
#include <optional>

namespace pokemon
{
    enum class Stat : std::uint8_t
    {
        Attack,
        Defense,
        SpecialAttack,
        SpecialDefense,
        Speed
    };

    enum class StatAlignmentName : std::uint8_t
    {
        Serious,

        Lonely,
        Adamant,
        Naughty,
        Brave,

        Bold,
        Impish,
        Lax,
        Relaxed,

        Modest,
        Mild,
        Rash,
        Quiet,

        Calm,
        Gentle,
        Careful,
        Sassy,

        Timid,
        Hasty,
        Jolly,
        Naive
    };

    struct StatAlignment
    {
        std::optional<Stat> increasedStat;
        std::optional<Stat> decreasedStat;

        float increasedMultiplier = 1.1f;
        float decreasedMultiplier = 0.9f;
    };
}
