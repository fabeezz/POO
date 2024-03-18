#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
#include <time.h>
#include <windows.h>

class Player
{
private:
    std::string playerName;
    float balance;
    std::string password;

public:
    Player(const std::string &name, float balance, const std::string &password) : playerName(name), balance(balance), password(password)
    {
        // std::cout << "Constr. de init. pentru Player: " << playerName << std::endl;
    }

    // Check if the password and player name are correct
    bool authPassword(const std::string &inputPassword) const
    {
        return inputPassword == password;
    }

    bool authPlayerName(const std::string &inputPlayerName) const
    {
        return inputPlayerName == playerName;
    }

    // Getters for playerName and balance
    std::string getName() const
    {
        return playerName;
    }
    float getBalance() const
    {
        return balance;
    }
};

class Item
{
private:
    std::string itemName;
    float itemPrice;
    std::string itemRarity;

public:
    Item(const std::string &name, float price, std::string rarity) : itemName(name), itemPrice(price), itemRarity(rarity)
    {
        // std::cout << "Constr. de init. Item" << itemName << std::endl;
    }

    // Getter function to output all information about the item
    void printItem() const
    {
        std::cout << "Item Name: " << itemName << ", Price: " << itemPrice << std::endl; // €
    }

    // Getter for the rarityy/color
    std::string getRarity() const
    {
        return itemRarity;
    }

    // Getter for item price
    float getItemPrice() const
    {
        return itemPrice;
    }
};

class Case
{
private:
    std::string caseName;
    float casePrice;
    std::vector<Item> items;

public:
    // vectors for each rariry, for storage
    std::vector<Item> blues;
    std::vector<Item> purples;
    std::vector<Item> pinks;
    std::vector<Item> reds;
    std::vector<Item> golds;

    Case(const std::string &caseName_, float casePrice_) : caseName(caseName_), casePrice(casePrice_)
    {
        // std::cout << "Constr. de init. Case: " << caseName << std::endl;
    }

    Case(const Case &other) : caseName(other.caseName), casePrice(other.casePrice)
    {
        std::cout << "Constr. de copiere Case" << std::endl;
    }

    ~Case()
    {
        // std::cout << "Destr. Case" << std::endl;
    }

    // Getter function to output all information about the case, including its items
    void printCase() const
    {
        std::cout << "Case Name: " << caseName << ", Price: " << casePrice << std::endl;
        std::cout << "Items in the case:" << std::endl;
        for (const auto &item : items)
        {
            item.printItem();
        }
    }

    float getCasePrice()
    {
        return casePrice;
    }

    // function to add all items to 'items' vector and their correct rarity vector
    void addItem(const Item &newItem)
    {
        items.push_back(newItem);
        std::string color;
        color = newItem.getRarity();
        if (color == "blue")
            blues.push_back(newItem);
        else if (color == "purple")
            purples.push_back(newItem);
        else if (color == "pink")
            pinks.push_back(newItem);
        else if (color == "red")
            reds.push_back(newItem);
        else if (color == "gold")
            golds.push_back(newItem);
    }

    // std::vector<Item> get() const
    // {
    //     std::vector<float> probabilities;
    //     for (const auto &item : items)
    //     {
    //         probabilities.push_back(item.getProbability());
    //     }
    //     return probabilities;
    // }

    // the case simulator, with the real CS2 odds
    Item openCase() const
    {
        int index = (rand() % 3910) + 1;
        int itemPick = rand();

        // std::cout << "Selected index: " << index << std::endl;

        // if (index == 1)
        //     std::cout << "You got a ST Knife\n";
        // else if (index <= 4)
        //     std::cout << "You got a ST Convert\n";
        if (index <= 13)
        {
            std::cout << "You got a Knife!\n";
            itemPick = itemPick % 13;
            return golds[itemPick];
        }
        // else if (index <= 25)
        //     std::cout << "You got a ST Classified\n";
        else if (index <= 47)
        {
            std::cout << "You got a Convert\n";
            itemPick = itemPick % 2;
            return reds[itemPick];
        }
        // else if (index <= 110)
        //     std::cout << "You got a ST Restricted\n";
        else if (index <= 223)
        {
            std::cout << "You got a Classified\n";
            itemPick = itemPick % 3;
            return pinks[itemPick];
        }
        // else if (index <= 536)
        //     std::cout << "You got a ST Mil-spec\n";
        else if (index <= 1098)
        {
            std::cout << "You got a Restricted\n";
            itemPick = itemPick % 5;
            return purples[itemPick];
        }
        else if (index <= 3910)
        {
            std::cout << "You got a Mil-spec\n";
            itemPick = itemPick % 7;
            return blues[itemPick];
        }
    }
};

