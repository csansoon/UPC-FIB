import os

pathDescifrados = 'C:/Users/Sanson/Documents/UPC/C/Classic/descifrados'
descifrados = []

for filename in os.listdir(pathDescifrados):
  descifrados.append(open(os.path.join(pathDescifrados, filename), 'r', encoding="utf8").read())
  
fileCifrado = open("cifrado.txt", "r", encoding="utf8")

cifrado = fileCifrado.read()

########################################

def solo_mayusculas(texto):
  soloMayusculas = ""
  for char in texto:
    if ord(char) >= ord('a') and ord(char) <= ord('z'):
      char = chr(ord(char) + (ord('A') - ord('a')))
    if ord(char) >= ord('A') and ord(char) <= ord('Z'):
      soloMayusculas = soloMayusculas + char
  return soloMayusculas

def analisis_frecuencia_trigramas(texto):
    conjuntoTrigramas = {}

    for index in range(0, len(texto) - 3, 3):
        trigrama = texto[index] + texto[index + 1] + texto[index + 2]
        if not trigrama in conjuntoTrigramas:
            conjuntoTrigramas[trigrama] = 0
        conjuntoTrigramas[trigrama] = conjuntoTrigramas[trigrama] + 1  

    return conjuntoTrigramas

def similitud(original, descifrado):
    parecido = 0
    for key in original:
        if original[key] in descifrado.values():
            parecido = parecido + 1
    return parecido / len(original)

###############################################

for index in range(len(descifrados)):
  descifrados[index] = solo_mayusculas(descifrados[index])

frecuenciasCifrado = analisis_frecuencia_trigramas(cifrado)

similitudes = []
#for texto in descifrados:
for index in range(len(descifrados)):
  texto = descifrados[index]
  frecuenciasTexto = analisis_frecuencia_trigramas(texto)
  parecido = similitud(frecuenciasCifrado, frecuenciasTexto) * 100
  similitudes.append(parecido)
  print(f"wells_{index + 1}: {parecido}%")

maxSimilitud = max(similitudes)
numText = similitudes.index(maxSimilitud)

print(f"El texto más similar es wells_{numText + 1}, con una similitud del {maxSimilitud}.")
print(descifrados[numText])
