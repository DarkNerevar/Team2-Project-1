/** -----------------------------------------------------------------------------
 *
 * @file  Ingame.h
 * @author Team2
 * Assignment:   EECS-448 Project1
 * @date Feb 13, 2022
 * brief:This file mainly deals with the interaction with the player.
 *
 ---------------------------------------------------------------------------- **/
#include "Attack.h"
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

