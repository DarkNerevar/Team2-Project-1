#include "Executive.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include "stdlib.h"
using namespace std;

Executive::Executive()
{
  m_player1PersonalKey = new char*[m_rows];			//Initializes the boards
  m_player2PersonalKey = new char*[m_rows];
  m_player1OpponentKey = new char*[m_rows];
  m_player2OpponentKey = new char*[m_rows];

  boardSetup();				//call to set up the boards
  playGame();				//call to run the game
}
void Executive::boardSetup()
{

  //Initializes arrays---------------------------
  for (int i = 0; i < m_rows; i++)
  {
    m_player1PersonalKey[i] = new char [m_cols];
    m_player2PersonalKey[i] = new char [m_cols];
    m_player1OpponentKey[i] = new char [m_cols];
    m_player2OpponentKey[i] = new char [m_cols];
  }

  for (int i = 0; i < m_rows; i++)
  {
    for (int j = 0; j < m_cols; j++)
    {
      m_player1PersonalKey[i][j] = '~';
      m_player2PersonalKey[i][j] = '~';
      m_player1OpponentKey[i][j] = '?';
      m_player2OpponentKey[i][j] = '?';
    }
  }
  
	startMenu();		//prints the start menu
  
  //--------------------------------------------
  //PLAYER 1 SETS THEIR BOARD BELOW
  //--------------------------------------------
  printPlayer1PersonalKey();			//prints player1's board
  int shipCount = 0;
  for (int i = 0; i < m_shipAmount; i++) //#ships to set
  {
		do							//has the user input the orientation for ship placement
		{
			cout << "\n1) Vertical\n";
			cout << "2) Horizontal\n";
			cout << "Which orientation would you like for ship " << i+1 << ": ";
			m_shipOrientation = validateInput();
			if(m_shipOrientation < 1 || m_shipOrientation > 2)
			{cout << "Invalid Input";}
		}while(m_shipOrientation < 1 || m_shipOrientation > 2);
   
	do
    {
        cout << "Player 1: Please enter column (A-J) for ship " << (i + 1) << ": ";			//user chooses column
        cin >> m_tempCol;
        m_shipCol = (int(toupper(m_tempCol)) - 65);

        cout << "Player 1: Please enter row (1-10) for ship " << (i + 1) << ": ";					//user chooses row
        m_shipRow = validateInput()-1;
		
		counter = 0;								//counter is used to check if placement is valid
		for(int j=0; j<=i; j++)
		{
			if(m_shipOrientation == 1)			//vertical orientation
			{
				//checks if the ship is out of bounds
				if ( (m_shipCol < 0 || m_shipCol >= m_cols) || ( (m_shipRow + j) < 0 || (m_shipRow + j) >= m_rows) )
				{
					cout << "Out of Bounds.\n";
					counter++;
				}
				//checks if the coordinate is already occupied
				else if(m_player1PersonalKey[m_shipRow + j][m_shipCol] == 'S' )
				{
					cout << "There's already a ship there.\n";
					counter++;
				}
			}
			if(m_shipOrientation == 2)				//horizontal orientation
			{
				//checcks if the ship is out of bounds
				if ( ( (m_shipCol + j) < 0 || (m_shipCol + j) >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
				{
					cout << "Out of Bounds.\n";
					counter++;
				}
				//checks if the coordinate is already occupied
				else if( m_player1PersonalKey[m_shipRow][m_shipCol + j] == 'S' )
				{
					cout << "There's already a ship there.\n";
					counter++;
				}
			}
		}
        if (counter != 0)			//prints if placement was invalid
        {cout << "Placement is not valid! Please enter a valid coordinate." << '\n';}
        else					//if placement was valid, then the ship is placed
        {
          for(int j=0; j<=i; j++)			//for loop places each section of the ship
          {
            if(m_shipOrientation == 1)
            {
              m_player1PersonalKey[m_shipRow + j][m_shipCol] = 'S';
              string coord = char((m_shipCol)+65)+to_string(m_shipRow+j+1);
              m_player1Ships[shipCount] = coord;
            }
            if(m_shipOrientation == 2)
            {
              m_player1PersonalKey[m_shipRow][m_shipCol + j] = 'S';
              string coord =char((m_shipCol+j)+65)+to_string(m_shipRow+1);
              m_player1Ships[shipCount] = coord;
            }
            shipCount++;
          }
        }
    }while (counter != 0);			//repeats until the ship is placed
  }
  cout << string(50,'\n');
  //--------------------------------------------
  //PLAYER 2 SETS THEIR BOARD BELOW
  //--------------------------------------------
  //same code as above, but for player 2
  
  printPlayer2PersonalKey();			//prints player2's board
  shipCount = 0;
  for (int i = 0; i < m_shipAmount; i++) //#ships to set
  {
		do				//allows the user to choose the orientation of the ship
		{
			cout << "\n1) Vertical\n";
			cout << "2) Horizontal\n";
			cout << "Which orientation would you like for ship " << i+1 << ": ";
			m_shipOrientation = validateInput();
			if(m_shipOrientation < 1 || m_shipOrientation > 2)
			{cout << "Invalid Input";}
		}while(m_shipOrientation < 1 || m_shipOrientation > 2);
   
	do
    {
        cout << "Player 2: Please enter column (A-J) for ship " << (i + 1) << ": ";			//gets the column for placement
        cin >> m_tempCol;
        m_shipCol = (int(toupper(m_tempCol)) - 65);

        cout << "Player 2: Please enter row (1-10) for ship " << (i + 1) << ": ";				//gets the row for placement
        m_shipRow = validateInput()-1;
		
		counter = 0;
		for(int j=0; j<=i; j++)
		{
			if(m_shipOrientation == 1)			//vertical orientation
			{
				if ( (m_shipCol < 0 || m_shipCol >= m_cols) || ( (m_shipRow + j) < 0 || (m_shipRow + j) >= m_rows) )
				{
					cout << "Out of Bounds.\n";
					counter++;
				}
				else if(m_player2PersonalKey[m_shipRow + j][m_shipCol] == 'S' )
				{
					cout << "There's already a ship there.\n";
					counter++;
				}
			}
			if(m_shipOrientation == 2)			//horizontal orientation
			{
				if ( ( (m_shipCol + j) < 0 || (m_shipCol + j) >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
				{
					cout << "Out of Bounds.\n";
					counter++;
				}
				else if( m_player2PersonalKey[m_shipRow][m_shipCol + j] == 'S' )
				{
					cout << "There's already a ship there.\n";
					counter++;
				}
			}
		}
        if (counter != 0)
        {cout << "Placement is not valid! Please enter a valid coordinate." << '\n';}
        else
        {
          for(int j=0; j<=i; j++)			//places each section of the ship
          {
            if(m_shipOrientation == 1)
            {
              m_player2PersonalKey[m_shipRow + j][m_shipCol] = 'S';
              string coord = char((m_shipCol)+65)+to_string(m_shipRow+j+1);
              m_player2Ships[shipCount] = coord;
            }
            if(m_shipOrientation == 2)
            {
              m_player2PersonalKey[m_shipRow][m_shipCol + j] = 'S';
              string coord = char((m_shipCol+j)+65)+to_string(m_shipRow+1);
              m_player2Ships[shipCount] = coord;
            }
            shipCount++;
          }
        }
    }while (counter != 0);
  }
  cout << string(50,'\n');
}
void Executive::startMenu()
{
	cout << "\n\n";
	cout << "-----------------------------------Battleship------------------------------------" << '\n';
	cout << "---------------------------------------------------------------------------------" << '\n';
	cout << "\n\n";
	cout << "Welcome to the Game!\n";
	
	printRules();			//prints information about the game
  
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
  setupShipsArr();
  cout << '\n';
}
void Executive::printRules()
{
	cout << "\n--------Rules & Information---------\n";
	cout << "The Objective of the game is to sink all of your opponents ships before they sink yours.\n";
	cout << "During your turn, you will be asked to input coordinates to fire upon.\n";
	cout << "To start the game you will be asked how many ships you want in play.\n";
	cout << "Then each player will take turns placing their ships.\n";
	cout << "Ships are placed either vertically or horizontally, you will be given the choice.\n";
	cout << "Players will then input the coordinates for their ship placement.\n";
	cout << "Coordinates for ship placement correspond to the front tip of each ship.\n";
	cout << "The orientation of the ship determines where the back of the ship is located\n";
	cout << "The ship will occupy the coordinates below or to the right of the tip of each ship.\n";
	cout << "Once all ships are placed, each player will take turns attacking.\n";
	cout << "The first player to destroy all of their opponent's ships wins.\n";
	cout << "Have fun!\n\n";
}
void Executive::playGame()
{
  do				//game loop that runs as long as the game is not finished
  {
    if (checkIfFinished() == false)			//player1's turn is first then player2
    {player1Turn();}
    if (checkIfFinished() == false)
    {player2Turn();}
  } while(checkIfFinished() == false);
  gameOver();		//calls game ending
}
void Executive::gameOver()
{
	cout << "\n\nGAME OVER!\n\n";
	cout << "Player " << m_winner << " has won!";
	cout << "\n\nCONGRADULATIONS\n\n";
}
void Executive::printMenu()
{
  cout << "-------Options-------\n";
  cout << "1) Attack enemy\n";
  cout << "2) View screens\n";
  cout << "3) See rules\n";
  cout << "Choice: ";

}
void Executive::printPlayer1PersonalKey()
{
  cout << "------------------------------[Player 1's Own Grid]------------------------------" << '\n';
  cout << "---------------------------------------------------------------------------------" << '\n';

  cout << '\t';
  for (int i = 0; i < m_cols; i++)		//prints the column coordinates (A-J) on the top of the board
  {
    cout << char(i + 65) << '\t';		//converts ascii letters(A-J) to numbers (0-9)
  }
  cout << '\n';
  for (int i = 0; i < m_rows; i++)
  {
    cout << (i+1) << '\t';				//prints the row coordinates (1-10) on the side of the board
    for (int j = 0; j < m_cols; j++)
    {
      cout << m_player1PersonalKey[i][j] << '\t';		//prints the grid of the players board
    }
    cout << '\n';
  }

  cout << "---------------------------------------------------------------------------------" << '\n';
}
void Executive::printPlayer2PersonalKey()
{
  cout << "------------------------------[Player 2's Own Grid]------------------------------" << '\n';
  cout << "---------------------------------------------------------------------------------" << '\n';

  cout << '\t';
  for (int i = 0; i < m_cols; i++)			//prints the column coordinates (A-J) on the top of the board	
  {
    cout << char(i + 65) << '\t';			//converts ascii letters(A-J) to numbers (0-9)
  }
  cout << '\n';
  for (int i = 0; i < m_rows; i++)
  {
    cout << (i+1) << '\t';					//prints the row coordinates (1-10) on the side of the board
    for (int j = 0; j < m_cols; j++)
    {
      cout << m_player2PersonalKey[i][j] << '\t';		//prints the grid of the players board
    }
    cout << '\n';
  }
  cout << "---------------------------------------------------------------------------------" << '\n';
}
void Executive::printPlayer1OpponentKey()
{
  cout << "----------------------------[Player 1's Battle Grid:]----------------------------" << '\n';
  cout << "---------------------------------------------------------------------------------" << '\n';
  cout << '\t';
  for (int i = 0; i < m_cols; i++)			//prints the column coordinates (A-J) on the top of the board
  {
    cout << char(i + 65) << '\t';			//converts ascii letters(A-J) to numbers (0-9)
  }
  cout << '\n';
  for (int i = 0; i < m_rows; i++)
  {
    cout << (i+1) << '\t';					//prints the row coordinates (1-10) on the side of the board
    for (int j = 0; j < m_cols; j++)
    {
      cout << m_player1OpponentKey[i][j] << '\t';			//prints the grid of the opponents board
    }
    cout << '\n';
  }
  cout << "---------------------------------------------------------------------------------" << '\n';
}
void Executive::printPlayer2OpponentKey()
{
  cout << "----------------------------[Player 2's Battle Grid:]----------------------------" << '\n';
  cout << "---------------------------------------------------------------------------------" << '\n';
  cout << '\t';
  for (int i = 0; i < m_cols; i++)				//prints the column coordinates (A-J) on the top of the board
  {
    cout << char(i + 65) << '\t';				//converts ascii letters(A-J) to numbers (0-9)
  }
  cout << '\n';
  for (int i = 0; i < m_rows; i++)
  {
    cout << (i+1) << '\t';						//prints the row coordinates (1-10) on the side of the board
    for (int j = 0; j < m_cols; j++)
    {
      cout << m_player2OpponentKey[i][j] << '\t';			//prints the grid of the opponents board
    }
    cout << '\n';
  }
  cout << "---------------------------------------------------------------------------------" << '\n';
}
void Executive::player1Turn()
{
  cout << "Player 1 turn.\n";
  do
  {
    printMenu();					//prints the menu of options
    m_playerChoice = validateInput();

      if (m_playerChoice == 1)		//attack
      {player1Attack();}
      else if (m_playerChoice == 2)			//print boards
      {
        printPlayer1OpponentKey();
        printPlayer1PersonalKey();
      }
      else if (m_playerChoice == 3)
      {printRules();}						//see rules and info
      else
      {cout << "Invalid entry.\n";}
    } while (m_playerChoice != 1);			//repeats until player1's turn is over (after they attack)

}
void Executive::player2Turn()
{
  cout << "Player 2 turn.\n";
  do
  {
    printMenu();							//prints the menu of options
    m_playerChoice = validateInput();

      if (m_playerChoice == 1)				//attack
      {player2Attack();}
      else if (m_playerChoice == 2)			//prints boards
      {
        printPlayer2OpponentKey();
        printPlayer2PersonalKey();
      }
      else if (m_playerChoice == 3)			//see rules and info
      {printRules();}
      else
      {cout << "Invalid entry.\n";}
    } while (m_playerChoice != 1);			//repeats until player2's turn is over (after they attack)

}
void Executive::player1Attack()
{
  //1) attack player2
  do
  {
	  counter = 0;					//counter used to check if attack was valid
	  
    cout << "Player 1: Please enter column (A-J) to attack player 2: ";				//gets the column to attack
    cin >> m_tempCol;
    m_shipCol = (int(toupper(m_tempCol)) - 65);
    cout << "Please enter row (1-10) to attack player 2: ";						//gets the row to attack
    m_shipRow = validateInput()-1;

	//checks if coordinates are in bounds
    if ( (m_shipCol < 0 || m_shipCol >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )			
    {
      cout << "Invalid coordinate entry!" << '\n';
	  counter++;
    }
	//checks if the coordinate was already hit
	else if ( m_player2PersonalKey[m_shipRow][m_shipCol] == 'X' )
	{
		cout << "Coordinate Already Hit. Aim Elsewhere!\n";
		counter++;
	}
	//checks if the coordinate was already shot
	else if ( m_player1OpponentKey[m_shipRow][m_shipCol] == '~' )
	{
		cout << "Coordinate Already Shot. Aim Elsewhere!\n";
		counter++;
	}
  }while (counter != 0);		//repeats until the shot is valid

  cout << string(50,'\n');

  //2) change player2's personal key if hit, and player1's opponent key regardless
  if ( m_player2PersonalKey[m_shipRow][m_shipCol] == 'S' )
  {
    m_player2PersonalKey[m_shipRow][m_shipCol] = 'X';
    m_player1OpponentKey[m_shipRow][m_shipCol] = 'X';
    hit(toupper(m_tempCol), m_shipRow+1, 1);
    bool tempSunk = isSunk(1);
    if(tempSunk)
    {
      cout << "----------------------\n";
      cout << "Player 1 sunk Player 2's ship!" << '\n';
      cout << "----------------------\n";
    }
    else
    {
      cout << "----------------------\n";
      cout << "Player 1 hit Player 2's ship!" << '\n';
      cout << "----------------------\n";
    }
  }
  else
  {
    cout << "-------------------------\n";
    cout << "Player 1 missed!" << '\n';
    cout << "-------------------------\n";
    m_player1OpponentKey[m_shipRow][m_shipCol] = '~';
  }
}
void Executive::player2Attack()
{
  //1) attack player1
  do
  {
	  counter = 0;							//counter used to check if attack was valid
	  
    cout << "Player 2: Please enter column (A-J) to attack player 1: ";			//gets the column to attack
    cin >> m_tempCol;
    m_shipCol = (int(toupper(m_tempCol)) - 65);
    cout << "Please enter row (1-10) to attack player 1: ";					//gets the row to attack
    m_shipRow = validateInput()-1;

	//checks if coordinates are in bounds
    if ( (m_shipCol < 0 || m_shipCol >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
    {
      cout << "Invalid coordinate entry!" << '\n';
	  counter++;
    }
	//checks if the coordinate was already hit
	else if ( m_player1PersonalKey[m_shipRow][m_shipCol] == 'X' )
	{
		cout << "Coordinate Already Hit. Aim Elsewhere!\n";
		counter++;
	}
	//checks if the coordinate was already shot
	else if ( m_player2OpponentKey[m_shipRow][m_shipCol] == '~' )
	{
		cout << "Coordinate Already Shot. Aim Elsewhere!\n";
		counter++;
	}
  }while (counter != 0);				//repeats until the shot is valid

  cout << string(50,'\n');

  //2) change player1's personal key if hit, and player2's personal key regardless
  if ( m_player1PersonalKey[m_shipRow][m_shipCol] == 'S' )
  {
    m_player1PersonalKey[m_shipRow][m_shipCol] = 'X';
    m_player2OpponentKey[m_shipRow][m_shipCol] = 'X';
    hit(toupper(m_tempCol), m_shipRow+1, 2);
    bool tempSunk = isSunk(2);
    if(tempSunk)
    {
      cout << "----------------------\n";
      cout << "Player 2 sunk Player 1's ship!" << '\n';
      cout << "----------------------\n";
    }
    else
    {
      cout << "----------------------\n";
      cout << "Player 2 hit Player 1's ship!" << '\n';
      cout << "----------------------\n";
    }
  }
  else
  {
    cout << "-------------------------\n";
    cout << "Player 2 missed!" << '\n';
    cout << "-------------------------\n";
    m_player2OpponentKey[m_shipRow][m_shipCol] = '~';
  }
}
bool Executive::checkIfFinished()
{
  m_player1ShipsRemaining = 0;
  m_player2ShipsRemaining = 0;

	//checks the entire board for remaining ships
  for (int i = 0; i < m_rows; i++)
  {
    for (int j = 0; j < m_cols; j++)
    {
      if (m_player1PersonalKey[i][j] == 'S')
      {m_player1ShipsRemaining ++;}
      if (m_player2PersonalKey[i][j] == 'S')
      {m_player2ShipsRemaining ++;}
    }
  }
  if (m_player1ShipsRemaining == 0)
  {
    m_winner = 2;
    return(true);
  }
  else if (m_player2ShipsRemaining == 0)
  {
    m_winner = 1;
    return(true);
  }
  else
  {return (false);}
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

//checks to see if a whole ship has sunk
 bool Executive::isSunk(int player)
 {
   int count = 1;
   if(player == 1) //checks if player 1 sunk one of player 2's ships
   {
     //goes through the array to see if the ship has sunk
     while(count <= m_shipArrSize)
     {
        int hit = 0;
        int start, end;
        getArrRange(count, &start, &end);
        for(int i = start; i <= end; i++)
        {
          if(m_player2Ships[i] == "L")
          {
            hit++;
          }
        }
        // if the hit amount == count, changes "L" to "X" so it doesn't count it as sunk again
        if(hit == count)
        {
          for(int i = start; i <= end; i++)
          {
            m_player2Ships[i] = "X";
          }
          return true;
        }
        count++;
      }
   }
   else //checks if player 2 sunk one of player 1's ships
   {
      while(count <= m_shipArrSize)
      {
        int hit = 0;
        int start, end;
        getArrRange(count, &start, &end);
        for(int i = start; i <= end; i++)
        {
          if(m_player1Ships[i] == "L")
          {
            hit++;
          }
        }
        if(hit == count)
        {
          for(int i = start; i <= end; i++)
          {
            m_player1Ships[i] = "X";
          }
          return true;
        }
        count++;
      }
    }
    return false;
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