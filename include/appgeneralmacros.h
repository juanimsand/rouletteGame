#ifndef APPGENERALMACROS_H
#define APPGENERALMACROS_H

// Definition of non specific application macros

#define OUTPUT_FILE_PATH                    "../output/rouletteGameOutput.txt"

#define HELP_OPTION                         "--help"
#define HELP_SHORTCUT_OPTION                "-h"
#define SAVE_TO_FILE_OPTION                 "--toFile"
#define BAD_ARGUMENTS                       "Bad argumets! Execute it with --help or -h argument for help!"

#define WELCOME_TEXT                        "\n************************* ROULETTE GAME *************************\n"
#define GOOD_BYE_TEXT                       "\n************************* GOOD BYE! THANKS FOR PLAYING *************************\n"
#define HELPER_TEXT                         "Simulation of 6 players playing the famous roulette game! Each player bet to: even, odd, 1 to 18, 19 to 36, red or black, respectively!\n\
After 10000 plays, total balance of 6 players is showed and quit!\n\
Each player has own notes for calculate how much they will bet on each roulette play, starting notes { 1, 2, 3, 4 }.\n\
Bet calculation is: addition of first and last number in notes. First bet will be 1 + 4 = 5.\n\n\
\tWon: The amount won is added at the end of notes.\n\
\tLost: The first and last items from notes are deleted.\n\
\tSpecial case: If only one item remains in notes, then the player bet that item.\n\n\
Bets has a minimum of 5 and a maximum of 4000.\n\
If player could not bet because the bet is out of range or no item left in notes, starts again with initial notes { 1, 2, 3, 4 }.\n\
When the game ends, balance of every player and total (of 6 players) is showed.\n\n\
Oh, those players are lucky, they have infinite money to bet :).\n\n\
--help | -h\t\t\t\t\tPrints help.\n\n\
--toFile\t\t\t\t\tSave output to file ../output/rouletteGameOutput.txt. If no argument is set, print output to console.\n\n"

// casino
#define CASINO_ALREADY_OPENED               "Casino is already open!"
#define OPENING_CASINO                      "Opening casino!"
#define CASINO_OPENED                       "Casino opened!"
#define CASINO_ALREADY_CLOSED               "Casino is already close!"
#define CLOSING_CASINO                      "Closing casino!"
#define CASINO_CLOSED                       "Casino closed!"
#define COULD_NOT_JOIN_ROULETTE_BY_CASINO   "Sorry, Casino is closed! It is not possible to join a roulette at the moment."
#define CLOSING_ALL_GAMES                   "Closing all games!"


// roulette
#define PLACE_YOUR_BETS                     "Place your bets please.."
#define NO_MORE_BETS                        "No more bets, thank you!"
#define ROULETTE_SPINNING                   "Roulette spinning.."
#define BALL_FLANG_OUT_ROULETTE             "Ball flang out of roulette while spinning!"
#define HOUSE_WINS                          "0, house wins!"
#define BAD_PLAYER_TYPE                     "Bad player type! Did not won nor lost!"
#define SHOWING_PLAYER_NOTES                "*** Showing player notes ***"


// roulette player
#define EVEN_STRING             "even"
#define ODD_STRING              "odd"
#define RED_STRING              "red"
#define BLACK_STRING            "black"
#define MINOR_STRING            "1 to 18"
#define MAJOR_STRING            "19 to 36"

#endif