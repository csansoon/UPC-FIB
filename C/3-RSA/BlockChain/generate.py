from random import randint
from blockchain import *
from colors import *
import pickle
from progress import printProgressBar


blocks = 100

print('Generating key...', end='\r')
key = rsa_key()
print('Generating message...', end='\r')
msg = randint(1, 2**1024)

print('Creating transaction...', end='\r')
trans = transaction(msg, key)

print('Initializing blockchain...', end='\r')
blockchain = block_chain(trans)

for index in range(blocks - 1):
    printProgressBar(index, blocks - 1)
    msg = randint(1, 2**1024)
    trans = transaction(msg, key)

    blockchain.add_block(trans)

valido, ultimo_bloque_correcto = blockchain.verify()
print()

blockchain.list_of_blocks[57].seed = blockchain.list_of_blocks[57].seed + 1

if valido:
    print(f' {good}✅ Todos los bloques de la cadena son válidos.{reset}\n')
    file = open("files/Cadena_100_bloques_validos_hasta_bloque_57.block", "wb")
    pickle.dump(blockchain, file)
else:
    print(f' {bad}❌ El bloque {ultimo_bloque_correcto + 1} es inválido.{reset}\n')
