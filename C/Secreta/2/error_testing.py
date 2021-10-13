from Polynomial import *
from progress import printProgressBar

print(f'GF product p(a, b)!=GF product t(a, b) per algun parell (a, b)')
for a in range(255):
    A = Polynomial(a)
    for b in range(255):
        B = Polynomial(b)

        if GF_product_p(A, B).value() != GF_product_t(A, B).value():
            printProgressBar(255 * 255, 255 * 255 - 1, length=50)
            print(f'❌ - GF_product_p({a}, {b}) != GF_product_t({a}, {b})')

        printProgressBar((a * 255) + b, 255 * 255 - 1, length=50)
print(f'✅')


print(f'GF product p(a, b)!=GF product p(b, a) per algun parell (a, b)')
for a in range(255):
    A = Polynomial(a)
    for b in range(255):
        B = Polynomial(b)

        if GF_product_p(A, B).value() != GF_product_p(B, A).value():
            printProgressBar(255 * 255, 255 * 255, length=50)
            print(f'❌ - GF_product_p({a}, {b}) != GF_product_p({b}, {a})')

        printProgressBar((a * 255) + b, 255 * 255 - 1, length=50)
print(f'✅')


print(f'GF product p(a, GF invers(a))!=1 per a!=0')
for a in range(1, 255):
    A = Polynomial(a)
    B = GF_invers(A)

    if GF_product_p(A, B).value() != 1:
        printProgressBar(255, 255, length=50)
        print(f'❌ - GF product p({a}, GF invers({a})) != 1')

    printProgressBar(a, 255 - 1, length=50)
print(f'✅')