height = input("Height: ")
while not height.isnumeric() or int(height) < 1 or int(height) > 8:
    height = input("Height: ")

a = int(height)


def space(space):
    for _ in range(space):
        print(" ", end="")


def row(bricks):
    for _ in range(bricks):
        print("#", end="")


for i in range(a):
    space(a - 1 - i)
    row(i + 1)
    print("  ", end="")
    row(i + 1)
    print()
