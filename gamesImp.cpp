//Ermin Dzani
//CSC1061 Computer Sci 2
//prof. Ralph Newby
//Gambling Game
//finished: 12/1/2023



#include "games.h"
#include <iostream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
using namespace std;

// funtion just to diaply the amount of points won or lost
void pointChange(int winnings)
{
  if (winnings <= 0)
  {
    cout << "You lost " << winnings << " points \n";
  }
  else
  {
    cout << "You won " << winnings << " points \n";
  }
}

// function for inputing how much they want to gamble with error handeling
int howMuchGamble(int points)
{
  int gamblePoints = 0;
  cout << "Enter the amount of points you want to gamble: ";
  while (!(cin >> gamblePoints) || points < gamblePoints || gamblePoints < 0)
  {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "You enterd an invalid amount of points. \n";
    cout << "Enter the amount of points you want to gamble: ";
  }
  return gamblePoints;
}

// funtion for what kind of die user wants to use with error hadeling
int diceSide(int sides)
{
  int diceSize = 6;
  cout << "Choose the size of the dice (6, 8, 10, 12, 20): ";
  while (!(cin >> diceSize) || diceSize != 6 && diceSize != 8 && diceSize != 10 && diceSize != 12 && diceSize != 20)
  {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Please enter one of the avaliable dice sizes." << endl;
    cout << "Choose the size of the dice (6, 8, 10, 12, 20): ";
  }
  return diceSize;
}

// constructor
Prize::Prize(const std::string &prizeName, int prizeCost)
{
  name = prizeName;
  cost = prizeCost;
}

// method implementations for getting/change names and cost
std::string Prize::getName() const
{
  return name;
}

int Prize::getCost() const
{
  return cost;
}

// Setter method implementations
void Prize::setName(const std::string &newName)
{
  name = newName;
}

void Prize::setCost(int newCost)
{
  cost = newCost;
}

// Constructor
Shop::Shop() : storeSize(0), boughtSize(0) {}

// imp for adding prize to shop list
void Shop::addPrize(const Prize &prize)
{
  if (storeSize < 10)
  {
    store[storeSize++] = prize;
  }
  else
  {
    cout << "Shop is full. Cannot add more prizes." << std::endl;
  }
}

// Method to buy a prize from the shop
int Shop::buyPrize(int index, int points)
{
  int pointsSpent = 0;
  if (index >= 0 && index < storeSize)
  {
    if (points >= store[index].getCost())
    {
      bought[boughtSize++] = store[index];
      pointsSpent = store[index].getCost();          // Track points spent
      points -= pointsSpent;                         // subtract points
      std::swap(store[index], store[storeSize - 1]); // Move purchased item to the end of the store
      --storeSize;                                   // Decrease store size to exclude purchased item
      cout << "Purchased " << bought[boughtSize - 1].getName() << std::endl;
    }
    else
    { // error handeling
      cout << "Insufficient points to buy this prize." << std::endl;
    }
  }
  else
  { // error handeling
    cout << "Invalid index. Please choose a valid prize." << std::endl;
  }
  return pointsSpent; // return the points the user used
}

// Method to display available prizes in the shop
int Shop::displayStore(int points)
{
  int spentPoints = 0; // Variable to hold the points spent
  char choice = 'a';
  do
  {
    cout << "Available Prizes in the Shop:" << std::endl;
    for (int i = 0; i < storeSize; ++i)
    {
      cout << i << ". " << store[i].getName() << " " << store[i].getCost() << std::endl;
    }

    cout << "Enter the index to buy, 'A' to sort alphabetically, 'N' to sort by cost, or 'E' to exit: ";
    cin >> choice;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    choice = std::toupper(choice);

    switch (choice)
    {
    case 'A':
      sortStoreByName(); // Utilizing existing sortStoreByName method
      cout << "Available items sorted alphabetically by name." << std::endl;
      break;
    case 'N':
      sortStoreByCost(); // Utilizing existing sortStoreByCost method
      cout << "Available items sorted by cost." << std::endl;
      break;
    case 'E':
      cout << "Exiting displayStore..." << std::endl;
      return spentPoints; // Return the total points spent
    default:
      if (isdigit(choice))
      {
        int index = choice - '0';
        if (index >= 0 && index < storeSize)
        {
          spentPoints += buyPrize(index, points); // Accumulate spent points
        }
        else
        {
          cout << "Invalid index. Please choose a valid prize." << std::endl;
        }
      }
      else
      {
        cout << "Invalid input. Please try again." << std::endl;
      }
      break;
    }
  } while (true);

  // Return the total points spent
  return spentPoints;
}

