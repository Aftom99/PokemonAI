
#include "move_database.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>

#include <nlohmann/json.hpp>

#include "move_json_loader.hpp"

namespace pokemon
{
    bool MoveDatabase::loadFromDirectory(
        const std::string &directory)
    {
        namespace fs = std::filesystem;

        if (!fs::exists(directory) || !fs::is_directory(directory))
        {
            std::cerr << "Move directory not found: "
                      << directory << '\n';

            return false;
        }

        std::unordered_map<std::string, Move> loadedMoves;

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

                Move move = moveFromJson(data);

                if (loadedMoves.contains(move.id))
                {
                    throw std::runtime_error(
                        "Duplicate Move ID: " + move.id);
                }

                loadedMoves.emplace(move.id, std::move(move));
            }
            catch (const std::exception &error)
            {
                std::cerr << "Error loading "
                          << entry.path().filename().string()
                          << ": " << error.what() << '\n';

                return false;
            }
        }

        moves = std::move(loadedMoves);

        return true;
    }

    const Move *MoveDatabase::getMove(
        const std::string &id) const
    {
        const auto it = moves.find(id);

        if (it == moves.end())
        {
            return nullptr;
        }

        return &it->second;
    }

    std::size_t MoveDatabase::size() const
    {
        return moves.size();
    }
}
