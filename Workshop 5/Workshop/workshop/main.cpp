#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <algorithm>
#include "room.hpp"
#include "player.hpp"
#include <windows.h>


// --- SCORE FUNCTIES ---
typedef struct _scoreInfo
{
    unsigned int points;
    uint8_t   playerNo;
    std::string name;

}ScoreInfo;

static ScoreInfo scoreInfo = { 0, 1, "Player One have Fun" };


// Score bijwerken en tonen in console
void updateScoreConsole(int points) {
    scoreInfo.points += points;
    std::cout << "[Score] " << scoreInfo.points << "\n";
}

// Score bijwerken maar niet tonen (stil)
void updateScoreSilent(int points) {
    scoreInfo.points += points;
}

void showPuzzel(std::string room)
{
	if (room == "startKamer")
	{
		std::cout << R"(
            ___________________________________________________
            / \                                                  \
            |   |                                                  |
            \_ |                                                  |
            |                                                  |
            |                                                  |
            |                                                  |
            |  6 8 2 (One number is correct and well placed)   |
            |  6 1 4 (One number is correct but wrong placed)  |
            |  2 0 6 (Two number is correct but wrong placed)  |
            |  7 3 8 (Nothing is correct)                      |
            |  7 8 0 (One number is correct but wrong placed)  |
            |                                                  |
            |                                                  |
            |                                                  |
            |                                                  |
            |   _______________________________________________|___
            |  /                                                  /
            \_/__________________________________________________/
        )" << '\n';
	}
    else if (room == "raadselKamer")
    {
		std::cout << "           _     _                _\n";
		std::cout << "|_   _|   |_|.  |_|.  _|   |_|   |    \/\n";
    }
}

//___________________________________  
//| _____s|  v| ___ |g___ ___e| |  l|t|
//| |m  | |_| |__r| |_|e__|____a| | | |
//| | | |_________|__ |______ |___|_| |
//| |_|k  |g_______i|______s|   |c____|
//|l___ |e|____n| |______ | |_|z|____e|
//|___|_|____ | |v  ___m|s|________g| |
//|b  ________|i| |__u| |______c| | | |
//| | |h________| |o__|____e|r| | __|r|
//|_| |__t|  e|___|__ |g____| | |_|r__|
//|  o____|i| |____t| |__ |  i|__o|__ |
//|n|_______|_______|___|___|___|_____|





