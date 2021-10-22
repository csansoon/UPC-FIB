from Crypto.Cipher import AES
import hashlib
import filetype
from progress import printProgressBar

def validPadding(bytes):
    padding = bytes[len(bytes) - 1]
    if padding == 0:
        return False
    for byte in bytes[len(bytes)-padding:]:
        if byte != padding:
            return False
    return True

chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'

fichero2 = open('fichero2.enc', 'rb')
original = bytearray(fichero2.read())

highest_value = 0
for i in range(len(chars)):
    if ord(chars[i]) > highest_value:
        highest_value = ord(chars[i])

variable_bits = highest_value.bit_length()

max_value = pow(2, variable_bits)
print('🔁 Comprobando todas las claves posibles...')
printProgressBar(0, max_value - 1, length=40)
found = False
for second_number in range(max_value):
    for first_number in range(max_value):
        preMasterKey = 8 * chr(second_number) + 8 * chr(first_number)
        preMasterKeyBytes = bytearray(preMasterKey, encoding='utf-8')
        H = hashlib.sha256()
        H.update(preMasterKeyBytes)
        H = H.digest()

        key = H[0:16]
        iv = H[16:]
        
        cipher = AES.new(key, mode=AES.MODE_CBC, iv=iv)
        text = cipher.decrypt(original)
        valid = validPadding(text)

        if valid:
            type = filetype.guess(text)
            fixedPreMasterKey = list(preMasterKey)
            for i in range(len(fixedPreMasterKey)):
                if fixedPreMasterKey[i] not in chars:
                    fixedPreMasterKey[i] = '_'
            fixedPreMasterKey = "".join(fixedPreMasterKey)

            if type == None:
                valid = False
            
            else:
                extension = type.extension
                filename = f'fichero2.{extension}'
                print(f'✅ Archivo descodificado correctamente con clave "{8*(hex(second_number) + " ")}{8*(hex(first_number)+" ")}"')
                f = open(f'{filename}', 'wb')
                f.write(text)
                found = True
                break
    if found:
        break
    printProgressBar(second_number, max_value - 1, length=40)
if not found:
    print('❌ El fichero no se ha podido descodificar.')
