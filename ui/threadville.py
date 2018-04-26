import pygame
from pygame.locals import *
import time

global tv_map
tv_map = []
file_name = "threadville_map.txt"
width_map = 12
height_map = 17
x_map = 831
y_map = 692
step_i = 58
step_j = 32
_begin = 130

#-------------------------------------------------------------------------#
#Function that loads map from disk to memory
def load_map():
    try:
        file_map = open(file_name, "r")
        line = file_map.readline()
        data = line.split("#")
        parse_data(data)
    except:
        print ("Sorry, couldn't load file...")


#Parse data into matrix
def parse_data(data):
    global tv_map
    tmp = 0
    for i in range(width_map):
        row = []
        for j in range(height_map):
            row += [int(data[tmp])]
            tmp += 1
        tv_map += [row]
    print ("Map loaded succesfully...")

#-------------------------------------------------------------------------#
def main():
    # Initialize GUI
    global tv_map
    pygame.init()
    wndw = pygame.display.set_mode((x_map, y_map))
    pygame.display.set_caption("Threadville")
    bckgrnd_img = pygame.image.load("img/map.png")
    pygame.mixer.music.load('threadville_song.mp3')
    pygame.mixer.music.play(15)

    while (True):

        #Load file from disk to memory
        load_map();
        print (tv_map)
        wndw.blit(bckgrnd_img, [0, 0])
        # Parse matrix to paint GUI
        for i in range (width_map):
            for j in range (height_map):
                if (tv_map[i][j] == 0):
                    pass
                else:
                    if (tv_map[i][j] < 9 and tv_map[i][j] > 0):
                        img = pygame.image.load("img/"+str(tv_map[i][j])+".png")
                        wndw.blit(img, [(j*step_j)+_begin,(i*step_i)])

        tv_map = []
        # Update screen
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
        pygame.display.update()
        time.sleep(0.5)


main()
