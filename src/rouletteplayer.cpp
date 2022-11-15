#include "rouletteplayer.h"

RoulettePlayer::RoulettePlayer(rouletteBetType _type, int _playerId, std::string _name)
{
    outputManager = nullptr;
    betType = _type;
    playerId = _playerId;
    name = _name;
    rouletteBalance = 0;
    resetNotes();
}

RoulettePlayer::~RoulettePlayer(){}

void RoulettePlayer::changeBetType(rouletteBetType newBetType)
{
    betType = newBetType;
    return;
}

void RoulettePlayer::setOutputManager(OutputManager& outputMan)
{
    outputManager = &outputMan;
    return;
}

rouletteBetType RoulettePlayer::getBetType() const
{
    return betType;
}

void RoulettePlayer::won()
{
    if(outputManager){
        // show won message
        outputManager->showPlayerWon(name, playerId, getBetTypeString(), currentRouletteBet);
    }
    notes.push_back(currentRouletteBet);
    return;
}

void RoulettePlayer::lost()
{
    if(outputManager){
        // show lost message
        outputManager->showPlayerLost(name, playerId, getBetTypeString(), currentRouletteBet);
    }
    if(notes.size() > 0){
        if(notes.size() == 1){
            notes.erase(notes.begin());
        }
        else{
            notes.pop_back();
            notes.erase(notes.begin());
        }
    }
    return;
}

void RoulettePlayer::bet()
{
    if(notes.empty()){
        if(outputManager){
            // show player is out of money
            outputManager->showPlayerOutOfMoney(name);
        }
        resetNotes();
    }
    else if(notes.size() == 1){
        if((notes[0] <= MAX_BET) && (notes[0] >= MIN_BET)){   // bet is valid
            currentRouletteBet = notes[0];
        }
        else{
            if(outputManager){
                // show player bet is out of range
                outputManager->showPlayerBetOutOfRange(name, notes[0]);
            }            
            updateRouletteBalance(notes[0]);
            resetNotes();
        }
    }
    else{
        int possibleNextBet = notes[0] + notes[notes.size() - 1];
        if((possibleNextBet <= MAX_BET) && (possibleNextBet >= MIN_BET)){   // bet is valid
            currentRouletteBet = possibleNextBet;
        }
        else{
            if(outputManager){
                // show player bet is out of range
                outputManager->showPlayerBetOutOfRange(name, possibleNextBet);
            } 
            updateTotalNotesToBalance();
            resetNotes();
        }
    }
    return;
}

void RoulettePlayer::getOutOfRoulette()
{
    // update balance
    updateTotalNotesToBalance();
    return;
}

int RoulettePlayer::getPlayerBalance() const
{
    return rouletteBalance;
}

void RoulettePlayer::showNotes()
{
    if(outputManager){
        // show notes
        outputManager->showPlayerNotes(name, notes);
    }
    return;
}

void RoulettePlayer::resetNotes()
{
    notes = {1, 2, 3, 4};
    updateRouletteBalance(INITIAL_BALANCE);
    currentRouletteBet = INITIAL_BET;
    return;
}

void RoulettePlayer::updateRouletteBalance(int addToBalance)
{
    rouletteBalance += addToBalance;
    if(outputManager){
        outputManager->showPlayerBalanceUpdated(name, rouletteBalance);
    }
    return;
}

void RoulettePlayer::updateTotalNotesToBalance()
{
    int total = 0;
    for(int i = 0; i < notes.size(); i++){
        total += notes[i];
    }
    updateRouletteBalance(total);
    return;
}

std::string RoulettePlayer::getBetTypeString()
{
    std::string typeString = "undefined";
    switch (betType){
        case rouletteBetType::EVEN:
            typeString = EVEN_STRING;
            break;
        case rouletteBetType::ODD:
            typeString = ODD_STRING;
            break;
        case rouletteBetType::_1_TO_18:
            typeString = MINOR_STRING;
            break;
        case rouletteBetType::_19_TO_36:
            typeString = MAJOR_STRING;
            break;
        case rouletteBetType::RED:
            typeString = RED_STRING;
            break;
        case rouletteBetType::BLACK:
            typeString = BLACK_STRING;
            break;
        default:
            if(outputManager){
                outputManager->showPlayerBetTypeUndefined(name);
            }
            break;
    }
    return typeString;
}