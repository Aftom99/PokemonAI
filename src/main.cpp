
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "core/ability_database.hpp"

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

    std::cout << "Pokemon AI - Ability Database Tests\n\n";

    pokemon::AbilityDatabase database;

    // 1. Load ability directory
    const bool loaded = database.loadFromDirectory("data/abilities");
    test("Load ability directory", loaded);

    // 2. Verify database size
    test("Correct number of loaded abilities", database.size() == 1);

    // 3. Retrieve Blaze
    const pokemon::Ability *blaze = database.getAbility("blaze");

    test(
        "Retrieve Blaze",
        blaze != nullptr &&
            blaze->name == "Blaze" &&
            blaze->description.find("Fire-type") != std::string::npos);

    // 4. Unknown ability
    test(
        "Unknown ability returns nullptr",
        database.getAbility("nonexistent_ability") == nullptr);

    const fs::path invalidDirectory =
        fs::temp_directory_path() / "pokemon_ai_invalid_abilities";

    fs::remove_all(invalidDirectory);
    fs::create_directories(invalidDirectory);

    // 5. Missing required field
    {
        std::ofstream file(invalidDirectory / "missing.json");

        file << R"({
            "id": "test_ability",
            "name": "Test Ability"
        })";
    }

    const bool missingFieldLoaded =
        database.loadFromDirectory(invalidDirectory.string());

    test("Reject missing required field", !missingFieldLoaded);

    // 6. Empty required field
    {
        fs::remove_all(invalidDirectory);
        fs::create_directories(invalidDirectory);

        std::ofstream file(invalidDirectory / "empty.json");

        file << R"({
            "id": "test_ability",
            "name": "",
            "description": "Test description"
        })";
    }

    const bool emptyFieldLoaded =
        database.loadFromDirectory(invalidDirectory.string());

    test("Reject empty required field", !emptyFieldLoaded);

    // 7. Wrong field type
    {
        fs::remove_all(invalidDirectory);
        fs::create_directories(invalidDirectory);

        std::ofstream file(invalidDirectory / "wrong_type.json");

        file << R"({
            "id": "test_ability",
            "name": "Test Ability",
            "description": 123
        })";
    }

    const bool wrongTypeLoaded =
        database.loadFromDirectory(invalidDirectory.string());

    test("Reject incorrect field type", !wrongTypeLoaded);

    // 8. Duplicate IDs
    {
        fs::remove_all(invalidDirectory);
        fs::create_directories(invalidDirectory);

        const std::string duplicateJson = R"({
            "id": "duplicate_ability",
            "name": "Duplicate Ability",
            "description": "Test description"
        })";

        std::ofstream first(invalidDirectory / "first.json");
        first << duplicateJson;
        first.close();

        std::ofstream second(invalidDirectory / "second.json");
        second << duplicateJson;
    }

    const bool duplicateLoaded =
        database.loadFromDirectory(invalidDirectory.string());

    test("Reject duplicate ability IDs", !duplicateLoaded);

    // 9. Preserve existing database after failed loads
    test(
        "Preserve database after failed loads",
        database.size() == 1 &&
            database.getAbility("blaze") != nullptr);

    fs::remove_all(invalidDirectory);

    std::cout << "\nResults: " << passed << "/" << total
              << " tests passed.\n";

    return passed == total ? 0 : 1;
}
