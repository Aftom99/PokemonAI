
#pragma once

#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>

#include "ability.hpp"

namespace pokemon
{
    inline std::string getRequiredAbilityString(
        const nlohmann::json &data,
        const std::string &field)
    {
        if (!data.is_object())
            throw std::runtime_error("Ability data must be a JSON object.");

        if (!data.contains(field))
            throw std::runtime_error("Missing required field: " + field);

        if (!data[field].is_string())
            throw std::runtime_error("Field must be a string: " + field);

        const std::string value = data[field].get<std::string>();

        if (value.empty())
            throw std::runtime_error("Field cannot be empty: " + field);

        return value;
    }

    inline Ability abilityFromJson(const nlohmann::json &data)
    {
        Ability ability;

        ability.id = getRequiredAbilityString(data, "id");
        ability.name = getRequiredAbilityString(data, "name");
        ability.description =
            getRequiredAbilityString(data, "description");

        return ability;
    }
}