// Method to display purchased prizes
void Shop::displayBought()
{
  char choice = 'a';
  do
  { // display the items
    cout << "Purchased Prizes:" << std::endl;
    for (int i = 0; i < boughtSize; ++i)
    {
      cout << i << ". " << bought[i].getName() << " " << bought[i].getCost() << std::endl;
    }

    cout << "Enter 'A' to sort alphabetically, 'N' to sort by cost, or 'E' to exit: "; // ask to sort list or exit
    cin >> choice;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    choice = std::toupper(choice);

    switch (choice)
    {
    case 'A':
      sortStoreByName(); // Utilizing existing sortStoreByName method
      cout << "Purchased items sorted alphabetically by name." << std::endl;
      break;
    case 'N':
      sortStoreByCost(); // Utilizing existing sortStoreByCost method
      cout << "Purchased items sorted by cost." << std::endl;
      break;
    case 'E':
      cout << "Exiting displayBought..." << std::endl;
      return; // Exit
    default:  // error
      cout << "Invalid input. Please try again." << std::endl;
      break;
    }
  } while (true);
}

// name sort with bubble sort
void Shop::sortStoreByName()
{
  for (int i = 0; i < storeSize - 1; ++i)
  {
    for (int j = 0; j < storeSize - i - 1; ++j)
    {
      if (store[j].getName() > store[j + 1].getName())
      {
        std::swap(store[j], store[j + 1]);
      }
    }
  }
}

// cost sort with bubble sort
void Shop::sortStoreByCost()
{
  for (int i = 0; i < storeSize - 1; ++i)
  {
    for (int j = 0; j < storeSize - i - 1; ++j)
    {
      if (store[j].getCost() > store[j + 1].getCost())
      {
        std::swap(store[j], store[j + 1]);
      }
    }
  }
}

// funtion to show bought items
void Shop::boughtList()
{
  cout << "Purchased Prizes:" << std::endl;
  for (int i = 0; i < boughtSize; ++i)
  {
    cout << i << ". " << bought[i].getName() << " " << bought[i].getCost() << std::endl;
  }
}

// Implementation for Dice class
Dice::Dice(int numSides)
{
  if (numSides == 6 || numSides == 8 || numSides == 10 || numSides == 12 || numSides == 20)
  {
    sides = numSides;
  }
  else
  {
    sides = 6; // Default to 6 sides if an invalid number is given
  }
  srand(static_cast<unsigned int>(time(0))); // random number generator
}

int Dice::roll()
{
  return (rand() % sides) + 1; // Generate a random number between 1 and the number of sides
}

int Dice::getSides()
{
  return sides;
}

// Implementation for Game class
Game::Game(int startingPoints, int numSides) : points(startingPoints), dice(numSides) {}

// Implementation for RouletteGame class
RouletteGame::RouletteGame(int startingPoints, int numSides) : Game(startingPoints, numSides) {}

int RouletteGame::play()
{
  // Implementation for play function in RouletteGame
  int bet = 0;
  int chosenSize = 6;
  int chosenBid = 0;

  // user selects what they want to bet on
  cout << "What would you like to bet on?\n";
  cout << "1. evens (2x points on win) \n";
  cout << "2. odds (2x points on win) \n";
  cout << "3. multiples of 3 (4x points on win) \n";
  cout << "4. multiples of 5 (6x points on win) \n";

  // error handeling
  while (!(cin >> chosenBid) || chosenBid < 0 || 5 < chosenBid)
  {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "You enterd an invalid selection. \n";
    cout << "What would you like to bet on? ";
  }

  // roll dice
  int rollResult = dice.roll();
  cout << "You rolled a " << rollResult << "\n";
  return handleResult(bet, chosenSize, chosenBid);
}

int RouletteGame::handleResult(int gamblePoints, int rollResult, int bid)
{

  // logic for how much handleResults should equal to and return that value
  // multipler based on dice size and 0 for on a loss
  switch (bid)
  {
  case 1:
  {
    if (rollResult % 2 == 0)
    {
      return 2;
    }
    else
    {
      return -1;
    }
    break;
  }
  case 2:
  {
    if ((rollResult + 1) % 2 == 0)
    {
      return 2;
    }
    else
    {
      return -1;
    }
    break;
  }
  case 3:
  {
    if (rollResult % 3 == 0 && rollResult % 3 != 1)
    {
      return 4;
    }
    else
    {
      return -1;
    }
    break;
  }
  case 4:
  {
    if (rollResult % 5 == 0 && rollResult % 5 != 1)
    {
      return 6;
    }
    else
    {
      return -1;
    }
    break;
  }
  default:
  {
    return 0;
  }
  }
}

