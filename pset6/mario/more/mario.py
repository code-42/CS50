from cs50 import get_int

def printHash(nTimes):
    print("#" * nTimes, end='')

def printSpace(nTimes):
    print(" " * nTimes, end='')

height=-1
while height < 0 or height > 23:
    height = get_int("Height: ")

for i in range(1, height+1):
    printSpace(height-i)
    printHash(i)
    # print 2 half pyramids with 2 spaces between
    print("  ", end='')
    printHash(i)
    print()





