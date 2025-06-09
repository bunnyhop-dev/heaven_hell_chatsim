#include <cstddef>
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;

struct GameState {
    int sin = 0;
    int goodness = 0;
    bool heaven = true;
    bool hell = false;
    int level = 1;
    string playerName = "Anonymous";
    bool hasAngel = false;
    bool hasDevil = false;
    int coins = 100;
};

vector<string> badWords = {"kill em all", "destroy world", "hate everyone", "end everything", "murder all"};
vector<string> goodWords = {"help others", "love all", "peace world", "forgive sins", "bless everyone"};
vector<string> angelAdvice = {"Be kind to others", "Help those in need", "Spread love and peace", "Forgive your enemies"};
vector<string> devilAdvice = {"Embrace the darkness", "Let chaos reign", "Power is everything", "Destroy your enemies"};

string generateRandomString(size_t length) {
    vector<string> godMessages = {
        "My child, walk in the light",
        "Love thy neighbor as thyself",
        "Peace be with you always",
        "Your heart must be pure",
        "Seek wisdom and understanding"
    };
    
    vector<string> luciferMessages = {
        "Darkness consumes all light",
        "Power corrupts, and I love it",
        "Welcome to eternal suffering",
        "Your soul belongs to me now",
        "Chaos is the only truth"
    };
    
    mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    
    if (length % 2 == 0) {
        uniform_int_distribution<> dist(0, godMessages.size() - 1);
        return godMessages[dist(rng)];
    } else {
        uniform_int_distribution<> dist(0, luciferMessages.size() - 1);
        return luciferMessages[dist(rng)];
    }
}

void saveGame(const GameState& state) {
    ofstream file("savegame.txt");
    if (file.is_open()) {
        file << state.sin << "\n";
        file << state.goodness << "\n";
        file << state.heaven << "\n";
        file << state.hell << "\n";
        file << state.level << "\n";
        file << state.playerName << "\n";
        file << state.hasAngel << "\n";
        file << state.hasDevil << "\n";
        file << state.coins << "\n";
        file.close();
        cout << "💾 Game saved successfully!\n";
    }
}

bool loadGame(GameState& state) {
    ifstream file("savegame.txt");
    if (file.is_open()) {
        file >> state.sin;
        file >> state.goodness;
        file >> state.heaven;
        file >> state.hell;
        file >> state.level;
        file.ignore();
        getline(file, state.playerName);
        file >> state.hasAngel;
        file >> state.hasDevil;
        file >> state.coins;
        file.close();
        cout << "💾 Game loaded successfully!\n";
        return true;
    }
    return false;
}

void showStatus(const GameState& state) {
    cout << "\n╔══════════════════════════════════╗\n";
    cout << "║           PLAYER STATUS          ║\n";
    cout << "╠══════════════════════════════════╣\n";
    cout << "║ Name: " << state.playerName << string(25 - state.playerName.length(), ' ') << "║\n";
    cout << "║ Location: " << (state.heaven ? "Heaven ☁️ " : "Hell 🔥  ") << "            ║\n";
    cout << "║ Level: " << state.level << string(23, ' ') << "║\n";
    cout << "║ Sin Level: " << state.sin << "/10" << string(18, ' ') << "║\n";
    cout << "║ Goodness: " << state.goodness << string(21, ' ') << "║\n";
    cout << "║ Coins: " << state.coins << string(22, ' ') << "║\n";
    cout << "║ Angel Helper: " << (state.hasAngel ? "Yes ✅" : "No ❌ ") << string(13, ' ') << "║\n";
    cout << "║ Devil Helper: " << (state.hasDevil ? "Yes ✅" : "No ❌ ") << string(13, ' ') << "║\n";
    cout << "╚══════════════════════════════════╝\n\n";
}

void showCommands() {
    cout << "\n📋 Available Commands:\n";
    cout << "• 'status' - Check your current state\n";
    cout << "• 'redeem' - Try to redeem your sins (costs 50 coins)\n";
    cout << "• 'shop' - Visit the celestial shop\n";
    cout << "• 'story' - Enter story mode\n";
    cout << "• 'minigame' - Play a mini game\n";
    cout << "• 'save' - Save your game\n";
    cout << "• 'load' - Load your game\n";
    cout << "• '0' - Exit game\n\n";
}

string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

bool containsBadWord(const string& input) {
    string lower = toLowerCase(input);
    for (const string& word : badWords) {
        if (lower.find(word) != string::npos) {
            return true;
        }
    }
    return false;
}

bool containsGoodWord(const string& input) {
    string lower = toLowerCase(input);
    for (const string& word : goodWords) {
        if (lower.find(word) != string::npos) {
            return true;
        }
    }
    return false;
}

