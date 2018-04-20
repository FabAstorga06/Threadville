import time

global tv_map
tv_map = []
file_name = "threadville_map.txt"
width_map = 3
height_map = 3

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
    global tv_map    
    while (True):
        load_map();
        print tv_map # AQUI SE PINTA LA GUI CADA MEDIO SEGUNDO !!!!
        tv_map = []
        time.sleep(0.5)

main()
