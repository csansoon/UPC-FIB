import os
# import sympy

pathDescifrados = 'C:/Users/Sanson/Documents/UPC-FIB/C/Classic/descifrados'
descifrados = {}
for filename in os.listdir(pathDescifrados):
  descifrados[filename] = open(os.path.join(pathDescifrados, filename), 'r', encoding="utf8").read()
  
fileCifrado = open("cifrado.txt", "r", encoding="utf8")
cifrado = fileCifrado.read()

solucion = open("descifrado.txt", "w", encoding="utf8")

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

def repeticiones_frecuencias(freq):
  analisis_repeticiones = {}
  for trigrama in freq:
    repeticiones_trigrama = freq[trigrama]
    if not repeticiones_trigrama in analisis_repeticiones:
      analisis_repeticiones[repeticiones_trigrama] = 0
    analisis_repeticiones[repeticiones_trigrama] = analisis_repeticiones[repeticiones_trigrama] + 1
  return analisis_repeticiones

def similitud(original, descifrado):
  repeticiones_original = repeticiones_frecuencias(original)
  repeticiones_descifrado = repeticiones_frecuencias(descifrado)
  parecido = 0
  for repeticiones in repeticiones_original:
    if repeticiones in repeticiones_descifrado and repeticiones_original[repeticiones] == repeticiones_descifrado[repeticiones]:
      parecido = parecido + 1
  return parecido / len(repeticiones_original)

def trigramas_mas_frecuentes(texto, number):
  conjuntoTrigramas = analisis_frecuencia_trigramas(texto)
  trigramas_frecuentes = sorted(conjuntoTrigramas, key=conjuntoTrigramas.get, reverse=True)[:number]
  return trigramas_frecuentes

###############################################


for file in descifrados:
  descifrados[file] = solo_mayusculas(descifrados[file])

frecuenciasCifrado = analisis_frecuencia_trigramas(cifrado)

similitudes = {}

for file in descifrados:
  texto = descifrados[file]
  frecuenciasTexto = analisis_frecuencia_trigramas(texto)
  parecido = similitud(frecuenciasCifrado, frecuenciasTexto) * 100
  similitudes[file] = parecido
  print(f"{file}: {parecido}%")

maxSimilitud = max(similitudes, key = similitudes.get)
parecido = similitudes[maxSimilitud]

print(f"El texto más similar es {maxSimilitud}, con una similitud del {parecido}%.")
#print(descifrados[numText])

trigramas_frecuentes = trigramas_mas_frecuentes(descifrados[maxSimilitud], 3)
print(f"Los trigramas más frecuentes son: {trigramas_frecuentes}")

solucion.write(descifrados[maxSimilitud])
solucion.close()