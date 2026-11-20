
cmake_minimum_required(VERSION 3.20)

project(PokemonAI
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(PokemonAI
    src/main.cpp
)

target_include_directories(PokemonAI PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

if(MSVC)
    target_compile_options(PokemonAI PRIVATE /W4 /permissive-)
else()
    target_compile_options(PokemonAI PRIVATE
        -Wall -Wextra -Wpedantic
    )
endif()
