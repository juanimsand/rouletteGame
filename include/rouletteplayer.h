#ifndef ROULETTEPLAYER_H
#define ROULETTEPLAYER_H

#include <string>
#include <vector>
#include <iostream>

#include "appgeneralmacros.h"

#define INITIAL_BALANCE -10
#define INITIAL_BET 5
#define MAX_BET 4000
#define MIN_BET 5
#define RANGE_MIN 0
#define RANGE_MAX 36

typedef enum rouletteBetType
{
    EVEN = 0,
    ODD,
    _1_TO_18,
    _19_TO_36,
    RED,
    BLACK
} rouletteBetType;

class RoulettePlayer
{

public:
    RoulettePlayer(rouletteBetType _type, int _playerId, std::string _name);
    ~RoulettePlayer();

    void changeBetType(rouletteBetType newBetType);
    rouletteBetType getBetType() const;
    void won();
    void lost();
    void bet();              // allows the player to bet in roulette (expected call from roullete)
    void getOutOfRoulette(); // player will leave roulette
    int getPlayerBalance() const;
    int getPlayerId() const;
    std::string getPlayerName() const;

    void showNotes();

private:
    int playerId;     // player id for let Casino keep track of players
    std::string name; // lets name players as Player A, Player B, etc.
    rouletteBetType betType;
    std::vector<int> notes; // notes for store earned money and for determine how much the player will bet in next roulette spin
    int currentRouletteBet; // current player bet
    int rouletteBalance;    // keep track of roulette player balance

    void resetNotes();                            // set notes with initial value { 1, 2, 3, 4 }
    void updateRouletteBalance(int addToBalance); // add argument to roulette balance
    void updateTotalNotesToBalance();
    std::string getBetTypeString();
};
#endif