import pygame
import serial
from sys import argv

port = '/dev/ttyUSB0'

if len(argv)>1:
	port = argv[1]

ser = serial.Serial(port)
mode = True
#pygame vars
pygame.init()
SIZE = [800, 640]
screen = pygame.display.set_mode(SIZE)
pygame.display.set_caption("Etch-A-Sketch")
#Canvas for painting, cursor for drawing cursor
canvas = pygame.Surface(screen.get_size())
canvas = canvas.convert()
cursor = pygame.Surface(screen.get_size())
canvas.fill((0, 0, 0))
cursor.set_colorkey((1,1,1))
screen.blit(canvas, (0, 0))
screen.blit(cursor, (0, 0))
pygame.display.flip()

line = [None, None]
brushSize = 1
#brush
x, y = 400, 320
#main loop
done=False
while not done:
	cursor.fill((1, 1, 1))
	#Keyboard input
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
				done = True

	found = False
	while not found:
		data = ser.read().decode()
		if data not in '\r\n':
			data = int(data)
			if data == 0:
				mode = not mode
				print("Switch!")
			else:
				incr = ((data-1)*(-2)+1)
				if mode:
					y -= incr
				else:
					x += incr
				found = True
	print((x,y))

	#pygame.draw.rect(cursor, colors[color], (x-brushSize, y-brushSize, brushSize, brushSize), 2)
	pygame.draw.rect(cursor, (0, 255, 0), (x-brushSize+2, y-brushSize+2, brushSize-4, brushSize-4), 2)
	
	pygame.draw.rect(canvas, (255,255,255), (x-brushSize, y-brushSize, brushSize, brushSize), 0)
					
	#Draw cursor on top of canvas
	screen.blit(canvas, (0, 0))
	screen.blit(cursor, (0, 0))
	pygame.display.flip()