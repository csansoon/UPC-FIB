from quarterround import QUARTERROUND
from progress import printProgressBar
import matplotlib.pyplot as plt

def binary_string(matrix):
    binary = ""
    for i in range(len(matrix)):
        i_binary = "{0:32b}".format(matrix[i])
        binary = binary + i_binary
    return binary

cambios_acumulados = []
cambios_en_bits = []
for i in range(32 * 4 * 4):
    cambios_acumulados.append(0)
    cambios_en_bits.append(0)

iterations = 4096

for counter in range(1, iterations):

    initial_state = [0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
                    0x00000000, 0x00000000, 0x00000000, 0x00000000,
                    0x00000000, 0x00000000, 0x00000000, 0x00000000,
                    counter, 0x00000000, 0x00000000, 0x00000000]
    initial_binary = binary_string(initial_state)

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
    final_binary = binary_string(final_state)

    # Stats
    cantidad_de_cambios = 0
    for i in range(len(final_binary)):
        if final_binary[i] != initial_binary[i]:
            cantidad_de_cambios = cantidad_de_cambios + 1
            cambios_en_bits[i] = cambios_en_bits[i] + 1
    cambios_acumulados[cantidad_de_cambios] = cambios_acumulados[cantidad_de_cambios] + 1

    printProgressBar(counter, iterations, length=50)


# Plots

fig, axs= plt.subplots(2, 1)

axs[0].bar(range(512), cambios_acumulados)
axs[0].set_ylabel('nombre de vegades que r bits han canviat')
axs[0].set_xlabel('nombre r de bits que han canviat')
axs[0].set_title('Freqüències del nombre total de bits que canvien')
axs[0].legend()

axs[1].bar(range(512), cambios_en_bits)
axs[1].set_ylabel('nombre de vegades que el bit ha canviat')
axs[1].set_xlabel('posició del bit')
axs[1].set_title('Freqüències de les posicions que canvien')
axs[1].legend()

plt.show()