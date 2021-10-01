# pip install chacha20poly1305
# source: https://github.com/ph4r05/py-chacha20poly1305
import os
from chacha20poly1305 import ChaCha20Poly1305

key = os.urandom(32)
key = 0x00000000000000000000000000000000
cip = ChaCha20Poly1305(key)

nonce = os.urandom(12)
nounce = 0x000000000000
ciphertext = cip.encrypt(nonce, b'test')

plaintext = cip.decrypt(nonce, ciphertext)
print(plaintext)