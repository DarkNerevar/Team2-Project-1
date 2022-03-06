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
#include "Move.h"
void Executive::playGame()
{
  while(checkIfFinished() == false)				//game loop that runs as long as the game is not finished
  {
    if (checkIfFinished() == false)			//player1's turn is first then player2
    {player1Turn();}
    if (checkIfFinished() == false)
    {player2Turn();}
  }
  if (checkEarlyTermination() == true)
  {
    earlyTermination(); //calls game ending for early termination
  }
  else
  {
    gameOver(); //calls game ending for non-early termination
  }
}
void Executive::earlyTermination()
{
	cout << "\n\nProgram terminated early.\n\n";
}
void Executive::gameOver()
{
	cout << "\n\nGAME OVER!\n\n";
	cout << "Player " << m_winner << " has won!";
	cout << "\n\nCONGRATULATIONS\n\n";
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
      else if(m_playerChoice == 2) {  //move ship
        if(move(1) == 1) { //if the player decides to go back
          std::cout << "\n\n\t\tgoing back\n" << std::endl;
          player1Turn();
        } else {
          std::cout << "\n\n\t\tend of turn\n" << std::endl;
        }
      }
      else if (m_playerChoice == 3)			//print boards
      {
        printPlayer1OpponentKey();
        printPlayer1PersonalKey();
      }
      else if (m_playerChoice == 4)
      {printRules();}						//see rules and info
      else if (m_playerChoice == 5)			//ends program early
      {
        m_isGameFinished = true;
        m_isGameTerminated = true;
      }
      else
      {cout << "Invalid entry.\n";}
    } while (m_playerChoice != 1  && m_playerChoice != 2 && checkEarlyTermination() == false);			//repeats until player1's turn is over (after they attack or exit program)

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
      else if(m_playerChoice == 2) {  //move ship
        if(move(2) == 1) { //if the player decides to go back
          std::cout << "\n\n\t\tgoing back\n" << std::endl;
          player2Turn();
        } else {
          std::cout << "\n\n\t\tend of turn\n" << std::endl;
        }
      }
      else if (m_playerChoice == 3)			//prints boards
      {
        printPlayer2OpponentKey();
        printPlayer2PersonalKey();
      }
      else if (m_playerChoice == 4)			//see rules and info
      {printRules();}
      else if (m_playerChoice == 5)			//ends program early
      {
        m_isGameFinished = true;
        m_isGameTerminated = true;
      }
      else
      {cout << "Invalid entry.\n";}
    } while (m_playerChoice != 1 && m_playerChoice != 2 && checkEarlyTermination() == false);			//repeats until player2's turn is over (after they attack or exit program)

}

