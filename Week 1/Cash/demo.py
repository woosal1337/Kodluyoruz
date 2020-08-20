import math

a = eval(input("Owes: "))

twentyFive = 0
ten = 0
five = 0
one = 0

if a > 0:
    twentyFive += math.floor(a / 0.25)
    a -= twentyFive * 0.25
    print("Left: {}".format(a))


    ten += math.floor(a / 0.10)
    a -= ten * 0.1


    five += math.floor(a / 0.05)
    a -= five * 0.05
    print(a)

    one += math.floor(a / 0.01)
    a -= one * 0.01
    print(a)

print(twentyFive + ten + five + one)
print("25s: {}".format(twentyFive))
print("10s: {}".format(ten))
print("5s: {}".format(five))
print("1s: {}".format(one))