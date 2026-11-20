#pragma once

#include "individual_pokemon.hpp"
#include "stat_points_validation.hpp"
#include "stat_alignment_validation.hpp"

namespace pokemon
{
    constexpr bool isValidIndividualPokemon(
        const IndividualPokemon &pokemon)
    {
        return pokemon.species != nullptr &&
               pokemon.level >= 1 &&
               pokemon.level <= 100 &&
               isValidStatPoints(pokemon.statPoints) &&
               isValidStatAlignment(pokemon.alignment);
    }
}