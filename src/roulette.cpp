#include "roulette.h"
#include <random>

Roulette::Roulette(int _id)
{
    id = _id;
    initializeRouletteNumbers();
}

Roulette::~Roulette(){}

void Roulette::initializeRouletteNumbers()
{
    rouletteNumbers = std::vector<rouletteNumber>(37);

    rouletteNumbers[0].number = 0;
    rouletteNumbers[0].even = false;
    rouletteNumbers[0].red = false;
    rouletteNumbers[0].minor = false;

    for(int i = 1; i < rouletteNumbers.size(); i++){
        rouletteNumbers[i].number = i;
        rouletteNumbers[i].minor = (i < 19);
        rouletteNumbers[i].even = ((i % 2) == 0);
        rouletteNumbers[i].red = (  ((i < 10) && (rouletteNumbers[i].even == false)) ||
                                    ((i > 10) && (i < 19) && (rouletteNumbers[i].even == true)) ||
                                    ((i > 18) && (i < 29) && (rouletteNumbers[i].even == false)) ||
                                    ((i > 28) && (rouletteNumbers[i].even == true)) );
    }
    return;
}

void Roulette::open()
{
    if(!enabled){
        enabled = true;
        // show roulette is opened message
        std::cout << "Roulette " << id << " opened!" << std::endl;
    }
    else{
        // show roulette is already open message
        std::cout << "Roulette " << id << " is already open!" << std::endl;
    }
    return;
}

void Roulette::close()
{
    if(enabled){
        // tells players on roulette
        tellPlayersToGetOut();
        enabled = false;
        // show roulette is closed message
        std::cout << "Roulette " << id << " closed!" << std::endl;
    }
    else{
        std::cout << "Roulette " << id << " is already close!" << std::endl;
    }
    return;
}

bool Roulette::isEnabled() const
{
    return enabled;
}

int Roulette::getRouletteId() const
{
    return id;
}

void Roulette::play(int plays)
{
    if(!enabled){
        // throw output showing error and return
        std::cout << "Roulette " << id << " is closed, could not play." << std::endl;
        return;
    }
    if(players.empty()){
        // throw output showing error and return
        std::cout << "Roulette " << id << " has no players to play." << std::endl;
        return;
    }
    std::cout << "Starting roulette number " << id << ".." << std::endl;
    for(int i = 0; i < plays; i++){ // play sequence for every iteration
        // show play number
        std::cout << "Roulette " << id << " play number " << (i + 1) << std::endl;
        if(i == (plays - 1)){
            std::cout << "Last roulette " << id << " play.." << std::endl;
        }
        // show place bets
        std::cout << PLACE_YOUR_BETS << std::endl;
        for(int j = 0; j < players.size(); j++){    // ask for bets
            players[j]->bet();
        }
        // show spinning state
        std::cout << NO_MORE_BETS << std::endl;
        std::cout << ROULETTE_SPINNING << std::endl;
        int number = spin();
        if(number < 0){
            std::cout << BALL_FLANG_OUT_ROULETTE << std::endl;
            continue;
        }
        if(number == 0){    // then nobody won
            // show house wins
            std::cout << HOUSE_WINS << std::endl;
            nobodyWon();
            // show players notes
            showPlayersNotes();
            continue;
        }
        // show number
        rouletteNumbers[number].red ? std::cout << number << ", red!" << std::endl : std::cout << number << ", black!" << std::endl;
        checkWinners(rouletteNumbers[number]);
        // show players notes
        showPlayersNotes();
    }
    return;
}

bool Roulette::addPlayer(RoulettePlayer& RoulettePlayer)
{
    bool playerAdded = false;
    if(enabled){
        players.push_back(&RoulettePlayer);
        playerAdded = true;
    }
    return playerAdded;
}

int Roulette::spin()
{
    // random logic from https://learn.microsoft.com/en-us/cpp/standard-library/random?view=msvc-170
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> dist(RANGE_MIN, RANGE_MAX); // distribute results between RANGE_MIN and RANGE_MAX inclusive.
    int number = dist(gen);
    // check number is not out of range
    if((number < RANGE_MIN) || (number > RANGE_MAX)){
        return -1;
    }
    return number;
}

void Roulette::checkWinners(rouletteNumber _number)
{
    // show number data (struct members)
    showNumberInformation(_number);
    for(int i = 0; i < players.size(); i++){
        switch (players[i]->getBetType()){
            case rouletteBetType::EVEN:
                _number.even ? players[i]->won() : players[i]->lost();
                break;
            case rouletteBetType::ODD:
                _number.even ? players[i]->lost() : players[i]->won();
                break;
            case rouletteBetType::_1_TO_18:
                _number.minor ? players[i]->won() : players[i]->lost();
                break;
            case rouletteBetType::_19_TO_36:
                _number.minor ? players[i]->lost() : players[i]->won();
                break;
            case rouletteBetType::RED:
                _number.red ? players[i]->won() : players[i]->lost();
                break;
            case rouletteBetType::BLACK:
                _number.red ? players[i]->lost() : players[i]->won();
                break;
            default:
                std::cout << BAD_PLAYER_TYPE << std::endl;
                break;
        }
    }
    return;
}

void Roulette::nobodyWon()
{
    for(int j = 0; j < players.size(); j++){    // announce lost
        players[j]->lost();
    }
    return;
}

void Roulette::tellPlayersToGetOut()
{
    for(int i = 0; i < players.size(); i++){
        players[i]->getOutOfRoulette();
    }
    return;
}

void Roulette::showNumberInformation(rouletteNumber _number)
{
    // show number information
    std::cout << "*** Number " << _number.number << " information ***" << std::endl;
    _number.red ? std::cout << RED_STRING << std::endl : std::cout << BLACK_STRING << std::endl;
    _number.even ? std::cout << EVEN_STRING << std::endl : std::cout << ODD_STRING << std::endl;
    _number.minor ? std::cout << MINOR_STRING << std::endl : std::cout << MAJOR_STRING << std::endl;
    return; 
}

void Roulette::showPlayersNotes()
{
    // show players notes
    std::cout << SHOWING_PLAYER_NOTES << std::endl;
    for(int j = 0; j < players.size(); j++){
        players[j]->showNotes();
    }
    return;
}