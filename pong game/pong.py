import turtle
import numpy
global paddle1, paddle2, ball, speed_y, speed_x, red_score, blue_score, dir1, dir2
dir1 , dir2 = 0, 0
sc = turtle.Screen()
red_score = 0
blue_score = 0
sc.setup(width = 800, height = 600)
sc.bgcolor("black")

sc.tracer(0)

score = turtle.Turtle()
score.color("white")
score.speed(0)
score.penup()
score.hideturtle()
score.goto(0, 260)

score.write(str(red_score) + " : " + str(blue_score), font = ('Arial', 30, 'italic'), align = 'center')

paddle1=turtle.Turtle()	
paddle1.shape("square")
paddle1.color("red")
paddle1.shapesize(stretch_wid = 5, stretch_len = 1)
paddle1.penup()
paddle1.setx(-360)
paddle1.sety(0)

paddle2=turtle.Turtle()	
paddle2.shape("square")
paddle2.color("blue")
paddle2.shapesize(stretch_wid = 5, stretch_len = 1)
paddle2.penup()
paddle2.setx(360)
paddle2.sety(0)

ball=turtle.Turtle()	
ball.shape("circle")
ball.color("white")
ball.penup()
ball.setx(0)
ball.sety(0)
ball.dx = 0.1
ball.dy = -0.1
ball.speed(0)
def paddle1_up():
	y = paddle1.ycor()
	dir1 = 20
	y += dir1
	paddle1.sety(y)

def paddle1_down():
	y = paddle1.ycor()
	dir1 = -20

	y += dir1
	paddle1.sety(y)


def paddle2_up():
	y = paddle2.ycor()
	dir2 = 20
	
	y += dir2
	paddle2.sety(y)

def paddle2_down():
	y = paddle2.ycor()
	dir2 = -20

	y += dir2
	paddle2.sety(y)
sc.listen()
sc.onkey(paddle1_up, "w")
sc.onkeypress(paddle1_down, "s")

sc.onkeypress(paddle2_up, "Up")
sc.onkeypress(paddle2_down, "Down")


def move_ball(ball, paddle1, paddle2):
	global red_score, blue_score
	x, y = ball.xcor(), ball.ycor()
	ball.goto(x+ ball.dx, y+ ball.dy)
	if y > 290:
		ball.sety(y - 1)
		ball.dy *= -1 
	elif y < -290:
		ball.sety(y + 1)
		ball.dy *= -1

	elif x > 400:
		ball.goto(0, 0)
		red_score += 1
		ball.dx *= -1
		score.clear()
		score.write(str(red_score) + " : " + str(blue_score), font = ('Arial', 30, 'italic'), align = 'center')

	elif x <-400:
		ball.goto(0,0)
		blue_score += 1
		score.clear()
		score.write(str(red_score) + " : " + str(blue_score), font = ('Arial', 30, 'italic'), align = 'center')

		ball.dx *= -1
	if   (y < paddle1.ycor() + 50 and y > paddle1.ycor() - 50) and (x < paddle1.xcor() + 20 and x > paddle1.xcor() - 20):
		ball.dx *= -1
		ball.setx(x + 5)
	if   (y < paddle2.ycor() + 50 and y > paddle2.ycor() - 50) and (x < paddle2.xcor() + 20 and x > paddle2.xcor() - 20):
		ball.dx *= -1
		ball.setx(x - 5)

		
def checkwinner():
	if(red_score == 3):
		return 1;
	elif blue_score == 3:
		return 2
	else:
		return 0




def gameover():
	global ball, paddle1, paddle2
	ball.goto(0 , 0)
if __name__ == "__main__":
	while True:
		sc.update()
		c = checkwinner()
		if c == 0:
			move_ball(ball, paddle1, paddle2)
		if c == 1:
			score.clear()
			score.goto(0 , 0)
			score.write("red winner", font = ('Arial', 30, 'italic'), align = 'center')
		elif c == 2:
			score.clear()
			score.goto(0 , 0)
			score.write("blue winner", font = ('Arial', 30, 'italic'), align = 'center')


