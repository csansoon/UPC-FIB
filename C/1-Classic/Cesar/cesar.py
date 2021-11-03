import os

pathDescifrados = 'C:/Users/Sanson/Documents/UPC-FIB/C/Classic/descifrados'
descifrados = {}
for filename in os.listdir(pathDescifrados):
  descifrados[filename] = open(os.path.join(pathDescifrados, filename), 'r', encoding="utf8").read()
  
fileCifrado = open("cifrado.txt", "r", encoding="utf8")

cifrado = fileCifrado.read()

solucion = open("descifrado.txt", "w", encoding="utf8")

########################################

def arreglar_desfase(texto):
    minCharacter = 99999999999

    # Encontrar el caracter más pequeño a partir del valor 256
    for char in texto:
        if ord(char) > 255 and ord(char) < minCharacter:
            minCharacter = ord(char)
    
    # Una vez encontrado, calcular el desfase que ha tenido, asumiendo que ese valor representa 'A'
    desfase = minCharacter - ord('A')

    # Modificar cada caracter que se encuentre en el rango del desfase
    textList = list(texto)
    for index in range(len(textList)):
        char = textList[index]
        if ord(char) > 255 and ord(char) < (minCharacter + (ord('z') - ord('A'))):
            newChar = chr(ord(char) - desfase)
            textList[index] = newChar
    texto = "".join(textList)

    return texto

def analisis_frecuencia(texto):
    charMap = {}

    for char in texto:
		# Tratar cada letra minúscula como si fuera mayúscula.
        if ord(char) >= ord('a') and ord(char) <= ord('z'):
            char = chr(ord(char) - (ord('a') - ord('A')))

        # Si el caracter es una letra, sumar el valor de las veces
		# que se ha encontrado ese caracter en el texto.
        if ord(char) >= ord('A') and ord(char) <= ord('Z'):
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

###############################################

cifrado = arreglar_desfase(cifrado)

frecuenciasCifrado = analisis_frecuencia(cifrado)

similitudes = {}
for filename in descifrados:
    texto = descifrados[filename]
    frecuenciasTexto = analisis_frecuencia(texto)
    similitudes[filename] = similitud(frecuenciasCifrado, frecuenciasTexto) * 100

maxSimilitud = max(similitudes, key = similitudes.get)
parecido = similitudes[maxSimilitud]

print(f"El texto más similar es {maxSimilitud}, con una similitud del {parecido}%.")

solucion.write(descifrados[maxSimilitud])
solucion.close()