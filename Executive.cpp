/** -----------------------------------------------------------------------------
 *
 * @file  Executive.cpp
 * @author Team2
 * Assignment:   EECS-448 Project1
 * @date Feb 13, 2022
 *
 ---------------------------------------------------------------------------- **/

#include "Executive.h"
#include "BoardSetup.h"

Executive::Executive()
{
  m_player1PersonalKey = new char*[m_rows];			//Initializes the boards
  m_player2PersonalKey = new char*[m_rows];
  m_player1OpponentKey = new char*[m_rows];
  m_player2OpponentKey = new char*[m_rows];

  m_player1PersonalOrigKey = new char* [m_rows];
  m_player2PersonalOrigKey = new char* [m_rows];

  boardSetup();				//call to set up the boards
  origCopy(); //creates copies of original personal keys
  playGame();				//call to run the game
}
void Executive::startMenu()
{
	cout << "\n\n";
	cout << "-----------------------------------Battleship------------------------------------" << '\n';
	cout << "---------------------------------------------------------------------------------" << '\n';
	cout << "\n\n";
	cout << "Welcome to the Game!\n";
	
	//---------------------------------------------
	//Determines if the game will be one or two player
	cout << "Would you like to a one player game, or play a two player game (pass and play)?:";

do
  {
    cout << "Please input which type of game you would like to play:\n1 - one player game\n2 - two player game\n";
    m_playerAmount = validateInput();
    if (m_playerAmount < 1 || m_playerAmount > 2)
    {
      cout << "Incorrect number of players!" << '\n';
    }

  } while (m_playerAmount < 1 || m_playerAmount > 2);
    cout << '\n';
	if(m_playerAmount == 2)
	{
		printRules();			//prints information about the game
		shipAmount();			//collects the number of ships
		setupShipsArr();		//creates the ship objects
		cout << '\n';
	}
	else if(m_playerAmount == 1)
	{
		
		printRules1Player();			//prints information about the game
		shipAmount();					//collects the number of ships
		setupShipsArr();				//creates the ship objects
		cout << '\n';
		difficultyLevel();				//collects the difficulty level
		}
  
  
}

void Executive::difficultyLevel()
{
	//---------------------------------------------
		//Obtains the difficulty level from the user
  
		do
		{
			cout << "Please input the difficulty you would like to play on:\n1 - Easy\n2 - Medium\n3 - Hard\n";
			m_opponentDifficulty = validateInput();
			if (m_opponentDifficulty < 1 || m_opponentDifficulty > 3)
			{
				cout << "Incorrect difficulty level!" << '\n';
			}

		} while (m_opponentDifficulty < 1 || m_opponentDifficulty > 3);
		cout << '\n';
}
void Executive::shipAmount()
{
	//--------------------------------------------
	//Obtains number of ships to play with from user
		do
		{
			cout << "Please input amount of ships (1-5) to play with: ";
			m_shipAmount = validateInput();
			if (m_shipAmount < 1 || m_shipAmount > 5)
			{
				cout << "Incorrect amount of ships!" << '\n';
			}

		} while (m_shipAmount < 1 || m_shipAmount > 5);
}
void Executive::printRules()
{
	cout << "\n--------Rules & Information---------\n";
	cout << "The Objective of the game is to sink all of your opponents ships before they sink yours.\n";
	cout << "To start the game you will be asked how many ships you want in play.\n";
	cout << "Then each player will take turns placing their ships.\n";
	cout << "Ships are placed either vertically or horizontally, you will be given the choice.\n";
	cout << "Players will then input the coordinates for their ship placement.\n";
	cout << "Coordinates for ship placement correspond to the front tip of each ship.\n";
	cout << "The orientation of the ship determines where the back of the ship is located\n";
	cout << "The ship will occupy the coordinates below or to the right of the tip of each ship.\n";
	cout << "Once all ships are placed, each player will take turns attacking.\n";
	cout << "During your turn, you will be asked to input coordinates to fire upon.\n";
	cout << "The first player to destroy all of their opponent's ships wins.\n";
	cout << "Have fun!\n\n";
}

void Executive::printRules1Player()
{
	cout << "\n--------Rules & Information---------\n";
	cout << "The Objective of the game is to sink all of your opponents ships before they sink yours.\n";
	cout << "To start the game you will be asked how many ships you want in play.\n";
	cout << "Then you will be asked what difficulty level you would like to play on.\n";
	cout << "Then you will place your ships.\n";
	cout << "Ships are placed either vertically or horizontally, you will be given the choice.\n";
	cout << "You will then input the coordinates for your ship placement.\n";
	cout << "Coordinates for ship placement correspond to the front tip of each ship.\n";
	cout << "The orientation of the ship determines where the back of the ship is located\n";
	cout << "The ship will occupy the coordinates below or to the right of the tip of each ship.\n";
	cout << "Once all ships are placed, each player (you and the computer opponent) will take turns attacking.\n";
	cout << "During your turn, you will be asked to input coordinates to fire upon.\n";
	cout << "The first player to destroy all of their opponent's ships wins.\n";
	cout << "Have fun!\n\n";
}
void Executive::printMenu()
{
  cout << "-------Options-------\n";
  cout << "1) Attack enemy\n";
  std::cout << "2) Move ship\n";
  cout << "3) View screens\n";
  cout << "4) See rules\n";
  cout << "5) Terminate program\n";
  cout << "Choice: ";

}
int Executive::validateInput()			//checks if interger input is valid
{
	int choice;
    std::cin >> choice;
    while ( std::cin.fail() )			//repeats until a valid integer is inputed
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Sorry, your input did not seem to be an int. Try again: ";
        std::cin >> choice;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return(choice);				//returns the valid input
}

//Sets up an array with coords to where all the ship segments are
void Executive::setupShipsArr()
{
  //for loop adds the amount of shipsegments to get the array size
  // 1 ship = 1; 2 ships = 3; 3 ships = 6; 4 ships = 10; 5 ships = 15
  for(int i = 0; i <= m_shipAmount; i++)
  {
    m_shipArrSize += i;
  }

  m_player1Ships = new string[m_shipArrSize];
  m_player2Ships = new string[m_shipArrSize];
}

//if the ship segment is hit, changes the element that was hit to "L"
 void Executive::hit(char col,int row,int player)
 {
    string coord = col+to_string(row);
  if(player == 1) //player 1
  {
    for(int i = 0; i < m_shipArrSize; i++)
    {
      if(m_player2Ships[i] == coord)
      {
        m_player2Ships[i] = "L";
      }
    }
  }
  else //player 2
  {
    for(int i = 0; i < m_shipArrSize; i++)
    {
      if(m_player1Ships[i] == coord)
      {
        m_player1Ships[i] = "L";
      }
    }
  }
 }

//switch statement to get the range of the ship segments depending on the size of the ships
 void Executive::getArrRange(int count, int *start, int *end)
 {
   //depending on count sets the start and end variables. Used to traverse the array of a specific ship
   switch(count)
   {
     case 1:
      *start = 0;
      *end = 0;
      break;
    case 2:
      *start = 1;
      *end = 2;
      break;
    case 3:
      *start = 3;
      *end = 5;
      break;
    case 4:
      *start = 6;
      *end = 9;
      break;
    case 5:
      *start = 10;
      *end = 14;
      break;
   }
 }
