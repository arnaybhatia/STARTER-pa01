// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argv, char **argc)
{
  if (argv < 3)
  {
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  ifstream cardFile1(argc[1]);
  ifstream cardFile2(argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail())
  {
    cout << "Could not open file " << argc[2];
    return 1;
  }

  set<CARD> alice_hand;
  // Read each file
  while (getline(cardFile1, line) && (line.length() > 0))
  {
    alice_hand.insert(CARD(line[0], line.substr(2)));
  }
  cardFile1.close();

  set<CARD> bob_hand;
  while (getline(cardFile2, line) && (line.length() > 0))
  {
    bob_hand.insert(CARD(line[0], line.substr(2)));
  }
  cardFile2.close();

  bool thing = true;
  bool turn = true;
  while (thing)
  {
    thing = false;
    if (turn)
    {
      for (CARD lol : alice_hand)
      {
        if (bob_hand.count(lol))
        {
          cout << "Alice picked matching card " << lol << endl;
          CARD c = lol;
          bob_hand.erase(c);
          alice_hand.erase(c);
          thing = true;
          break;
        }
      }
    }
    else
    {
      for (auto loll = bob_hand.rbegin(); loll != bob_hand.rend(); ++loll)
      {
        CARD lol = *loll;
        if (alice_hand.count(lol))
        {
          cout << "Bob picked matching card " << lol << endl;
          CARD c = lol;
          bob_hand.erase(c);
          alice_hand.erase(c);
          thing = true;
          break;
        }
      }
    }
    turn = !turn;
  }
  cout << endl << "Alice's cards:" << endl;
  for (auto c : alice_hand)
  {
    cout << c << endl;
  }

  cout << endl << "Bob's cards:" << endl;
  for (auto c : bob_hand)
  {
    cout << c << endl;
  }
  return 0;
}
