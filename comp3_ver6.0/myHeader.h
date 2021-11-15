#pragma once


#include <iostream>
#include <vector>
#include <conio.h> //for _getch()
#include <Windows.h> //for sleep
#include <string> //for getline
#include <fstream> //For files
//#include <algorithm>
#include <ctime>

std::fstream highScores("Highscores.txt", std::ios::in | std::ios::app | std::ios::out);



//gamemodes
void playerVersusPlayer();
void playerVersusAI();

//CreateAI	
int createAI(int x);



//points and players 

int playerOneScore{};
int playerTwoScore{};

std::string playerOne{};
std::string playerTwo{};

void menu();

//Global variables

int checkLastMove{}; //This is going to be our ypos from our last move, so we can check horizontal, vertically and diagonally from that piece.

int setMarker = { 0 }; // Where markers is going to drop down from. The xpos 
int markerGoingDown{};

//For å velge skitn ///////////////////////////////////////////////////////////////////////
int xpos = { 2 };

char playerPosition[7] = { '1','2','3','4','5','6','7' };
char copyPlayerPosition[7] = { '1','2','3','4','5','6','7' };

//char playerMarker = 'o';
char playerMarker = {};



//Selecting where you are going to put something
void printPlayerPosition();
void printCopyPlayerPosition();
void marker();

void choosingPosition();
bool movement();

//Wincondition
bool winCondition();

//Playboard
void printBoard();
void animationBoard();	//Animation

char board[6][7] =
{
	{'*','*','*','*','*','*','*'},
	{'*','*','*','*','*','*','*'},
	{'*','*','*','*','*','*','*'},
	{'*','*','*','*','*','*','*'},
	{'*','*','*','*','*','*','*'},
	{'*','*','*','*','*','*','*'}
};

void printBoard() {

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (j % 7 == 0) { std::cout << '\n'; }
			std::cout << "[" << board[i][j] << "]";
		}
	}

}

void animationBoard()
{


	checkLastMove = 0;
	int y = 0;
	//checkLastMove = y;


	//	Doesnt set marker if there isnt a star there so it wont place if its full in one colomn
	//	And also wont let the marker get out of bounds

	while (y != 7 && board[y][setMarker] == '*' && board[y][setMarker]) {

		system("cls");

		if (y > 0)
		{
			board[y - 1][setMarker] = '*';
		}


		//board[y][setMarker] = 'x';
		board[y][setMarker] = playerMarker;
		printBoard();

		//spillbrett[y-1][setMarker] = '*';
		y++;
		checkLastMove++;


		Sleep(50);

	}
}

void printPlayerPosition()
{
	for (int i = 0; i < 7; i++)
	{
		std::cout << "[" << playerPosition[i] << "]";
	}

}

void printCopyPlayerPosition()
{
	for (int i = 0; i < 7; i++)
	{
		playerPosition[i] = copyPlayerPosition[i];
	}

}

void marker()
{
	playerPosition[xpos] = playerMarker;
}

void choosingPosition()
{
	bool moving = true;

	while (moving)
	{

		system("cls");
		marker(); //spawns
		printPlayerPosition();
		printBoard();
		moving = movement(); //To break the loop and get the setMarker's position that gets sent to animation
		printCopyPlayerPosition();
		marker();
	}

}

bool movement()
{
	char input{};
	input = _getch();
	switch (input)
	{
	case'a':case'A':
		if (xpos == 0) { break; }

		else
		{
			xpos -= 1;
		}
		break;
	case'd':case'D':
		if (xpos == 6) { break; }
		else
		{
			xpos += 1;
		}
		break;
	case 13: //enter
	{
		setMarker = xpos;
		return false;
	}

	default:
		break;
	}

	return true;
}


bool winCondition()
{
	int y{};
	int x{};

	for (int col = 5; col >= 0; --col)
	{
		for (int row = 6; row >= 0; --row)
		{

			if (board[col][row] == playerMarker &&
				board[col - 1][row - 1] == playerMarker &&
				board[col - 2][row - 2] == playerMarker &&
				board[col - 3][row - 3] == playerMarker)
			{
				return false;//
			}


			if (board[col][row] == playerMarker &&
				board[col][row - 1] == playerMarker &&
				board[col][row - 2] == playerMarker &&
				board[col][row - 3] == playerMarker)
			{
				return false;//
			}

			if (board[col][row] == playerMarker &&
				board[col - 1][row] == playerMarker &&
				board[col - 2][row] == playerMarker &&
				board[col - 3][row] == playerMarker)
			{
				return false;//
			}

			if (board[col][row] == playerMarker &&
				board[col + 1][row - 1] == playerMarker &&
				board[col + 2][row - 2] == playerMarker &&
				board[col + 3][row - 3] == playerMarker)
			{
				return false;//
			}

			if (board[col][row] == playerMarker &&
				board[col + 1][row] == playerMarker &&
				board[col + 2][row] == playerMarker &&
				board[col + 3][row] == playerMarker)
			{
				return false;//
			}

		}
	}




	//return true;
}

