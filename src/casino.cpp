#include "casino.h"

Casino::Casino()
{
    outputManager = nullptr;
    initializeGames();
}

Casino::~Casino(){}

void Casino::open()
{
    if(opened){
        if(outputManager){
            outputManager->showCasinoAlreadyOpen();
        }
        return;
    }
    if(outputManager){
        outputManager->showOpeningCasino();
    }
    opened = true;
    if(outputManager){
        // show casino is open!
        outputManager->showCasinoOpened();
    }
    return;
}

void Casino::close()
{
    std::cout << std::endl;
    if(!opened){
        if(outputManager){
            outputManager->showCasinoAlreadyClose();
        }
        return;
    }
    if(outputManager){
        outputManager->showClosingCasino();
    }
    // close all games
    closeGames();
    opened = false;
    if(outputManager){
        outputManager->showCasinoClosed();
    }
    return;
}

bool Casino::isOpen() const
{
    return opened;
}

void Casino::setOutputManager(OutputManager& outputMan)
{
    outputManager = &outputMan;
    return;
}

bool Casino::joinRoulette(RoulettePlayer& player)
{
    bool couldJoin = false;
    if(!opened){
        if(outputManager){
            outputManager->showCouldNotJoinByCasino();
        }
        return couldJoin;
    }
    if(roulettes.empty()){
        if(outputManager){
            // show no roulettes to join availables at the moment message
            outputManager->showCouldNotJoinByRouletteAvailable(player.name);
        }
        return couldJoin;
    }
    for(int i = 0; i < roulettes.size(); i++){
        if(roulettes[i].isEnabled()){
            couldJoin = roulettes[i].addPlayer(player);
            if(couldJoin){
                if(outputManager){
                    outputManager->showPlayerHasJoinedRoulette(player.name, roulettes[i].getRouletteId());
                }
                break;
            }
        }
    }
    if(!couldJoin){
        if(outputManager){
            outputManager->showCouldNotJoinByRouletteClosed(player.name);
        }
    }
    return couldJoin;
}

void Casino::openRoulettes()
{
    for(int i = 0; i < roulettes.size(); i++){
        openRoulette(i);
    }
    return;
}

void Casino::openRoulette(int rouletteId)
{
    if((rouletteId >= 0) && (rouletteId < roulettes.size())){
        roulettes[rouletteId].setOutputManager(*outputManager);
        roulettes[rouletteId].open();
    }
    return;
}

void Casino::playRoulettes()
{
    for(int i = 0; i < roulettes.size(); i++){
        playRoulette(i);
    }
    return;
}

void Casino::playRoulette(int rouletteId)
{
    if((rouletteId >= 0) && (rouletteId < roulettes.size())){
        roulettes[rouletteId].play();
    }
    return;
}

void Casino::initializeGames()
{
    initializeRoulettes();
    return;
}

void Casino::initializeRoulettes()
{
    int newRouletteId = roulettes.size();
    Roulette roulette(newRouletteId);
    roulettes.push_back(roulette);
    return;
}

void Casino::closeGames()
{
    if(outputManager){
        // show closing games message
        outputManager->showClosingAllGames();
    }
    closeRoulettes();
    return;
}

void Casino::closeRoulettes()
{
    for(int i = 0; i < roulettes.size(); i++){
        roulettes[i].close();
    }
    return;
}