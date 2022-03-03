from PIL import Image, ImageDraw
import numpy as np
class Grapher:
	
	def __init__(self, scale, unit_size, resolution = 10):
		self.scale = scale
		self.unit_size = unit_size
		self.size = (unit_size[0] * scale[0], unit_size[1] * scale[1]);
		self.initialize_image()
		self.resolution = resolution

	#create the image and draw grid and subgrid
	def initialize_image(self):
		scale = self.scale
		unit_size = self.unit_size
		self.img = Image.new(mode = "RGB", size = self.size, color = "white")
		self.draw = ImageDraw.Draw(self.img)

		#draw grid and subgrid
		for i in range(scale[0] + 1):
			for j in range(1, 5):
				self.draw.line([(0, i * unit_size[0] + unit_size[0] * j / 5), (self.img.size[0],i * unit_size[0] + unit_size[0] * j / 5)],fill = (200,200,200), width = 0)

			self.draw.line([(0, i * unit_size[0]), (self.img.size[0],i * unit_size[0])],fill = (100,100,100), width = 2)
		for i in range(scale[1] + 1):
			for j in range(1, 5):
				self.draw.line([(i * unit_size[1] + unit_size[1] * j / 5, 0), (i * unit_size[1] + unit_size[1] * j / 5, self.img.size[1])],fill = (200,200,200), width = 0)
			
			self.draw.line([(i * unit_size[1], 0), (i * unit_size[1] , self.img.size[1])],fill = (100, 100, 100), width = 2)

		# draw axis
		self.draw.line([(self.img.size[0] / 2, 0), (self.img.size[0] / 2 , self.img.size[1])],fill = "black", width = 4)
		self.draw.line([(0, self.img.size[1] / 2), (self.img.size[0], self.img.size[1] / 2)],fill = "black", width = 4)



	#draw the graph using marching squares from field values;
	def draw_function(self, f):
		r =1
		rez = self.resolution
		field = self.calculate_field(f)
		print(field)

		(col, row) = field.shape
		s = np.sign
		for y in range(row - 1):
			for x in range(col - 1):
				signs = s(field[y][x]) + s(field[y][x + 1]) + s(field[y + 1][x]) + s(field[y + 1][x + 1])
				if(-4 < signs < 4):
					self.draw.rectangle([(x * rez, y * rez), (x * rez + rez, y * rez + rez)], fill = "green")

					

		
	#calculate the scalar value at each corner of a march_square
	def calculate_field(self, f):
		rez = self.resolution
		col, row = 1 + int(self.size[0] / rez), 1 + int(self.size[1] / rez)
		field = np.zeros((row, col), dtype = 'f')

		for i in range(row):
			for j in range(col):
				field[i, j] = self.oriented_f(f, (j * rez - self.size[0] / 2) / float(self.scale[0]) , (i * rez - self.size[1] / 2) / float(self.scale[1]))
		return field

	def oriented_f(self, f, x, y):
		return f(x, -y);
	def show(self):
		self.img.show();
