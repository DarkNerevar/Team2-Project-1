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
          player1Turn();
        } 
      }
      else if (m_playerChoice == 3) {   //giant shot
        player1GiantShot();
      }
      else if (m_playerChoice == 4) {   //scoreboard

      }
      else if (m_playerChoice == 5)			//print boards
      {
        printPlayer1OpponentKey();
        printPlayer1PersonalKey();
      }
      else if (m_playerChoice == 6)
      {printRules();}						//see rules and info
      else if (m_playerChoice == 7)			//ends program early
      {
        m_isGameFinished = true;
        m_isGameTerminated = true;
      }
      else
      {cout << "Invalid entry.\n";}
    } while (m_playerChoice != 1  && m_playerChoice != 2 && m_playerChoice != 3 && checkEarlyTermination() == false);			//repeats until player1's turn is over (after they attack or exit program)

}
void Executive::player2Turn()
{
	if(m_playerAmount == 2)
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
          player2Turn();
        }
      }
      else if (m_playerChoice == 3) {   //giant shot
        player1GiantShot();
      }
      else if (m_playerChoice == 4) {   //scoreboard

      }
			else if (m_playerChoice == 5)			//prints boards
			{
				printPlayer2OpponentKey();
				printPlayer2PersonalKey();
			}
			else if (m_playerChoice == 6)			//see rules and info
			{printRules();}
			else if (m_playerChoice == 7)			//ends program early
			{
				m_isGameFinished = true;
				m_isGameTerminated = true;
			}
			else
			{cout << "Invalid entry.\n";}
		} while (m_playerChoice != 1 && m_playerChoice != 2 && m_playerChoice != 3 && checkEarlyTermination() == false);			//repeats until player2's turn is over (after they attack or exit program)
	}

	else if(m_playerAmount == 1)
	{
		if(m_opponentDifficulty == 1)
		{
			player2ComputerAttackDifficulty1();
		}
		
		else if(m_opponentDifficulty == 2)
		{
			player2ComputerAttackDifficulty2();
		}
		
		else if(m_opponentDifficulty == 3)
		{
			player2ComputerAttackDifficulty3();
		}
		
		
	}

}