void celestialShop(GameState& state) {
    cout << "\n🏪 Welcome to the Celestial Shop!\n";
    cout << "Your coins: " << state.coins << "\n\n";
    cout << "Items available:\n";
    cout << "1. Angel Helper (Cost: 200 coins) - Gives good advice\n";
    cout << "2. Devil Helper (Cost: 150 coins) - Gives dark advice\n";
    cout << "3. Holy Water (Cost: 100 coins) - Reduces sin by 2\n";
    cout << "4. Cursed Potion (Cost: 80 coins) - Increases sin by 1 but gives 50 coins\n";
    cout << "5. Exit shop\n";
    
    int choice;
    cout << "Choose item (1-5): ";
    cin >> choice;
    cin.ignore();
    
    switch(choice) {
        case 1:
            if (state.coins >= 200 && !state.hasAngel) {
                state.coins -= 200;
                state.hasAngel = true;
                cout << "👼 Angel helper acquired! They will give you holy guidance.\n";
            } else if (state.hasAngel) {
                cout << "You already have an angel helper!\n";
            } else {
                cout << "Not enough coins!\n";
            }
            break;
        case 2:
            if (state.coins >= 150 && !state.hasDevil) {
                state.coins -= 150;
                state.hasDevil = true;
                cout << "😈 Devil helper acquired! They will whisper dark secrets.\n";
            } else if (state.hasDevil) {
                cout << "You already have a devil helper!\n";
            } else {
                cout << "Not enough coins!\n";
            }
            break;
        case 3:
            if (state.coins >= 100) {
                state.coins -= 100;
                state.sin = max(0, state.sin - 2);
                cout << "💧 Holy water consumed! Sin reduced by 2.\n";
            } else {
                cout << "Not enough coins!\n";
            }
            break;
        case 4:
            if (state.coins >= 80) {
                state.coins -= 80;
                state.sin++;
                state.coins += 50;
                cout << "🧪 Cursed potion consumed! Sin increased but you gained 50 coins.\n";
            } else {
                cout << "Not enough coins!\n";
            }
            break;
        case 5:
            cout << "Thanks for visiting!\n";
            break;
        default:
            cout << "Invalid choice!\n";
    }
}

void storyMode(GameState& state) {
    cout << "\n📖 Story Mode - Chapter " << state.level << "\n";
    cout << "═══════════════════════════════════════\n";
    
    if (state.heaven) {
        cout << "You stand before the golden gates of Heaven.\n";
        cout << "The clouds beneath your feet feel soft and warm.\n";
        cout << "Suddenly, a figure approaches you...\n\n";
        cout << "Mysterious Figure: 'Mortal soul, you have been given a second chance.'\n";
        cout << "What do you say?\n";
        cout << "1. 'I am grateful for this opportunity'\n";
        cout << "2. 'I don't deserve to be here'\n";
        cout << "3. 'I want to go back to Earth'\n";
    } else {
        cout << "The fires of Hell burn around you.\n";
        cout << "You hear the screams of the damned echoing in the distance.\n";
        cout << "Lucifer appears before you with a wicked grin...\n\n";
        cout << "Lucifer: 'Welcome to your new home, lost soul.'\n";
        cout << "What do you do?\n";
        cout << "1. 'I accept my fate'\n";
        cout << "2. 'I want to escape this place'\n";
        cout << "3. 'I challenge you to a duel'\n";
    }
    
    int choice;
    cout << "Your choice (1-3): ";
    cin >> choice;
    cin.ignore();
    
    switch(choice) {
        case 1:
            state.goodness += 10;
            state.coins += 20;
            cout << "Your humility is noted. +10 Goodness, +20 Coins\n";
            break;
        case 2:
            state.sin += 2;
            state.coins += 30;
            cout << "Your honesty has consequences. +2 Sin, +30 Coins\n";
            break;
        case 3:
            state.level++;
            state.coins += 50;
            cout << "Your boldness advances the story. Level up! +50 Coins\n";
            break;
    }
}

void miniGame(GameState& state) {
    cout << "\n🎮 Mini Game: Guess the Holy Number!\n";
    cout << "I'm thinking of a number between 1 and 10.\n";
    
    mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<> dist(1, 10);
    int target = dist(rng);
    
    int guess;
    cout << "Your guess: ";
    cin >> guess;
    cin.ignore();
    
    if (guess == target) {
        cout << "🎉 Correct! The number was " << target << "!\n";
        state.coins += 50;
        state.goodness += 5;
        cout << "Reward: +50 coins, +5 goodness\n";
    } else {
        cout << "❌ Wrong! The number was " << target << ".\n";
        cout << "Better luck next time!\n";
    }
}

void redemptionSystem(GameState& state) {
    if (state.coins < 50) {
        cout << "💰 You need at least 50 coins to attempt redemption!\n";
        return;
    }
    
    cout << "\n✨ Redemption Ritual ✨\n";
    cout << "You kneel and pray for forgiveness...\n";
    cout << "The ritual costs 50 coins. Continue? (y/n): ";
    
    char choice;
    cin >> choice;
    cin.ignore();
    
    if (choice == 'y' || choice == 'Y') {
        state.coins -= 50;
        mt19937 rng(static_cast<unsigned int>(time(nullptr)));
        uniform_int_distribution<> dist(1, 100);
        int chance = dist(rng);
        
        if (chance <= 70) { // 70% success rate
            int reduction = min(3, state.sin);
            state.sin -= reduction;
            state.goodness += 5;
            cout << "🙏 Your prayers were heard! Sin reduced by " << reduction << ", Goodness +5\n";
            
            if (state.hell && state.sin <= 3) {
                state.hell = false;
                state.heaven = true;
                cout << "🌟 Miracle! You've been allowed back into Heaven!\n";
            }
        } else {
            cout << "😞 Your redemption failed this time. Try again later.\n";
        }
    }
}

