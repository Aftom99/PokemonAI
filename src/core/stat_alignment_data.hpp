
#pragma once

#include "stat_alignment.hpp"

namespace pokemon
{
    constexpr StatAlignment getStatAlignment(StatAlignmentName name)
    {
        switch (name)
        {
        case StatAlignmentName::Serious:
            return {};

        case StatAlignmentName::Lonely:
            return {Stat::Attack, Stat::Defense};

        case StatAlignmentName::Adamant:
            return {Stat::Attack, Stat::SpecialAttack};

        case StatAlignmentName::Naughty:
            return {Stat::Attack, Stat::SpecialDefense};

        case StatAlignmentName::Brave:
            return {Stat::Attack, Stat::Speed};

        case StatAlignmentName::Bold:
            return {Stat::Defense, Stat::Attack};

        case StatAlignmentName::Impish:
            return {Stat::Defense, Stat::SpecialAttack};

        case StatAlignmentName::Lax:
            return {Stat::Defense, Stat::SpecialDefense};

        case StatAlignmentName::Relaxed:
            return {Stat::Defense, Stat::Speed};

        case StatAlignmentName::Modest:
            return {Stat::SpecialAttack, Stat::Attack};

        case StatAlignmentName::Mild:
            return {Stat::SpecialAttack, Stat::Defense};

        case StatAlignmentName::Rash:
            return {Stat::SpecialAttack, Stat::SpecialDefense};

        case StatAlignmentName::Quiet:
            return {Stat::SpecialAttack, Stat::Speed};

        case StatAlignmentName::Calm:
            return {Stat::SpecialDefense, Stat::Attack};

        case StatAlignmentName::Gentle:
            return {Stat::SpecialDefense, Stat::Defense};

        case StatAlignmentName::Careful:
            return {Stat::SpecialDefense, Stat::SpecialAttack};

        case StatAlignmentName::Sassy:
            return {Stat::SpecialDefense, Stat::Speed};

        case StatAlignmentName::Timid:
            return {Stat::Speed, Stat::Attack};

        case StatAlignmentName::Hasty:
            return {Stat::Speed, Stat::Defense};

        case StatAlignmentName::Jolly:
            return {Stat::Speed, Stat::SpecialAttack};

        case StatAlignmentName::Naive:
            return {Stat::Speed, Stat::SpecialDefense};
        }

        return {};
    }
}
