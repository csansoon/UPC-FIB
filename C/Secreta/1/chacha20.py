# Cada número ocupa exactamente 32 bits
# ["expa"]    ["nd 3"]    ["2-by"]    ["te k"]
# [key]       [key]       [key]       [key]
# [key]       [key]       [key]       [key]
# [counter]   [nonce]     [nonce]     [nonce]

import sys
from quarterround import QUARTERROUND

def print_state(matrix):
    print(f'[{hex(matrix[0])}][{hex(matrix[1])}][{hex(matrix[2])}][{hex(matrix[3])}]')
    print(f'[{hex(matrix[4])}][{hex(matrix[5])}][{hex(matrix[6])}][{hex(matrix[7])}]')
    print(f'[{hex(matrix[8])}][{hex(matrix[9])}][{hex(matrix[10])}][{hex(matrix[11])}]')
    print(f'[{hex(matrix[12])}][{hex(matrix[13])}][{hex(matrix[14])}][{hex(matrix[15])}]')


for counter in range(1, 64):
    initial_state = [0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
                    0x00000000, 0x00000000, 0x00000000, 0x00000000,
                    0x00000000, 0x00000000, 0x00000000, 0x00000000,
                    counter, 0x00000000, 0x00000000, 0x00000000]

    state = []
    for value in initial_state:
        state.append(value)

    for i in range(10): 
        # Column rounds:
        QUARTERROUND(state, 0, 4, 8, 12)
        QUARTERROUND(state, 1, 5, 9, 13)
        QUARTERROUND(state, 2, 6, 10, 14)
        QUARTERROUND(state, 3, 7, 11, 15)

        # Diagonal rounds
        QUARTERROUND(state, 0, 5, 10, 15)
        QUARTERROUND(state, 1, 6, 11, 12)
        QUARTERROUND(state, 2, 7, 8, 13)
        QUARTERROUND(state, 3, 4, 9, 14)

    final_state = []
    for i in range(len(state)):
        final_state.append((state[i] + initial_state[i]) % pow(2,32))

    print(f"\nFINAL STATE (counter = {counter}):")
    print_state(final_state)