int main()
{
    // rand seed to be unix time
    srand((int)time(NULL));

    // players
    std::vector<Player> players;
    players.push_back(Player("Fabi", 5000, "parolafabi"));
    players.push_back(Player("Tudi", 100, "parolatudi"));
    players.push_back(Player("Cosmin", 200, "parolacosmin"));
    players.push_back(Player("Vlad", 300, "parolavlad"));

    // authetication method
    std::string inputPlayerName;
    std::string inputPassword;
    bool authenticated = false;
    float availableBalance = 0;

    while (!authenticated)
    {
        std::cout << "Enter your Username (or type 'exit' to quit): ";
        std::cin >> inputPlayerName;
        if (inputPlayerName == "exit")
            return 0;

        std::cout << "Enter your password: ";
        std::cin >> inputPassword;
        for (const auto &player : players)
        {
            if (player.authPassword(inputPassword) && player.authPlayerName(inputPlayerName))
            {
                Sleep(1500);
                std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                std::cout << "Authentication successful. Welcome, " << player.getName() << "!" << std::endl;
                // std::cout << "Your current balance is: $" << player.getBalance() << std::endl;
                std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                availableBalance = player.getBalance();
                authenticated = true;
                break;
            }
        }
        if (!authenticated)
        {
            Sleep(1500);
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            std::cout << "Authentication failed. Incorrect username or password. Wish to continue? ('y' / 'n')" << std::endl;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            std::cin >> inputPlayerName;
            if (inputPlayerName == "n")
                return 0;
        }
    }

    // std::cout << "Current Balance: " << availableBalance << std::endl;

    // items
    Item item1("Dual Berettas | Hideout", 0.3, "blue");
    Item item2("Nova | Dark Sigil", 0.3, "blue");
    Item item3("Tec-9 | Slag", 0.4, "blue");
    Item item4("UMP-45 | Motorized", 0.35, "blue");
    Item item5("XM1014 | Irezumi", 0.3, "blue");
    Item item6("SSG 08 | Dezastre", 0.5, "blue");
    Item item7("MAC-10 | Light Box", 0.7, "blue");
    Item item8("MP7 | Just Smile", 2.15, "purple");
    Item item9("Sawed-Off | Analog Input", 2.3, "purple");
    Item item10("Five-SeveN | Hybrid", 2.25, "purple");
    Item item11("M4A4 | Etch Lord", 3, "purple");
    Item item12("Glock-18 | Block-18", 3.5, "purple");
    Item item13("USP-S | Jawbreaker", 15.5, "pink");
    Item item14("Zeus x27 | Olympus", 17, "pink");
    Item item15("M4A1-S | Black Lotus", 35, "pink");
    Item item16("AK-47 | Inheritance", 130, "red");
    Item item17("AWP | Chrome Cannon", 110, "red");
    Item item18("Kukri Knife | Vanilla", 1044, "gold");
    Item item19("Kukri Knife | Slaughter", 950, "gold");
    Item item20("Kukri Knife | Blue Steel", 650, "gold");
    Item item21("Kukri Knife | Case Hardened", 1000, "gold");
    Item item22("Kukri Knife | Crimson Web", 870, "gold");
    Item item23("Kukri Knife | Stained", 450, "gold");
    Item item24("Kukri Knife | Scorched", 400, "gold");
    Item item25("Kukri Knife | Forest DDPAT", 500, "gold");
    Item item26("Kukri Knife | Night Stripe", 550, "gold");
    Item item27("Kukri Knife | Safari Mesh", 350, "gold");
    Item item28("Kukri Knife | Urban Masked", 400, "gold");
    Item item29("Kukri Knife | Boreal Forest", 350, "gold");
    Item item30("Kukri Knife | Fade", 1500, "gold");

    // the case
    Case kwCase("Kilowatt Case", 2.54);
    kwCase.addItem(item1);
    kwCase.addItem(item2);
    kwCase.addItem(item3);
    kwCase.addItem(item4);
    kwCase.addItem(item5);
    kwCase.addItem(item6);
    kwCase.addItem(item7);
    kwCase.addItem(item8);
    kwCase.addItem(item9);
    kwCase.addItem(item10);
    kwCase.addItem(item11);
    kwCase.addItem(item12);
    kwCase.addItem(item13);
    kwCase.addItem(item14);
    kwCase.addItem(item15);
    kwCase.addItem(item16);
    kwCase.addItem(item17);
    kwCase.addItem(item18);
    kwCase.addItem(item19);
    kwCase.addItem(item20);
    kwCase.addItem(item21);
    kwCase.addItem(item22);
    kwCase.addItem(item23);
    kwCase.addItem(item24);
    kwCase.addItem(item25);
    kwCase.addItem(item26);
    kwCase.addItem(item27);
    kwCase.addItem(item28);
    kwCase.addItem(item29);
    kwCase.addItem(item30);

    std::string userInput;
    int userNumber;
    float spentOnCases = 0;
    float earnedFromCase = 0;

    Sleep(2000);

    while (true)
    {
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "What do you want to do next? (type the number)" << std::endl;
        std::cout << "(1) Open cases!" << std::endl;
        std::cout << "(2) Show balance." << std::endl;
        std::cout << "(3) Top up balance :)" << std::endl;
        std::cout << "(4) Quit :/" << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

        std::cin >> userInput;
        Sleep(1500);
        if (userInput != "1" && userInput != "2" && userInput != "3" && userInput != "4")
        {
            std::cout << "Only numbers... try again? ('y' / 'n')" << std::endl;
            std::cin >> userInput;
            if (userInput == "n" || userInput != "y")
            {
                std::cout << "Bye!" << std::endl;
                break;
            }
        }
        else if (userInput == "1")
        {
            while (true)
            {
                std::cout << "You got " << availableBalance << "$ left." << std::endl;
                std::cout << "How many cases do you want to open? ('0' to quit)" << std::endl;
                std::cin >> userNumber;
                if (userNumber == 0)
                    break;
                else
                {
                    Sleep(1500);
                    spentOnCases = userNumber * kwCase.getCasePrice();
                    earnedFromCase = 0;
                    if (availableBalance < spentOnCases)
                    {
                        std::cout << "Insufficient balance!" << std::endl;
                    }
                    else
                    {
                        std::cout << "Let's open..." << std::endl;
                        // std::cout << "Money spent on cases: " << spentOnCases << std::endl;
                        for (int i = 1; i <= userNumber; i++)
                        {

                            Item selected = kwCase.openCase();
                            std::cout << "You obtained: ";
                            selected.printItem();
                            earnedFromCase += selected.getItemPrice();
                        }
                        availableBalance -= spentOnCases;
                    }
                    Sleep(500);
                    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                    std::cout << "You spent: " << spentOnCases << "$ on cases." << std::endl;
                    std::cout << "You earned items valued at: " << earnedFromCase << "$." << std::endl;
                    if (earnedFromCase - spentOnCases < 0)
                        std::cout << "So you lost: " << earnedFromCase - spentOnCases << "$." << std::endl;
                    else
                        std::cout << "So you earned: " << earnedFromCase - spentOnCases << "$." << std::endl;
                    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                    Sleep(1000);
                    std::cout << "Try again? ('y'/'n')" << std::endl;
                    std::cin >> userInput;
                    if (userInput == "n")
                    {
                        Sleep(500);
                        break;
                    }
                }
            }
        }
        else if (userInput == "2")
        {
            Sleep(500);
            std::cout << "Current Balance: " << availableBalance << "$." << std::endl;
            Sleep(500);
        }
        else if (userInput == "3")
        {
            Sleep(500);
            availableBalance += 1000;
            std::cout << "You got an additional 1000$." << std::endl;
            std::cout << "(99% of all gamblers stop before a lifechanging win...)" << std::endl;
        }
        else if (userInput == "4")
        {
            Sleep(500);
            std::cout << "Bye!" << std::endl;
            break;
        }
    }
    return 0;
}