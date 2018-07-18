from cs50 import get_float

# initialize number of coins to give customer
coins = 0

# initialize change
change = 0
while change <= 0:
    change = get_float("How much change is owed?")

# work with whole numbers
cents = change * 100

# get number of quarters
while cents >= 25:
    coins += 1
    cents -= 25

# get number of dimes
while cents >= 10:
    coins += 1
    cents -= 10

# get number of nickels
while cents >= 5:
    coins += 1
    cents -= 5

# get number of pennies
while cents >= 1:
    coins += 1
    cents -= 1

# print the number of coins
print(coins)
