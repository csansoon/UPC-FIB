from Crypto.PublicKey import RSA
import sympy
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

        # ? si no es realmente la raíz correcta significa que el resultado
        # ? no era entero y por lo tanto este valor de r·s no es correcto
        if r_s ** 2 != id_notable:
            continue

        # r + s   =  r_s   }
        # r · s   =  rxs   }  solve r, s
        # r² + s² =  r2_s2 }

        # r² - (r_s) r + (rxs) = 0
        solutions = quadratic_formula(1, -r_s, rxs)

        for r in solutions:
            s0 = r_s - r
            s1 = rxs // r
            if s0 != s1:
                continue
            s = s0

            p = (r << (size_4)) | s
            q = (s << (size_4)) | r

            return p, q

    print(f'{bad}❌ No r s values were found{reset}')
    return


def quadratic_formula(a, b, c):
    # (-b +- sqrt(b**2 - 4ac)) / 2a
    solutions = []
    if a == 0:
        return solutions

    d = b**2 - (4 * a * c)
    if d < 0:
        return solutions

    discriminator = isqrt(d)
    if discriminator**2 != d:
        return solutions

    x0 = (-b + discriminator) // (2*a)
    x1 = (-b - discriminator) // (2*a)
    solutions.append(x0)
    if x1 != x0:
        solutions.append(x1)
    return solutions
