from random import randint
from blockchain import *
import time
from colored import fg, bg, attr

gray = fg('#989898')
highlight = fg('#FFC648')
attribute = fg('#2D91FF')
good = fg('#16C60C')
bad = fg('#F03A17')
reset = attr(0)

private_key = rsa_key()

print(f'\n{attribute}p - primeP{reset}\n{gray}{private_key.primeP}{reset}')
print(f'\n{attribute}q - primeQ{reset}\n{gray}{private_key.primeQ}{reset}')
print(f'\n{attribute}n - modulus{reset}\n{gray}{private_key.modulus}{reset}')
print(f'\n{attribute}r - length{reset}\n{gray}{private_key.length}{reset}')
print(f'\n{attribute}e - publicExponent{reset}\n{gray}{private_key.publicExponent}{reset}')
print(f'\n{attribute}d - privateExponent{reset}\n{gray}{private_key.privateExponent}{reset}')
print(f'\n{attribute}privateExponentModulusPhiP{reset}\n{gray}{private_key.privateExponentModulusPhiP}{reset}')
print(f'\n{attribute}privateExponentModulusPhiQ{reset}\n{gray}{private_key.privateExponentModulusPhiQ}{reset}')
print(f'\n{attribute}inverseQModulusP{reset}\n{gray}{private_key.inverseQModulusP}{reset}')

message = randint(1, 2**1024)

start_time = time.perf_counter_ns()
firma = private_key.sign(message)
time_firma = time.perf_counter_ns() - start_time

start_time = time.perf_counter_ns()
firma_slow = private_key.sign_slow(message)
time_firma_slow = time.perf_counter_ns() - start_time

print(f'\n{highlight}message{reset}\n{gray}{message}{reset}')
print(f'\n{highlight}sign{attribute} ({time_firma / 1000000} ms){reset}\n{gray}{firma}{reset}')
print(f'\n{highlight}sign_slow{attribute} ({time_firma_slow / 1000000} ms){reset}\n{gray}{firma_slow}{reset}\n')

if (time_firma >= time_firma_slow):
    print(f'{bad}⏱️ La función sign es demasiado lenta.{reset}')
if (firma == firma_slow):
    print(f'{good}✅ Ambas firmas son iguales.{reset}')
else:
    print(f'{bad}❌ Las firmas son diferentes.{reset}')