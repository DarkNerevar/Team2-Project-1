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
  if ( m_player2PersonalKey[m_shipRow][m_shipCol] == '1' ||  m_player2PersonalKey[m_shipRow][m_shipCol] == '2' ||  m_player2PersonalKey[m_shipRow][m_shipCol] == '3' ||  m_player2PersonalKey[m_shipRow][m_shipCol] == '4' ||  m_player2PersonalKey[m_shipRow][m_shipCol] == '5' )
  {
    m_tempNumSunk = m_player2PersonalKey[m_shipRow][m_shipCol];
    m_player2PersonalKey[m_shipRow][m_shipCol] = 'X';
    m_player1OpponentKey[m_shipRow][m_shipCol] = 'X';
    hit(toupper(m_tempCol), m_shipRow+1, 1);
    bool tempSunk = isSunk(1);
    if(tempSunk)
    {
      cout << "----------------------\n";
      cout << "Player 1 sunk Player 2's ship!" << '\n';
      cout << "----------------------\n";
	  sleep_for(seconds(3));
      markPlayer1OpponentShipSunk();
	  m_player1Hits++;
	  m_player1ShipsSunk++;
    }
    else
    {
      cout << "----------------------\n";
      cout << "Player 1 hit Player 2's ship!" << '\n';
      cout << "----------------------\n";
	  sleep_for(seconds(3));
	  m_player1Hits++;
    }
  }
  else
  {
    cout << "-------------------------\n";
    cout << "Player 1 missed!" << '\n';
    cout << "-------------------------\n";
	sleep_for(seconds(3));
    m_player1OpponentKey[m_shipRow][m_shipCol] = '~';
	m_player2PersonalKey[m_shipRow][m_shipCol] = '*';
	m_player1Misses++;
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
  if ( m_player1PersonalKey[m_shipRow][m_shipCol] == '1' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '2' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '3' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '4' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '5' )
  {
    m_tempNumSunk = m_player1PersonalKey[m_shipRow][m_shipCol];
    m_player1PersonalKey[m_shipRow][m_shipCol] = 'X';
    m_player2OpponentKey[m_shipRow][m_shipCol] = 'X';
    hit(toupper(m_tempCol), m_shipRow+1, 2);
    bool tempSunk = isSunk(2);
    if(tempSunk)
    {
      cout << "----------------------\n";
      cout << "Player 2 sunk Player 1's ship!" << '\n';
      cout << "----------------------\n";
      markPlayer2OpponentShipSunk();
	  m_player2Hits++;
	  m_player2ShipsSunk++;
    }
    else
    {
      cout << "----------------------\n";
      cout << "Player 2 hit Player 1's ship!" << '\n';
      cout << "----------------------\n";
	  m_player2Hits++;
    }
  }
  else
  {
    cout << "-------------------------\n";
    cout << "Player 2 missed!" << '\n';
    cout << "-------------------------\n";
    m_player2OpponentKey[m_shipRow][m_shipCol] = '~';
	m_player1PersonalKey[m_shipRow][m_shipCol] = '*';
	m_player2Misses++;
  }
}


