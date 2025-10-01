#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <algorithm>
#include "room.hpp"
#include "player.hpp"


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


int main() {
    // Functiepointer kiezen: of console log, of stil
    void (*updateScore)(int);
    bool debugMode = true; // zet op false om score stil bij te houden
    if (debugMode) {
        updateScore = &updateScoreConsole;
    }
    else {
        updateScore = &updateScoreSilent;
    }

    // Kamers maken
    auto lobby = std::make_shared<Room>("Lobby", "Centrale hal van het ziekenhuis.");
    auto apotheek = std::make_shared<Room>("Apotheek", "Hier liggen medicijnen in gekoelde kasten.");
    auto ic = std::make_shared<Room>("IC", "Een patient wacht op de juiste medicatie.");
    auto opslag = std::make_shared<Room>("Opslagruimte", "Een donkere ruimte vol met kasten en opladers.");
    auto ok = std::make_shared<Room>("Operatiekamer", "Chirurgen wachten op de juiste medicatie. De deur is beveiligd.");

    // Verbindingen leggen
    lobby->exits["west"] = apotheek;
    lobby->exits["oost"] = ic;
    lobby->exits["zuid"] = opslag;

    apotheek->exits["oost"] = lobby;
    ic->exits["west"] = lobby;
    opslag->exits["noord"] = lobby;
    opslag->exits["oost"] = ok;
    ok->exits["west"] = opslag;

    // Items plaatsen
    apotheek->items = { "MedicatieA", "MedicatieB" };
    opslag->items = { "Batterij", "Toegangskaart" };

    // Speler aanmaken
    Player robot;
    robot.currentRoom = lobby;

    std::cout << "Welkom zorgrobot! Je missie: lever de juiste medicijnen af.\n";
    std::cout << "Commando's: ga <richting>, pak <item>, inventaris, lever <item>, stop\n";

    bool running = true;
    bool medicatieA_gegeven = false;

    while (running) {
        robot.currentRoom->showInfo();

        std::cout << "\n> ";
        std::string command, arg;
        std::cin >> command;

        if (command == "ga") {
            std::cin >> arg;
            if (robot.currentRoom->exits.count(arg)) {
                // Check toegang operatiekamer
                if (robot.currentRoom->exits[arg] == ok && !robot.hasItem("Toegangskaart")) {
                    std::cout << "De deur naar de operatiekamer is vergrendeld. Je hebt een Toegangskaart nodig.\n";
                }
                else {
                    robot.currentRoom = robot.currentRoom->exits[arg];
                }
            }
            else {
                std::cout << "Geen uitgang in die richting.\n";
            }
        }
        else if (command == "pak") {
            std::cin >> arg;
            robot.pickUp(arg);
            updateScore(5); // punten voor item oppakken
        }
        else if (command == "inventaris") {
            robot.showInventory();
        }
        else if (command == "lever") {
            std::cin >> arg;
            if (robot.currentRoom == ic) {
                if (arg == "MedicatieA" && robot.hasItem("MedicatieA")) {
                    std::cout << "Patient op de IC heeft de juiste medicatie gekregen. Goed gedaan!\n";
                    medicatieA_gegeven = true;
                    updateScore(20);
                }
                else if (arg == "MedicatieB" && robot.hasItem("MedicatieB")) {
                    std::cout << "FOUT! Verkeerde medicatie aan IC-patient. Game Over.\n";
                    updateScore(-50);
                    break;
                }
                else {
                    std::cout << "Je hebt dat item niet.\n";
                }
            }
            else if (robot.currentRoom == ok) {
                if (arg == "MedicatieB" && robot.hasItem("MedicatieB") && medicatieA_gegeven) {
                    std::cout << "Chirurgen hebben de juiste medicatie ontvangen.\n";
                    std::cout << "MISSIE GESLAAGD! Alle patienten zijn geholpen.\n";
                    robot.showAsciiArt();
                    updateScore(50);
                    break;
                }
                else if (arg == "MedicatieB" && robot.hasItem("MedicatieB") && !medicatieA_gegeven) {
                    std::cout << "De chirurgen wachten, maar je hebt de IC-patient nog niet geholpen!\n";
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
