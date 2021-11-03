# x8 + x4 + x3 + x2 + 1
m = [True, False, True, True, True, False, False, False, True]
superscripts = ['⁰','¹','²','³','⁴','⁵','⁶','⁷','⁸','⁹']

#* Crea un polinomio a partir de un valor
def polinomi_binari(value):
    polinomi = []
    for i in range(8):
        polinomi.append(False)

    str_binary = "{0:08b}".format(value)
    for i in range(8):
        if str_binary[7 - i] == "1":
            polinomi[i] = True
    
    return polinomi

#* Devuelve el valor numérico de un polinomio
def value(polinomi):
    result = 0
    for i in range(len(polinomi)):
        result = result + (polinomi[i] * pow(2, i))
    return result

#* Devuelve un string que representa el polinomio dado
def str_polinomi(polinomi):
    str_polinomi = ""
    first_print = True
    for index in range(len(polinomi)):
        power = len(polinomi) - index - 1
        if polinomi[power]:
            if first_print:
                first_print = False
            else:
                str_polinomi = str_polinomi + " + "
            if (power == 0):
                str_polinomi = str_polinomi + "1"
            else:
                str_polinomi = str_polinomi + "x"
                str_power = str(power)
                for digit in str_power:
                    str_polinomi = str_polinomi + superscripts[int(digit, base=10)]
    return str_polinomi

#* Elimina los valores excedentes de un polinomio
def irreduct_polinomi(polinomi):
    irreduct = False
    while not irreduct:
        index = len(polinomi) - 1
        if polinomi[index]:
            irreduct = True
        else:
            polinomi.pop(index)
    return polinomi

#* Calcula el valor de un polinomio según el módulo dado
def GF_mod(polinomi, module):
    irreduct_polinomi(polinomi)
    irreduct_polinomi(module)
    if value(polinomi) < value(module):
        return polinomi
    shifted_module = []
    for element in module:
        shifted_module.append(element)
    while len(polinomi) > len(shifted_module):
        shifted_module.insert(0, False)
    # polinomi & shifted_module should be the same size by now
    for index in range(len(polinomi)):
        polinomi[index] = polinomi[index] ^ shifted_module[index]
    return GF_mod(polinomi, module)

#* Calcula la suma de dos polinomios
def GF_suma(a, b):
    result = []
    for i in range(8):
        result.append(a[i] ^ b[i])
    return result

#* Calcula el producto de dos polinomios
def GF_product_p(a, b):
    products = []
    for a_index in range(len(a)):
        if a[a_index]:
            for b_index in range(len(b)):
                if b[b_index]:
                    if not (a_index + b_index) in products:
                        products.append(a_index + b_index)
                    else:
                        products.remove(a_index + b_index)
    #
    result = []
    for i in range(max(products) + 1):
        result.append(False)
    for product_value in products:
        result[product_value] = True

    modded_result = GF_mod(result, m)
    return modded_result