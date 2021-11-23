import sympy
from progress import printProgressBar
import random
import hashlib


class rsa_key:

    def __init__(self, bits_modulo=2048, e=2**16+1, debug=False):
        self.publicExponent = e  # (e) representado por entero

        bits_prime = (int)(bits_modulo / 2)
        max_prime = 2**bits_prime
        min_prime = 2**(bits_prime - 1)
        self.primeP = sympy.randprime(min_prime, max_prime)
        self.primeQ = sympy.randprime(min_prime, max_prime)

        while self.primeP == self.primeQ or sympy.gcd(self.publicExponent, self.primeP - 1) != 1 or sympy.gcd(self.publicExponent, (self.primeP - 1) * (self.primeQ - 1)) != 1:
            self.primeP = sympy.randprime(min_prime, max_prime)
            self.primeQ = sympy.randprime(min_prime, max_prime)

        self.modulus = self.primeP * self.primeQ

        self.length = (self.primeP - 1) * (self.primeQ - 1)  # (r)
        # (d) = inverso modular de e mod (p-1)(q-1)
        self.privateExponent = (int)(pow(self.publicExponent, -1, self.length))

        self.privateExponentModulusPhiP = self.privateExponent % sympy.totient(
            self.primeP)
        self.privateExponentModulusPhiQ = self.privateExponent % sympy.totient(
            self.primeQ)

        self.inverseQModulusP = sympy.gcdex(self.primeQ, self.primeP)[0]

    def sign(self, message):
        # ? Devuelve un entero que es la firma de message hecha con la clave RSA haciendo servir el TXR
        xp = pow(message, self.privateExponentModulusPhiP, self.primeP)
        xq = pow(message, self.privateExponentModulusPhiQ, self.primeQ)
        return (xq + self.primeQ * self.inverseQModulusP * (xp - xq)) % self.modulus

    def sign_slow(self, message):
        # ? Devuelve un entero que es la firma de message hecha con la clave RSA sin usar el TXR
        return pow(message, self.privateExponent, mod=self.modulus)


class rsa_public_key:

    def __init__(self, rsa_key):
        # exponente público de la clave rsa_key
        self.publicExponent = rsa_key.publicExponent
        self.modulus = rsa_key.modulus  # módulo de la clave rsa_key

    def verify(self, message, signature):
        # ? Devuelve True si signature corresponde a una firma de message hecha con la clave RSA asociada a la clave pública RSA
        return message == pow(signature, self.publicExponent, self.modulus)


class transaction:
    '''
    Una transacción es válida si
    signature^publicExponent ≡ message mod(modulus)
    '''

    def __init__(self, message, RSAkey):
        # RSAkey = clave RSA con la que se firma la transacción
        # clave pública RSA correspondiente a RSAkey
        self.public_key = rsa_public_key(RSAkey)
        # documento que se firma a la transacción representado por un entero
        self.message = message
        # firma de message hecha con la clave RSAkey representada por un entero
        self.signature = RSAkey.sign(message)

    def verify(self):
        # ? Devuelve True si signature corresponde con una firma de message hecha con la clave pública public_key
        return self.public_key.verify(self.message, self.signature)


d = 16
condition = pow(2, 256 - d)


class block:
    '''
    Un bloque es válido si la transacción es válida y su hash h satisface la condición h < 2^{256-d}
    donde d es un parámetro que indica el proof of work necesario para generar un bloque válido.
    Para esta práctica, d=16.
    '''
    # seed = random entre 0 y 256 bits

    def __init__(self):
        '''
        self.block_hash # SHA256 del bloque actual representado por un entero
        self.previous_block_hash # SHA256 del bloque anterior representado por un entero
        self.transaction # transacción válida
        self.seed # entero
        '''

    def genesis(self, transaction):
        # ? Genera el primer bloque de una cadena con la transacción transaction que se caracteriza por:
        # ?  - previous_block_hash=0
        # ?  - es válido
        self.previous_block_hash = 0
        self.transaction = transaction
        self.find_hash()
        return self

    def next_block(self, transaction):
        # ? Genera el siguiente bloque válido con la transacción
        new_block = block()
        new_block.previous_block_hash = self.block_hash
        new_block.transaction = transaction
        new_block.find_hash()
        return new_block

    def find_hash(self):
        # ? Encuentra el hash correcto para esta transacción
        global condition

        found = False
        while not found:
            self.seed = random.randint(0, 2**256)
            h = self.calculate_hash()

            if h < condition:
                self.block_hash = h
                found = True

    def calculate_hash(self):
        entrada = str(self.previous_block_hash)
        entrada = entrada + str(self.transaction.public_key.publicExponent)
        entrada = entrada + str(self.transaction.public_key.modulus)
        entrada = entrada + str(self.transaction.message)
        entrada = entrada + str(self.transaction.signature)
        entrada = entrada + str(self.seed)

        return int(hashlib.sha256(entrada.encode()).hexdigest(), 16)

    def verify_block(self):
        global condition
        # ? Verifica si un bloque es válido:
        # ?  - Comprueba que el hash del bloque anterior cumple con las condiciones exigidas
        # ?  - Comprueba que la transacción del bloque es válida
        # ?  - Comprueba que el hash del bloque cumple con las condiciones exigidas
        if not (self.previous_block_hash < condition):
            return False
        if not (self.block_hash < condition):
            return False
        if not (self.block_hash == self.calculate_hash()):
            return False
        if not (self.transaction.verify()):
            return False
        return True


class block_chain:
    def __init__(self, transaction):
        # ? Genera una cadena de bloques donde el primero es un bloque "genesis" generado con la transacción transaction
        first_block = block().genesis(transaction)
        self.list_of_blocks = [first_block]

    def add_block(self, transaction):
        # ? Añade a la cadena un nuevo bloque válido generado con la transacción
        last_block = self.list_of_blocks[-1]
        next_block = last_block.next_block(transaction)
        self.list_of_blocks.append(next_block)

    def verify(self):
        # ? Verifica si la cadena de bloques es válida:
        # ? Si la cadena no es válida, devuelve False y hasta qué bloque es válido.
        if len(self.list_of_blocks) == 0:
            return True, len(self.list_of_blocks) - 1
        # ?  - Comprueba que el prime bloque es un bloque génesis
        if self.list_of_blocks[0].previous_block_hash != 0:
            return False, -1
        # ?  - Comprueba que por cada bloque de la cadena el siguiente es el correcto
        # ?  - Comprueba que todos los bloques son válidos
        for index in range(len(self.list_of_blocks)):
            if not self.list_of_blocks[index].verify_block():
                return False, index - 1
            if index > 0 and self.list_of_blocks[index].previous_block_hash != self.list_of_blocks[index - 1].block_hash:
                return False, index - 1
        return True, len(self.list_of_blocks) - 1
