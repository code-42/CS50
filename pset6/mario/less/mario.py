from cs50 import get_int

def printHash(nTimes):
    print("#" * nTimes, end='')

def printSpace(nTimes):
    print(" " * nTimes, end='')

height=-1
while height < 0 or height > 23:
    height = get_int("Height: ")

for i in range(2, height+2):
    printSpace(height-i+1)
    printHash(i)
    print()

# print()



