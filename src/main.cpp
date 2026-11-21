
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "core/move_database.hpp"

int main()
{
    namespace fs = std::filesystem;

    int passed = 0;
    int total = 0;

    auto test = [&](const std::string &name, bool condition)
    {
        ++total;

        if (condition)
        {
            ++passed;
            std::cout << "[PASS] " << name << '\n';
        }
        else
        {
            std::cout << "[FAIL] " << name << '\n';
        }
    };

    std::cout << "Pokemon AI - Move Database Tests\n\n";

    pokemon::MoveDatabase database;

    // Test 1: Load move directory
    const bool loaded = database.loadFromDirectory("data/moves");
    test("Load move directory", loaded);

    // Test 2: Verify database size
    test("Correct number of loaded moves", database.size() == 2);

    // Test 3: Retrieve Flamethrower
    const pokemon::Move *flamethrower =
        database.getMove("flamethrower");

    test(
        "Retrieve Flamethrower",
        flamethrower != nullptr &&
            flamethrower->name == "Flamethrower" &&
            flamethrower->type == pokemon::Type::Fire &&
            flamethrower->category == pokemon::MoveCategory::Special &&
            flamethrower->power == 90);

    // Test 4: Retrieve Protect
    const pokemon::Move *protect = database.getMove("protect");

    test(
        "Retrieve Protect",
        protect != nullptr &&
            protect->name == "Protect" &&
            protect->type == pokemon::Type::Normal &&
            protect->category == pokemon::MoveCategory::Status &&
            protect->power == 0 &&
            protect->priority == 4 &&
            protect->target == pokemon::MoveTarget::User);

    // Test 5: Unknown move
    test(
        "Unknown move returns nullptr",
        database.getMove("nonexistent_move") == nullptr);

    // Prepare a directory containing duplicate move IDs
    const fs::path duplicateDirectory =
        fs::temp_directory_path() / "pokemon_ai_duplicate_moves";

    fs::remove_all(duplicateDirectory);
    fs::create_directories(duplicateDirectory);

    const std::string duplicateMoveJson = R"({
        "id": "duplicate_move",
        "name": "Test Move",
        "type": "Normal",
        "category": "Physical",
        "power": 40,
        "accuracy": 100,
        "priority": 0,
        "target": "SingleOpponent"
    })";

    {
        std::ofstream first(duplicateDirectory / "first.json");
        first << duplicateMoveJson;

        std::ofstream second(duplicateDirectory / "second.json");
        second << duplicateMoveJson;
    }

    // Test 6: Reject duplicate IDs
    const bool duplicateLoaded =
        database.loadFromDirectory(duplicateDirectory.string());

    test("Reject duplicate move IDs", !duplicateLoaded);

    // Test 7: Preserve existing database after failed load
    test(
        "Preserve database after failed load",
        database.size() == 2 &&
            database.getMove("flamethrower") != nullptr &&
            database.getMove("protect") != nullptr);

    fs::remove_all(duplicateDirectory);

    std::cout << "\nResults: " << passed << "/" << total
              << " tests passed.\n";

    return passed == total ? 0 : 1;
}
