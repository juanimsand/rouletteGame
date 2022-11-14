#include "roulette.h"
#include <random>

Roulette::Roulette(int _id)
{
    outputManager = nullptr;
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
        if(i < 19){ // it is minor
            rouletteNumbers[i].minor = true;
        }
        else{
            rouletteNumbers[i].minor = false;
        }
        if((i % 2) == 0){   // it is even
            rouletteNumbers[i].even = true;
        }
        else{
            rouletteNumbers[i].even = false;
        }
        if((i < 10) && (rouletteNumbers[i].even == false)){ // lower than 10 and odd, then is red
            rouletteNumbers[i].red = true;
        }
        else if((i > 10) && (i < 19) && (rouletteNumbers[i].even == true)){    // greater than 10, lower than 19 and even, then is red
            rouletteNumbers[i].red = true;
        }
        else if((i > 18) && (i < 29) && (rouletteNumbers[i].even == false)){    // greater than 10, lower than 19 and odd, then is red
            rouletteNumbers[i].red = true;
        }
        else if((i > 28) && (rouletteNumbers[i].even == true)){    // greater than 28 and even, then is red
            rouletteNumbers[i].red = true;
        }
        else{   // is black
            rouletteNumbers[i].red = false;
        }
    }
    return;
}

void Roulette::open()
{
    if(!enabled){
        enabled = true;
        if(outputManager){
            // show roulette is opened message
            outputManager->showRouletteOpened(id);
        }
    }
    else{
        if(outputManager){
            // show roulette is already open message
            outputManager->showRouletteAlreadyOpen(id);
        }
    }
    return;
}

void Roulette::close()
{
    if(enabled){
        // tells players on roulette
        tellPlayersToGetOut();
        enabled = false;
        if(outputManager){
            // show roulette is closed message
            outputManager->showRouletteClosed(id);
        }
    }
    else{
        if(outputManager){
            // show roulette is already close message
            outputManager->showRouletteAlreadyClose(id);
        }
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

void Roulette::setOutputManager(OutputManager& outputMan)
{
    outputManager = &outputMan;
    return;
}

void Roulette::play(int plays)
{
    if(!enabled){
        if(outputManager){
            // throw output showing error and return
            outputManager->showCouldNotPlayDueToClose(id);
        }
        return;
    }
    if(players.empty()){
        if(outputManager){
            // throw output showing error and return
            outputManager->showCouldNotPlayDueToLackOfPlayers(id);
        }
        return;
    }
    if(outputManager){
        outputManager->showStartingRoulette(id);
    }
    for(int i = 0; i < plays; i++){ // play sequence for every iteration
        if(outputManager){  // show play number
            outputManager->showRoulettePlayNumber(id, (i + 1));
        }
        if(i == (plays - 1)){
            if(outputManager){
                outputManager->showLastRoulettePlay(id);
            }
        }
        if(outputManager){  // show ask for bets
            outputManager->showPlaceBets();
        }
        for(int j = 0; j < players.size(); j++){    // ask for bets
            players[j]->bet();
        }
        if(outputManager){  // show spinning state
            outputManager->showNoMoreBets();
            outputManager->showRouletteSpinning();
        }
        int number = spin();
        if(number < 0){
            if(outputManager){  //show error while spinning, nobody won, nobody lost and continue
                outputManager->showBallFlangOut();
            }
            continue;
        }
        if(number == 0){    // then nobody won
            if(outputManager){  // show 0 number status
                outputManager->showHouseWins();
            }
            nobodyWon();
            // show players notes
            showPlayersNotes();
            continue;
        }
        if(outputManager){  // show number information
            outputManager->showWinnerNumber(number, rouletteNumbers[number].red);
        }
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
                if(_number.even){   // winner
                    players[i]->won();
                }
                else{   // lost
                    players[i]->lost();
                }
                break;
            case rouletteBetType::ODD:
                if(!_number.even){   // winner
                    players[i]->won();
                }
                else{   // lost
                    players[i]->lost();
                }
                break;
            case rouletteBetType::_1_TO_18:
                if(_number.minor){   // winner
                    players[i]->won();
                }
                else{   // lost
                    players[i]->lost();
                }
                break;
            case rouletteBetType::_19_TO_36:
                if(!_number.minor){   // winner
                    players[i]->won();
                }
                else{   // lost
                    players[i]->lost();
                }
                break;
            case rouletteBetType::RED:
                if(_number.red){   // winner
                    players[i]->won();
                }
                else{   // lost
                    players[i]->lost();
                }
                break;
            case rouletteBetType::BLACK:
                if(!_number.red){   // winner
                    players[i]->won();
                }
                else{   // lost
                    players[i]->lost();
                }
                break;
            default:
                if(outputManager){
                    outputManager->showBadPlayerType();
                }
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
    if(outputManager){  // show number information
        outputManager->showNumberInfo(_number.number, _number.red, _number.even, _number.minor);
    }
    return; 
}

void Roulette::showPlayersNotes()
{
    // show players notes
    if(outputManager){
        outputManager->showPlayerNotesTitle();
    }
    for(int j = 0; j < players.size(); j++){
        players[j]->showNotes();
    }
    return;
}