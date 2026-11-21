
#include "pokemon_database.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include "pokemon_json_loader.hpp"

namespace pokemon
{
    bool PokemonDatabase::loadFromDirectory(
        const std::string &directory)
    {
        namespace fs = std::filesystem;

        if (!fs::exists(directory) || !fs::is_directory(directory))
        {
            std::cerr << "Pokemon directory not found: "
                      << directory << '\n';

            return false;
        }

        std::unordered_map<std::string, PokemonSpecies> loadedPokemon;

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
                {
                    throw std::runtime_error(
                        "Could not open file.");
                }

                nlohmann::json data;
                file >> data;

                const std::string id = getRequiredString(data, "id");

                PokemonSpecies species =
                    pokemonSpeciesFromJson(data);

                if (id.empty())
                {
                    throw std::runtime_error(
                        "Pokemon ID cannot be empty.");
                }

                if (loadedPokemon.contains(id))
                {
                    throw std::runtime_error(
                        "Duplicate Pokemon ID: " + id);
                }

                loadedPokemon.emplace(id, std::move(species));
            }
            catch (const std::exception &error)
            {
                std::cerr << "Error loading "
                          << entry.path().filename().string()
                          << ": " << error.what() << '\n';

                return false;
            }
        }

        pokemon = std::move(loadedPokemon);

        return true;
    }

    const PokemonSpecies *PokemonDatabase::getPokemon(
        const std::string &id) const
    {
        const auto it = pokemon.find(id);

        if (it == pokemon.end())
        {
            return nullptr;
        }

        return &it->second;
    }

    std::size_t PokemonDatabase::size() const
    {
        return pokemon.size();
    }
}
