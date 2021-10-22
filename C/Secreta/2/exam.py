from polynomial import *

print(Polynomial(m).str())
a = Polynomial(0x05)
a_i = GF_invers(a, generator=5)

print(f'a = {a.str()}')
print(f'a invers = {a_i.str()} = {hex(a_i.value)}')