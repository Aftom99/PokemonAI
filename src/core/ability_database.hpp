
#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>

#include "ability.hpp"

namespace pokemon
{
    class AbilityDatabase
    {
    public:
        bool loadFromDirectory(const std::string &directory);
        const Ability *getAbility(const std::string &id) const;
        std::size_t size() const;

    private:
        std::unordered_map<std::string, Ability> abilities;
    };
}
