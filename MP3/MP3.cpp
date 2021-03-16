/*
MP3
Mia Prasinos
10/15/2020
Runs a game of Tic Tac Toe between two players and allows them to keep playing while keeping track of wins and ties
*/


#include <iostream>
#include <string>
#include <vector>

using namespace std;

// the size of the square game board
const int SIZE = 3;

// function prototypes
void displayGameStats(int ties, int player1Score, int player2Score, string player1Name, string player2Name);
void displayBoard(char board[SIZE][SIZE]);
void locationToBoardLocation(int lovation, int &row, int &column);
int getPlayerInput(string playerName);
void placeMarkOnBoard(char board[SIZE][SIZE], char playerMark, int location);
bool isLegalMove(char board[SIZE][SIZE], int location);
bool hasThreeInRow(char board[SIZE][SIZE], char playerMark);
void clearBoard(char board[SIZE][SIZE]);

int main() {
	// gets username from each player
	string playerOne = "player 1";
	string playerTwo = "player 2";
	
	// gets usernames and assigns them to players
	cout << "Welcome to tic tac toe!" << endl;
	cout << "Player 1 please enter name: ";
	cin >> playerOne;
	cout << "Player 2 please enter name: ";
	cin >> playerTwo; 
	cout << endl;


	// initializes the game board with the numbers in respective locations
	char gameBoard[SIZE][SIZE] = { {'1', '2', '3'},
								{'4', '5', '6'},
								{'7', '8', '9'} };

	// initializes variables to keep track of points
	int player1Games = 0;
	int player2Games = 0;
	int tieGames = 0;
	
	
	displayBoard(gameBoard);

	// initializes variable for location on board
	int moveLocation = 0;
	
	// variable to tell which player's turn it is, 1 is player 1, and 2 is player 2
	int playerTurn = 1;

	// sets the mark that will be used for player one and two, x or o
	char playerOneMark = 'X';
	char playerTwoMark = 'O';

	// keeps track of how many moves have been made to recognize a tie
	int turnCount = 1;

	// used to determine if the players want to keep playing
	bool moreGame = true;

	// determines starter player
	int starterPlayer = 1;
	if (starterPlayer == 1) {
		playerTurn = 1;
	}
	else if (starterPlayer == 2) {
		playerTurn = 2;
	}

	while (moreGame) {

	
		// loops through the players turns until it finds a set of three or the board is filled
		while (!(hasThreeInRow(gameBoard, playerOneMark)) && !(hasThreeInRow(gameBoard, playerTwoMark)) && turnCount < 10) {
			
			// Determines which turn it is, goes through the turn, and then switches the player
			if (playerTurn == 1) {
				moveLocation = getPlayerInput(playerOne);
				if (moveLocation == 0) {
					moveLocation = getPlayerInput(playerOne);
				}
				if (isLegalMove(gameBoard, moveLocation)) {
					placeMarkOnBoard(gameBoard, playerOneMark, moveLocation);
					displayBoard(gameBoard);
					playerTurn = 2;
				}
				else {
					cout << "You cannot go there, please try again. " << endl;
					playerTurn = 1;
				}
			}
			else if (playerTurn == 2) {

				moveLocation = getPlayerInput(playerTwo);
				if (moveLocation == 0) {
					moveLocation = getPlayerInput(playerTwo);
				}
				if (isLegalMove(gameBoard, moveLocation)) {
					placeMarkOnBoard(gameBoard, playerTwoMark, moveLocation);
					displayBoard(gameBoard);
					playerTurn = 1;
				}
				else {
					cout << "You cannot go there, please try again. " << endl;
					playerTurn = 2;
				}
			}

			turnCount++;
		}


		if (hasThreeInRow(gameBoard, playerOneMark)) {
			player1Games++;
			cout << playerOne << " Wins!" << endl;
			turnCount = 0;
		}
		else if (hasThreeInRow(gameBoard, playerTwoMark)) {
			player2Games++;
			cout << playerTwo << " Wins!" << endl;
			turnCount = 0;
		}
		else {
			tieGames++;
			cout << "It's a tie! " << endl;
			turnCount = 0;
		}


		char playAgain = 'a';
		cout << "Would you like to play again (y or n): ";
		cin >> playAgain;

		if (playAgain == 'y') {
			moreGame = true;
			if (starterPlayer == 1) {
				starterPlayer = 2;
				playerTurn = starterPlayer;
			}
			else {
				starterPlayer = 1;
				playerTurn = starterPlayer;
			}
			clearBoard(gameBoard);
			displayBoard(gameBoard);
		}
		else {
			moreGame = false;
		}


	}
	displayGameStats(tieGames, player1Games, player2Games, playerOne, playerTwo);
	clearBoard(gameBoard);
	
}


