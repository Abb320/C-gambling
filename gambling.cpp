#include <iostream>
#include <iostream>
#include <limits>
#include <array>
#include "games.h"
using namespace std;

// Ermin Dzanic
// CSC1061 Computer Sci 2
// Prof. Ralph Newby
// Gambling game

int main()
{

  // creating prizes
  Prize prize1("Teddy Bear", 100);
  Prize prize2("Yoyo", 50);
  Prize prize3("Candy", 10);
  Prize prize4("Xbox", 500);
  Prize prize5("Ps5", 500);
  Prize prize6("Nerf Gun", 300);
  Prize prize7("Chess set", 150);
  Prize prize8("Drone", 1000);
  Prize prize9("Toy", 100);
  Prize prize10("THE Death Star", 999999);

  // creating shop and adding items to shop
  Shop shop;

  shop.addPrize(prize1);
  shop.addPrize(prize2);
  shop.addPrize(prize3);
  shop.addPrize(prize4);
  shop.addPrize(prize5);
  shop.addPrize(prize6);
  shop.addPrize(prize7);
  shop.addPrize(prize8);
  shop.addPrize(prize9);
  shop.addPrize(prize10);

  // some variables and pointers used through out the code

  // win used as a place holder for values to subtract from points
  int *win;
  int winnings = 0;
  win = &winnings;

  int gamblePoints = 1;
  int diceSize = 6;

  // points player has
  int *pts;
  int points = 500;
  pts = &points;

  // starting loop for what user wants too do
  while (true)
  {
    cout << endl;
    cout << "You have " << *pts << "\n";
    cout << "Choose a game to play:\n";
    cout << "1. Roulette (pay out based on selection) \n";
    cout << "2. Blackjack (2x pay out on win) \n";
    cout << "3. Slots (1.5x pay out times number of sides on dice) \n";
    cout << "4. Prize counter (see owned or buy prizes) \n";
    cout << "Enter your choice (1-4) or any other character to quit: ";

    // get users choice
    int choice;
    cin >> choice;

    if (choice < 1 || 5 <= choice) // if the user puts something not a choice game will end
    {
      // show final points and prizes
      cout << "Exiting the game. Final points: " << *pts << endl;
      cout << "You also bought " << endl;
      shop.boughtList();
      system("pause");
      break;
    }
    else if (choice == 1 || choice == 2 || choice == 3)
    {
      // if the choice is 1 to 3, the user will need to select an amount of points to gamble and a dice size
      while (true)
      {
        gamblePoints = howMuchGamble(*pts);
        diceSize = diceSide(diceSize);
        cout << endl;
        break;
      }
    }
    else
    { // otherwise if they put 4 they will be taken to the shop
    }

    switch (choice)
    {
    case 1:
    {                                                // if they choose 1, they will play the roulette game
      RouletteGame roulette(gamblePoints, diceSize); // create game
      *win = gamblePoints * roulette.play();         // change win pointer
      pointChange(*win);                             // display point change
      *pts += *win;                                  // change points
      break;
    }
    case 2: // if they choose 2, they will play black jack.
    {
      Blackjack blackjack(gamblePoints, diceSize); // create game
      *win = gamblePoints * blackjack.play();      // change win pointer
      pointChange(*win);                           // diplay point change
      *pts += *win;                                // change points
      break;
    }
    case 3: // if they choose 3, they will play slots
    {
      Slots slots(gamblePoints, diceSize); // create game
      *win = gamblePoints * slots.play();  // change win pointer
      pointChange(*win);                   // display point change
      *pts += *win;                        // change points
      break;
    }
    case 4: // if they choose 4, they will see the store
    {
      // get user input to see the store or the bought prizes
      char option;
      cout << endl;
      cout << "Would you like to (V)iew your prizes or (B)uy prizes? ";
      cin >> option;

      // logic for seeing bough prizes
      if (option == 'V' || option == 'v')
      {
        shop.displayBought(); // View bought prizes
        // logic for seeing the store
      }
      else if (option == 'B' || option == 'b')
      {
        *pts = *pts - shop.displayStore(*pts); // Display available prizes and change points if they bought something
      }
      else
      {
        // error handeling
        cout << "Invalid option." << endl;
      }
      break;
    }
    default:
      break;
    }
  }

  return 0;
}
