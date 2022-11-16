# Roulette game
Simple C++ project of roulette game simulation.

## What rouletteGame application does

The application simulates the famous roulette game. The simulation consists of 10000 spins with 6 people playing at the same time. Each person bets on *red*, *black*, *1 to 18*, *19 to 36*, *even*, or *odd* throughout the simulation.
After each spin, the house pays the bet to the winning players. Then, if the game must continue, the players return to place their respective bets.

### Bet method
<p>Each player has their own notes to calculate how much they will bet on each roulette spin. Starting notes: { 1, 2, 3, 4 }.</p>
<p>Bet calculation: Addition of first and last number in notes. First bet will be 1 + 4 = 5.</p>

* **Won:**&nbsp;&nbsp;&nbsp;&nbsp;The amount earned is added at the end of notes. If bet is 1 + 4 = 5, then notes are { 1, 2, 3, 4, 5 }
* **Lost:**&nbsp;&nbsp;&nbsp;&nbsp;The first and last items from notes are deleted. So, if the player bets based on the initial notes { 1, 2, 3, 4 } and lose, then his notes will be { 2, 3 }.
* **Special case:**&nbsp;&nbsp;&nbsp;&nbsp;If only one item remains in the notes, then the player bet that item.

&nbsp;
Bets has a minimum of 5 and a maximum of 4000.
If a player cannot bet because the bet is out of range or there is no item in the notes, he starts over with the initial notes { 1, 2, 3, 4 }.

When the game ends, the balance of each player and the total (of 6 players) is showed.
Oh, players are lucky, they have infinite money to bet :).

## Project
This project was developed in C++ using:
* WSL (Ubuntu 20.04 LTS).
* CMake (version 3.16.3).
* GNU Make 4.2.1. Built for x86_64-pc-linux-gnu.
* g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0.
* GNU gdb (Ubuntu 9.2-0ubuntu1~20.04.1) 9.2.

### Repository structure
On root you should find:
* include/
    * appgeneralmacros.h
    * casino.h
    * roulette.h
    * rouletteplayer.h
* src/
    * casino.cpp
    * roulette.cpp
    * rouletteplayer.cpp
* build/
* output/
* rouletteGame.cpp
* CMakeLists.txt

### Build
#### Read section [Fixes]
To build this project you must have CMake (and make) installed. Follow this steps:

1. Go to repository root directory.
2. Go to build directory:
    * `ls build/`
3. Clean directory. **Be careful, you are going to delete everything in folder, be sure to be at build directory (and do not forget the . preceding the / )** :
    * `rm -r ./*`
4. Run cmake, this should generate new files in build folder:
    * `cmake ../`
5. Run make, this should generate application executable:
    * `make`
6. You just generated the rouletteGame application executable, congrats!

## How to run

Follow the [building process steps](#build) for generate the executable file, it should be located in build/ directory.
A useful help text is displayed if you execute it with `--help` or `-h` as argument.

## Fixes

1. For test how the application works I cloned this repository from another enviroment (another PC with Ubuntu 18.04). When I followed the [building process steps](#build), step 4 failed. The failure executing `cmake ../` was cause by line `target_compile_features(rouletteGame PRIVATE cxx_std_20)` of CMakeLists.txt, so I changed it for `target_compile_features(rouletteGame PRIVATE cxx_std_17)`. Also I updated the line `cmake_minimum_required(VERSION 3.5)` by `cmake_minimum_required(VERSION 3.10)`. With these changes I could build and execute the application without problems.
