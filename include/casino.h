#ifndef CASINO_H
#define CASINO_H

#include "roulette.h"
#include "outputmanager.h"

class Casino{

    public:

        Casino();
        ~Casino();

        void open();
		void close();
		bool isOpen() const;

        void setOutputManager(OutputManager& outputMan);

        bool joinRoulette(RoulettePlayer &player);	// take player by reference or a copy? maybe by reference is better -> check that!
												    // check if a roulette from roulettes vector is available and add player to it
        
        void openRoulettes();
        void openRoulette(int rouletteId);
        void playRoulettes();		// start every roulette if roulettes are not already started
		void playRoulette(int rouletteId);	// start roulette with id = rouletteId it must be the index of roulettes vector

	private:

		bool opened = false;	// keep track if casino is open or not! maybe is better to initialized it on constructor
		std::vector<Roulette> roulettes;	// maybe is beter to set it in the constructor
        OutputManager* outputManager;

        void initializeGames();
        void initializeRoulettes();
        void closeGames();
        void closeRoulettes();

};



#endif