#include <iostream>

#include "core/individual_pokemon_validation.hpp"

int main()
{
    const pokemon::PokemonSpecies charizard{
        {"charizard", "Charizard"},
        pokemon::Type::Fire,
        pokemon::Type::Flying,
        true,
        {78, 84, 78, 109, 85, 100}};

    const pokemon::IndividualPokemon validPokemon{
        &charizard, 50, pokemon::Gender::Male, {2, 10, 0, 0, 0, 10}, pokemon::StatAlignmentName::Adamant};

    const pokemon::IndividualPokemon invalidAlignment{
        &charizard, 50, pokemon::Gender::Male, {2, 10, 0, 0, 0, 10}, static_cast<pokemon::StatAlignmentName>(255)};

    std::cout << "Pokemon AI - Stat Alignment Validation Test\n\n";

    std::cout << "Valid Alignment: "
              << pokemon::isValidIndividualPokemon(validPokemon) << '\n';

    std::cout << "Invalid Alignment: "
              << pokemon::isValidIndividualPokemon(invalidAlignment) << '\n';

    return 0;
}