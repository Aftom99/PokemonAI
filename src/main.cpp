
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "core/pokemon_database.hpp"

namespace fs = std::filesystem;

bool runTest(const std::string &name, bool condition)
{
    std::cout << (condition ? "[PASS] " : "[FAIL] ")
              << name << '\n';

    return condition;
}

void writePokemonFile(
    const fs::path &path,
    const std::string &id,
    const std::string &name)
{
    std::ofstream file(path);

    file << R"({
        "id": ")"
         << id << R"(",
        "name": ")"
         << name << R"(",
        "form": "Normal",
        "types": ["Fire", "Flying"],
        "base_stats": {
            "hp": 78,
            "attack": 84,
            "defense": 78,
            "special_attack": 109,
            "special_defense": 85,
            "speed": 100
        }
    })";
}

int main()
{
    std::cout << "Pokemon AI - Database Integration Tests\n\n";

    const fs::path testRoot = "database_test_data";
    const fs::path validDirectory = testRoot / "valid";
    const fs::path duplicateDirectory = testRoot / "duplicates";

    fs::remove_all(testRoot);
    fs::create_directories(validDirectory);
    fs::create_directories(duplicateDirectory);

    writePokemonFile(
        validDirectory / "charizard.json",
        "charizard",
        "Charizard");

    writePokemonFile(
        validDirectory / "pikachu.json",
        "pikachu",
        "Pikachu");

    writePokemonFile(
        duplicateDirectory / "pokemon_a.json",
        "duplicate",
        "Charizard");

    writePokemonFile(
        duplicateDirectory / "pokemon_b.json",
        "duplicate",
        "Pikachu");

    int passed = 0;
    int total = 0;

    auto test = [&](const std::string &name, bool condition)
    {
        ++total;
        if (runTest(name, condition))
            ++passed;
    };

    pokemon::PokemonDatabase database;

    // 1. Load valid directory.
    const bool loaded = database.loadFromDirectory(
        validDirectory.string());

    test("Successfully load Pokemon directory", loaded);

    // 2. Verify number of loaded Pokemon.
    test("Correct Pokemon database size",
         database.size() == 2);

    // 3. Retrieve an existing Pokemon.
    const auto *charizard = database.getPokemon("charizard");

    test("Retrieve Pokemon by ID",
         charizard != nullptr &&
             charizard->form.displayName == "Charizard");

    // 4. Unknown ID should return nullptr.
    test("Unknown Pokemon ID returns nullptr",
         database.getPokemon("missing") == nullptr);

    // 5. Duplicate IDs should cause loading to fail.
    const bool duplicateLoaded = database.loadFromDirectory(
        duplicateDirectory.string());

    test("Reject duplicate Pokemon IDs",
         !duplicateLoaded);

    // 6. Failed loading should preserve existing database.
    test("Preserve database after failed load",
         database.size() == 2 &&
             database.getPokemon("charizard") != nullptr &&
             database.getPokemon("pikachu") != nullptr);

    fs::remove_all(testRoot);

    std::cout << "\nResults: " << passed
              << "/" << total << " tests passed.\n";

    return passed == total ? 0 : 1;
}
