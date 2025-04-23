import random
import os

# Carga palabras desde el archivo base
with open("palabras_base.txt", "r", encoding="utf-8") as f:
    palabras = [line.strip() for line in f if line.strip()]

# Archivo de salida
output_file = "archivo_20gb.txt"
objetivo_bytes = 20 * 1024 * 1024 * 1024  # 20 GB

# Escribe hasta alcanzar el tamaño deseado
with open(output_file, "w", encoding="utf-8") as out:
    size = 0
    while size < objetivo_bytes:
        # Genera línea con entre 5 y 12 palabras aleatorias
        linea = " ".join(random.choices(palabras, k=random.randint(5, 12))) + "\n"
        out.write(linea)
        size += len(linea.encode("utf-8"))  # cuenta tamaño real en bytes

print("✅ Archivo de 20 GB generado con éxito.")
