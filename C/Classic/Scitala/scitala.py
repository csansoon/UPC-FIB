import os

pathDescifrados = 'C:/Users/Sanson/Documents/UPC/C/Classic/descifrados'
descifrados = []

for filename in os.listdir(pathDescifrados):
  #print(filename)
  descifrados.append(open(os.path.join(pathDescifrados, filename), 'r', encoding="utf8").read())
  
cifrado = open("cifrado.txt", "r", encoding="utf8").read()

########################################

print(f"Longitud del texto cifrado: {len(cifrado)}")

textosimilar = -1
diferencia = 99999999

for i in range(len(descifrados)):
  longitud = len(descifrados[1])

  if abs(longitud - len(cifrado)) < diferencia:
    textosimilar = i
    diferencia = abs(longitud - len(cifrado))

  print(f"Longitud del texto {(i + 1)}: {len(descifrados[i])}")

print(f"Texto con longitud más similar: {(textosimilar + 1)}")


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
