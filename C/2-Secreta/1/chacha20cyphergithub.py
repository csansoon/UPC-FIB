# pip install chacha20poly1305
# source: https://github.com/ph4r05/py-chacha20poly1305
import os
import numpy
from chacha20poly1305 import ChaCha20Poly1305

key_array = numpy.empty(4)
for i in range(4):
    key_array[i] = 0
#nonce_array = numpy.empty(12/8)
#for i in range(12):
#    nonce_array[i] = 0

print(bytearray(key_array))

#key = os.urandom(32)
key = bytearray(key_array)
cip = ChaCha20Poly1305(key)

#nonce = os.urandom(12)
#nonce = bytearray(nonce_array)
nonce = bytearray(b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00')
ciphertext = cip.encrypt(nonce, b'test')

plaintext = cip.decrypt(nonce, ciphertext)
print(plaintext)