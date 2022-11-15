#include "rouletteplayer.h"

RoulettePlayer::RoulettePlayer(rouletteBetType _type, int _playerId, std::string _name)
{
    betType = _type;
    playerId = _playerId;
    name = _name;
    rouletteBalance = 0;
    resetNotes();
}

RoulettePlayer::~RoulettePlayer() {}

void RoulettePlayer::changeBetType(rouletteBetType newBetType)
{
    betType = newBetType;
    return;
}

rouletteBetType RoulettePlayer::getBetType() const
{
    return betType;
}

void RoulettePlayer::won()
{
    // show won message
    std::cout << name << " (id: " << playerId << ") bet on " << getBetTypeString() << " and won " << currentRouletteBet << std::endl;
    notes.push_back(currentRouletteBet);
    return;
}

void RoulettePlayer::lost()
{
    // show lost message
    std::cout << name << " (id: " << playerId << ") bet on " << getBetTypeString() << " and lost " << currentRouletteBet << std::endl;
    if (notes.size() > 0)
    {
        if (notes.size() == 1)
        {
            notes.erase(notes.begin());
        }
        else
        {
            notes.pop_back();
            notes.erase(notes.begin());
        }
    }
    return;
}

void RoulettePlayer::bet()
{
    if (notes.empty())
    {
        // show player is out of money
        std::cout << name << " is out of money!" << std::endl;
        resetNotes();
    }
    else if (notes.size() == 1)
    {
        if ((notes[0] <= MAX_BET) && (notes[0] >= MIN_BET))
        { // bet is valid
            currentRouletteBet = notes[0];
        }
        else
        {
            // show player bet is out of range
            std::cout << name << " bet " << notes[0] << " is out of range!" << std::endl;
            updateRouletteBalance(notes[0]);
            resetNotes();
        }
    }
    else
    {
        int possibleNextBet = notes[0] + notes[notes.size() - 1];
        if ((possibleNextBet <= MAX_BET) && (possibleNextBet >= MIN_BET))
        { // bet is valid
            currentRouletteBet = possibleNextBet;
        }
        else
        {
            std::cout << name << " bet " << notes[0] << " is out of range!" << std::endl;
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
    // show notes
    std::cout << name << " notes are: ";
    if (notes.empty())
    {
        std::cout << "{ }" << std::endl;
        return;
    }
    std::cout << "{ ";
    for (int i = 0; i < notes.size(); i++)
    {
        std::cout << notes[i];
        if (i != (notes.size() - 1))
        {
            std::cout << ", ";
        }
        else
        {
            std::cout << " }" << std::endl;
        }
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
    std::cout << name << " balance updated. Balance is: " << rouletteBalance << std::endl;
    return;
}

void RoulettePlayer::updateTotalNotesToBalance()
{
    int total = 0;
    for (int i = 0; i < notes.size(); i++)
    {
        total += notes[i];
    }
    updateRouletteBalance(total);
    return;
}

std::string RoulettePlayer::getBetTypeString()
{
    std::string typeString = "undefined";
    switch (betType)
    {
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
        std::cout << name << " has bet type undefined!" << std::endl;
        break;
    }
    return typeString;
}