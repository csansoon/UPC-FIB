from Crypto.Cipher import AES
from AES import *
import hashlib
import filetype
from progress import printProgressBar

chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'


fichero2 = open('fichero2.enc', 'rb')
original = bytearray(fichero2.read())

highest_value = 0
for i in range(len(chars)):
    if ord(chars[i]) > highest_value:
        highest_value = ord(chars[i])
print(f'Highest character: \'{chr(highest_value)}\' with value {highest_value}')

variable_bits = highest_value.bit_length()

#######

first_number = ord('M')
second_number = ord('A')

preMasterKey = 8 * chr(second_number) + 8 * chr(first_number)
preMasterKeyBytes = bytearray(preMasterKey, encoding='utf-8')
H = hashlib.sha256()
H.update(preMasterKeyBytes)
H = H.digest()

iv = H[0:16]
key = H[16:]

cipher = AES.new(key, mode=AES.MODE_CBC, iv=iv)
text = cipher.decrypt(original)
#print(text)

#######

max_value = pow(2, variable_bits)
printProgressBar(0, max_value - 1, length=40)
for second_number in range(max_value):
    for first_number in range(max_value):
        preMasterKey = 8 * chr(second_number) + 8 * chr(first_number)
        preMasterKeyBytes = bytearray(preMasterKey, encoding='utf-8')
        H = hashlib.sha256()
        H.update(preMasterKeyBytes)
        H = H.digest()

        iv = H[0:16]
        key = H[16:]
        
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
                print(f'⚠️ Padding válido [{fixedPreMasterKey}]')
            
            else:
                extension = type.extension
                filename = f'{fixedPreMasterKey}.{extension}'
                print(f'✅ {filename}')
                f = open(f'./decrypted/{filename}', 'wb')
                f.write(text)

    printProgressBar(second_number, max_value - 1, length=40)

