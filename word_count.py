from collections import defaultdict

conteo = defaultdict(int)

with open("archivo_20gb.txt", "r", encoding="utf-8") as f:
    for linea in f:
        palabras = linea.strip().split()
        for palabra in palabras:
            conteo[palabra] += 1

# Guarda el resultado
with open("resultado.txt", "w", encoding="utf-8") as out:
    for palabra, cantidad in conteo.items():
        out.write(f"{palabra} {cantidad}\n")
