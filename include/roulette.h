#ifndef ROULETTE_H
#define ROULETTE_H

#include "rouletteplayer.h"
#include "appgeneralmacros.h"

#define PLAYS_DEFAULT_QTY       10000

typedef struct rouletteNumber{
    int number;
    bool even;
    bool red;
    bool minor;
}rouletteNumber;

class Roulette{

    public:

        Roulette(int _id);
        ~Roulette();

        void open();	// enable roulette for play
		void close();	// disable roulette for play
		bool isEnabled() const;	// returns if roulette is enabled or not
        int getRouletteId() const;  // returns roulette id

		void play(int plays = PLAYS_DEFAULT_QTY);	// receive from casino how many times it must play, check if it is enabled and if there are players on roulette, if there are then spin, gets number, check winner, etc

		bool addPlayer(RoulettePlayer& RoulettePlayer);	// adds a player to the table (players vector)

	private:

		std::vector<rouletteNumber> rouletteNumbers;	// maybe initialized it on constructor
		bool enabled;	// keep track if roulette is enabled or not
        int id;

		std::vector<RoulettePlayer*> players;	// initialize in constructor

        void initializeRouletteNumbers();
        int spin(); // returns the number between 0 and 36, if there was a problem with the random function it will return a int < 0
		void checkWinners(rouletteNumber _number);		// check if player won or lost -> calls won or lost from RoulettePlayer
        void nobodyWon();
        void tellPlayersToGetOut();
        void showNumberInformation(rouletteNumber _number);
        void showPlayersNotes();
};

#endif