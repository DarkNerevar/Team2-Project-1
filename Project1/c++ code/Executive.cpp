#include "Executive.h"
#include <iostream>
#include <fstream>
#include "stdlib.h"
using namespace std;

Executive::Executive()
{
  m_player1PersonalKey = new char*[m_rows];
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
  //--------------------------------------------
  //Obtains number of ships to play with from user
  
  cout << "\n\n";
  cout << "------------------------------------Battleship-----------------------------------" << '\n';
  cout << "---------------------------------------------------------------------------------" << '\n';
  
  do
  {
    cout << "Welcome! Please input amount of ships (1-5) to play with: ";
    cin >> m_shipAmount;
    if (m_shipAmount < 1 || m_shipAmount > 5)
    {
      cout << "Incorrect amount of ships!" << '\n';
    }

  } while (m_shipAmount < 1 || m_shipAmount > 5);
  //--------------------------------------------
  //PLAYER 1 SETS THEIR BOARD BELOW
  //--------------------------------------------
  printPlayer1PersonalKey();
  for (int i = 0; i < m_shipAmount; i++) //#ships to set
  {
    m_shipNumber = 0;
    do
    {
      for (int j = 0; j <= i; j++) //# of sections in ship
      {
        m_shipNumber = j;

        cout << "Player 1: Please enter column (A-J) for ship " << (i + 1) << " , section #" << (j + 1) << ": ";
        cin >> m_tempCol;
        m_shipCol = (int(m_tempCol) - 65);

        cout << "Player 1: Please enter row for ship " << (i + 1) << " , section #" << (j + 1) << ": ";
        cin >> m_shipRow;

        if ( (m_shipCol < 0 || m_shipCol > m_cols) || (m_shipRow < 0 || m_shipRow > m_rows) || ( m_player1PersonalKey[m_shipRow][m_shipCol] == 0 ) )
        {
          cout << "Placement is not valid! Please enter a valid coordinate." << '\n';
        }
        else
        {
          m_player1PersonalKey[m_shipRow][m_shipCol] = 'S';
        }
      }
    }while ( (m_shipCol < 0 || m_shipCol > m_cols) || (m_shipRow < 0 || m_shipRow > m_rows));
  }

  cout << string(50,'\n');
  //--------------------------------------------
  //PLAYER 2 SETS THEIR BOARD BELOW
  //--------------------------------------------
  printPlayer2PersonalKey();
  for (int i = 0; i < m_shipAmount; i++) //#ships to set
  {
    m_shipNumber = 0;
    do
    {
      for (int j = 0; j <= i; j++) //# of sections in ship
      {
        m_shipNumber = j;

        cout << "Player 2: Please enter column (A-J) for ship " << (i + 1) << " , section #" << (j + 1) << ": ";
        cin >> m_tempCol;
        m_shipCol = (int(m_tempCol) - 65);

        cout << "Player 2: Please enter row for ship " << (i + 1) << " , section #" << (j + 1) << ": ";
        cin >> m_shipRow;

        if ( (m_shipCol < 0 || m_shipCol > m_cols) || (m_shipRow < 0 || m_shipRow > m_rows) || ( m_player2PersonalKey[m_shipRow][m_shipCol] == 0 ) )
        {
          cout << "Placement is not valid! Please enter a valid coordinate." << '\n';
        }
        else
        {
          m_player2PersonalKey[m_shipRow][m_shipCol] = 'S';
        }
      }
    }while ( (m_shipCol < 0 || m_shipCol > m_cols) || (m_shipRow < 0 || m_shipRow > m_rows));
  }

  cout << string(50,'\n');
  //----------------------------------------------------------------------

}
void Executive::playGame()
{
  do
  {
    if (checkIfFinished() == false)
    {
      player1Turn();
    }
    if (checkIfFinished() == false)
    {
      player2Turn();
    }
  } while(checkIfFinished() == false);

  cout << "Player " << m_winner << " has won!\n";
}
void Executive::printMenu()
{
  cout << "-------Options-------\n";
  cout << "1) Attack enemy\n";
  cout << "2) View screens\n";
  cout << "3) See rules\n";

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
    cout << i << '\t';
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
    cout << i << '\t';
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
    cout << i << '\t';
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
    cout << i << '\t';
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
    cin >> m_playerChoice;

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
        cout << "...\n";
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
    cin >> m_playerChoice;

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
        cout << "...\n";
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
    cout << "Player 1: Please enter column (A-J) to attack player 2: ";
    cin >> m_tempCol;
    m_shipCol = (int(m_tempCol) - 65);
    cout << "Please enter row (0-9) to attack player 2: ";
    cin >> m_shipRow;

    if ( (m_shipCol < 0 || m_shipCol > m_cols) || (m_shipRow < 0 || m_shipRow > m_rows) )
    {
      cout << "Invalid coordinate entry!" << '\n';
    }
  }while ( (m_shipCol < 0 || m_shipCol > m_cols) || (m_shipRow < 0 || m_shipRow > m_rows) );

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
    cout << "Player 2: Please enter column (A-J) to attack player 1: ";
    cin >> m_tempCol;
    m_shipCol = (int(m_tempCol) - 65);
    cout << "Please enter row (0-9) to attack player 1: ";
    cin >> m_shipRow;

    if ( (m_shipCol < 0 || m_shipCol > m_cols) || (m_shipRow < 0 || m_shipRow > m_rows) )
    {
      cout << "Invalid coordinate entry!" << '\n';
    }
  }while ( (m_shipCol < 0 || m_shipCol > m_cols) || (m_shipRow < 0 || m_shipRow > m_rows) );

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



/*
NEEDS IMPLEMENTATION:
-isValidMove for players one and two
-check for determining if entire ship was sunk
-Add menu for setup, something like this:
void Executive::setupMenu()
{
  cout << "1) Print personal board\n";
  cout << "2) Place ship\n";
  cout << "3) End setup\n";
}
*/
