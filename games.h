#ifndef GAMES_H
#define GAMES_H

#include <cstdlib>
#include <ctime>
#include <string>

// function to change the users points
void pointChange(int winnings);

// function to ask user for points to gamble
int howMuchGamble(int points);

// function to ask user for dice size
int diceSide(int sides);

// class for prizes to be in shop
class Prize
{
private:
  std::string name;
  int cost;

public:
  // Constructor declaration
  Prize(const std::string &prizeName, int prizeCost);

  // Gets
  std::string getName() const;
  int getCost() const;

  // Sets
  void setName(const std::string &newName);
  void setCost(int newCost);
  Prize() : name(""), cost(0) {}
};

class Shop
{
private:
  Prize store[10];  // items in shop
  Prize bought[10]; // items bough
  int storeSize;    // Tracks the number of prizes in the store
  int boughtSize;   // Tracks the number of purchased prizes
  int points;

public:
  // Constructor
  Shop();

  // add prizes
  void addPrize(const Prize &prize);

  // buy a prize from the shop
  int buyPrize(int index, int points);

  // display available prizes in the shop
  int displayStore(int points);

  // display purchased prizes
  void displayBought();

  // sort the list by name
  void sortStoreByName();

  // sort the list by cost
  void sortStoreByCost();

  // function to only show bought
  void boughtList();
};

// class for dice
class Dice
{
private:
  int sides;

public:
  Dice(int numSides);

  int roll();

  int getSides();
};

// base class for game that all other games will inherate
class Game
{
protected:
  int points;
  Dice dice;

public:
  Game(int startingPoints, int numSides);

  virtual int play() = 0;
};

// roulette game
class RouletteGame : public Game
{
public:
  // make the game
  RouletteGame(int startingPoints, int numSides);
  int play();                                                  // play the game
  int handleResult(int gamblePoints, int rollResult, int bid); // logic for the game

private:
  int bidPlaced;
};

class Blackjack : public Game
{
public:
  Blackjack(int startingPoints, int numSides);         // make the game
  int play();                                          // play the game
  int playBlackjack(int gamblePoints, int chosenSize); // game for user
  int simulateHouse(int chosenSize, int max);          // game for house
private:
  int max;
};

class Slots : public Game
{
public:
  Slots(int startingPoints, int numSides); // make the game

  int play();                                      // play the game
  int playSlots(int gamblePoints, int chosenSize); // logic for slots
};

#endif // GAMES_H
