import cs50
import sys
from cs50 import get_string

# program must accept a single command-line argument, a non-negative integer. Let’s call it k
if len(sys.argv[1:]) < 1 or len(sys.argv[1:]) > 1:
    print("usage: ./caesar.py k")
    exit(1)

# k must be a non-negative integer (e.g., 1). No need to check that it’s indeed numeric.
k = int(sys.argv[1])

# prompt the user for a string of plaintext
p = ""
while p == "":
    p = get_string("plaintext: ")

# loop through plaintext string and encrypt the letters
# program must preserve case
print("ciphertext: ", end='')
for c in p:
    if(c.isalpha()):
        if(c.isupper()):
            print(chr(((ord(c) + k - ord('A')) % 26) + ord('A')), end='')
        else:
            print(chr(((ord(c) + k - ord('a')) % 26) + ord('a')), end='')
    else:
        print(c, end='')

# After outputting ciphertext, you should print a newline.
print()