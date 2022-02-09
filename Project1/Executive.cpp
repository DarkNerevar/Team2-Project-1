#include "Executive.h"
#include <iostream>
#include <fstream>
#include <limits>
#include "stdlib.h"
using namespace std;

Executive::Executive()
{
  m_player1PersonalKey = new char*[m_rows];			//Initializes the boards
  m_player2PersonalKey = new char*[m_rows];
  m_player1OpponentKey = new char*[m_rows];
  m_player2OpponentKey = new char*[m_rows];

  boardSetup();
  playGame();
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
  printPlayer1PersonalKey();
  for (int i = 0; i < m_shipAmount; i++) //#ships to set
  {
		do
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
        cout << "Player 1: Please enter column (A-J) for ship " << (i + 1) << ": ";
        cin >> m_tempCol;
        m_shipCol = (int(m_tempCol) - 65);

        cout << "Player 1: Please enter row for ship " << (i + 1) << ": ";
        m_shipRow = validateInput()-1;
		
		counter = 0;
		for(int j=0; j<=i; j++)
		{
			if(m_shipOrientation == 1)
			{
				if ( (m_shipCol < 0 || m_shipCol >= m_cols) || ( (m_shipRow + j) < 0 || (m_shipRow + j) >= m_rows) )
				{
					cout << "Out of Bounds.\n";
					counter++;
				}
				else if(m_player1PersonalKey[m_shipRow + j][m_shipCol] == 'S' )
				{
					cout << "There's already a ship there.\n";
					counter++;
				}
			}
			if(m_shipOrientation == 2)
			{
				if ( ( (m_shipCol + j) < 0 || (m_shipCol + j) >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
				{
					cout << "Out of Bounds.\n";
					counter++;
				}
				else if( m_player1PersonalKey[m_shipRow][m_shipCol + j] == 'S' )
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
			for(int j=0; j<=i; j++)
			{
				if(m_shipOrientation == 1)
				{m_player1PersonalKey[m_shipRow + j][m_shipCol] = 'S';}
				if(m_shipOrientation == 2)
				{m_player1PersonalKey[m_shipRow][m_shipCol + j] = 'S';}
			}
        }
    }while (counter != 0);
  }
  
  cout << string(50,'\n');
  //--------------------------------------------
  //PLAYER 2 SETS THEIR BOARD BELOW
  //--------------------------------------------
  
  printPlayer2PersonalKey();
  for (int i = 0; i < m_shipAmount; i++) //#ships to set
  {
		do
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
        cout << "Player 2: Please enter column (A-J) for ship " << (i + 1) << ": ";
        cin >> m_tempCol;
        m_shipCol = (int(m_tempCol) - 65);

        cout << "Player 2: Please enter row for ship " << (i + 1) << ": ";
        m_shipRow = validateInput()-1;
		
		counter = 0;
		for(int j=0; j<=i; j++)
		{
			if(m_shipOrientation == 1)
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
			if(m_shipOrientation == 2)
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
			for(int j=0; j<=i; j++)
			{
				if(m_shipOrientation == 1)
				{m_player2PersonalKey[m_shipRow + j][m_shipCol] = 'S';}
				if(m_shipOrientation == 2)
				{m_player2PersonalKey[m_shipRow][m_shipCol + j] = 'S';}
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
	
	printRules();
  
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
  gameOver();
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
  for (int i = 0; i < m_cols; i++)
  {
    cout << char(i + 65) << '\t';
  }
  cout << '\n';
  for (int i = 0; i < m_rows; i++)
  {
    cout << (i+1) << '\t';
    for (int j = 0; j < m_cols; j++)
    {
      cout << m_player1PersonalKey[i][j] << '\t';
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
  for (int i = 0; i < m_cols; i++)
  {
    cout << char(i + 65) << '\t';
  }
  cout << '\n';
  for (int i = 0; i < m_rows; i++)
  {
    cout << (i+1) << '\t';
    for (int j = 0; j < m_cols; j++)
    {
      cout << m_player2PersonalKey[i][j] << '\t';
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
  for (int i = 0; i < m_cols; i++)
  {
    cout << char(i + 65) << '\t';
  }
  cout << '\n';
  for (int i = 0; i < m_rows; i++)
  {
    cout << (i+1) << '\t';
    for (int j = 0; j < m_cols; j++)
    {
      cout << m_player1OpponentKey[i][j] << '\t';
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
  for (int i = 0; i < m_cols; i++)
  {
    cout << char(i + 65) << '\t';
  }
  cout << '\n';
  for (int i = 0; i < m_rows; i++)
  {
    cout << (i+1) << '\t';
    for (int j = 0; j < m_cols; j++)
    {
      cout << m_player2OpponentKey[i][j] << '\t';
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
    printMenu();
    m_playerChoice = validateInput();

      if (m_playerChoice == 1)
      {
        player1Attack();
      }
      else if (m_playerChoice == 2)
      {
        printPlayer1OpponentKey();
        printPlayer1PersonalKey();
      }
      else if (m_playerChoice == 3)
      {
        printRules();
      }
      else
      {
        cout << "Invalid entry.\n";
      }
    } while (m_playerChoice != 1);

}
void Executive::player2Turn()
{
  cout << "Player 2 turn.\n";
  do
  {
    printMenu();
    m_playerChoice = validateInput();

      if (m_playerChoice == 1)
      {
        player2Attack();
      }
      else if (m_playerChoice == 2)
      {
        printPlayer2OpponentKey();
        printPlayer2PersonalKey();
      }
      else if (m_playerChoice == 3)
      {
        printRules();
      }
      else
      {
        cout << "Invalid entry.\n";
      }
    } while (m_playerChoice != 1);

}
void Executive::player1Attack()
{
  //1) attack player2
  do
  {
	  counter = 0;
    cout << "Player 1: Please enter column (A-J) to attack player 2: ";
    cin >> m_tempCol;
    m_shipCol = (int(m_tempCol) - 65);
    cout << "Please enter row (1-10) to attack player 2: ";
    m_shipRow = validateInput()-1;

    if ( (m_shipCol < 0 || m_shipCol >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
    {
      cout << "Invalid coordinate entry!" << '\n';
	  counter++;
    }
	else if ( m_player2PersonalKey[m_shipRow][m_shipCol] == 'X' )
	{
		cout << "Coordinate Already Hit. Aim Elsewhere!\n";
		counter++;
	}
	else if ( m_player1OpponentKey[m_shipRow][m_shipCol] == '~' )
	{
		cout << "Coordinate Already Shot. Aim Elsewhere!\n";
		counter++;
	}
  }while (counter != 0);

  cout << string(50,'\n');

  //2) change player2's personal key if hit, and player1's opponent key regardless
  if ( m_player2PersonalKey[m_shipRow][m_shipCol] == 'S' )
  {
    cout << "----------------------\n";
    cout << "Player 1 hit Player 2's ship!" << '\n';
    cout << "----------------------\n";
    m_player2PersonalKey[m_shipRow][m_shipCol] = 'X';
    m_player1OpponentKey[m_shipRow][m_shipCol] = 'X';
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
	  counter = 0;
    cout << "Player 2: Please enter column (A-J) to attack player 1: ";
    cin >> m_tempCol;
    m_shipCol = (int(m_tempCol) - 65);
    cout << "Please enter row (1-10) to attack player 1: ";
    m_shipRow = validateInput()-1;

    if ( (m_shipCol < 0 || m_shipCol >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
    {
      cout << "Invalid coordinate entry!" << '\n';
	  counter++;
    }
	else if ( m_player1PersonalKey[m_shipRow][m_shipCol] == 'X' )
	{
		cout << "Coordinate Already Hit. Aim Elsewhere!\n";
		counter++;
	}
	else if ( m_player2OpponentKey[m_shipRow][m_shipCol] == '~' )
	{
		cout << "Coordinate Already Shot. Aim Elsewhere!\n";
		counter++;
	}
  }while (counter != 0);

  cout << string(50,'\n');

  //2) change player1's personal key if hit, and player2's personal key regardless
  if ( m_player1PersonalKey[m_shipRow][m_shipCol] == 'S' )
  {
    cout << "----------------------\n";
    cout << "Player 2 hit Player 1's ship!" << '\n';
    cout << "----------------------\n";
    m_player1PersonalKey[m_shipRow][m_shipCol] = 'X';
    m_player2OpponentKey[m_shipRow][m_shipCol] = 'X';
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

  for (int i = 0; i < m_rows; i++)
  {
    for (int j = 0; j < m_cols; j++)
    {
      if (m_player1PersonalKey[i][j] == 'S')
      {
        m_player1ShipsRemaining ++;
      }
      if (m_player2PersonalKey[i][j] == 'S')
      {
        m_player2ShipsRemaining ++;
      }
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
  {
    return (false);
  }
}
int Executive::validateInput()
{
	int choice;
    std::cin >> choice;
    while ( std::cin.fail() )
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Sorry, your input did not seem to be an int. Try again: ";   
        std::cin >> choice;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return(choice);
}

