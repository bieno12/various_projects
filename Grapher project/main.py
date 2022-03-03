from grapher import Grapher
from random import randrange
import math as m
global equation
def f(x, y):
	global equation
	try:
		x =eval(equation)
		return x;
	except:
		return -1;




if __name__ == "__main__":
	global equation
	terms = input("enter equation:").split("=")

	equation = terms[0] + "- (" + terms[1] + ")"
	scale = tuple(map(int, input("enter scale:").split()))
	unit_size = tuple(map(int, input("enter unit_size:").split()))
	resolution = int(input("enter resolution:"))
	graph = Grapher(scale = scale, unit_size = unit_size, resolution = resolution)
	graph.draw_function(f)
	graph.show()



