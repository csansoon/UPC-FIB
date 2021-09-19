import os

pathDescifrados = 'C:/Users/Sanson/Documents/UPC-FIB/C/Classic/descifrados'
descifrados = {}
for filename in os.listdir(pathDescifrados):
  descifrados[filename] = open(os.path.join(pathDescifrados, filename), 'r', encoding="utf8").read()
  
cifrado = open("cifrado.txt", "r", encoding="utf8").read()

########################################

print(f"Longitud del texto cifrado: {len(cifrado)}")

textosimilar = -1
diferencia = 99999999

for filename in descifrados:
  texto = descifrados[filename]
  longitud = len(texto)

  if abs(longitud - len(cifrado)) < diferencia:
    textosimilar = filename
    diferencia = abs(longitud - len(cifrado))

  print(f"Longitud del texto {filename}: {len(texto)}")

print(f"Texto con longitud más similar: {filename}")


# HOLAQUETALESTAS

# r = 3

# HOL
# AQU
# ETA
# LES
# TAS

# HAELTOQTEALUASS

# s = 5

# HAELTOQTEALUASS

# 5*3 = 15
