/** -----------------------------------------------------------------------------
 *
 * @file  Attack.h
 * @author Team2
 * Assignment:   EECS-448 Project1
 * @date Feb 13, 2022
 * brief:This file is responsible for handling the operation of player attacks
 *
 ---------------------------------------------------------------------------- **/
#include "Check.h"
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