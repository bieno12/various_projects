/*
This is a cmd recreation of a popular game called SOS game 
made by: Zeyad Shahin (20210150)
*/

#include <iostream>
#include <cstdio>
#include <utility>
#include <string>
#include <algorithm>
using namespace std;

//board where the game state is stored, 0 is empty, 1 is letter O, 2 is letter S
int board[5][5];

//player_turn represent the current player (0, 1)
int player_turn = 0;

//current score of each player
int score0 = 0, score1 = 0;

//print_score print the score of each player
void print_score()
{
	cout << "player 1 : " << score0 << endl;
	cout << "player 2 : " << score1 << endl << endl;
}
//print the board 
void print_board()
{

	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			if (board[i][j] == 0)
				cout << "_|";
			else if(board[i][j] == 1)
				cout << "O|";
			else if(board[i][j] == 2)
				cout << "S|";
		}
		cout << endl;
	}
	cout << endl;
}
//values_in repeats the input process until valid integers are obtained
//it is used in get_play() internally
pair<int,int> values_in()
{


	int returnvalue = 0;
	int x, y;		
	cout << "enter x y: ";
	string in;
	getline(cin, in);
	if(in.find(" ") == string::npos)
	{
		cout << "enter valid input\n";
		return values_in();
	}
	try
	{
		x = stoi(in.substr(0, in.find(" ")));
		y = stoi(in.substr(in.find("") + 1));

	}
	catch(...)
	{
		cout << "enter valid input\n";
		return values_in();
	}
	
	return make_pair(x, y);
}


//get_play is responsible for return a valid tuple input from each player
//and applies the input to the board
pair<int, int> get_play()
{
	auto [x, y] = values_in();
	x--; y--;
	while ((x < 0) || (x > 4) || (y < 0) || (y > 4) || (board[y][x] != 0))
	{
		cout << "enter valid values please :)\n";
		auto pr = values_in();
		x = pr.first;
		y = pr.second;
		x--; y--;
	}
	string play;
	cout << "enter your play : ";
	getline(cin, play);
	while(play != "s"  && play != "o"
		&&  play != "S" && play != ")")
	{
		cout << "enter valid play please :) \n";
		getline(cin, play);
	}
	if(play == "s" || play == "S")
		board[y][x] = 2;
	else
		board[y][x] = 1;
	return make_pair(x, y);

}

//calculate_score(x,y) takes the position on board where S or O exists;
//it returns the number of SOS sequences caused by the x,y position
//
//there are eight directions to check for the sequence 
int calculate_score(int x, int y)
{

	int score = 0;
	//in case board(x,y) is O
	if (board[y][x] == 1)
	{
		//up and down
		if((y -1 >=0 && board[y - 1][x] == 2) && (y + 1 < 5 && board[y + 1][x] == 2))
			score += 1;

		//left and right
		if((x - 1 >= 0 && board[y][x - 1] == 2) && (x + 1 < 5 && board[y][x + 1] == 2))
			score += 1;

		// \ diagonal ie top-left and bottom-right
		if((x-1 >=0 && y-1 >= 0 && board[y-1][x-1] == 2) && (x+1 <5 && y+1 < 5 && board[y+1][x+1] == 2))
			score += 1;
		// / diagonal ie top-right and bottom-left
		if((x+1 <5 && y-1 >= 0 &&  board[y-1][x+1] == 2) && (x-1 >=0 && y+1 < 5 &&  board[y+1][x-1] == 2))
			score += 1;
	}
	else
	{
		//in case board(x,y) is S

		//top left corner ie x-2 , y-2
		if (x - 2 >= 0 && y - 2 >= 0)
			if (board[y - 1][x - 1] == 1 && board[y - 2][x - 2] == 2)
				score+= 1;
		//top side ie x, y -2
		if (y - 2 >=0)
			if (board[y - 1][x] == 1 && board[y - 2][x] == 2)
				score += 1;
		//top right corner ie x+2, y-2
		if (x + 2 < 5 && y - 2 >= 0)
			if (board[y - 1][x + 1] == 1 && board[y - 2][x + 2] == 2)
				score += 1;
		//right side ie x+2 , y
		if (x + 2 < 5)
			if (board[y][x + 1] == 1 && board[y][x + 2] == 2)
				score += 1;
		//bottom right corner ie x+2, y+2
		if (x + 2 < 5 && y + 2 < 5)
			if (board[y + 1][x + 1] == 1 && board[y + 2][x + 2] == 2)
				score += 1;				
		//bottom side ie x,y + 2
		if (y + 2 < 5)
			if (board[y + 1][x] == 1 && board[y + 2][x] == 2)
				score += 1;
		//bottom left corner ie x-2, y + 2
		if (x -2 >= 0 && y + 2 < 5)
			if (board[y + 1][x - 1] == 1 && board[y + 2][x - 2] == 2)
				score += 1;
		//left side ie x -2, y
		if (x - 2 >= 0)
			if (board[y][x - 1] == 1 && board[y][x - 2] == 2)
				score += 1;
	}
	return score;
}


//gameover is called upon the filling of the whole board
void gameover()
{
	if(score0 > score1)
		cout << "player 1 won the match!";
	else if(score1 > score0)
		cout << "player 2 won the match!";
	else
		cout << "its a tie!";

}

//main is where the game loop is
//first inform whose turn it is
//then get input from player
//calculate the scored caused by the move
//add the score to the current player
//change the player turn
//repeat until the game is over
//check if game is over in each iteration
int main()
{
	int movecount = 0;
	print_board();
	while (true)
	{
		if(player_turn)
			cout << "player 2 's turn\n";
		else
			cout << "player 1 's turn\n";
		auto [x, y] = get_play();
		print_board();
		int score = calculate_score(x, y);
		if(player_turn)
			score1 += score;
		else
			score0 += score;
		print_score();
		player_turn = !player_turn;
	}
	gameover();
}