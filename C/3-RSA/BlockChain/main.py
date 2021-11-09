from random import randint
from blockchain import *
import time
from colored import fg, bg, attr

gray = fg('#989898')
highlight = fg('#FFC648')
attribute = fg('#2D91FF')
good = fg('#16C60C')
bad = fg('#F03A17')
reset = attr(0)

private_key = rsa_key()
public_key = rsa_public_key(private_key)

message = randint(1, 2**1024)

trans1 = transaction(message, private_key) 

block1 = block.genesis(trans1)

if (block1.verify_block()):
    print(f'{good}✅ Bloque correcto.{reset}')
else:
    print(f'{bad}❌ Bloque incorrecto.{reset}')