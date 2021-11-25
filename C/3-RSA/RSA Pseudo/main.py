import glob
from re import M
from Crypto.PublicKey import RSA
from Crypto.Cipher import AES
from find_primes import find_primes
from colors import *
import sympy
import subprocess
import os
import filetype

input_pubkey = 'files/carlos.sanson_pubkeyRSA_pseudo.pem'
input_encrypted_key = 'files/carlos.sanson_RSA_pseudo.enc'
input_encrypted_file = 'files/carlos.sanson_AES_pseudo.enc'

output_private_key = 'files/carlos.sanson_privkeyRSA_pseudo.pem'
output_key = 'files/carlos.sanson_AES_key.'
output_file = 'files/carlos.sanson_AES_pseudo'


def main():

    my_key = RSA.importKey(
        open(input_pubkey, 'rb').read())

    p, q = find_primes(my_key)

    print(f'{attribute}P = {gray}{p}{reset}\n')
    print(f'{attribute}Q = {gray}{q}{reset}\n')
    if not sympy.isprime(p):
        print(f'{bad}❌ P no es primo.{reset}')
        return 0, 0
    if not sympy.isprime(q):
        print(f'{bad}❌ Q no es primo.{reset}')
        return 0, 0
    if p*q != my_key.n:
        print(f'{bad}❌ P*Q != N.{reset}')
        return 0, 0

    n = my_key.n
    e = my_key.e
    d = (int)(pow(e, -1, (p - 1) * (q - 1)))

    my_key = RSA.construct((n, e, d))

    with open(output_private_key, 'wb') as file:
        file.write(my_key.exportKey('PEM'))
        file.close()
        print(
            f'{good}✅ Archivo {highlight}{output_private_key}{good} guardado correctamente.{reset}\n')

    AES_password = os.popen(
        f'openssl pkeyutl -decrypt -in {input_encrypted_key} -inkey {output_private_key}').read()

    print(f'Ahora ejecuta este comando en una consola desde esta misma carpeta:')
    print(f'> {highlight}openssl {gray}enc -d -aes-128-cbc -pbkdf2 -in {attribute}{input_encrypted_file}{gray} -out {attribute}{output_file}{gray}{reset}')
    print(f'E introduce esta decryption password:')
    print(f'> {attribute}{AES_password}{reset}\n')
    input(f'Pulsa {attribute}ENTER{reset} para continuar...')

    try:
        with open(output_file, 'rb') as file:
            filedata = file.read()
            type = filetype.guess(filedata)

            if type == None:
                print(
                    f'{bad}❌ Se ha descifrado el archivo pero no se ha encontrado su extensión correcta')
            else:
                extension = type.extension
                f = open(f'{output_file}.{extension}', 'wb')
                f.write(filedata)
                print(
                    f'{good}✅ Se ha descifrado correctamente el fichero {highlight}{output_file}.{extension}{good}.{reset}')
    except:
        print(f'{bad}❌ No se ha podido abrir el archivo {attribute}{output_file}{bad}.')
        print(
            f'{bad}   Esto se puede deber a una mala ejecución del comando anterior.{reset}')
    try:
        os.remove(output_file)
    except:
        ''


if __name__ == "__main__":
    main()
