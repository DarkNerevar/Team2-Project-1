/** -----------------------------------------------------------------------------
 *
 * @file  BoardSetup.h
 * @author Team2
 * Assignment:   EECS-448 Project1
 * @date Feb 13, 2022
 * brief:This file is responsible for placing the player's ship on the sea
 *
 ---------------------------------------------------------------------------- **/
#include "Printboard.h"
void Executive::boardSetup()
{
	startMenu();		//prints the start menu
	if(m_playerAmount == 2)
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
						else if(m_player1PersonalKey[m_shipRow + j][m_shipCol] == '1' || m_player1PersonalKey[m_shipRow + j][m_shipCol] == '2' || m_player1PersonalKey[m_shipRow + j][m_shipCol] == '3' || m_player1PersonalKey[m_shipRow + j][m_shipCol] == '4' || m_player1PersonalKey[m_shipRow + j][m_shipCol] == '5' )
						{
							cout << "There's already a ship there.\n";
							counter++;
						}
					}
					if(m_shipOrientation == 2)				//horizontal orientation
					{
						//checks if the ship is out of bounds
						if ( ( (m_shipCol + j) < 0 || (m_shipCol + j) >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
						{
							cout << "Out of Bounds.\n";
							counter++;
						}
						//checks if the coordinate is already occupied
						else if( m_player1PersonalKey[m_shipRow][m_shipCol + j] == '1' || m_player1PersonalKey[m_shipRow][m_shipCol + j] == '2' || m_player1PersonalKey[m_shipRow][m_shipCol + j] == '3' || m_player1PersonalKey[m_shipRow][m_shipCol + j] == '4' || m_player1PersonalKey[m_shipRow][m_shipCol + j] == '5' )
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
							//std::cout << static_cast<char>(shipCount + 49) << '\n';
							//std::cout << stoc (stoi(shipCount + 1));
							m_player1PersonalKey[m_shipRow + j][m_shipCol] = static_cast<char>(shipCount + 49);
							string coord = char((m_shipCol)+65)+to_string(m_shipRow+j+1);
							m_player1Ships[shipCount] = coord;
						}
						if(m_shipOrientation == 2)
						{
							m_player1PersonalKey[m_shipRow][m_shipCol + j] = static_cast<char>(shipCount + 49);
							string coord =char((m_shipCol+j)+65)+to_string(m_shipRow+1);
							m_player1Ships[shipCount] = coord;
						}
						//shipCount++;
					}
					shipCount++;
				}	
				printPlayer1PersonalKey();
			}while (counter != 0);			//repeats until the ship is placed
		}
		shipCount = 0;
		cout << string(100,'\n');
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
						else if(m_player2PersonalKey[m_shipRow + j][m_shipCol] == '1' || m_player2PersonalKey[m_shipRow + j][m_shipCol] == '2' || m_player2PersonalKey[m_shipRow + j][m_shipCol] == '3' || m_player2PersonalKey[m_shipRow + j][m_shipCol] == '4' || m_player2PersonalKey[m_shipRow + j][m_shipCol] == '5' )
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
						else if( m_player2PersonalKey[m_shipRow][m_shipCol + j] == '1' || m_player2PersonalKey[m_shipRow][m_shipCol + j] == '2' || m_player2PersonalKey[m_shipRow][m_shipCol + j] == '3' || m_player2PersonalKey[m_shipRow][m_shipCol + j] == '4' || m_player2PersonalKey[m_shipRow][m_shipCol + j] == '5' )
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
							m_player2PersonalKey[m_shipRow + j][m_shipCol] = static_cast<char>(shipCount + 49);
							string coord = char((m_shipCol)+65)+to_string(m_shipRow+j+1);
							m_player2Ships[shipCount] = coord;
						}
						if(m_shipOrientation == 2)
						{
							m_player2PersonalKey[m_shipRow][m_shipCol + j] = static_cast<char>(shipCount + 49);
							string coord = char((m_shipCol+j)+65)+to_string(m_shipRow+1);
							m_player2Ships[shipCount] = coord;
						}
						//shipCount++;
					}
					shipCount++;
				}
				printPlayer2PersonalKey();
			}while (counter != 0);
		}
		shipCount = 0;
		cout << string(100,'\n');
		
		
		
		
	}
		else if(m_playerAmount == 1)
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
							else if(m_player1PersonalKey[m_shipRow + j][m_shipCol] == '1' || m_player1PersonalKey[m_shipRow + j][m_shipCol] == '2' || m_player1PersonalKey[m_shipRow + j][m_shipCol] == '3' || m_player1PersonalKey[m_shipRow + j][m_shipCol] == '4' || m_player1PersonalKey[m_shipRow + j][m_shipCol] == '5' )
							{
								cout << "There's already a ship there.\n";
								counter++;
							}
						}
						if(m_shipOrientation == 2)				//horizontal orientation
						{
							//checks if the ship is out of bounds
							if ( ( (m_shipCol + j) < 0 || (m_shipCol + j) >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
							{
								cout << "Out of Bounds.\n";
								counter++;
							}
							//checks if the coordinate is already occupied
							else if( m_player1PersonalKey[m_shipRow][m_shipCol + j] == '1' || m_player1PersonalKey[m_shipRow][m_shipCol + j] == '2' || m_player1PersonalKey[m_shipRow][m_shipCol + j] == '3' || m_player1PersonalKey[m_shipRow][m_shipCol + j] == '4' || m_player1PersonalKey[m_shipRow][m_shipCol + j] == '5' )
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
								//std::cout << static_cast<char>(shipCount + 49) << '\n';
								//std::cout << stoc (stoi(shipCount + 1));
								m_player1PersonalKey[m_shipRow + j][m_shipCol] = static_cast<char>(shipCount + 49);
								string coord = char((m_shipCol)+65)+to_string(m_shipRow+j+1);
								m_player1Ships[shipCount] = coord;
							}
							if(m_shipOrientation == 2)
							{
								m_player1PersonalKey[m_shipRow][m_shipCol + j] = static_cast<char>(shipCount + 49);
								string coord =char((m_shipCol+j)+65)+to_string(m_shipRow+1);
								m_player1Ships[shipCount] = coord;
							}
							//shipCount++;
						}
						shipCount++;
					}	
					printPlayer1PersonalKey();
				}while (counter != 0);			//repeats until the ship is placed
			}
			shipCount = 0;
			cout << string(100,'\n');
			//--------------------------------------------
			//PLAYER 2 SETS THEIR BOARD BELOW
			//--------------------------------------------
			//same code as above, but for a computer opponent
			
			//printPlayer2PersonalKey();			//prints player2's board //(Not Necessary for a computer opponent)
			shipCount = 0;
			for (int i = 0; i < m_shipAmount; i++) //#ships to set
			{
				do				//allows the user to choose the orientation of the ship
				{
					//cout << "\n1) Vertical\n";						 //(Not Necessary for a computer opponent)
					//cout << "2) Horizontal\n"; 						 //(Not Necessary for a computer opponent)
					//cout << "Which orientation would you like for ship " << i+1 << ": ";				//(Not Necessary for a computer opponent)
					m_shipOrientation = rand() % 1 + 2;
					//if(m_shipOrientation < 1 || m_shipOrientation > 2)	//(Not Necessary for a computer opponent)
					//{cout << "Invalid Input";}							//(Not Necessary for a computer opponent)
				}while(m_shipOrientation < 1 || m_shipOrientation > 2);

			do	
			{
				//cout << "Player 2: Please enter column (A-J) for ship " << (i + 1) << ": ";			//gets the column for placement	//(Not Necessary for a computer opponent)
				//cin >> m_tempCol;																										//(Not Necessary for a computer opponent)
				m_shipCol = rand() % 10;

				//cout << "Player 2: Please enter row (1-10) for ship " << (i + 1) << ": ";				//gets the row for placement	//(Not Necessary for a computer opponent)
				m_shipRow = rand() % 10;;

				counter = 0;
				for(int j=0; j<=i; j++)
				{
					if(m_shipOrientation == 1)			//vertical orientation
					{
						if ( (m_shipCol < 0 || m_shipCol >= m_cols) || ( (m_shipRow + j) < 0 || (m_shipRow + j) >= m_rows) )
						{
							//cout << "Out of Bounds.\n";
							counter++;
						}
						else if(m_player2PersonalKey[m_shipRow + j][m_shipCol] == '1' || m_player2PersonalKey[m_shipRow + j][m_shipCol] == '2' || m_player2PersonalKey[m_shipRow + j][m_shipCol] == '3' || m_player2PersonalKey[m_shipRow + j][m_shipCol] == '4' || m_player2PersonalKey[m_shipRow + j][m_shipCol] == '5' )
						{
							//cout << "There's already a ship there.\n";
							counter++;
						}
					}
					if(m_shipOrientation == 2)			//horizontal orientation
					{
						if ( ( (m_shipCol + j) < 0 || (m_shipCol + j) >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
						{
							//cout << "Out of Bounds.\n";
							counter++;
						}
						else if( m_player2PersonalKey[m_shipRow][m_shipCol + j] == '1' || m_player2PersonalKey[m_shipRow][m_shipCol + j] == '2' || m_player2PersonalKey[m_shipRow][m_shipCol + j] == '3' || m_player2PersonalKey[m_shipRow][m_shipCol + j] == '4' || m_player2PersonalKey[m_shipRow][m_shipCol + j] == '5' )
						{
							//cout << "There's already a ship there.\n";
							counter++;
						}
					}
				}
				if (counter != 0)
				{}
				//{cout << "Placement is not valid! Please enter a valid coordinate." << '\n';}
				else
				{
					for(int j=0; j<=i; j++)			//places each section of the ship
					{
						if(m_shipOrientation == 1)
						{
							m_player2PersonalKey[m_shipRow + j][m_shipCol] = static_cast<char>(shipCount + 49);
							string coord = char((m_shipCol)+65)+to_string(m_shipRow+j+1);
							m_player2Ships[shipCount] = coord;
						}
						if(m_shipOrientation == 2)
						{
							m_player2PersonalKey[m_shipRow][m_shipCol + j] = static_cast<char>(shipCount + 49);
							string coord = char((m_shipCol+j)+65)+to_string(m_shipRow+1);
							m_player2Ships[shipCount] = coord;
						}
						//shipCount++;
					}
					shipCount++;
				}
				//printPlayer2PersonalKey();
			}while (counter != 0);
		}
		shipCount = 0;
		cout << string(100,'\n');
		}
}


void Executive::origCopy() //creates original arrays, used for references to first beginning board.
{
  //initializes copy keys
  for (int i = 0; i < m_rows; i++)
  {
    m_player1PersonalOrigKey[i] = new char [m_cols];
    m_player2PersonalOrigKey[i] = new char [m_cols];
  }
  //copies to original keys
  for (int i = 0; i < m_rows; i++)
  {
    for (int j = 0; j < m_cols; j++)
    {
      m_player1PersonalOrigKey[i][j] = m_player1PersonalKey[i][j];
      m_player2PersonalOrigKey[i][j] = m_player2PersonalKey[i][j];
    }
  }
}
