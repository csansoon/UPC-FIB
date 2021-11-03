
#? x8 + x4 + x3 + x2 + 1
m = 0b100011101

superscripts = ['⁰','¹','²','³','⁴','⁵','⁶','⁷','⁸','⁹']

class NotPolynomialError(Exception):
    def __init__(self, var):
        self.var = var
        self.message = f'\'{var}\' is not a Polynomial.'
        super().__init__(self.message)
    pass

class NotGeneratorError(Exception):
    def __init__(self, var):
        self.var = var
        self.message = f'\'{var}\' is not a valid generator.'
        super().__init__(self.message)
    pass

class Polynomial:

    #* Crea un polinomio a partir de un valor
    def __init__(self, value):
        self.value = value
    
    def copy(self):
        return Polynomial(self.value)

    #* Devuelve el valor numérico de un polinomio
    def value(self, base=2):
        return self.value
    

    #* Devuelve un string que representa el polinomio dado
    def str(self):
        if self.value == 0:
            return '0'
        binary_string = format(self.value, 'b')
        first_print = True
        str_polinomi = ""
        for index, digit in enumerate(binary_string):
            power = len(binary_string) - index - 1
            if digit == '1':
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
#    def irreduct(self):
#        irreduct = False
#        while not irreduct:
#            index = len(self.values) - 1
#            if self.values[index]:
#                irreduct = True
#            else:
#                self.values.pop(index)
#        return self.values

    #* Calcula el valor de un polinomio según el módulo dado
    def mod(self, mod):
        pol = self.copy()

        desfase = len(format(pol.value, 'b')) - len(format(mod.value, 'b'))

        if (desfase < 0):
            return pol

        shifted_module = mod.value << desfase
        
        pol = Polynomial(pol.value ^ shifted_module)

        return pol.mod(mod)

#! FIN DE LA CLASE


#* Calcula la suma de dos polinomios
def GF_add(a, b):
    return Polynomial(a.value ^ b.value)


#* Calcula el producto de dos polinomios
def GF_product_p(a, b):
    if a.value == 0 or b.value == 0:
        return Polynomial(0)
    
    products = []
    a_str = format(a.value, 'b')
    b_str = format(b.value, 'b')
    for a_index in range(len(a_str)):
        if a_str[len(a_str) - a_index - 1] == '1':
            for b_index in range(len(b_str)):
                if b_str[len(b_str) - b_index - 1] == '1':
                    if not (a_index + b_index) in products:
                        products.append(a_index + b_index)
                    else:
                        products.remove(a_index + b_index)
    result = 0
    for product_value in products:
        result = result | (1<<product_value)
    
    pol_result = Polynomial(result)

    modded_result = pol_result.mod(Polynomial(m))
    return modded_result


#* Devuelve si el valor dado es un generador válido
def GF_es_generador(a):
    pol_a = Polynomial(a)
    current_value = pol_a.copy()
    values = [1, pol_a.value]
    for i in range(2, 255):
        current_value = GF_product_p(current_value, pol_a)
        values.append(current_value.value)
    
    #print(values)

    for i in range(1,255):
        if not i in values:
            return False
    return True

#* Genera las tablas exponencial y logarítmica del generador introducido
def GF_tables(a):
    if not GF_es_generador(a):
        raise NotGeneratorError(a)
    
    pol_a = Polynomial(a)
    current_value = pol_a.copy()
    exponencial = [1, pol_a.value]
    for i in range(2, 255):
        current_value = GF_product_p(current_value, pol_a)
        exponencial.append(current_value.value)

    logaritme = []
    for i in range(255):
        index = i
        if i == 0:
            index = 255
        logaritme.append(exponencial.index(index))

    result = {}
    result['exponential'] = exponencial # Resultado de calcular g^i
    result['logarithmic'] = logaritme # Valor que necesitaríamos para que g^a = i
    return result


#* Calcula el producto de dos polinomios a partir de las tablas de un generador
def GF_product_t(a, b, generator=2, tables=None):
    if tables == None:
        tables = GF_tables(generator)
    
    if a.value == 0 or b.value == 0:
        return Polynomial(0)

    exp = tables['exponential']

    index_a = exp.index(a.value)
    index_b = exp.index(b.value)

    result = exp[(index_a + index_b) % 255]

    return Polynomial(result)


def GF_invers(a, generator=2, tables=None):
    if tables == None:
        tables = GF_tables(generator)
    
    if a.value == 0:
        return Polynomial(0)
    
    exp = tables['exponential']

    index_a = exp.index(a.value)

    result = exp[(-index_a) % 255]

    return Polynomial(result)