int main() {
    GameState gameState;
    string user;
    
    cout << "╔══════════════════════════════════════════════╗\n";
    cout << "║    Heaven & Hell Chat Simulator - Complete   ║\n";
    cout << "║              Edition v2.0                    ║\n";
    cout << "╚══════════════════════════════════════════════╝\n\n";
    
    cout << "Enter your name: ";
    getline(cin, gameState.playerName);
    
    cout << "\nWould you like to load a saved game? (y/n): ";
    char loadChoice;
    cin >> loadChoice;
    cin.ignore();
    
    if (loadChoice == 'y' || loadChoice == 'Y') {
        if (!loadGame(gameState)) {
            cout << "No saved game found. Starting new game...\n";
        }
    }
    
    cout << "\nWelcome " << gameState.playerName << "! 👋\n";
    cout << "Type 'help' for commands or just start chatting!\n";
    cout << "Be careful with your words... both God and Lucifer are listening! 👁️\n\n";
    
    srand(static_cast<unsigned int>(time(nullptr)));
    
    do {
        string randomString = generateRandomString(rand() % 10 + 1);
        
        cout << "YOU: ";
        getline(cin, user);
        
        if (user == "0") break;
        
        // Commands
        if (toLowerCase(user) == "help") {
            showCommands();
            continue;
        } else if (toLowerCase(user) == "status") {
            showStatus(gameState);
            continue;
        } else if (toLowerCase(user) == "redeem") {
            redemptionSystem(gameState);
            continue;
        } else if (toLowerCase(user) == "shop") {
            celestialShop(gameState);
            continue;
        } else if (toLowerCase(user) == "story") {
            storyMode(gameState);
            continue;
        } else if (toLowerCase(user) == "minigame") {
            miniGame(gameState);
            continue;
        } else if (toLowerCase(user) == "save") {
            saveGame(gameState);
            continue;
        } else if (toLowerCase(user) == "load") {
            loadGame(gameState);
            continue;
        }
        
        // Helper advice
        if (gameState.hasAngel && rand() % 3 == 0) {
            mt19937 rng(static_cast<unsigned int>(time(nullptr)));
            uniform_int_distribution<> dist(0, angelAdvice.size() - 1);
            cout << "👼 Angel whispers: \"" << angelAdvice[dist(rng)] << "\"\n";
        }
        
        if (gameState.hasDevil && rand() % 3 == 0) {
            mt19937 rng(static_cast<unsigned int>(time(nullptr)));
            uniform_int_distribution<> dist(0, devilAdvice.size() - 1);
            cout << "😈 Devil whispers: \"" << devilAdvice[dist(rng)] << "\"\n";
        }
        
        // Check for good/bad words
        if (containsBadWord(user)) {
            gameState.sin++;
            gameState.coins += 10; // Sin pays
            cout << "⚠️  Dark words detected! Sin +1, Coins +10\n";
            
            if (gameState.sin >= 10 && gameState.heaven) {
                gameState.hell = true;
                gameState.heaven = false;
                cout << "\n🔥 You have been banished from Heaven! Welcome to Hell! 🔥\n";
                cout << "Lucifer: Finally! A new soul for my collection...\n\n";
            }
        }
        
        if (containsGoodWord(user)) {
            gameState.goodness++;
            gameState.sin = max(0, gameState.sin - 1);
            gameState.coins += 5;
            cout << "✨ Holy words detected! Goodness +1, Sin -1, Coins +5\n";
        }
        
        // Responses based on location
        if (gameState.heaven) {
            if (gameState.sin > 7) {
                cout << "God: I am very disappointed in you, my child...\n";
            } else if (gameState.goodness > 20) {
                cout << "God: You are truly blessed, " << gameState.playerName << "!\n";
            } else {
                cout << "God: " << randomString << "\n";
            }
        } else if (gameState.hell) {
            if (gameState.sin > 15) {
                cout << "Lucifer: Excellent work spreading chaos, my servant!\n";
            } else {
                cout << "Lucifer: " << randomString << "\n";
            }
        }
        
        // Level progression
        if ((gameState.goodness + gameState.sin) % 10 == 0 && (gameState.goodness + gameState.sin) > 0) {
            gameState.level++;
            gameState.coins += 100;
            cout << "🎉 Level up! You are now level " << gameState.level << "! +100 coins\n";
        }
        
        cout << endl;
        
    } while(user != "0");
    
    cout << "\n═══ FINAL RESULTS ═══\n";
    showStatus(gameState);
    
    if (gameState.goodness > gameState.sin) {
        cout << "🌟 Despite everything, goodness prevailed in your heart.\n";
    } else {
        cout << "🔥 The darkness consumed your soul in the end.\n";
    }
    
    cout << "Thanks for playing, " << gameState.playerName << "! Goodbye! 👋\n";
    
    return 0;
}
