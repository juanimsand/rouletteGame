cmake_minimum_required(VERSION 3.10)

project(rouletteGame
        VERSION 0.0.1
        DESCRIPTION "Roulette game application."
        LANGUAGES CXX)

add_executable(rouletteGame roulettegame.cpp src/casino.cpp src/roulette.cpp src/rouletteplayer.cpp)
target_compile_features(rouletteGame PRIVATE cxx_std_17)
target_include_directories(rouletteGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)