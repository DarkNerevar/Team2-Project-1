/** -----------------------------------------------------------------------------
 *
 * @file  Executive.h
 * @author Team2
 * Assignment:   EECS-448 Project1
 * @date Feb 13, 2022
 * brief:This file is responsible for defining the required variables and methods
 *
 ---------------------------------------------------------------------------- **/
#ifndef Executive_H
#define Executive_H
#include <iostream>
#include <limits>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
class Executive
{
    private:
      char m_tempNumSunk = ' ';

      bool m_isGameFinished = false;
      bool m_isGameTerminated = false;

      int m_rows = 10;
      int m_cols = 10;

      char** m_player1PersonalKey = nullptr;
      char** m_player2PersonalKey = nullptr;
      char** m_player1OpponentKey = nullptr;
      char** m_player2OpponentKey = nullptr;

      char** m_player1PersonalOrigKey = nullptr;
      char** m_player2PersonalOrigKey = nullptr;

      int m_shipAmount = 0;
      int m_shipOrientation = 1;
      int counter = 0;
	  
	  int m_playerAmount = 0;
	  int m_opponentDifficulty = 0;
	  bool m_computerHit = 0;
	  int m_computerHitList = 0;
	  int m_computerCol = 0;
	  int m_computerRow = 0;

      char m_tempCol = ' ';
      int m_shipCol = 0;
      int m_shipRow = 0;
      int m_shipArrSize = 0;

      int m_playerChoice = 0;

      int m_player1ShipsRemaining = 0;
      int m_player2ShipsRemaining = 0;
      int m_winner = 0;
      string* m_player1Ships = nullptr;
      string* m_player2Ships = nullptr;

      int giantShotLeft1 = 1;
      int giantShotLeft2 = 1;
    
    public:

      void setupShipsArr();
      void hit(char col,int row, int player);
      bool checkEarlyTermination();
      bool isSunk(int player);
      void getArrRange(int count, int *start, int *end);

      Executive();

      void boardSetup();
      void origCopy();
      void startMenu();
      void printRules();
	  void printRules1Player();
	  void shipAmount();
	  void difficultyLevel();
      void playGame();
      void earlyTermination();
  	  void gameOver();
      void printMenu();
      void printPlayer1PersonalKey();
      void printPlayer2PersonalKey();
      void printPlayer1OpponentKey();
      void printPlayer2OpponentKey();
      void player1Turn();
      void player2Turn();
      void player1Attack();
      void player2Attack();
	  void player2ComputerAttackDifficulty1();
	  void player2ComputerAttackDifficulty2();
	  void player2ComputerAttackDifficulty3();
      void markPlayer1OpponentShipSunk();
      void markPlayer2OpponentShipSunk();
      bool checkIfFinished();
  	  int validateInput();
      void player1GiantShot(); //Drake
      void player2GiantShot(); //Drake
      bool checkAllHitOf1(int col, int row);//Drake
      bool checkAllHitOf2(int col, int row);//Drake

      int move(int player);

      ~Executive()
      {
        for (int i = 0; i < m_rows; i++)
        {
          delete[] m_player1PersonalKey[i];
          delete[] m_player2PersonalKey[i];
          delete[] m_player1OpponentKey[i];
          delete[] m_player2OpponentKey[i];

          delete[] m_player1PersonalOrigKey[i];
          delete[] m_player2PersonalOrigKey[i];
        }

        delete[] m_player1Ships;
        delete[] m_player2Ships;

        delete[] m_player1PersonalKey;
        delete[] m_player2PersonalKey;
        delete[] m_player1OpponentKey;
        delete[] m_player2OpponentKey;

        delete[] m_player1PersonalOrigKey;
        delete[] m_player2PersonalOrigKey;

      }

};
#endif
