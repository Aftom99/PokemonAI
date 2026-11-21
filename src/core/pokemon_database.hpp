
#pragma once

#include <string>
#include <unordered_map>

#include "pokemon.hpp"

namespace pokemon
{
    class PokemonDatabase
    {
    public:
        bool loadFromDirectory(const std::string &directory);

        const PokemonSpecies *getPokemon(
            const std::string &id) const;

        std::size_t size() const;

    private:
        std::unordered_map<std::string, PokemonSpecies> pokemon;
    };
}
