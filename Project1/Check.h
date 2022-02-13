/** -----------------------------------------------------------------------------
 *
 * @file  Check.h
 * @author Team2
 * Assignment:   EECS-448 Project1
 * @date Feb 13, 2022
 * brief:This document is responsible for checking the state of the ship.
 *
 ---------------------------------------------------------------------------- **/
bool Executive::checkIfFinished()
{
  m_player1ShipsRemaining = 0;
  m_player2ShipsRemaining = 0;

	//checks the entire board for remaining ships
  for (int i = 0; i < m_rows; i++)
  {
    for (int j = 0; j < m_cols; j++)
    {
      if (m_player1PersonalKey[i][j] == 'S')
      {m_player1ShipsRemaining ++;}
      if (m_player2PersonalKey[i][j] == 'S')
      {m_player2ShipsRemaining ++;}
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
  {return (false);}
}

//checks to see if a whole ship has sunk
 bool Executive::isSunk(int player)
 {
   int count = 1;
   if(player == 1) //checks if player 1 sunk one of player 2's ships
   {
     //goes through the array to see if the ship has sunk
     while(count <= m_shipArrSize)
     {
        int hit = 0;
        int start, end;
        getArrRange(count, &start, &end);
        for(int i = start; i <= end; i++)
        {
          if(m_player2Ships[i] == "L")
          {
            hit++;
          }
        }
        // if the hit amount == count, changes "L" to "X" so it doesn't count it as sunk again
        if(hit == count)
        {
          for(int i = start; i <= end; i++)
          {
            m_player2Ships[i] = "X";
          }
          return true;
        }
        count++;
      }
   }
   else //checks if player 2 sunk one of player 1's ships
   {
      while(count <= m_shipArrSize)
      {
        int hit = 0;
        int start, end;
        getArrRange(count, &start, &end);
        for(int i = start; i <= end; i++)
        {
          if(m_player1Ships[i] == "L")
          {
            hit++;
          }
        }
        if(hit == count)
        {
          for(int i = start; i <= end; i++)
          {
            m_player1Ships[i] = "X";
          }
          return true;
        }
        count++;
      }
    }
    return false;
 }
