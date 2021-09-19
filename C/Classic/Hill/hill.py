import os
import numpy as np
from numpy import matrix

pathDescifrados = 'C:/Users/Sanson/Documents/UPC/C/Classic/descifrados'
descifrados = []

for filename in os.listdir(pathDescifrados):
  descifrados.append(open(os.path.join(pathDescifrados, filename), 'r', encoding="utf8").read())
  
fileCifrado = open("cifrado.txt", "r", encoding="utf8")

cifrado = fileCifrado.read()

########################################

# a = matrix([[1,2],[3,4]])

def trigramasMasFrecuente(texto, n):
    conjuntoTrigramas = {}

    for index in range(0, len(texto) - 3, 3):
        trigrama = texto[index] + texto[index + 1] + texto[index + 2]
        if not trigrama in conjuntoTrigramas:
            conjuntoTrigramas[trigrama] = 0
        conjuntoTrigramas[trigrama] = conjuntoTrigramas[trigrama] + 1

    #return max(conjuntoTrigramas, key=conjuntoTrigramas.get)
    return sorted(conjuntoTrigramas, key=conjuntoTrigramas.get, reverse=True)[:n]

def valueOf(char):
  if ord(char) >= ord('a') and ord(char) <= ord('z'):
    char = chr(ord(char) + (ord('A') - ord('a')))
  
  if ord(char) >= ord('A') and ord(char) <= ord('Z'):
    return ord(char) - ord('A')
  
  return -1

def inverse(matrix):
  return np.linalg.inv(matrix)

def mod26(matrix):
  for array in matrix:
    for element in array:
      element = element % 26
  return matrix

########################################

trigramasOriginales = ['THE','THA','ETH']
trigramasFrecuentes = trigramasMasFrecuente(cifrado, 3)

print(f"Trigramas más frecuentes encontrados: {trigramasFrecuentes}")

matrixOriginal = matrix([[valueOf(trigramasOriginales[0][0]), valueOf(trigramasOriginales[1][0]), valueOf(trigramasOriginales[2][0])], [valueOf(trigramasOriginales[0][1]), valueOf(trigramasOriginales[1][1]), valueOf(trigramasOriginales[2][1])], [valueOf(trigramasOriginales[0][2]), valueOf(trigramasOriginales[1][2]), valueOf(trigramasOriginales[2][2])]])
matrixFrecuentes = matrix([[valueOf(trigramasFrecuentes[0][0]), valueOf(trigramasFrecuentes[1][0]), valueOf(trigramasFrecuentes[2][0])], [valueOf(trigramasFrecuentes[0][1]), valueOf(trigramasFrecuentes[1][1]), valueOf(trigramasFrecuentes[2][1])], [valueOf(trigramasFrecuentes[0][2]), valueOf(trigramasFrecuentes[1][2]), valueOf(trigramasFrecuentes[2][2])]])

# K * matrixOriginal (mod 26) = matrixFrecuentes

inverseMatrixOriginal = mod26(inverse(matrixOriginal))

# K = matrixFrecuentes * inverseMatrixOriginal

key = mod26(matrix.dot(matrixFrecuentes, inverseMatrixOriginal))

print(f"Key: {key}")

#trigramaOriginal = matrix([[ord('T')],[ord('H')],[ord('E')]])

#matrixTrigramaFrecuente = matrix([[trigramaFrecuente[0]],[trigramaFrecuente[1]],trigramaFrecuente[2]])

#trigramaFrecuenteInverso = np.linalg.inv(matrixTrigramaFrecuente) 

#print(trigramaFrecuenteInverso)