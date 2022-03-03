import pygame
import random
from cell import Cell
#some constants
WHITE = (255, 255,255)
BLACK = (0, 0,0)
SCREEN_SIZE =(500,500)
CENTER = (SCREEN_SIZE[0]//2, SCREEN_SIZE[1]//2)
DELAY = 500#ms
#some global variables
cells = []
clicked_cells = []
player1 = 0; player2 = 0
turn = 0

gameover = False
#counter is counting the clicked cells
counter = 0; 
#intialize the game display
pygame.init()
font = pygame.font.SysFont("", 50);

display = pygame.display.set_mode(SCREEN_SIZE);

pygame.display.set_caption("memory game ")

#game_running is self explanatory
game_running = True

#all revieled check if all cells are revieled
def all_revieled():
	global cells
	for c in cells:
		if not c.is_revealed:
			return False;
	return True;

#intialize cells with values
def intialize_cells():
	global cells;
	chars = 'ABCDEFGHIJABCDEFGHIJ'
	#shuffle the characters
	chars = ''.join(random.sample(chars,len(chars)))
	#create cells with spacing between them
	for i in range(len(chars)):
		c = Cell(chars[i], ((SCREEN_SIZE[0] / 10 * i)%SCREEN_SIZE[0], 50 * (i // 10) + 100), 40, display)
		cells.append(c)

#create text objects to print scores of both players
def draw_score():
	global display, font

	score1 = font.render(f"player A: {player1}", False, (0, 255, 0))
	score2 = font.render(f"player B: {player2}", False, (0, 0, 255))
	display.blit(score1, (50, 400));
	display.blit(score2, (300, 400));

#update_screen is responsible for displaying and rendering 
def update_screen():
	global gameover, turn, player1, player2
	display.fill(BLACK)

	#draw each cell
	for cl in cells:
		cl.draw();
	
	#draw the score
	draw_score();
	#draw the current player turn
	text = None
	if turn:
		text = font.render("B's turn", False, (0, 0, 255))
	else:
		text = font.render(f"A's turn", False, (0, 255, 0))
	display.blit(text, (SCREEN_SIZE[0]// 2 - 50, 0));
	
	#in case game is over, overlay the drawn with the winning screen
	if gameover:
		display.fill(BLACK)
		turn = not turn
		if player1 < player2:
			text = font.render("player B Won", False, (0, 0, 255))
		elif player1 > player2:
			text = font.render("player A Won", False, (0, 255, 0))
		else:
			text = font.render("Its a tie", False, (0, 255, 255))

		display.blit(text, CENTER)	

	#update the display
	pygame.display.update()
#main function where the game loop exists
def main():
	global game_running, revieled_cells
	global cells, counter,player1, player2, turn
	intialize_cells();

	while game_running:
	
		#update the screen each frame
		
		for event in pygame.event.get():
	
			#check for quiting condition
			if event.type == pygame.QUIT:
				game_running = False
			#check for mouse clicks
			if event.type == pygame.MOUSEBUTTONUP:
				pos = pygame.mouse.get_pos()
				for c in cells:
					if c.on_cell(pos):
						if not c.is_revealed:
							c.is_shown =True
							c.draw();
							pygame.display.update()
							clicked_cells.append(c)
							counter += 1
							if(counter == 2):

								#wait for delay 
								pygame.time.delay(DELAY)
								#check if match
								if(clicked_cells[0].character == clicked_cells[1].character):
									clicked_cells[0].is_revealed = True
									clicked_cells[1].is_revealed = True
									#add score to current player
									player1 += not turn
									player2 += turn

								else:
									clicked_cells[0].is_shown = False;
									clicked_cells[1].is_shown = False;
								#clear data
								counter = 0;
								clicked_cells.clear();
								#change turn
								turn = not turn
		#check if game is over
		if all_revieled():
			gameover = True;
		update_screen();


if __name__ == '__main__':
	main()