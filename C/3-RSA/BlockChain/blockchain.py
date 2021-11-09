import sympy
from progress import printProgressBar
debug_range = 5000

class rsa_key:

    def __init__(self, bits_modulo=2048, e=2**16+1, debug = False):
        self.publicExponent = e # (e) representado por entero
        #self.privateExponent # (d) representado por entero
        #self.modulus # (n) representado por entero
        #self.primeP # (p) representado por entero
        #self.primeQ # (q) representado por entero
        #self.privateExponentModulusPhiP # (d_p) privateExponent módulo primeP-1 representado por un entero
        #self.privateExponentModulusPhiQ # (d_q) privateExponent módulo primeQ-1 representado por un entero
        #self.inverseQModulusP # inverso de primeQ módulo primeP representado por un entero

        bits_prime = (int)(bits_modulo / 2)
        max_prime = 2**bits_prime
        self.primeP = sympy.randprime(2, max_prime)
        if (debug): self.primeP = sympy.randprime(2, debug_range)
        while sympy.gcd(self.publicExponent, self.primeP - 1) != 1:
            next = sympy.nextprime(self.primeP)
            if (next < max_prime):
                self.primeP = next
            else:
                self.primeP = 1
        self.primeQ = sympy.randprime(2, max_prime)
        if (debug): self.primeQ = sympy.randprime(2, debug_range)
        originalQ = self.primeQ
        while self.primeP == self.primeQ or sympy.gcd(self.publicExponent, (self.primeP - 1) * (self.primeQ - 1)) != 1:
            print(f'{self.primeQ}', end='\r')
            next = sympy.nextprime(self.primeQ)
            if (next < max_prime):
                self.primeQ = next
            else:
                self.primeQ = 1
            if self.primeQ == originalQ:
                print('ERROR: primeQ not found.')
                break
        

        self.modulus = self.primeP * self.primeQ
        if (self.modulus >= 2**bits_modulo):
            print('ERROR: Módulo demasiado grande')

        self.length = (self.primeP - 1) * (self.primeQ - 1) # (r)
        self.privateExponent = (int)(pow(self.publicExponent, -1, self.length)) # (d)
        #self.privateExponent = (int)(sympy.gcdex(self.publicExponent, self.length)[0]) #! Puede devolver valores negativos

        #self.privateExponent = (1/self.publicExponent) % sympy.gcd(self.primeP - 1, self.primeQ - 1) #! devuelve decimal
        #self.privateExponent = pow(self.publicExponent, -1, (int)(sympy.gcd(self.primeP-1, self.primeQ-1))) #! devuelve 1

        self.privateExponentModulusPhiP = self.privateExponent % (self.primeP - 1)
        self.privateExponentModulusPhiQ = self.privateExponent % (self.primeQ - 1)

        self.inverseQModulusP = sympy.gcdex(self.primeQ, self.primeP)[0]
        
    
    def sign(self, message):
        #? Devuelve un entero que es la firma de message hecha con la clave RSA haciendo servir el TXR
        xp = pow(message, self.modulus, self.primeP)
        xq = pow(message, self.modulus, self.primeQ)
        p, q = sympy.gcdex(self.primeP, self.primeQ)[:2]
        return xp * p * self.primeP + xq * q * self.primeQ

    

    def sign_slow(self, message):
        #? Devuelve un entero que es la firma de message hecha con la clave RSA sin usar el TXR
        return pow(message, self.privateExponent, mod=self.modulus)


class rsa_public_key:

    def __init__(self, rsa_key):
        self.publicExponent = rsa_key.publicExponent # exponente público de la clave rsa_key
        self.modulus = rsa_key.modulus # módulo de la clave rsa_key


    def verify(self, message, signature):
        #? Devuelve True si signature corresponde a una firma de message hecha con la clave RSA asociada a la clave pública RSA
        ''



class transaction:
    '''
    Una transacción es válida si
    signature^publicExponent ≡ message mod(modulus)
    '''

    def __init__ (self, message, RSAkey):
        # RSAkey = clave RSA con la que se firma la transacción
        self.public_key = RSAkey# clave pública RSA correspondiente a RSAkey
        self.message = message # documento que se firma a la transacción representado por un entero
        self.signature # firma de message hecha con la clave RSAkey representada por un entero

    
    def verify(self):
        #? Devuelve True si signature corresponde con una firma de message hecha con la clave pública public_key
        ''



class block:
    '''
    Un bloque es válido si la transacción es válida y su hash h satisface la condición h < 2^{256-d}
    donde d es un parámetro que indica el proof of work necesario para generar un bloque válido.
    Para esta práctica, d=16.
    '''

    def __init__(self):
        self.block_hash # SHA256 del bloque actual representado por un entero
        self.previous_block_hash # SHA256 del bloque anterior representado por un entero
        self.transaction # transacción válida
        self.seed # entero

    
    def genesis(self, transaction):
        #? Genera el primer bloque de una cadena con la transacción transaction que se caracteriza por:
        #?  - previous_block_hash=0
        #?  - es válido
        ''

    
    def next_block(self, transaction):
        #? Genera el siguiente bloque válido con la transacción
        ''
    

    def verify_block(self):
        #? Verifica si un bloque es válido:
        #?  - Comprueba que el hash del bloque anterior cumple con las condiciones exigidas
        #?  - Comprueba que la transacción del bloque es válida
        #?  - Comprueba que el hash del bloque cumple con las condiciones exigidas
        ''
    


class block_chain:
    def __init__(self, transaction):
        #? Genera una cadena de bloques donde el primero es un bloque "genesis" generado con la transacción transaction
        self.list_of_blocks
    

    def add_block(self, transaction):
        #? Añade a la cadena un nuevo bloque válido generado con la transacción
        ''
    

    def verify(self):
        #? Verifica si la cadena de bloques es válida:
        #?  - Comprueba que todos los bloques son válidos
        #?  - Comprueba que el prime bloque es un bloque génesis
        #?  - Comprueba que por cada bloque de la cadena el siguiente es el correcto
        #? Si la cadena no es válida, devuelve False y hasta qué bloque es válido.
        ''