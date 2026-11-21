
#include "ability_database.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>

#include <nlohmann/json.hpp>

#include "ability_json_loader.hpp"

namespace pokemon
{
    bool AbilityDatabase::loadFromDirectory(
        const std::string &directory)
    {
        namespace fs = std::filesystem;

        if (!fs::exists(directory) || !fs::is_directory(directory))
        {
            std::cerr << "Ability directory not found: "
                      << directory << '\n';
            return false;
        }

        std::unordered_map<std::string, Ability> loadedAbilities;

        for (const auto &entry : fs::directory_iterator(directory))
        {
            if (!entry.is_regular_file() ||
                entry.path().extension() != ".json")
            {
                continue;
            }

            try
            {
                std::ifstream file(entry.path());

                if (!file.is_open())
                    throw std::runtime_error("Could not open file.");

                nlohmann::json data;
                file >> data;

                Ability ability = abilityFromJson(data);

                if (loadedAbilities.contains(ability.id))
                {
                    throw std::runtime_error(
                        "Duplicate Ability ID: " + ability.id);
                }

                loadedAbilities.emplace(
                    ability.id, std::move(ability));
            }
            catch (const std::exception &error)
            {
                std::cerr << "Error loading "
                          << entry.path().filename().string()
                          << ": " << error.what() << '\n';

                return false;
            }
        }

        abilities = std::move(loadedAbilities);
        return true;
    }

    const Ability *AbilityDatabase::getAbility(
        const std::string &id) const
    {
        const auto it = abilities.find(id);

        if (it == abilities.end())
            return nullptr;

        return &it->second;
    }

    std::size_t AbilityDatabase::size() const
    {
        return abilities.size();
    }
}
