#include "mainheader.h"

using namespace std;

string controls = string("Controls:\n") + // displays the controls for the game
                  "Type \"b\" to see your current balance.\n" +
                  "Type \"s\" to open the shop.\n" +
                  "Type \"t\" to see your current trees.\n\n" + "--> ";

map<string, tuple<double, string, double>> shopMap = {
    // dictionary/map to store info on the different tree types
    {"b", make_tuple(1.0, "Banana", 0.16)},
    {"s", make_tuple(4.0, "Strawberry", 0.37)},
    {"k", make_tuple(12.0, "Kiwi", 0.51)},
    {"w", make_tuple(30.0, "Watermelon", 1.05)},
    {"o", make_tuple(100.0, "Orange", 8.02)},
    {"p", make_tuple(500.0, "Peach", 10.12)},
    {"c", make_tuple(1000.0, "Coconut", 100.30)},
    {"pr", make_tuple(5000.0, "Pear", 347.33)},
    {"pi", make_tuple(30000.0, "Pineapple", 1783.47)},
    {"g", make_tuple(65000.0, "Grapes", 54843.86)},
    {"m", make_tuple(1000001.0, "Mango", 99999.99)},
};

void printTreeCollection(
    vector<string>
        collectedTrees) { // prints all trees that have been collected so far
  cout << "Your tree collection includes:" << endl;
  for (string s : collectedTrees) { // Displays collected trees
    cout << s << endl;
  }
}

void purchaseTree(vector<string> &collectedTrees, string key,
                  string controls, // function that controls how trees are
                                   // purchased and takes into account all cases
                  double &balance, double &incomePerSecond) {
  system("clear");
  if (shopMap.find(key) == shopMap.end()) { // checks for invalid inputs

    cout << "Invalid input!\n\n" << controls;
    return;
  }
  string name = get<1>(shopMap[key]); // sets the input to the correct tree type
  bool test = false;

  for (string s :
       collectedTrees) { // checks if the tree has been purchased already
    if (name == s) {
      test = true;
      break;
    }
  }
  if (balance < get<0>(shopMap[key])) { // checks for the correct balance

    cout << "You do not have enough money to purchase this tree!" << endl;
    cout << "Please wait to collect more money or purchase an affordable "
            "tree.\n\n"
         << controls;
    return;
  }
  if (test != true) { // purchases the tree if player has enough money and
                      // stores it in the collectedTrees

    cout << "You have bought a " << name << " tree!" << endl;
    if (get<1>(shopMap[key]) == "Pear") {
      cout << "And an extra Partridge!";
      collectedTrees.push_back("Partridge");
    }
    balance -= get<0>(shopMap[key]);
    incomePerSecond += get<2>(shopMap[key]);
    collectedTrees.push_back(name);
    cout << "\n";
    printTreeCollection(collectedTrees);
    cout << endl << controls;
  } else {
    cout << "You have already purchased this tree!";
    cout << "\n\n" << controls;
  }
}

// Disasters-------------------------------------------------------------------------------------------------------------
void disasters(
    double &balance, string controls,
    double &incomePerSecond, // random chance for each disaster to happen.
                             // multiple disasters/blessings can occur at once
    bool &tornado, bool &drought, bool &bank_blessing, bool &locust_swarm,
    bool &rain) {
  srand(time(0));

  while (true) {
    int randomnum = rand() % 200;

    if (randomnum < 3 && randomnum > 2 && tornado == false) {
      tornado = true;
      cout
          << "Fierce winds ravage your farm! Your balance takes a hit!\n\n--> ";
      balance *= 0.8;
    }
    if (randomnum < 54 && randomnum > 53 && drought == false) {
      drought = true;
      cout << "A drought ravages over your farm! Profits are cut for "
              "the next minute!\n\n--> ";
      incomePerSecond *= .7;
    }
    if (randomnum < 7 && randomnum > 6 && bank_blessing == false) {
      bank_blessing = true;
      cout << "Your bank has been blessed with luck! Your balance has "
              "doubled!\n\n--> ";
      balance *= 2;
    }
    if (randomnum < 10 && randomnum > 8 && locust_swarm == false) {
      locust_swarm = true;
      cout << "A locust swarm has arrived at your farm! Your fruit quality "
              "drops!\n\n--> ";
      incomePerSecond *= 0.3;
    }
    if (randomnum < 57 && randomnum > 56 && rain == false) {
      rain = true;
      cout << "It is raining! Your farm production has increased for five "
              "minutes!\n\n--> ";
      incomePerSecond *= 1.25;
    }
    sleep(1);
  }
}

