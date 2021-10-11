from operations import *

a = 0b01010111
b = 0b10000011
expected_result = 0b00110001

pol_a = polinomi_binari(a)
pol_b = polinomi_binari(b)

result = GF_product_p(pol_a, pol_b)

print(f'a = {a}')
print(f'b = {b}')
print(f'expected result = {expected_result}')
print(f'{a} * {b} = {value(result)}')
