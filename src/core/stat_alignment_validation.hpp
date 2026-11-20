#pragma once

#include "stat_alignment.hpp"

namespace pokemon
{
    constexpr bool isValidStatAlignment(StatAlignmentName alignment)
    {
        return alignment >= StatAlignmentName::Serious &&
               alignment <= StatAlignmentName::Naive;
    }
}