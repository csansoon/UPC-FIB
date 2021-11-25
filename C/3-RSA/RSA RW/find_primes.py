import glob
from Crypto.PublicKey import RSA
import sympy
from colors import *


def find_primes(my_key):
    pems = glob.glob('files\\keys\\*.pem')

    p = 1

    for filename in pems:
        external_key = RSA.importKey(open(filename, 'rb').read())
        p = sympy.gcd(my_key.n, external_key.n)
        if p > 1 and p != my_key.n:
            break

    if p == 1:
        print(f'{bad}❌ No se ha encontrado ningún común divisor.{reset}')
        return

    p = p
    q = my_key.n / p
    p = (int)(p)
    q = (int)(q)

    return p, q
