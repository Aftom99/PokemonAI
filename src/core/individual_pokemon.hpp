
#pragma once

#include <cstdint>

#include "pokemon.hpp"
#include "types.hpp"
#include "stat_points.hpp"
#include "stat_alignment.hpp"

namespace pokemon
{
    struct IndividualPokemon
    {
        const PokemonSpecies *species = nullptr;

        std::uint8_t level = 50;

        Gender gender = Gender::Genderless;

        StatPoints statPoints;

        StatAlignmentName alignment = StatAlignmentName::Serious;
    };
}
