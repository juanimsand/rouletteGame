cmake_minimum_required(VERSION 3.15)

project(rouletteGame
        VERSION 0.0.1
        DESCRIPTION "Roulette game application."
        LANGUAGES CXX)

add_executable(rouletteGame rouletteGame.cpp src/outputmanager.cpp src/casino.cpp src/roulette.cpp src/rouletteplayer.cpp)
target_compile_features(rouletteGame PRIVATE cxx_std_20)
target_include_directories(rouletteGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)