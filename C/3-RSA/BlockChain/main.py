from random import randint
from blockchain import *
from colors import *
import pickle

files = [
    'Cadena_bloques_bloque_falso',
    'Cadena_bloques_seed_falsa',
    'Cadena_bloques_transaccion_falsa',
    'Cadena_bloques_valida'
]

for filename in files:

    with open(f'files/{filename}.block', 'rb') as file:
        blockchain = pickle.load(file)

    title = filename.replace('_', ' ')
    print(f'{highlight}{title}:{reset}')
    valido, ultimo_bloque_correcto = blockchain.verify()
    if valido:
        print(f' {good}✅ Todos los bloques de la cadena son válidos.{reset}\n')
    else:
        print(f' {bad}❌ El bloque {ultimo_bloque_correcto + 1} es inválido.{reset}\n')