int main() {
    // Functiepointer kiezen: of console log, of stil
    void (*updateScore)(int);
    bool debugMode = true; // zet op false om score stil bij te houden

    bool codeKamerOpen = false;
    bool slotKamerOpen = false;

    if (debugMode) {
        updateScore = &updateScoreConsole;
    }
    else {
        updateScore = &updateScoreSilent;
    }

    // Kamers maken
    auto startKamer = std::make_shared<Room>("Start kamer", "Een lege kamer met een bureau en een gesloten deur");
    auto raadselKamer = std::make_shared<Room>("Raadselkamer", "Op de muur staat een puzzel");
    auto codeKamer = std::make_shared<Room>("Codekamer", "Een kamer met een elektronisch slot en cijfers op de muur.");
    auto slotKamer = std::make_shared<Room>("Slotkamer", "Een grote GROTE deur met een magisch slot.");

	startKamer-> exits["raadselKamer"] = raadselKamer;
	raadselKamer->exits["startKamer"] = startKamer;
	raadselKamer->exits["codeKamer"] = codeKamer;
	codeKamer->exits["raadselKamer"] = raadselKamer;
	codeKamer->exits["slotKamer"] = slotKamer;
    slotKamer->exits["codeKamer"] = codeKamer;

	startKamer->items = { "Notitieboekje met hints" };
    raadselKamer->items = { "Sleutel1" };
    codeKamer->items = { "Sleutel2" };
    slotKamer->items = { "Sleutel1 + Sleutel2 om te ontsnappen." };

    // Verbindingen leggen
    //lobby->exits["west"] = apotheek;
    // Items plaatsen
    //apotheek->items = { "MedicatieA", "MedicatieB" };

    /*
     *      [SLOT]                                          [HINTS]
     *⠀⠀⠀⠀⠀ ⢀⣀⣠⣤⣤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                         6 8 2 (One number is correct and well placed)
⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀                          6 1 4 (One number is correct but wrong placed)
⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⠟⠋⠁⠀⠀⠈⠙⠻⣿⣿⣷⡄⠀⠀⠀⠀⠀⠀⠀                          2 0 6 (Two number is correct but wrong placed)
⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀                          7 3 8 (Nothing is correct)
⠀⠀⠀⠀⠀⠀⢸⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⡇⠀⠀⠀⠀⠀⠀Code (4 cijfers):         7 8 0 (One number is correct but wrong placed)
⠀⠀⠀⠀⠀⠀⢸⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢸⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢀⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⡀⠀⠀⠀⠀
⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀-- -- -- --
⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀
⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀
⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠈⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠁⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠛⠛⠛⠛⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
     */

    // Speler aanmaken
    Player robot;
    robot.currentRoom = startKamer;

    std::cout << "Welkom in de escape room! Je missie: escape the room\n";
    std::cout << "Commando's: ga <richting>, pak <item>, inventaris, lever <item>, stop\n";

    bool running = true;
    

    while (running) {
        robot.currentRoom->showInfo();

        std::cout << "\n> ";
        std::string command, arg;
        std::cin >> command;

        if (command == "ga") {
            std::cin >> arg;
            if (robot.currentRoom->exits.count(arg)) {
                // Check toegang slotkamer
                if (robot.currentRoom->exits[arg] == codeKamer && codeKamerOpen == false) {
                    std::cout << "De deur naar deze kamer is vergrendeld.\n";
                }
                else if (robot.currentRoom->exits[arg] == slotKamer && slotKamerOpen == false) {
                    std::cout << "De deur naar deze kamer is vergrendeld.\n";
                }
                else {
                    robot.currentRoom = robot.currentRoom->exits[arg];
                }
            }

            else {
                std::cout << "Geen uitgang in die richting.\n";
            }
        }
        else if (command == "puzzel" && robot.currentRoom == codeKamer)
        {
            std::cout << "test";
        }
        else if (command == "pak") {
            std::cin >> arg;
            robot.pickUp(arg);
            updateScore(5); // punten voor item oppakken
        }
        else if (command == "inventaris") {
            robot.showInventory();
        }
        else if (command == "open") {
            std::cin >> arg;
            if (robot.currentRoom == slotKamer) {
                if (arg == "Sleutel1" && robot.hasItem("Sleutel1")) {
                    std::cout << "De deur van de code kamer is geopend. Goed gedaan!\n";
                    codeKamerOpen = true;
                    updateScore(20);
                }
                else if (arg == "Sleutel2" && robot.hasItem("Sleutel2")) {
                    std::cout << "De deur van de slot kamer is geopend. Goed gedaan!.\n";
                    slotKamerOpen = true;
                    updateScore(20);
                    break;
                }
                else {
                    std::cout << "Je hebt dat item niet.\n";
                }
            }
            else if (robot.currentRoom == raadselKamer)
            {
                if (robot.hasItem("Sleutel1"))
                {
                    std::cout << "De deur naar de code kamer is ontgrendeld..\n";
                    codeKamerOpen = true;
                }
            }
            else if (robot.currentRoom == codeKamer) {
                if (robot.hasItem("Sleutel2")) {
                    std::cout << "De deur naar de slotkamer is ontgrendeld..\n";
                    slotKamerOpen = true;
                    // robot.showAsciiArt();
                    // updateScore(50);
                    break;
                }
                else {
                    std::cout << "Je kunt dat hier niet afleveren.\n";
                }
            }
            else {
                std::cout << "Hier kun je niets afleveren.\n";
            }
        }
        else if (command == "stop") {
            std::cout << "Spel beeindigd.\n";
            running = false;
        }
        else {
            std::cout << "Onbekend commando.\n";
        }
    }
    std::cout << "\nEindscore: " << scoreInfo.points << "\n";
    return 0;

}
