/** -----------------------------------------------------------------------------
 *
 * @file  Printboard.h
 * @author Team2
 * Assignment:   EECS-448 Project1
 * @date Feb 13, 2022
 * brief:This document is responsible for showing the sea surface to player.
 *
 ---------------------------------------------------------------------------- **/
#include "Ingame.h"
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