void disasterTimer(bool &tornado,
                   double &incomePerSecond, // handles the cooldown and length
                                            // of disasters/blessings, as well as
                                            // resets their effects
                   double &balance, bool &drought, bool &bank_blessing,
                   bool &locust_swarm, bool &rain) {
  while (true) {
    if (tornado) {
      sleep(15);
      tornado = false;
    }
    if (drought) {
      sleep(60);
      drought = false;
      incomePerSecond *= 1.42857142857;
    }
    if (bank_blessing) {
      sleep(15);
      bank_blessing = false;
    }
    if (locust_swarm) {
      sleep(15);
      locust_swarm = false;
      incomePerSecond *= 1.3333333333;
    }
    if (rain) {
      sleep(120);
      tornado = false;
      incomePerSecond *= 0.8;
    }
  }
}

void balanceTick(
    double &balance, string controls,
    bool &balanceThread, // ticks/updates the balance visually and keeps
                         // displaying the current disaster/blessing constantly
                         // while checking your balance
    bool &tornado, bool &drought, bool &bank_blessing, bool &locust_swarm,
    bool &rain) {

  while (true) {
    if (balanceThread) {
      system("clear");
      cout << controls;

      cout << setprecision(2) << fixed << "Total Balance: $" << balance << endl
           << "--> ";
      if (tornado) {
        cout << "Fierce winds ravage your farm! Your balance takes a "
                "hit!\n\n--> ";
      }
      if (drought) {
        cout << "A drought ravages over your farm! Profits are cut "
                "for the next minute!\n\n--> ";
      }
      if (bank_blessing) {
        cout << "Your bank has been blessed with luck! Your balance has "
                "doubled!\n\n--> ";
      }
      if (locust_swarm) {
        cout << "A locust swarm has arrived at your farm! Your fruit quality "
                "drops!\n\n--> ";
      }
      if (rain) {
        cout << "It is raining! Your farm production has increased for 2 "
                "minutes!\n\n--> ";
      }
      sleep(1);
    }
  }
}

void awaitInput(double &balance, double &incomePerSecond,
                bool &balanceThread, // main frame function used to await the
                                     // next input to make actions
                int &sleepTime) {
  string input1;
  string input2;
  bool mineral = false;
  bool soil = false;
  vector<string> collectedTrees = {"Apple"};

  string shoptext = string("Welcome to the shop, what would you like to do?") +
                    "\n-1. Buy next tree" +
                    "\n-2. Buy better soil $25 (one time purchase)" +
                    "\n-3. Buy mineral water $100 (one time purchase)" +
                    "\n-4. Quit" + "\n--> ";

  cout << controls;

  while (true) {

    cin >> input1;
    balanceThread = false;
    system("clear");
    cout << controls;
    // balance scene
    if (input1 == "b") {
      balanceThread = true;
    }
    // shop scene
    if (input1 == "s") {
      system("clear");
      cout << shoptext;
      while (true) {
        cin >> input1;
        if (input1 == "1") { // Takes in input for type of tree using characters
          system("clear");
          cout << "What tree type would you like to buy?" << endl;
          cout << "Type b for a Banana Tree: $1" << endl;
          cout << "Type s for a Strawberry Bush: $4" << endl;
          cout << "Type k for a Kiwi Tree: $12" << endl;
          cout << "Type w for a Watermelon Vine: $30" << endl;
          cout << "Type o for a Orange Tree: $100" << endl;
          cout << "Type p for a Peach Tree: $500" << endl;
          cout << "Type c for a Coconut Tree: $1,000" << endl;
          cout << "Type pr for a Pear Tree: $5,000" << endl;
          cout << "Type pi for a Pineapple Tree: $30,000" << endl;
          cout << "Type g for a Grape Tree: $65,000" << endl;
          cout << "Type m for a Mango Tree: $1,000,001" << endl;
          cin >> input2;
          purchaseTree(collectedTrees, input2, shoptext, balance,
                       incomePerSecond);
        }
        if (input1 == "2") {
          if (soil == false && balance >= 25) {
            cout << "Bought High Quality Soil.\n-->";
            soil = true;
            sleepTime = 1;
            balance -= 25;
          } else if (soil == false && balance < 25) {
            cout << "You do not have enough money to purchase this upgrade!"
                 << endl;
          } else if (soil) {
            cout << "You have already purchased this upgrade!\n-->";
          }
        }
        if (input1 == "3") {
          if (mineral == false && balance >= 100) {
            cout << "Bought Mineral Water\n-->";
            mineral = true;
            incomePerSecond *= 1.1;
            balance -= 100;
          } else if (mineral == false && balance < 100) {
            cout << "You do not have enough money to purchase this upgrade!"
                 << endl;
          } else if (mineral) {
            cout << "You have already purchased this upgrade!\n-->";
          }
        }
        if (input1 == "4") {
          system("clear");
          cout << controls;
          break;
        }
      }
    }

    if (input1 == "t") { // displays current trees scene
      printTreeCollection(collectedTrees);
    }
  }
}

void tick(
    double &balance, double &incomePerSecond,
    int &sleepTime) { // tick function to update the balance every so often

  while (true) {

    balance += incomePerSecond;

    sleep(sleepTime);
  }
}