import hashlib


def get_message():
    # mensaje = preambulo + mensaje de la conexion

    preambulo = ''

    for i in range(64):
        preambulo = preambulo + '20'

    for char in 'TLS 1.3, server CertificateVerify':
        preambulo = preambulo + (hex(ord(char))[2:])

    preambulo = preambulo + '00'

    # print(preambulo)

    # SHA384 del mensaje.bin
    mensaje384 = 0
    with open('mensaje.bin', 'rb') as file:
        mensaje384 = hashlib.sha384(file.read()).hexdigest()
    # print(f'Hash del mensaje: {mensaje384}')

    mensaje = bytes(bytearray.fromhex(preambulo + mensaje384))

    m = int(hashlib.sha256(mensaje).hexdigest(), 16)
    # print(f'M: {m}')
    return m
