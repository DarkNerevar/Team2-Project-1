
#include "Executive.h"

//helper method
bool isAlive(int shipNumber, char** playerKey) {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if((int)playerKey[i][j] - 48 == shipNumber) return true; 
        }
    }
    return false;
}

int Executive::move(int player) {

    int selectedShip = 0;
    int shipRow = 0;
    int shipCol = 0;
    m_shipOrientation = 0;
    bool validPlacement = true;
    bool firstLoop = true;

    /**
     * 1. get the ship the player wants to move
     *      a. check if input is valid and ship is not sunk
     * 2. get new orientation
     * 3. get col of new location
     *      a. check if valid input
     * 4. get row of new location
     *      b. check if valid input
     * 5. check if overlap & bounds
     * 6. update player1PersonalKey
     * 7. update player2OpponentKey
    **/

    if(player == 1){
        while(true) {
            while(true) {
                //go back
                if(firstLoop) {
                    firstLoop = false;
                    break;
                } else {
                    std::cout << "Would you like to go back? (Y/N) " << std::endl;
                    char ans;
                    std::cin >> ans;

                    if(std::toupper(ans) == 'Y') {
                        return 1;
                    } else if (std::toupper(ans) == 'N') {
                        break;
                    } else {
                        std::cout << "Invalid input!" << std::endl;
                    }
                }
            }

            //get the ship the player wants to move
            while(true){
                validPlacement = true;

                std::cout << "Which ship do you want to move? (1 - " << m_shipAmount << ")\t";            

                selectedShip = validateInput(); //validate input

                //check if ship has not been hit
                int numSquares = 0;
                for(int i = 0; i < 10; i ++) {
                    for(int j = 0; j < 10; j ++) {
                        if((int)m_player1PersonalKey[i][j] - 48 == selectedShip) numSquares++;
                    }
                } 

                //if selectedShip == number of squares, then the ship has noot been hit
                if(selectedShip == numSquares) {
                    if(isAlive(selectedShip, m_player1PersonalKey)) {  //check if the selected ship is sunk
                        break; //break out of loop
                    } else { //ship is sunk
                        std::cout << "Invalid input! Select a ship that is not sunk!" << std::endl; //invalid input message
                    }
                } else if(selectedShip < 1 || selectedShip > m_shipAmount) {
                    std::cout << "There is no " << selectedShip << " in the game. Select a valid ship." << std::endl;
                } else { //ship is hit
                    std::cout << "A ship that has been hit cannot move. It's sinking." << std::endl;
                }
            }

            //get new orientation
            while(true) {
                std::cout << "\n1) Vertical\n2) Horizontal\nWhich orientation would you like for ship " << selectedShip << ": ";
                
                //get orientation & validate input
                m_shipOrientation = validateInput();
                
                //if illegal input
                if(m_shipOrientation < 1 || m_shipOrientation > 2) {
                    std::cout << "Invalid Input. Please enter '1' or '2':\t";
                } else {
                    break;
                }
            }

            //get ne row & col
            //get col
            std::cout << "Player 1: Please enter column (A-J) to move ship " << selectedShip << " to: ";
            std::cin >> m_tempCol;
            shipCol = (int(std::toupper(m_tempCol)) - 65);

            //get row
            std::cout << "Player 1: Please enter row (1-10) to move ship " << selectedShip << " to: ";
            shipRow = validateInput() - 1;

            //check if ship is in bounds
            if(m_shipOrientation == 1)  { //vertial
                if(shipCol < 0 || shipCol > 9 || shipRow < 0 || shipRow + selectedShip > 9) {
                    std::cout << "Moving ship " << selectedShip << " to " << (char)(shipCol + 65) << shipRow + 1 << " would be out of bounds. Please try again." << std::endl;
                    validPlacement = false;
                }
            } else {    //horizontal
                if(shipCol < 0 || shipCol + selectedShip > 9 || shipRow < 0 || shipRow > 9) {
                    std::cout << "Moving ship " << selectedShip << " to " << (char)(shipCol + 65) << shipRow + 1 << " would be out of bounds. Please try again." << std::endl;
                    validPlacement = false;
                } 
            }

            //check that ship is not placed on a square that has been shot at
            if(validPlacement) {
                //check check that the ship does not overlap or intersect with any previously shot at squares
                if(m_shipOrientation == 1) {    //vertical
                    for(int i = 0; i < selectedShip; i++) {
                        //check if the space not valid
                        if(m_player2OpponentKey[shipRow + i][shipCol] != '?') { //~ is open space
                            if(m_player2OpponentKey[shipRow + i][shipCol] == 'X') { //check space has not been hit
                                std::cout << "Moving ship " << selectedShip << " to " << (char)(shipCol + 65) << shipRow + 1 << " would overlap it with a hit square. Please try again." << std::endl;
                            }
                            else if(m_player2OpponentKey[shipRow + i][shipCol] == '~') { //check is space has been
                                std::cout << "Moving ship " << selectedShip << " to " << (char)(shipCol + 65) << shipRow + 1 << " would overlap it with a missed square. Please try again." << std::endl;
                            }
                            validPlacement = false;
                        }
                    }
                } else {    //horizontal
                    for(int i = 0; i < selectedShip; i++) {
                        //check if the space not valid
                        if(m_player2OpponentKey[shipRow][shipCol + i] != '?') { //~ is open space
                            if(m_player2OpponentKey[shipRow][shipCol + i] == 'X') { //check space has not been hit
                                std::cout << "Moving ship " << selectedShip << " to " << std::toupper(m_tempCol) << shipRow + 1 << " would overlap it with a hit square. Please try again." << std::endl;
                            }
                            else if(m_player2OpponentKey[shipRow][shipCol + i] == '~') { //check is space has been
                                std::cout << "Moving ship " << selectedShip << " to " << std::toupper(m_tempCol) << shipRow + 1 << " would overlap it with a missed square. Please try again." << std::endl;
                            }
                            validPlacement = false;
                        }
                    }
                }
            }
            //break out of loop if ship move is valid. otherwise try again
            if(validPlacement) break;
        }

        //update player1PersonalKey
        for(int i = 0; i < 10; i++ ) {  //change all of the ships preivioussquares to ~
            for(int j = 0; j < 10; j++) {
                if((int)m_player1PersonalKey[i][j] - 48 == selectedShip) m_player1PersonalKey[i][j] = '~';
            }
        }

        if(m_shipOrientation == 1) {    //if vertical
            for(int i = 0; i < selectedShip; i++) { //draw ships new location
                std::cout << selectedShip << " " << (char)selectedShip;
                m_player1PersonalKey[shipRow + i][shipCol] = selectedShip + '0';
            }
        } else { //horizontal
            for(int i = 0; i < selectedShip; i++) { //draw ships new location
                m_player1PersonalKey[shipRow][shipCol + i] = selectedShip + '0';
            }
        }
    }
    else {  //player2
        while(true) {
            while(true) {
                //go back
                if(firstLoop) {
                    firstLoop = false;
                    break;
                } else {
                    std::cout << "Would you like to go back? (Y/N) " << std::endl;
                    char ans;
                    std::cin >> ans;

                    if(std::toupper(ans) == 'Y') {
                        return 1;
                    } else if (std::toupper(ans) == 'N') {
                        break;
                    } else {
                        std::cout << "Invalid input!" << std::endl;
                    }
                }
            }

            //get the ship the player wants to move
            while(true){
                validPlacement = true;

                std::cout << "Which ship do you want to move? (1 - " << m_shipAmount << ")\t";            

                selectedShip = validateInput(); //validate input

                //check if ship has not been hit
                int numSquares = 0;
                for(int i = 0; i < 10; i ++) {
                    for(int j = 0; j < 10; j ++) {
                        if((int)m_player2PersonalKey[i][j] - 48 == selectedShip) numSquares++;
                    }
                } 

                //if selectedShip == number of squares, then the ship has noot been hit
                if(selectedShip == numSquares) {
                    if(isAlive(selectedShip, m_player2PersonalKey)) {  //check if the selected ship is sunk
                        break; //break out of loop
                    } else { //ship is sunk
                        std::cout << "Invalid input! Select a ship that is not sunk!" << std::endl; //invalid input message
                    }
                } else if(selectedShip < 1 || selectedShip > m_shipAmount) {
                    std::cout << "There is no " << selectedShip << " in the game. Select a valid ship." << std::endl;
                } else { //ship is hit
                    std::cout << "A ship that has been hit cannot move. It's sinking." << std::endl;
                }
            }

            //get new orientation
            while(true) {
                std::cout << "\n1) Vertical\n2) Horizontal\nWhich orientation would you like for ship " << selectedShip << ": ";
                
                //get orientation & validate input
                m_shipOrientation = validateInput();
                
                //if illegal input
                if(m_shipOrientation < 1 || m_shipOrientation > 2) {
                    std::cout << "Invalid Input. Please enter '1' or '2':\t";
                } else {
                    break;
                }
            }

            //get ne row & col
            //get col
            std::cout << "Player 1: Please enter column (A-J) to move ship " << selectedShip << " to: ";
            std::cin >> m_tempCol;
            shipCol = (int(std::toupper(m_tempCol)) - 65);

            //get row
            std::cout << "Player 1: Please enter row (1-10) to move ship " << selectedShip << " to: ";
            shipRow = validateInput() - 1;

            //check if ship is in bounds
            if(m_shipOrientation == 1)  { //vertial
                if(shipCol < 0 || shipCol > 9 || shipRow < 0 || shipRow + selectedShip > 9) {
                    std::cout << "Moving ship " << selectedShip << " to " << (char)(shipCol + 65) << shipRow + 1 << " would be out of bounds. Please try again." << std::endl;
                    validPlacement = false;
                }
            } else {    //horizontal
                if(shipCol < 0 || shipCol + selectedShip > 9 || shipRow < 0 || shipRow > 9) {
                    std::cout << "Moving ship " << selectedShip << " to " << (char)(shipCol + 65) << shipRow + 1 << " would be out of bounds. Please try again." << std::endl;
                    validPlacement = false;
                } 
            }

            //check that ship is not placed on a square that has been shot at
            if(validPlacement) {
                //check check that the ship does not overlap or intersect with any previously shot at squares
                if(m_shipOrientation == 1) {    //vertical
                    for(int i = 0; i < selectedShip; i++) {
                        //check if the space not valid
                        if(m_player1OpponentKey[shipRow + i][shipCol] != '?') { //~ is open space
                            if(m_player1OpponentKey[shipRow + i][shipCol] == 'X') { //check space has not been hit
                                std::cout << "Moving ship " << selectedShip << " to " << (char)(shipCol + 65) << shipRow + 1 << " would overlap it with a hit square. Please try again." << std::endl;
                            }
                            else if(m_player1OpponentKey[shipRow + i][shipCol] == '~') { //check is space has been
                                std::cout << "Moving ship " << selectedShip << " to " << (char)(shipCol + 65) << shipRow + 1 << " would overlap it with a missed square. Please try again." << std::endl;
                            }
                            validPlacement = false;
                        }
                    }
                } else {    //horizontal
                    for(int i = 0; i < selectedShip; i++) {
                        //check if the space not valid
                        if(m_player1OpponentKey[shipRow][shipCol + i] != '?') { //~ is open space
                            if(m_player1OpponentKey[shipRow][shipCol + i] == 'X') { //check space has not been hit
                                std::cout << "Moving ship " << selectedShip << " to " << (char)(shipCol + 65) << shipRow + 1 << " would overlap it with a hit square. Please try again." << std::endl;
                            }
                            else if(m_player1OpponentKey[shipRow][shipCol + i] == '~') { //check is space has been
                                std::cout << "Moving ship " << selectedShip << " to " << (char)(shipCol + 65) << shipRow + 1 << " would overlap it with a missed square. Please try again." << std::endl;
                            }
                            validPlacement = false;
                        }
                    }
                }
            }
            //break out of loop if ship move is valid. otherwise try again
            if(validPlacement) break;
        }

        //update player1PersonalKey
        for(int i = 0; i < 10; i++ ) {  //change all of the ships preivioussquares to ~
            for(int j = 0; j < 10; j++) {
                if((int)m_player2PersonalKey[i][j] - 48 == selectedShip) m_player2PersonalKey[i][j] = '~';
            }
        }

        if(m_shipOrientation == 1) {    //if vertical
            for(int i = 0; i < selectedShip; i++) { //draw ships new location
                std::cout << selectedShip << " " << (char)selectedShip;
                m_player2PersonalKey[shipRow + i][shipCol] = selectedShip + '0';
            }
        } else { //horizontal
            for(int i = 0; i < selectedShip; i++) { //draw ships new location
                m_player2PersonalKey[shipRow][shipCol + i] = selectedShip + '0';
            }
        }
    }

    return 0;
}
