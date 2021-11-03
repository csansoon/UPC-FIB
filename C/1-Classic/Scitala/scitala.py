import os

pathDescifrados = 'C:/Users/Sanson/Documents/UPC-FIB/C/Classic/descifrados'
descifrados = {}
for filename in os.listdir(pathDescifrados):
  descifrados[filename] = open(os.path.join(pathDescifrados, filename), 'r', encoding="utf8").read()
  
cifrado = open("cifrado.txt", "r", encoding="utf8").read()

solucion = open("descifrado.txt", "w", encoding="utf8")

########################################

def analisis_frecuencia(texto):
  charMap = {}

  for char in texto:
    if not char in charMap:
        charMap[char] = 0
    charMap[char] = charMap[char] + 1    
  
  return charMap

def similitud(original, descifrado):
    parecido = 0
    for key in original:
        if original[key] in descifrado.values():
            parecido = parecido + 1
    return parecido / len(original)

#########################################

frecuenciasCifrado = analisis_frecuencia(cifrado)

similitudes = {}
for filename in descifrados:
  texto = descifrados[filename]
  frecuenciasTexto = analisis_frecuencia(texto)
  parecido = similitud(frecuenciasCifrado, frecuenciasTexto) * 100
  similitudes[filename] = parecido
  print(f"{filename}: {parecido}%")


maxSimilitud = max(similitudes, key = similitudes.get)
parecido = similitudes[maxSimilitud]

print(f"El texto más similar es {maxSimilitud}, con una similitud del {parecido}%.")

solucion.write(descifrados[maxSimilitud])
solucion.close()