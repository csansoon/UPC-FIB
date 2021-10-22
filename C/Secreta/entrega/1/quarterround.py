import numpy as np

OVERFLOW = pow(2,32)

# suma módulo 2^32
def suma32(a, b):
    return (a + b) % OVERFLOW
    #return np.sum(a, b, dtype=np.int32)
    
def xor32(a, b):
    # return (np.bitwise_xor(a, b)) % OVERFLOW
    return (a ^ b) % OVERFLOW

def left_shift32(a, b):
    return (a * pow(2,b)) % OVERFLOW
    #return np.left_shift(a, b, dtype=np.int32)

def QUARTERROUND(matrix, a, b, c, d):
    matrix[a] = suma32(matrix[a],matrix[b])
    matrix[d] = xor32(matrix[d], matrix[a])
    matrix[d] = left_shift32(matrix[d], 16)
    #d <<<= 16

    matrix[c] = suma32(matrix[c], matrix[d])
    matrix[b] = xor32(matrix[b], matrix[c])
    matrix[b] = left_shift32(matrix[b], 12)
    #b <<<= 12

    matrix[a] = suma32(matrix[a],matrix[b])
    matrix[d] = xor32(matrix[d], matrix[a])
    matrix[d] = left_shift32(matrix[d], 8)
    #d <<<= 8

    matrix[c] = suma32(matrix[c], matrix[d])
    matrix[b] = xor32(matrix[b], matrix[c])
    matrix[b] = left_shift32(matrix[b], 7)
    #b <<<= 7

    return matrix