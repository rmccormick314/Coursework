import math

integer = 1
register = 0

while integer <= 10:
    print(integer)
    if integer == 10:
        print('=')
    else:
        print('+')
    register += integer
    integer += 1

print(register)
