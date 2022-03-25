# This is a cmd recreation of a popular game called SOS game 
#
# made by: Zeyad Shahin (20210150)


#board where the game state is stored, 0 is empty, 1 is letter O, 2 is letter S
global board;
board = [[0 for i in range(5)] for i in range(5)];

#player_turn represent the current player (0, 1)
global player_turn
player_turn = 0;

#current score of each player
global score0, score1
score0, score1 = 0, 0

#print_score print the score of each player
def print_score():
	global score0, score1
	print("player 1 : ", score0)
	print("player 2 : ", score1)
	print()

#print the board 
def print_board():
	global board
	for l in board:
		for x in l:
			if x == 0:
				print('_', end = '')
			elif x == 1:
				print('O', end = '')
			elif x == 2:
				print('S', end = '')
			print('|', end = '');
		print()
	print()

#values_in repeats the input process until valid integers are obtained
#it is used in get_play() internally
def values_in():

	try:
		(x, y) =  map(int, input("enter x y: ").split())
		return (x, y);
	except:
		print("enter valid input")
		return values_in();
	return (-1,-1)

#get_play is responsible for return a valid tuple input from each player
#and applies the input to the board
def get_play():
	global board
	(x, y) = values_in();
	x -=1; y -= 1
	while x < 0 or x > 4 or y < 0 or y > 4 or board[y][x] != 0:
		print("enter valid values please :)")
		(x, y) = values_in();
		x -= 1
		y -= 1
	play = input("enter your play: ")
	while(play.upper() != 'S' and play.upper() != 'O'):
		play = input("enter valid play please :) : ")
	if(play.upper() == 'S'):
		board[y][x] = 2
	else:
		board[y][x] = 1;
	return (x, y);

#calculate_score(x,y) takes the position on board where S or O exists;
#it returns the number of SOS sequences caused by the x,y position
#
#there are eight directions to check for the sequence 
def calculate_score(x, y):
	global board
	score = 0
	#in case board(x,y) is O
	if board[y][x] == 1:
		#up and down
		if (y -1 >=0 and board[y - 1][x] == 2) and (y + 1 < 5 and board[y + 1][x] == 2):
			score += 1
		#left and right
		if (x - 1 >= 0 and board[y][x - 1] == 2) and (x + 1 < 5 and board[y][x + 1] == 2):
			score += 1
		# \ diagonal ie top-left and bottom-right
		if (x-1 >=0 and y-1 >= 0 and board[y-1][x-1] == 2) and (x+1 <5 and y+1 < 5 and board[y+1][x+1] == 2):
			score += 1
		# / diagonal ie top-right and bottom-left
		if (x+1 <5 and y-1 >= 0 and  board[y-1][x+1] == 2) and (x-1 >=0 and y+1 < 5 and  board[y+1][x-1] == 2):
			score += 1
	else:
		#in case board(x,y) is S

		#top left corner ie x-2 , y-2
		if x - 2 >= 0 and y - 2 >= 0:
			if board[y - 1][x - 1] == 1 and board[y - 2][x - 2] == 2:
				score+= 1
		#top side ie x, y -2
		if y - 2 >=0:
			if board[y - 1][x] == 1 and board[y - 2][x] == 2:
				score += 1
		#top right corner ie x+2, y-2
		if x + 2 < 5 and y - 2 >= 0:
			if board[y - 1][x + 1] == 1 and board[y - 2][x + 2] == 2:
				score += 1
		#right side ie x+2 , y
		if x + 2 < 5:
			if board[y][x + 1] == 1 and board[y][x + 2] == 2:
				score += 1
		#bottom right corner ie x+2, y+2
		if x + 2 < 5 and y + 2 < 5:
			if board[y + 1][x + 1] == 1 and board[y + 2][x + 2] == 2:
				score += 1				
		#bottom side ie x,y + 2
		if y + 2 < 5:
			if board[y + 1][x] == 1 and board[y + 2][x] == 2:
				score += 1
		#bottom left corner ie x-2, y + 2
		if x -2 >= 0 and y + 2 < 5:
			if board[y + 1][x - 1] == 1 and board[y + 2][x - 2] == 2:
				score += 1
		#left side ie x -2, y
		if x - 2 >= 0:
			if board[y][x - 1] == 1 and board[y][x - 2] == 2:
				score += 1
	return score
#
#gameover is called upon the filling of the whole board
#

def gameover():
	global score0, score1
	if(score0 > score1):
		print("player 1 won the match!")
	elif score1 > score0:
		print("player 2 won the match!")
	else:
		print("its a tie!")

#main is where the game loop is
#first inform whose turn it is
#then get input from player
#calculate the scored caused by the move
#add the score to the current player
#change the player turn
#repeat until the game is over
#check if game is over in each iteration
def main():
	global player_turn, score0, score1
	movecount = 0;
	print_board();
	while True:
		movecount += 1;
		if player_turn:
			print("player 2 's turn")
		else:
			print("player 1 's turn")
		(x,y) = get_play(); 
		print_board();
		score = calculate_score(x, y);
		if player_turn:
			score1 += score
		else:
			score0 += score
		print_score();
		if movecount >= 25:
			break;
		else:
			movecount += 1
		if(not(score)):
			player_turn = not(player_turn)
	gameover();

#call the main function to start the game
main()