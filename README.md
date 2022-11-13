# Roulette game
Simple cpp project of roulette game simulation.

## What rouletteGame application does

Simulate 10000 plays of 6 players playing the famous roulette game!
Each player bet to: *even*, *odd*, *1 to 18*, *19 to 36*, *red* or *black*, respectively!
After 10000 plays, total balance of 6 players is showed and quit!

### Bet method
<p>Each player has own notes for calculate how much they will bet on each roulette play, starting notes: { 1, 2, 3, 4 }.</p>
<p>Bet calculation is: addition of first and last number in notes. First bet will be 1 + 4 = 5.</p>

* **Won:**&nbsp;&nbsp;&nbsp;&nbsp;The amount won is added at the end of notes.
* **Lost:**&nbsp;&nbsp;&nbsp;&nbsp;The first and last items from notes are deleted.
* **Special case:**&nbsp;&nbsp;&nbsp;&nbsp;If only one item remains in notes, then the player bet that item.

<p>&nbsp;</p>
<p>Bets has a minimum of 5 and a maximum of 4000.</p>
<p>If player could not bet because the bet is out of range or no item left in notes, starts again with initial notes { 1, 2, 3, 4 }.</p>

<p>When the game ends, balance of each player and total (of 6 players) is showed.</p>
<p>Oh, players are lucky, they have infinite money to bet :).</p>

## Project
This project was developed in C++ using:
* WSL (Ubuntu 20.04 LTS).
* CMake (version 3.16.3).
* GNU Make 4.2.1. Built for x86_64-pc-linux-gnu.
* g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0.
* GNU gdb (Ubuntu 9.2-0ubuntu1~20.04.1) 9.2.

### Structure
On repository folder you should find:
* include/
    * appGeneralMacros.h
    * casino.h
    * outputmanager.h
    * roulette.h
    * rouletteplayer.h
* src/
    * casino.cpp
    * outputmanager.cpp
    * roulette.cpp
    * rouletteplayer.cpp
* build/
    * CMakeFiles/
    * cmake_install.cmake
    * CMakeCache.txt
    * MakeFile
    * rouletteGame
* output/
    * rouletteGameOutput.txt
* rouletteGame.cpp
* CMakeLists.txt

### Build

For build this project you must have CMake (and make) installed. Follow this steps:
0. Go to repositroy directory.
1. Go to build directory:
    * ls build/
2. Clean directory. **Be careful, you are going to delete everyting in folder, be sure to be at build directory (and do not forget the . preceding the / )**:
    * rm -r ./*
3. Run cmake, this should generate the new files in build folder:
    * cmake ../
4. Run make, this should generate application executable:
    * make
5. You just generate the rouletteGame application executable.

## How to run

<p>In build folder you should find the rouletteGame executable.</p>
<p>A help of how to execute it is displayed if you executed with --help or -h argument.</p>
