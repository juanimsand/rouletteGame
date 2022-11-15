#include "casino.h"

Casino::Casino()
{
    initializeGames();
}

Casino::~Casino() {}

void Casino::open()
{
    if (opened)
    {
        std::cout << CASINO_ALREADY_OPENED << std::endl;
        return;
    }
    std::cout << OPENING_CASINO << std::endl;
    opened = true;
    std::cout << CASINO_OPENED << std::endl;
    return;
}

void Casino::close()
{
    if (!opened)
    {
        std::cout << CASINO_ALREADY_CLOSED << std::endl;
        return;
    }
    std::cout << CLOSING_CASINO << std::endl;
    // close all games
    closeGames();
    opened = false;
    std::cout << CASINO_CLOSED << std::endl;
    return;
}

bool Casino::isOpen() const
{
    return opened;
}

bool Casino::addPlayerToRoulette(std::shared_ptr<RoulettePlayer> &player)
{
    bool couldJoin = false;
    if (!opened)
    {
        std::cout << COULD_NOT_JOIN_ROULETTE_BY_CASINO << std::endl;
        return couldJoin;
    }
    if (roulettes.empty())
    {
        std::cout << "Sorry " << player->getPlayerName() << ", there are no roulettes availables at the moment." << std::endl;
        return couldJoin;
    }
    for (int i = 0; i < roulettes.size(); i++)
    {
        if (roulettes[i].isEnabled())
        {
            couldJoin = roulettes[i].addPlayer(player);
            if (couldJoin)
            {
                std::cout << player->getPlayerName() << " has joined roulette " << roulettes[i].getRouletteId() << "." << std::endl;
                break;
            }
        }
    }
    if (!couldJoin)
    {
        std::cout << "Sorry " << player->getPlayerName() << ", no roulette open at the moment." << std::endl;
    }
    return couldJoin;
}

void Casino::openRoulettes()
{
    for (int i = 0; i < roulettes.size(); i++)
    {
        openRoulette(i);
    }
    return;
}

void Casino::openRoulette(int rouletteId)
{
    if ((rouletteId >= 0) && (rouletteId < roulettes.size()))
    {
        roulettes[rouletteId].open();
    }
    return;
}

void Casino::playRoulettes()
{
    for (int i = 0; i < roulettes.size(); i++)
    {
        playRoulette(i);
    }
    return;
}

void Casino::playRoulette(int rouletteId)
{
    if ((rouletteId >= 0) && (rouletteId < roulettes.size()))
    {
        roulettes[rouletteId].play(4);
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
    /*
    int newRouletteId = roulettes.size();
    Roulette roulette(newRouletteId);
    roulettes.push_back(roulette);
    */
    roulettes.push_back(Roulette(roulettes.size()));
    return;
}

void Casino::closeGames()
{
    // show closing games message
    std::cout << CLOSING_ALL_GAMES << std::endl;
    closeRoulettes();
    return;
}

void Casino::closeRoulettes()
{
    for (int i = 0; i < roulettes.size(); i++)
    {
        roulettes[i].close();
    }
    return;
}