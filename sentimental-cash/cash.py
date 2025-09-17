dollars = input("Changed owed: ")

while True:
    try:
        while float(dollars) < 0:
            dollars = input("Changed owed: ")
        break
    except ValueError:
        dollars = input("Changed owed: ")


cents = float(dollars)


def calculate_coins(cents, coin_value):
    num_coins = 0
    while cents >= coin_value:
        num_coins += 1
        cents = cents - coin_value

    return num_coins


quarters = calculate_coins(cents, 0.25)
cents = round(cents - (quarters * 0.25), 2)
dimes = calculate_coins(cents, 0.1)
cents = round(cents - (dimes * 0.1), 2)
nickels = calculate_coins(cents, 0.05)
cents = round(cents - (nickels * 0.05), 2)
pennies = calculate_coins(cents, 0.01)

print(quarters + dimes + nickels + pennies)
