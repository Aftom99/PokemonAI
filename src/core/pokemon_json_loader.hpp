
#pragma once

#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>

#include "pokemon.hpp"
#include "types.hpp"
#include "stats.hpp"

namespace pokemon
{
    inline Type parseType(const std::string &typeName)
    {
        if (typeName == "Normal")
            return Type::Normal;
        if (typeName == "Fire")
            return Type::Fire;
        if (typeName == "Water")
            return Type::Water;
        if (typeName == "Electric")
            return Type::Electric;
        if (typeName == "Grass")
            return Type::Grass;
        if (typeName == "Ice")
            return Type::Ice;
        if (typeName == "Fighting")
            return Type::Fighting;
        if (typeName == "Poison")
            return Type::Poison;
        if (typeName == "Ground")
            return Type::Ground;
        if (typeName == "Flying")
            return Type::Flying;
        if (typeName == "Psychic")
            return Type::Psychic;
        if (typeName == "Bug")
            return Type::Bug;
        if (typeName == "Rock")
            return Type::Rock;
        if (typeName == "Ghost")
            return Type::Ghost;
        if (typeName == "Dragon")
            return Type::Dragon;
        if (typeName == "Dark")
            return Type::Dark;
        if (typeName == "Steel")
            return Type::Steel;
        if (typeName == "Fairy")
            return Type::Fairy;

        throw std::invalid_argument(
            "Unknown Pokemon type: " + typeName);
    }

    inline PokemonSpecies pokemonSpeciesFromJson(
        const nlohmann::json &data)
    {
        if (!data.is_object())
        {
            throw std::invalid_argument(
                "Pokemon data must be a JSON object.");
        }

        const std::string name = data.at("name").get<std::string>();
        const std::string form = data.at("form").get<std::string>();

        const auto &types = data.at("types");

        if (!types.is_array() || types.empty() || types.size() > 2)
        {
            throw std::invalid_argument(
                "Pokemon must have one or two types.");
        }

        const Type primaryType =
            parseType(types.at(0).get<std::string>());

        const bool hasSecondaryType = types.size() == 2;

        const Type secondaryType = hasSecondaryType
                                       ? parseType(types.at(1).get<std::string>())
                                       : Type::Normal;

        const auto &baseStats = data.at("base_stats");

        return {
            {name + (form == "Normal" ? "" : " (" + form + ")"), name},
            primaryType,
            secondaryType,
            hasSecondaryType,
            {baseStats.at("hp").get<std::uint16_t>(),
             baseStats.at("attack").get<std::uint16_t>(),
             baseStats.at("defense").get<std::uint16_t>(),
             baseStats.at("special_attack").get<std::uint16_t>(),
             baseStats.at("special_defense").get<std::uint16_t>(),
             baseStats.at("speed").get<std::uint16_t>()}};
    }
}
