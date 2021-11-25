from Crypto.PublicKey import RSA
import sympy
import math
import decimal
from colors import *


def isqrt(n):
    x = n
    y = (x + 1) // 2
    while y < x:
        x = y
        y = (x + n // x) // 2
    return x


def find_primes(my_key):
    n = my_key.n
    size = my_key.size_in_bits()
    size_4 = (int)(size / 4)

    rxs_right = n % 2**size_4       # primeros SIZE/4 bits
    rxs_left = n >> (3 * size_4)    # últimos  SIZE/4 bits

    # ? Pueden haber 3 posibles valores de r·s, según
    # ? el carry que puede haber ocurrido en la suma.

    rxs_alt = []  # Posibles valores de r·s
    rxs_alt.append(((rxs_left) << (size_4)) | rxs_right)
    rxs_alt.append(((rxs_left - 1) << (size_4)) | rxs_right)
    rxs_alt.append(((rxs_left - 2) << (size_4)) | rxs_right)

    for rxs in rxs_alt:  # r·s
        r2_s2 = (n - rxs - (rxs << (2 * size_4))) >> (size_4)  # r² + s²
        id_notable = r2_s2 + 2 * rxs   # r² + 2rs + s²
        r_s = (int)(sympy.sqrt(id_notable))
#       r_s = isqrt(id_notable)

        # ? si no es realmente la raíz correcta significa que el resultado
        # ? no era entero y por lo tanto este valor de r·s no es correcto
        if r_s ** 2 != id_notable:
            print(f'{bad}❌ La raíz de {gray}{id_notable}{bad} no es entera.{reset}\n')
            continue

        print(f'{good}✅ La raíz de {gray}{id_notable}{good} es entera.{reset}\n')

        # r + s   =  r_s   }
        # r · s   =  rxs   }  solve r, s
        # r² + s² =  r2_s2 }

        #r, s = sympy.symbols('r s')
        #solution = sympy.solve(r**2 - r_s * r + rxs)
        # print(solution)
        solutions = quadratic_formula(1, -r_s, rxs)

        for r in solutions:
            if r != (int)(r):
                print(f'{bad}❌ r is not an integer ({gray}{r}{bad}){reset}')
            r = (int)(r)
            s0 = r_s - r
            s1 = rxs / r
            if s0 != s1:
                print(f'{bad}❌ The solution is not valid{reset}')
                continue
            print(f'{good}✅ Encontrado!{reset}')
            print(f'{attribute} r = {gray}{r}{reset}')
            print(f'{attribute} s = {gray}{s0}{reset}')

    print(f'{bad}❌ No r s values were found{reset}')


def quadratic_formula(a, b, c):
    # (-b +- sqrt(b**2 - 4ac)) / 2a
    solutions = []
    if a == 0:
        print(f'{bad}❌ A = 0{reset}')
        return solutions

    d = b**2 - (4 * a * c)
    if d < 0:
        print(f'{bad}❌ b² - (4 * a * c){reset}')
        return solutions

    discriminator = isqrt(d)
    if discriminator**2 != d:
        print(f'{bad}❌ La raíz del discriminator no es entero{reset}')
        return solutions

    x0 = (-b + discriminator) / (2*a)
    x1 = (-b - discriminator) / (2*a)
    solutions.append(x0)
    if x1 != x0:
        solutions.append(x1)
    return solutions