// Implementation for Blackjack class
Blackjack::Blackjack(int startingPoints, int numSides) : Game(startingPoints, numSides) {}

int Blackjack::play()
{
  int gameblePoints = 0;
  int chosenSide = 6;
  int total = dice.roll() + dice.roll();
  int bust = (2 * dice.getSides()) + 1;
  int playerTotal = 0;
  int houseTotal = 0;
  char choice = 'a';

  // user playes game
  playerTotal = playBlackjack(bust, gameblePoints);

  //"house" plays game
  houseTotal = simulateHouse(dice.getSides(), bust);

  // show the final scores
  cout << "You ended with " << playerTotal << endl;
  cout << "The house ended with " << houseTotal << endl;

  // logic for who won
  if (playerTotal < houseTotal)
  {
    cout << "The house has won. " << endl;
    return 0;
  }
  else
  {
    cout << "You won! " << endl;
    return 2;
  }
}

int Blackjack::playBlackjack(int gamblePoints, int chosenSize)
{
  int bust = gamblePoints;
  int total = dice.roll() + dice.roll();
  int rollResult = 0;
  char choice = 'a';

  // show user max and their current
  cout << "dont go over " << bust << endl;
  cout << "Your current total is " << total << endl;
  while (true)
  {
    do
    { // ask user if they want to roll or stay with error handeling
      cout << "Do you want to (R)oll or (S)tay? \n";
      cin >> choice;
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      choice = tolower(choice);
    } while (!cin.fail() && choice != 'r' && choice != 's');

    // if user choice is r, the dice will get rolled, display the roll,
    // add it to their previous total and diplay that and loop back to the start
    if (choice == 'r')
    {
      rollResult = dice.roll();
      total = total + rollResult;
      cout << "You rolled a " << rollResult << endl;
      if (total <= bust)
      { // logic for if the user gets is under the limit
        cout << "You total is " << total << endl;
        continue;
      }
      else
      { // logic if user goes over limit
        cout << "Your total is " << total << " and you busted, better luck next time" << endl;
        return 0;
        break;
      }
    }
    else
    { // if user says s
      return total;
      break;
    }
  }
}

int Blackjack::simulateHouse(int chosenSize, int max)
{
  // show user houses hand
  int rollResult = 0;
  int houseHand = dice.roll() + dice.roll();
  cout << "The house has rolled a " << houseHand << endl;
  system("pause"); // a lot of pauses so user knows whats happening

  int stop = 0;
  while (stop != 1)
  { // the house is purley random
    // house will roll the dice and if its divisable by 2 they will roll
    // if its odd they will fold
    // this makes it a 50/50 if they roll or stay
    int random = dice.roll();
    if (random % 2 == 0)
    {
      rollResult = dice.roll();                                 // if they roll an even
      cout << "The house rolled a " << rollResult << endl;      // show user what house rolled
      houseHand = houseHand + rollResult;                       // add to house total
      cout << "The house has a total of " << houseHand << endl; // display total
      system("pause");
      if (houseHand <= max)
      {
        continue;
      }
      else
      {
        return 0; // house goes over max
        break;
      }
    }
    else
    { // house rolls odd
      cout << "The house ended with a total of " << houseHand << endl;
      system("pause");
      stop += 1;
    }
  }
  return houseHand;
}

// Implementation for Slots class
Slots::Slots(int startingPoints, int numSides) : Game(startingPoints, numSides) {}

int Slots::play()
{
  int gamblePoints = 0;
  int chosenSize = 6;
  // just returns slots funtion
  return playSlots(gamblePoints, chosenSize);
}

int Slots::playSlots(int gamblePoints, int chosenSize)
{
  // roll 3 dice of chosen sides
  int dice1 = dice.roll();
  int dice2 = dice.roll();
  int dice3 = dice.roll();
  // show user results
  cout << "You rolled: " << dice1 << ", " << dice2 << ", " << dice3 << std::endl;

  //if they are all the same the user wins 1.5x the amount of sides of the dice\
  //else they loose it all
  if (dice1 == dice2 && dice2 == dice3)
  {
    return 1.5 * dice.getSides();
  }
  else
  {
    return 0;
  }
}
