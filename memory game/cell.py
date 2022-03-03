import pygame
class Cell:
	#each cell contaions a character and position for it
	#and a bool to describe its state
	#for rendering: each cell has a text surface and a cover surface;
	#surface is where the text should be drawn
	def __init__(self, character, position, size, surface):

		self.character = character
		self.position = position
		self.is_revealed = False
		self.is_shown = False
		self.size = size
		self.surface = surface
		font = pygame.font.SysFont("", int(1.75 * size))
		self.text = font.render(character, True, (255,255,255));
		self.cover = pygame.Surface((size,size))
		self.cover.fill((255,0,0))
		#r is rect object that is used for detecting clicks
		self.r = self.cover.get_rect(topleft = position)


	#the method for drawing the cell on screen based on position if revieled or shown;
	#shown is when a player chooses two cells to know what behind them
	#revieled is the constant state of being shown when a match was found
	def draw(self):

		if self.is_revealed or self.is_shown:
			self.surface.blit(self.cover, self.position);
			self.surface.blit(self.text, self.position);
		else:
			self.surface.blit(self.cover, self.position);
	#on_cell checks if the position is within the cell colider
	def on_cell(self, pos):
		return True if self.r.collidepoint(pos) else False;
