
#pragma once

#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>

#include "move.hpp"

namespace pokemon
{
    inline Type parseMoveType(const std::string &typeName)
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

        throw std::invalid_argument("Unknown move type: " + typeName);
    }

    inline MoveCategory parseMoveCategory(const std::string &category)
    {
        if (category == "Physical")
            return MoveCategory::Physical;
        if (category == "Special")
            return MoveCategory::Special;
        if (category == "Status")
            return MoveCategory::Status;

        throw std::invalid_argument(
            "Unknown move category: " + category);
    }

    inline MoveTarget parseMoveTarget(const std::string &target)
    {
        if (target == "SingleOpponent")
            return MoveTarget::SingleOpponent;
        if (target == "AllOpponents")
            return MoveTarget::AllOpponents;
        if (target == "AllAdjacent")
            return MoveTarget::AllAdjacent;
        if (target == "AllAdjacentExceptUser")
            return MoveTarget::AllAdjacentExceptUser;
        if (target == "User")
            return MoveTarget::User;
        if (target == "UserSide")
            return MoveTarget::UserSide;
        if (target == "Ally")
            return MoveTarget::Ally;
        if (target == "AllAllies")
            return MoveTarget::AllAllies;
        if (target == "Field")
            return MoveTarget::Field;
        if (target == "RandomOpponent")
            return MoveTarget::RandomOpponent;

        throw std::invalid_argument("Unknown move target: " + target);
    }

    inline const nlohmann::json &getRequiredMoveField(
        const nlohmann::json &data,
        const std::string &fieldName)
    {
        if (!data.is_object())
        {
            throw std::invalid_argument(
                "Move data must be a JSON object.");
        }

        if (!data.contains(fieldName))
        {
            throw std::invalid_argument(
                "Missing required field: " + fieldName);
        }

        return data.at(fieldName);
    }

    inline std::string getRequiredMoveString(
        const nlohmann::json &data,
        const std::string &fieldName)
    {
        const auto &value = getRequiredMoveField(data, fieldName);

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

    template <typename T>
    inline T getRequiredMoveInteger(
        const nlohmann::json &data,
        const std::string &fieldName,
        std::int64_t minimum,
        std::int64_t maximum)
    {
        const auto &value = getRequiredMoveField(data, fieldName);

        if (!value.is_number_integer())
        {
            throw std::invalid_argument(
                "Field must be an integer: " + fieldName);
        }

        std::int64_t number;

        if (value.is_number_unsigned())
        {
            const auto unsignedNumber = value.get<std::uint64_t>();

            if (unsignedNumber >
                static_cast<std::uint64_t>(maximum))
            {
                throw std::invalid_argument(
                    "Field is outside allowed range: " + fieldName);
            }

            number = static_cast<std::int64_t>(unsignedNumber);
        }
        else
        {
            number = value.get<std::int64_t>();
        }

        if (number < minimum || number > maximum)
        {
            throw std::invalid_argument(
                "Field is outside allowed range: " + fieldName);
        }

        return static_cast<T>(number);
    }

    inline Move moveFromJson(const nlohmann::json &data)
    {
        Move move;

        move.id = getRequiredMoveString(data, "id");
        move.name = getRequiredMoveString(data, "name");

        move.type = parseMoveType(
            getRequiredMoveString(data, "type"));

        move.category = parseMoveCategory(
            getRequiredMoveString(data, "category"));

        move.power = getRequiredMoveInteger<std::uint16_t>(
            data, "power", 0, 65535);

        move.accuracy = getRequiredMoveInteger<std::uint8_t>(
            data, "accuracy", 0, 100);

        move.priority = getRequiredMoveInteger<std::int8_t>(
            data, "priority", -128, 127);

        move.target = parseMoveTarget(
            getRequiredMoveString(data, "target"));

        return move;
    }
}
