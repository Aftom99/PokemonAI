
#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>

#include "move.hpp"

namespace pokemon
{
    class MoveDatabase
    {
    public:
        bool loadFromDirectory(const std::string &directory);

        const Move *getMove(const std::string &id) const;

        std::size_t size() const;

    private:
        std::unordered_map<std::string, Move> moves;
    };
}