void playerVersusPlayer()
{
	char yOrN{};

	bool win = true;

	int turn = 0;

	while (win)
	{
		if (turn % 2 == 0) { playerMarker = 'O'; }
		else playerMarker = 'X';

		choosingPosition();
		animationBoard();
		//Can only win after round 6
		if (turn >= 6 && turn <= 42) {
			//win = winCondition(); // To break the loop
			win = winCondition();
		}
		turn++;
		
	}

	while (win == false)
	{
		system("cls");
		if (turn % 2 == 0) {
			std::cout << " " << playerOne << " Won! Wanna play againe?\n";
			//Adds point in the file to the playername
			playerOneScore += 1;
			highScores << playerOne << " " << playerOneScore << "\n";
			highScores << playerTwo << " " << playerTwoScore << "\n";
		}
		else
		{
			std::cout << " " << playerTwo << " Won! Wanna play againe?\n";
			//Adds point in the file to the playername
			playerTwoScore += 1;
			highScores << playerOne << " " << playerOneScore << "\n";
			highScores << playerTwo << " " << playerTwoScore << "\n";
		}
		std::cin >> yOrN;
		switch (yOrN)
		{
		case'y':case'Y':
			//resetBoard();

			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					board[i][j] = '*';
				}
			}



			playerVersusPlayer();
			break;

		case'n':case'N':
			exit(0);
			break;
		default:
			break;
		}
	}

}

//If player two is ai, the game will run player vs ai.
void menu()
{

	std::cout << "Welcome to Connect Four" << std::endl;

	std::cout << "Please Type your Name player 1: " << std::endl;
	std::cin >> playerOne;
	std::cout << "Welcome aboard " << playerOne << "!" << std::endl;

	std::cout << "\n\n\n";

	std::cout << "Please Type your Name player 2: " << std::endl;
	//getline(std::cin, playerTwo);
	std::cin >> playerTwo;
	if (playerTwo == "AI")
	{
		std::cout << "N00b" << std::endl;
		Sleep(1000);
		std::cout << "y0u_rE--iN 4 a r34L tR34T" << std::endl;
		Sleep(1000);
		system("cls");
		playerVersusAI();
		//Kjøre player vs ai	
	}
	else if (playerTwo == "Ai")
	{
		std::cout << "Oh..\n"; Sleep(1000); std::cout << "I see..."; Sleep(1600); std::cout << " so you think it's easy";
		Sleep(1500);
		std::cout << "\nEASY AGAINST THE SMARTEST COMPUTER \n";
		Sleep(1500);
		std::cout << "IN THE WORLD??!!"; Sleep(2000); system("cls"); playerVersusAI();
		//Kjøre player vs ai

	}
	else if (playerTwo == "ai")
	{
		//Kjøre player vs ai
		std::cout << "Hahahaaha\n";
		Sleep(1000);
		system("cls"); 
		Sleep(1000);
		std::cout << "HaHAHAHAAHA!\n";
		Sleep(1000);
		std::cout << "Show me what you got...";
		Sleep(1000);
		std::cout << " " << playerOne <<"\n";
		Sleep(3000);
		playerVersusAI();

	}
	else if (playerTwo == "aI")
	{	
		std::cout << "Hi " << playerOne << "\n";
		Sleep(1000);
		std::cout << "Prepare yourself.\n";
		Sleep(2000);
		system("cls");
		Sleep(1000);
		std::cout << "Because you're in trouble now!\n";
		Sleep(1000);
		system("cls");
		playerVersusAI();
		
	
	}
	else
	{
		std::cout << "Welcome aboard " << playerTwo << "!" << std::endl;
		system("cls");
		Sleep(500);
		std::cout << "Now...\n";
		Sleep(600);
		std::cout << "Now...\n";
		Sleep(750);
		std::cout << "Now...\n";
		Sleep(700);
		std::cout << "Now...\n";
		Sleep(400);
		system("cls");
		std::cout << "Let's get this game starting.." << std::endl;
		Sleep(1000);
		std::cout << "Shall we? "<< std::endl;
		Sleep(1000);
		playerVersusPlayer();
	}

}

void playerVersusAI()
{
	char yOrN{};

	bool win = true;

	int turn = 0;

	while (win)
	{
		if (turn % 2 == 0)
		{
			setMarker = createAI(xpos);
			playerMarker = 'O';
		}
		else {
			playerMarker = 'X';
			choosingPosition();
		}

		animationBoard();
		//Can only win after round 6
		if (turn >= 6) {
			
			win = winCondition();// To break the loop
		}
		turn++;
	}

	while (win == false)
	{
		system("cls");
		if (turn % 2 == 0)
		{

			std::cout << " " << playerOne << " Won! Wanna play againe?\n";
			//Adds point in the file to the playername
			playerOneScore += 1;
			highScores << playerOne << " " << playerOneScore << "\n";
			highScores << playerTwo << " " << playerTwoScore << "\n";
		}
		else {
			std::cout << " " << playerTwo << " Won! Wanna play againe?\n";
			//Adds point in the file to the playername
			playerTwoScore += 1;
			highScores << playerOne << " " << playerOneScore << "\n";
			highScores << playerTwo << " " << playerTwoScore << "\n";
		}

		std::cin >> yOrN;
		switch (yOrN)
		{
		case'y':case'Y':
			//resets board
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					board[i][j] = '*';
				}
			}



			playerVersusAI();
			break;

		case'n':case'N':
			exit(0);
			break;
		default:
			break;
		}
	}
}

//Used code from my github
int createAI(int x)
{

	srand(time(0));

	int randomNumber{};

	x = randomNumber;

	randomNumber = rand() % 7 + 1;

	return randomNumber;
}