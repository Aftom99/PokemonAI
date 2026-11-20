
#pragma once

#include "types.hpp"
#include "stats.hpp"
#include "form.hpp"

namespace pokemon
{
    struct PokemonSpecies
    {
        PokemonForm form;

        Type primaryType;
        Type secondaryType;

        bool hasSecondaryType = false;

        Stats baseStats;
    };
}
