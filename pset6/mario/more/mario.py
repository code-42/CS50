from cs50 import get_int


# this function prints hash marks
def printHash(nTimes):
    print("#" * nTimes, end='')


# this function prints spaces
def printSpace(nTimes):
    print(" " * nTimes, end='')


# initialize height
height = -1
while height < 0 or height > 23:
    height = get_int("Height: ")

# loop to height + 1 and call print functions
for i in range(1, height + 1):
    printSpace(height - i)
    printHash(i)
    # print 2 half pyramids with 2 spaces between
    print("  ", end='')
    printHash(i)
    print()