/**
* Displays the board at the set size
* @param board[SIZE][SIZE] the board which is set up in main
*/
void displayBoard(char board[SIZE][SIZE]) {
	int space = 0;
	cout << " ";

	// loops through the array to display all values
	for (int x = 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			if (y < SIZE - 1) {
				cout << board[x][y] << " | "; // adds a dash between each location
			}
			else {
				cout << board[x][y];
			}
			space++;

			//determines when to go to the next line and adds a dash to seperate 
			if (space % SIZE == 0) {
				if (space < (SIZE*SIZE)) {
					cout << endl;
					cout << "---+---+---" << endl << " ";
				}
				
			}
		}
	}
	cout << endl << endl;
}

/**
* This function displays how many games each player has won and tied
* @param ties amount of games tied
* @param player1Score amount of games player 1 wins
* @param player2Score amount of games player 2 wins
* @param player1Name name entered by user 1
* @param player2Name name entered by user 2
*/
void displayGameStats(int ties, int player1Score, int player2Score, string player1Name, string player2Name) {
	cout << endl; // adds a line for formatting
	cout << player1Name << " Score: " << player1Score << endl; // displays player 1 score and name
	cout << player2Name << " Score: " << player2Score << endl; // displayes player 2 score and name
	cout << "Games Tied: " << ties << endl; // displays games tied
}

/**
* This function takes the location as a single integer and converts it to a row and column value
* @param location the location on the board
* @param &row the row value
* @param &column the column value
*/
void locationToBoardLocation(int location, int &row, int &column) {
	if (location <= SIZE){
		row = 0;
		column = location - 1;
	}
	else if (location <= (SIZE * 2)) {
		row = 1;
		column = location - 4;
	}
	else if (location <= (SIZE * SIZE) ) {
		row = 2;
		column = location - 7;
	}
}

/**
* Prompts the current player to choose a location and continues to prompt if they put an invalid integer
* @param playerName the name of the player playing now
* @return playerLocation a number 1-9 corresponding to a spot on the board
*/
int getPlayerInput(string playerName) {
	int playerLocation;
	cout << playerName << " pick a location (1-9): ";
	cin >> playerLocation;
	if (playerLocation <= 9 && playerLocation >=1) {
		return playerLocation;
	}
	else {
		cout << "That is not a spot, please choose a different one." << endl;
		playerLocation = 0;
		return playerLocation;
	}

}

/**
* places an x or an o on the spot chosen by the current player
* @param board[SIZE][SIZE]
* @param playerMark will be an x for player one and an o for player two 
* @location chosen by the current player, uses locationToBoardLocation function to convert it to the array location
*/
void placeMarkOnBoard(char board[SIZE][SIZE], char playerMark, int location) {
	int yLocation = 9999999;
	int xLocation = 9999999;
	locationToBoardLocation(location, yLocation, xLocation);
	board[yLocation][xLocation] = playerMark;
}


/**
* checks the location the player wants to play to see if there is already an X or O there
* @param board[SIZE][SIZE]
* @param location chosen by the current player, uses locationToBoardLocation function to convert it to the array location
*/
bool isLegalMove(char board[SIZE][SIZE], int location) {
	int yLocation = 9999999;
	int xLocation = 9999999;
	locationToBoardLocation(location, yLocation, xLocation);
	if (board[yLocation][xLocation] == 'X' || board[yLocation][xLocation] == 'O') {
		return false;
	}
	else {
		return true;
	}
}

/**
* Checks all the possible combinations of 3 in a row
* @param board uses the game board
* @param playerMark checks the x or o
* @return true if there is a combination of 3
* @return false if there is no combination of 3
*/
bool hasThreeInRow(char board[SIZE][SIZE], char playerMark) {
	//checks for horizontal sets of three and their possible combinations
	if (board[0][0] == playerMark && board[0][1] == playerMark && board[0][2] == playerMark) {
		return true;
	}
	else if (board[1][0] == playerMark && board[1][1] == playerMark && board[1][2] == playerMark) {
		return true;
	}
	else if (board[2][0] == playerMark && board[2][1] == playerMark && board[2][2] == playerMark) {
		return true;
	}
	// checks for vertical sets of three and their possible combinations
	else if (board[0][0] == playerMark && board[1][0] == playerMark && board[2][0] == playerMark) {
		return true;
	}
	else if (board[0][1] == playerMark && board[1][1] == playerMark && board[2][1] == playerMark) {
		return true;
	}
	else if (board[0][2] == playerMark && board[1][2] == playerMark && board[2][2] == playerMark) {
		return true;
	}
	// checks for diagonal sets of three and their possible combinations
	else if (board[0][0] == playerMark && board[1][1] == playerMark && board[2][2] == playerMark) {
		return true;
	}
	else if (board[2][0] == playerMark && board[1][1] == playerMark && board[0][2] == playerMark) {
		return true;
	}
	else {
		return false;
	}
}


void clearBoard(char board[SIZE][SIZE]) {
	board[0][0] = '1';
	board[0][1] = '2';
	board[0][2] = '3';
	board[1][0] = '4';
	board[1][1] = '5';
	board[1][2] = '6';
	board[2][0] = '7';
	board[2][1] = '8';
	board[2][2] = '9';
}


