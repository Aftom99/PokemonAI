
#include <iostream>
#include <string>

#include "core/pokemon_json_loader.hpp"

bool runTest(
    const std::string &testName,
    const nlohmann::json &data,
    bool shouldSucceed)
{
    try
    {
        pokemon::pokemonSpeciesFromJson(data);

        if (!shouldSucceed)
        {
            std::cout << "[FAIL] " << testName
                      << " - Invalid data was accepted.\n";
            return false;
        }

        std::cout << "[PASS] " << testName << '\n';
        return true;
    }
    catch (const std::exception &)
    {
        if (shouldSucceed)
        {
            std::cout << "[FAIL] " << testName
                      << " - Valid data was rejected.\n";
            return false;
        }

        std::cout << "[PASS] " << testName << '\n';
        return true;
    }
}

int main()
{
    nlohmann::json validPokemon = {
        {"name", "Charizard"},
        {"form", "Normal"},
        {"types", {"Fire", "Flying"}},
        {"base_stats", {{"hp", 78}, {"attack", 84}, {"defense", 78}, {"special_attack", 109}, {"special_defense", 85}, {"speed", 100}}}};

    nlohmann::json zeroStat = validPokemon;
    zeroStat["base_stats"]["hp"] = 0;

    nlohmann::json excessiveStat = validPokemon;
    excessiveStat["base_stats"]["hp"] = 256;

    nlohmann::json decimalStat = validPokemon;
    decimalStat["base_stats"]["hp"] = 78.5;

    std::cout << "Pokemon AI - Combined Base Stat Tests\n\n";

    int passed = 0;

    passed += runTest("Valid base stat", validPokemon, true);
    passed += runTest("Zero base stat", zeroStat, false);
    passed += runTest("Base stat above 255", excessiveStat, false);
    passed += runTest("Decimal base stat", decimalStat, false);

    std::cout << "\nResults: "
              << passed << "/4 tests passed.\n";

    return passed == 4 ? 0 : 1;
}
