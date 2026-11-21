
#pragma once

#include <stdexcept>
#include <string>
#include <cstdint>

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

    inline std::string getRequiredString(
        const nlohmann::json &data,
        const std::string &fieldName)
    {
        if (!data.contains(fieldName))
        {
            throw std::invalid_argument(
                "Missing required field: " + fieldName);
        }

        const auto &value = data.at(fieldName);

        if (!value.is_string())
        {
            throw std::invalid_argument(
                "Field must be a string: " + fieldName);
        }

        const std::string result = value.get<std::string>();

        if (result.empty())
        {
            throw std::invalid_argument(
                "Field cannot be empty: " + fieldName);
        }

        return result;
    }

    inline std::uint16_t parseBaseStat(
        const nlohmann::json &baseStats,
        const std::string &statName)
    {
        if (!baseStats.is_object())
        {
            throw std::invalid_argument(
                "Pokemon base_stats must be a JSON object.");
        }

        if (!baseStats.contains(statName))
        {
            throw std::invalid_argument(
                "Missing base stat: " + statName);
        }

        const auto &value = baseStats.at(statName);

        if (!value.is_number_integer())
        {
            throw std::invalid_argument(
                "Base stat must be an integer: " + statName);
        }

        if (value.is_number_unsigned())
        {
            const std::uint64_t statValue =
                value.get<std::uint64_t>();

            if (statValue < 1 || statValue > 255)
            {
                throw std::invalid_argument(
                    "Base stat out of valid range (1-255): " + statName);
            }

            return static_cast<std::uint16_t>(statValue);
        }

        const std::int64_t statValue =
            value.get<std::int64_t>();

        if (statValue < 1 || statValue > 255)
        {
            throw std::invalid_argument(
                "Base stat out of valid range (1-255): " + statName);
        }

        return static_cast<std::uint16_t>(statValue);
    }

    inline PokemonSpecies pokemonSpeciesFromJson(
        const nlohmann::json &data)
    {
        if (!data.is_object())
        {
            throw std::invalid_argument(
                "Pokemon data must be a JSON object.");
        }

        const std::string name = getRequiredString(data, "name");
        const std::string form = getRequiredString(data, "form");

        const auto &types = data.at("types");

        if (!types.is_array() || types.empty() || types.size() > 2)
        {
            throw std::invalid_argument(
                "Pokemon must have one or two types.");
        }

        for (const auto &type : types)
        {
            if (!type.is_string())
            {
                throw std::invalid_argument(
                    "Pokemon types must contain strings.");
            }

            parseType(type.get<std::string>());
        }

        const Type primaryType =
            parseType(types.at(0).get<std::string>());

        const bool hasSecondaryType = types.size() == 2;

        if (hasSecondaryType &&
            types.at(0) == types.at(1))
        {
            throw std::invalid_argument(
                "Pokemon cannot have duplicate types.");
        }

        const Type secondaryType = hasSecondaryType
                                       ? parseType(types.at(1).get<std::string>())
                                       : Type::Normal;

        const auto &baseStats = data.at("base_stats");

        return {
            {name + (form == "Normal" ? "" : " (" + form + ")"), name},
            primaryType,
            secondaryType,
            hasSecondaryType,
            {parseBaseStat(baseStats, "hp"),
             parseBaseStat(baseStats, "attack"),
             parseBaseStat(baseStats, "defense"),
             parseBaseStat(baseStats, "special_attack"),
             parseBaseStat(baseStats, "special_defense"),
             parseBaseStat(baseStats, "speed")}};
    }
}
