# x8 + x4 + x3 + x2 + 1
m = [True, False, True, True, True, False, False, False, True]


def polinomi_binari(value):
    polinomi = []
    for i in range(8):
        polinomi.append(False)

    str_binary = "{0:08b}".format(value)
    for i in range(8):
        if str_binary[7 - i] == "1":
            polinomi[i] = True
    
    return polinomi


def value(polinomi):
    result = 0
    for i in range(len(polinomi)):
        result = result + (polinomi[i] * pow(2, i))
    return result


def GF_suma(a, b):
    result = []
    for i in range(8):
        result.append(a[i] ^ b[i])
    return result


def GF_product_p(a, b):
    product = value(a) * value(b)
    print(f'product before mod = {bin(product)}')
    product = product % value(m)
    print(f'm = {value(m)}')
    return polinomi_binari(product)