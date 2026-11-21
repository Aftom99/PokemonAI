
cmake_minimum_required(VERSION 3.20)

project(PokemonAI
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(nlohmann_json)

add_executable(PokemonAI
    src/main.cpp
    src/core/pokemon_database.cpp
)

target_include_directories(PokemonAI PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(PokemonAI PRIVATE
    nlohmann_json::nlohmann_json
)

if(MSVC)
    target_compile_options(PokemonAI PRIVATE /W4 /permissive-)
else()
    target_compile_options(PokemonAI PRIVATE
        -Wall -Wextra -Wpedantic
    )
endif()