void Executive::player2ComputerAttackDifficulty1() //randomly fires
{
  //1) attack player1
  do
  {
	  counter = 0;							//counter used to check if attack was valid

    m_shipCol = rand() % 10;
    m_shipRow = rand() % 10;

	//checks if coordinates are in bounds
    if ( (m_shipCol < 0 || m_shipCol >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
    {
	  counter++;
    }
	//checks if the coordinate was already hit
	else if ( m_player1PersonalKey[m_shipRow][m_shipCol] == 'X' )
	{
		counter++;
	}
	//checks if the coordinate was already shot
	else if ( m_player2OpponentKey[m_shipRow][m_shipCol] == '~' )
	{
		counter++;
	}
  }while (counter != 0);				//repeats until the shot is valid

  cout << string(50,'\n');

  cout << "----------------------\n";
  cout << "Player 2 is firing at " << (char)(m_shipCol + 65) << m_shipRow - 1 << '\n';
  cout << "----------------------\n";

  //2) change player1's personal key if hit, and player2's personal key regardless
  if ( m_player1PersonalKey[m_shipRow][m_shipCol] == '1' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '2' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '3' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '4' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '5' )
  {
    m_tempNumSunk = m_player1PersonalKey[m_shipRow][m_shipCol];
    m_player1PersonalKey[m_shipRow][m_shipCol] = 'X';
    m_player2OpponentKey[m_shipRow][m_shipCol] = 'X';
    hit(toupper(m_tempCol), m_shipRow+1, 2);
    bool tempSunk = isSunk(2);
    if(tempSunk)
    {
      cout << "----------------------\n";
      cout << "Player 2 sunk Player 1's ship!" << '\n';
      cout << "----------------------\n";
	  markPlayer2OpponentShipSunk();
	  m_player2Hits++;
	  m_player2ShipsSunk++;
    }
    else
    {
      cout << "----------------------\n";
      cout << "Player 2 hit Player 1's ship!" << '\n';
      cout << "----------------------\n";
	  m_player2Hits++;
    }
  }
  else
  {
    cout << "-------------------------\n";
    cout << "Player 2 missed!" << '\n';
    cout << "-------------------------\n";
    m_player2OpponentKey[m_shipRow][m_shipCol] = '~';
	m_player1PersonalKey[m_shipRow][m_shipCol] = '*';
	m_player2Misses++;
  }
}

void Executive::player2ComputerAttackDifficulty2() // this method randomly fires and then if there is a hit it fires around that hit until there is another hit, and does that until a ship is sunk, and then repeats until all ships are sunk.
{
  //1) attack player1 if the a hit hasn't occured since the last sunk ship (or the begining of the game)
  if(m_computerHit == 0)
  {
	do
	{
		counter = 0;							//counter used to check if attack was valid
		m_computerCol = rand() % 10;
		m_computerRow =  rand() % 10;
		m_shipCol = m_computerCol;
		m_shipRow = m_computerRow;

		//checks if coordinates are in bounds
		if ( (m_shipCol < 0 || m_shipCol >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
		{
		counter++;
		}
		//checks if the coordinate was already hit
		else if ( m_player1PersonalKey[m_shipRow][m_shipCol] == 'X' )
		{
			counter++;
		}
		//checks if the coordinate was already shot
		else if ( m_player2OpponentKey[m_shipRow][m_shipCol] == '~' )
		{
			counter++;
		}
	}while (counter != 0);				//repeats until the shot is valid

	cout << string(50,'\n');

	cout << "----------------------\n";
  	cout << "Player 2 is firing at " << (char)(m_shipCol + 65) << m_shipRow - 1 << '\n';
  	cout << "----------------------\n";

	//2) change player1's personal key if hit, and player2's personal key regardless
	if ( m_player1PersonalKey[m_shipRow][m_shipCol] == '1' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '2' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '3' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '4' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '5' )
	{
		m_tempNumSunk = m_player1PersonalKey[m_shipRow][m_shipCol];
		m_player1PersonalKey[m_shipRow][m_shipCol] = 'X';
		m_player2OpponentKey[m_shipRow][m_shipCol] = 'X';
		hit(toupper(m_tempCol), m_shipRow+1, 2);
		bool tempSunk = isSunk(2);
		if(tempSunk)
		{
			cout << "----------------------\n";
			cout << "Player 2 sunk Player 1's ship!" << '\n';
			cout << "----------------------\n";
			markPlayer2OpponentShipSunk();
			m_computerHit = 0;
			m_player2Hits++;
			m_player2ShipsSunk++;
		}
		else
		{
			cout << "----------------------\n";
			cout << "Player 2 hit Player 1's ship!" << '\n';
			cout << "----------------------\n";
			m_computerHit = 1;
			m_player2Hits++;
		}
	}	
	else
	{
		cout << "-------------------------\n";
		cout << "Player 2 missed!" << '\n';
		cout << "-------------------------\n";
		m_player2OpponentKey[m_shipRow][m_shipCol] = '~';
		m_player1PersonalKey[m_shipRow][m_shipCol] = '*';
		m_player2Misses++;
	}
  }
  
  //Attack if the last attack was a hit but not sunk
   else if(m_computerHit == 1 && m_computerHitList == 0)
  {
	do
	{
		counter = 0;							//counter used to check if attack was valid
		m_computerCol--;
		m_shipCol = m_computerCol;
		m_shipRow = m_computerRow;

		//checks if coordinates are in bounds
		if ( (m_shipCol < 0 || m_shipCol >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
		{
		counter++;
		}
		//checks if the coordinate was already hit
		else if ( m_player1PersonalKey[m_shipRow][m_shipCol] == 'X' )
		{
			counter++;
		}
		//checks if the coordinate was already shot
		else if ( m_player2OpponentKey[m_shipRow][m_shipCol] == '~' )
		{
			counter++;
		}
	}while (counter != 0);				//repeats until the shot is valid

	cout << string(50,'\n');
	cout << "----------------------\n";
  	cout << "Player 2 is firing at " << (char)(m_shipCol + 65) << m_shipRow - 1 << '\n';
  	cout << "----------------------\n";
	

	//2) change player1's personal key if hit, and player2's personal key regardless
	if ( m_player1PersonalKey[m_shipRow][m_shipCol] == '1' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '2' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '3' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '4' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '5' )
	{
		m_tempNumSunk = m_player1PersonalKey[m_shipRow][m_shipCol];
		m_player1PersonalKey[m_shipRow][m_shipCol] = 'X';
		m_player2OpponentKey[m_shipRow][m_shipCol] = 'X';
		hit(toupper(m_tempCol), m_shipRow+1, 2);
		bool tempSunk = isSunk(2);
		if(tempSunk)
		{
			cout << "----------------------\n";
			cout << "Player 2 sunk Player 1's ship!" << '\n';
			cout << "----------------------\n";
			markPlayer2OpponentShipSunk();
			m_computerHit = 0;
			m_player2Hits++;
			m_player2ShipsSunk++;
		}
		else
		{
			cout << "----------------------\n";
			cout << "Player 2 hit Player 1's ship!" << '\n';
			cout << "----------------------\n";
			m_computerHit = 1;
			m_player2Hits++;
		}
	}	
	else
	{
		cout << "-------------------------\n";
		cout << "Player 2 missed!" << '\n';
		cout << "-------------------------\n";
		m_player2OpponentKey[m_shipRow][m_shipCol] = '~';
		m_player1PersonalKey[m_shipRow][m_shipCol] = '*';
		m_computerHitList = 1;
		m_player2Misses++;
	}
  }
  
   //Attack if the last attack was a hit but not sunk 2
   if(m_computerHit == 1 && m_computerHitList == 1)
  {
	do
	{
		counter = 0;							//counter used to check if attack was valid
		m_computerCol++;
		m_computerRow--;
		m_shipCol = m_computerCol;
		m_shipRow = m_computerRow;

		//checks if coordinates are in bounds
		if ( (m_shipCol < 0 || m_shipCol >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
		{
		counter++;
		}
		//checks if the coordinate was already hit
		else if ( m_player1PersonalKey[m_shipRow][m_shipCol] == 'X' )
		{
			counter++;
		}
		//checks if the coordinate was already shot
		else if ( m_player2OpponentKey[m_shipRow][m_shipCol] == '~' )
		{
			counter++;
		}
	}while (counter != 0);				//repeats until the shot is valid

	cout << string(50,'\n');
	cout << "----------------------\n";
  	cout << "Player 2 is firing at " << (char)(m_shipCol + 65) << m_shipRow - 1 << '\n';
  	cout << "----------------------\n";

	//2) change player1's personal key if hit, and player2's personal key regardless
	if ( m_player1PersonalKey[m_shipRow][m_shipCol] == '1' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '2' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '3' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '4' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '5' )
	{
		m_tempNumSunk = m_player1PersonalKey[m_shipRow][m_shipCol];
		m_player1PersonalKey[m_shipRow][m_shipCol] = 'X';
		m_player2OpponentKey[m_shipRow][m_shipCol] = 'X';
		hit(toupper(m_tempCol), m_shipRow+1, 2);
		bool tempSunk = isSunk(2);
		if(tempSunk)
		{
			cout << "----------------------\n";
			cout << "Player 2 sunk Player 1's ship!" << '\n';
			cout << "----------------------\n";
			markPlayer2OpponentShipSunk();
			m_computerHit = 0;
			m_computerHitList = 0;
			m_player2Hits++;
			m_player2ShipsSunk++;
		}
		else
		{
			cout << "----------------------\n";
			cout << "Player 2 hit Player 1's ship!" << '\n';
			cout << "----------------------\n";
			m_computerHit = 1;
			m_computerHitList = 0;
			m_player2Hits++;
		}
	}	
	else
	{
		cout << "-------------------------\n";
		cout << "Player 2 missed!" << '\n';
		cout << "-------------------------\n";
		m_player2OpponentKey[m_shipRow][m_shipCol] = '~';
		m_player1PersonalKey[m_shipRow][m_shipCol] = '*';
		m_computerHitList = 2;
		m_player2Misses++;
	}
  } 
  
     //Attack if the last attack was a hit but not sunk 3
   if(m_computerHit == 1 && m_computerHitList == 2)
  {
	do
	{
		counter = 0;							//counter used to check if attack was valid
		m_computerCol++;
		m_computerRow++;
		m_shipCol = m_computerCol;
		m_shipRow = m_computerRow;

		//checks if coordinates are in bounds
		if ( (m_shipCol < 0 || m_shipCol >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
		{
		counter++;
		}
		//checks if the coordinate was already hit
		else if ( m_player1PersonalKey[m_shipRow][m_shipCol] == 'X' )
		{
			counter++;
		}
		//checks if the coordinate was already shot
		else if ( m_player2OpponentKey[m_shipRow][m_shipCol] == '~' )
		{
			counter++;
		}
	}while (counter != 0);				//repeats until the shot is valid

	cout << string(50,'\n');
	cout << "----------------------\n";
  	cout << "Player 2 is firing at " << (char)(m_shipCol + 65) << m_shipRow - 1 << '\n';
  	cout << "----------------------\n";

	//2) change player1's personal key if hit, and player2's personal key regardless
	if ( m_player1PersonalKey[m_shipRow][m_shipCol] == '1' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '2' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '3' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '4' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '5' )
	{
		m_tempNumSunk = m_player1PersonalKey[m_shipRow][m_shipCol];
		m_player1PersonalKey[m_shipRow][m_shipCol] = 'X';
		m_player2OpponentKey[m_shipRow][m_shipCol] = 'X';
		hit(toupper(m_tempCol), m_shipRow+1, 2);
		bool tempSunk = isSunk(2);
		if(tempSunk)
		{
			cout << "----------------------\n";
			cout << "Player 2 sunk Player 1's ship!" << '\n';
			cout << "----------------------\n";
			markPlayer2OpponentShipSunk();
			m_computerHit = 0;
			m_computerHitList = 0;
			m_player2Hits++;
			m_player2ShipsSunk++;
		}
		else
		{
			cout << "----------------------\n";
			cout << "Player 2 hit Player 1's ship!" << '\n';
			cout << "----------------------\n";
			m_computerHit = 1;
			m_computerHitList = 0;
			m_player2Hits++;
		}
	}	
	else
	{
		cout << "-------------------------\n";
		cout << "Player 2 missed!" << '\n';
		cout << "-------------------------\n";
		m_player2OpponentKey[m_shipRow][m_shipCol] = '~';
		m_player1PersonalKey[m_shipRow][m_shipCol] = '*';
		m_computerHitList = 3;
		m_player2Misses++;
	}
  } 
  
       //Attack if the last attack was a hit but not sunk 4
   if(m_computerHit == 1 && m_computerHitList == 3)
  {
	do
	{
		counter = 0;							//counter used to check if attack was valid
		m_computerRow++;
		m_shipCol = m_computerCol;
		m_shipRow = m_computerRow;

		//checks if coordinates are in bounds
		if ( (m_shipCol < 0 || m_shipCol >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
		{
		counter++;
		}
		//checks if the coordinate was already hit
		else if ( m_player1PersonalKey[m_shipRow][m_shipCol] == 'X' )
		{
			counter++;
		}
		//checks if the coordinate was already shot
		else if ( m_player2OpponentKey[m_shipRow][m_shipCol] == '~' )
		{
			counter++;
		}
	}while (counter != 0);				//repeats until the shot is valid

	cout << string(50,'\n');
	cout << "----------------------\n";
  	cout << "Player 2 is firing at " << (char)(m_shipCol + 65) << m_shipRow - 1 << '\n';
  	cout << "----------------------\n";

	//2) change player1's personal key if hit, and player2's personal key regardless
	if ( m_player1PersonalKey[m_shipRow][m_shipCol] == '1' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '2' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '3' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '4' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '5' )
	{
		m_tempNumSunk = m_player1PersonalKey[m_shipRow][m_shipCol];
		m_player1PersonalKey[m_shipRow][m_shipCol] = 'X';
		m_player2OpponentKey[m_shipRow][m_shipCol] = 'X';
		hit(toupper(m_tempCol), m_shipRow+1, 2);
		bool tempSunk = isSunk(2);
		if(tempSunk)
		{
			cout << "----------------------\n";
			cout << "Player 2 sunk Player 1's ship!" << '\n';
			cout << "----------------------\n";
			markPlayer2OpponentShipSunk();
			m_computerHit = 0;
			m_computerHitList = 0;
			m_player2Hits++;
			m_player2ShipsSunk++;
		}
		else
		{
			cout << "----------------------\n";
			cout << "Player 2 hit Player 1's ship!" << '\n';
			cout << "----------------------\n";
			m_computerHit = 1;
			m_computerHitList = 0;
			m_player2Hits++;
		}
	}	
	else
	{
		cout << "-------------------------\n";
		cout << "Player 2 missed!" << '\n';
		cout << "-------------------------\n";
		m_player2OpponentKey[m_shipRow][m_shipCol] = '~';
		m_player1PersonalKey[m_shipRow][m_shipCol] = '*';
		m_player2Misses++;
	}
  }
  
}

void Executive::player2ComputerAttackDifficulty3()
{
  //1) attack player1
  do
  {
	  counter = 0;							//counter used to check if attack was valid
	  //Finds an unhit coordinate to target
	for (int i = 0; i < m_rows; i++)
		{	
			for (int j = 0; j < m_cols; j++)
			{
				if((m_player1PersonalKey[i][j] == '1')||(m_player1PersonalKey[i][j] == '2')||(m_player1PersonalKey[i][j] == '3')||(m_player1PersonalKey[i][j] == '4')||(m_player1PersonalKey[i][j] == '5')) 
				{
					m_shipRow = i;
					m_shipCol = j;
				}
			}
		}
   

	//checks if coordinates are in bounds
    if ( (m_shipCol < 0 || m_shipCol >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
    {
	  counter++;
    }
	//checks if the coordinate was already hit
	else if ( m_player1PersonalKey[m_shipRow][m_shipCol] == 'X' )
	{
		counter++;
	}
	//checks if the coordinate was already shot
	else if ( m_player2OpponentKey[m_shipRow][m_shipCol] == '~' )
	{
		counter++;
	}
  }while (counter != 0);				//repeats until the shot is valid

  cout << string(50,'\n');
  cout << "----------------------\n";
	cout << "Player 2 is firing at " << (char)(m_shipCol + 65) << m_shipRow - 1 << '\n';
	cout << "----------------------\n";

  //2) change player1's personal key if hit, and player2's personal key regardless
  if ( m_player1PersonalKey[m_shipRow][m_shipCol] == '1' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '2' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '3' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '4' ||  m_player1PersonalKey[m_shipRow][m_shipCol] == '5' )
  {
    m_tempNumSunk = m_player1PersonalKey[m_shipRow][m_shipCol];
    m_player1PersonalKey[m_shipRow][m_shipCol] = 'X';
    m_player2OpponentKey[m_shipRow][m_shipCol] = 'X';
    hit(toupper(m_tempCol), m_shipRow+1, 2);
    bool tempSunk = isSunk(2);
    if(tempSunk)
    {
      cout << "----------------------\n";
      cout << "Player 2 sunk Player 1's ship!" << '\n';
      cout << "----------------------\n";
      markPlayer2OpponentShipSunk();
	  m_player2Hits++;
	  m_player2ShipsSunk++;
    }
    else
    {
      cout << "----------------------\n";
      cout << "Player 2 hit Player 1's ship!" << '\n';
      cout << "----------------------\n";
	  m_player2Hits++;
    }
  }
  else
  {
    cout << "-------------------------\n";
    cout << "Player 2 missed!" << '\n';
    cout << "-------------------------\n";
    m_player2OpponentKey[m_shipRow][m_shipCol] = '~';
	m_player1PersonalKey[m_shipRow][m_shipCol] = '*';
	m_player2Misses++;
  }
}


void Executive::markPlayer1OpponentShipSunk()
{
  for (int i = 0; i < m_rows; i++)
  {
    for (int j = 0; j < m_cols; j++)
    {
      if (m_player2PersonalOrigKey[i][j] == m_tempNumSunk)
      {
        m_player1OpponentKey[i][j] = m_tempNumSunk;
      }
    }
  }
}

void Executive::markPlayer2OpponentShipSunk()
{
  for (int i = 0; i < m_rows; i++)
  {
    for (int j = 0; j < m_cols; j++)
    {
      if (m_player1PersonalOrigKey[i][j] == m_tempNumSunk)
      {
        m_player2OpponentKey[i][j] = m_tempNumSunk;
      }
    }
  }
}

void Executive::player1GiantShot(){
  //check amount of giant shots

  if (giantShotLeft1==0){
    cout << "----------------------\n";
    cout<<"You dont have any giant shots left.\n";
    cout << "----------------------\n";
    player1Turn();
    return;
  } else {
    giantShotLeft1--;
    
	if(giantShotLeft1 == 0) {
		cout << "----------------------\n";
    	cout<<"You are now firing your final Giant SHot.\n";
    	cout << "----------------------\n";
	} else {
		cout << "----------------------\n";
    	cout<<"You have "<<giantShotLeft1<<" giant shots left.\n";
   		cout << "----------------------\n";
	}
  }


  //1) attack player2 with giant shot
  do
  {
	  counter = 0;					//counter used to check if attack was valid

    cout << "Player 1: Please enter column (A-J) to attack player 2 with giant shot: ";				//gets the column to attack
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
	//checks if the coordinate was already hit or shot
    else if ( checkAllHitOf1(m_shipCol,m_shipRow))
    {
      cout << "All Coordinates Already Hit or Shot. Aim Elsewhere!\n";
      counter++;
    }
  }while (counter != 0);		//repeats until the shot is valid
  
  bool tempMiss= true;
  for(int i=m_shipCol-1;i<m_shipCol+2;i++){
    if(i<0 || i>m_cols) continue;
    for(int j=m_shipRow-1;j<m_shipRow+2;j++){
      if(j<0 || j>m_rows) continue;
      //2) change player2's personal key if hit, and player1's opponent key regardless
      if ( m_player2PersonalKey[j][i] == '1' ||  m_player2PersonalKey[j][i] == '2' ||  m_player2PersonalKey[j][i] == '3' ||  m_player2PersonalKey[j][i] == '4' ||  m_player2PersonalKey[j][i] == '5' )
      {
        tempMiss=false;
        m_tempNumSunk = m_player2PersonalKey[j][i];
        m_player2PersonalKey[j][i] = 'X';
        m_player1OpponentKey[j][i] = 'X';
        hit(toupper(m_tempCol), j+1, 1);
        bool tempSunk = isSunk(1);
        if(tempSunk)
        {
          cout << "----------------------\n";
          cout << "Player 1 sunk Player 2's ship!" << '\n';
          cout << "----------------------\n";
		  markPlayer1OpponentShipSunk();
		  m_player1Hits++;
		  m_player1ShipsSunk++;
        }
        else
        {
          cout << "----------------------\n";
          cout << "Player 1 hit Player 2's ship!" << '\n';
          cout << "----------------------\n";
		  m_player1Hits++;
        }
      }
      else
      {
        m_player1OpponentKey[j][i] = '~';
		m_player2PersonalKey[j][i] = '*';
      }
    }
  }
  if (tempMiss){
    cout << "-------------------------\n";
    cout << "Player 1 missed with a giant shot!" << '\n';
    cout << "-------------------------\n";
	m_player1Misses++;
  }

  

}

bool Executive::checkAllHitOf1(int col, int row){
  for(int i=col-1;i<col+2;i++){
    if(i<0 || i>=m_cols) {
      continue;}

    for(int j=row-1;j<row+2;j++){
       if(j<0 || j>=m_rows) {
      }else{
      if (m_player1OpponentKey[j][i] == '?') return false;
      }

    }
  }
  return true;
}

void Executive::player2GiantShot(){
  //check amount of giant shots

  if (giantShotLeft2==0){
    cout << "----------------------\n";
    cout<<"You dont have any giant shots left.\n";
    cout << "----------------------\n";
    player2Turn();
    return;
  } else {
    giantShotLeft2--;
    if(giantShotLeft2 == 0) {
		cout << "----------------------\n";
    	cout<<"You are now firing your final Giant SHot.\n";
    	cout << "----------------------\n";
	} else {
		cout << "----------------------\n";
    	cout<<"You have "<<giantShotLeft2<<" giant shots left.\n";
   		cout << "----------------------\n";
	}
  }

  

  //1) attack player1 with giant shot
  do
  {
	  counter = 0;					//counter used to check if attack was valid

    cout << "Player 2: Please enter column (A-J) to attack player 1 with giant shot: ";				//gets the column to attack
    cin >> m_tempCol;
    m_shipCol = (int(toupper(m_tempCol)) - 65);
    cout << "Please enter row (1-10) to attack player 1: ";						//gets the row to attack
    m_shipRow = validateInput()-1;

	//checks if coordinates are in bounds
    if ( (m_shipCol < 0 || m_shipCol >= m_cols) || (m_shipRow < 0 || m_shipRow >= m_rows) )
    {
      cout << "Invalid coordinate entry!" << '\n';
	    counter++;
    }
	//checks if the coordinate was already hit or shot
    else if ( checkAllHitOf2(m_shipCol,m_shipRow))
    {
      cout << "All Coordinates Already Hit or Shot. Aim Elsewhere!\n";
      counter++;
    }
  }while (counter != 0);		//repeats until the shot is valid
  
  bool tempMiss= true;
  for(int i=m_shipCol-1;i<m_shipCol+2;i++){
    if(i<0 || i>m_cols) continue;
    for(int j=m_shipRow-1;j<m_shipRow+2;j++){
      if(j<0 || j>m_rows) continue;
      //2) change player1's personal key if hit, and player2's opponent key regardless
      if ( m_player1PersonalKey[j][i] == '1' ||  m_player1PersonalKey[j][i] == '2' ||  m_player1PersonalKey[j][i] == '3' ||  m_player1PersonalKey[j][i] == '4' ||  m_player2PersonalKey[j][i] == '5' )
      {
        tempMiss=false;
        m_tempNumSunk = m_player1PersonalKey[j][i];
        m_player1PersonalKey[j][i] = 'X';
        m_player2OpponentKey[j][i] = 'X';
        hit(toupper(m_tempCol), j+1, 2); 
        bool tempSunk = isSunk(2);
        if(tempSunk)
        {
          cout << "----------------------\n";
          cout << "Player 2 sunk Player 1's ship!" << '\n';
          cout << "----------------------\n";
          markPlayer2OpponentShipSunk();
		  m_player2Hits++;
		  m_player2ShipsSunk++;
        }
        else
        {
          cout << "----------------------\n";
          cout << "Player 2 hit Player 1's ship!" << '\n';
          cout << "----------------------\n";
		  m_player2Hits++;
        }
      }
      else
      {
        m_player2OpponentKey[j][i] = '~';
		m_player1PersonalKey[j][i] = '*';
      }
    }
  }
  if (tempMiss){
    cout << "-------------------------\n";
    cout << "Player 2 missed with a giant shot!" << '\n';
    cout << "-------------------------\n";
	m_player2Misses++;
  }

  

}

bool Executive::checkAllHitOf2(int col, int row){
    for(int i=col-1;i<col+2;i++){
    if(i<0 || i>=m_cols) {
      continue;}

    for(int j=row-1;j<row+2;j++){
       if(j<0 || j>=m_rows) {
      }else{
      if (m_player2OpponentKey[j][i] == '?') return false;
      }

    }
  }
  return true;
}
