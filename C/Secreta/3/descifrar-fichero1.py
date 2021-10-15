from Crypto.Cipher import AES
from AES import *
from AES import *
import filetype

keyfile = open('clave1.key', 'rb')
key = bytearray(keyfile.read())

#print(f'key = {key}')

fichero1 = open('fichero1.enc', 'rb')
original = bytearray(fichero1.read())

modes= {
    'ECB': AES.MODE_ECB,
    'CBC': AES.MODE_CBC,
    'CFB': AES.MODE_CFB,
    'OFB': AES.MODE_OFB,
    'CTR': AES.MODE_CTR,
    'OPENGP': AES.MODE_OPENPGP,
    'CCM': AES.MODE_CCM,
    'EAX': AES.MODE_EAX,
    'GCM': AES.MODE_GCM,
    #'SIV': AES.MODE_SIV,  # No funciona con una key de 16 bytes
    'OCB': AES.MODE_OCB
}

needs_iv = [AES.MODE_CBC, AES.MODE_CFB, AES.MODE_OFB, AES.MODE_OPENPGP]

validResults = []

for modename, mode in modes.items():
    encryptedtext = original

    if mode in needs_iv:
        iv = original[0:16]
        encryptedtext = original[16:]
        cipher = AES.new(key, mode=mode, iv=iv)
    else:
        cipher = AES.new(key, mode=mode)

    text = cipher.decrypt(encryptedtext)

    valid = validPadding(text)

    if valid:
        type = filetype.guess(text)

        if type == None:
            valid = False
        
        else:
            extension = type.extension
            f = open(f'./decrypted/{modename}.{extension}', 'wb')
            f.write(text)
            print(f'✅ {modename}.{extension}')

    if not valid:
        print(f'❌ {modename}')