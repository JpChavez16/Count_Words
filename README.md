# 📊 Desafío: Word Count en Archivos de 20GB (C++ con OpenMP y Python)

Este proyecto aborda el problema de contar palabras en un archivo de texto extremadamente grande (20 GB), sin utilizar herramientas de procesamiento distribuido como **MapReduce** o **Apache Spark**. Se exploran dos implementaciones:

- 🧠 **Python secuencial** para facilitar el desarrollo y la lectura del algoritmo.
- ⚡ **C++ con OpenMP** para lograr una ejecución eficiente y paralela.

---

## ⚠️ Consideraciones al leer archivos grandes

- Los archivos de 20GB pueden tener **saltos de línea, caracteres especiales o líneas truncadas** si no se gestionan los bloques con cuidado.
- En la versión paralela se evita leer líneas incompletas en cada hilo ajustando el inicio de lectura (`seekg` y `getline`).

---

## 🛠 Generación del archivo de prueba (20GB)

Antes de ejecutar el conteo de palabras, necesitas generar el archivo masivo con el script de C++.

### ✏️ Configuración

El generador parte de un archivo base de palabras (por ejemplo, `inputs/palabras_base.txt`) y lo repite hasta alcanzar los 20GB deseados.

#### Configura el archivo `generar_archivo.cpp`:

```cpp
const size_t BLOCK_SIZE = 1024 * 1024; // 1 MB por bloque
size_t FILE_SIZE_GB = 20;
const size_t FILE_SIZE_BYTES = FILE_SIZE_GB * 1024 * 1024 * 1024;

string input_file = "inputs/palabras_base.txt";  // Archivo base (7MB aprox.)
string output_file = "archivo_20GB.txt";         // Archivo de salida
string output_dir = "outputs_test";              // Carpeta de salida
```
---

## ⚠📁 Estructura del proyecto

```
├── generar_archivo.cpp         # Generador del archivo de 20GB
├── contar_palabras.py          # Word count secuencial en Python
├── wordcount_parallel.cpp      # Word count paralelo con OpenMP
├── inputs/
│   └── palabras_base.txt       # Archivo de palabras en español (~7MB)
├── outputs_test/               # Carpeta para resultados (NO incluida en el repo)
└── README.md                   # Este documento
```
---

## ⚠✅ Requisitos
```
C++17 o superior
Compatibilidad con OpenMP ( -fopenmp)
Python 3.x
Memoria recomendada: 8 GB+
Disco con al menos 20 GB de espacio libre
```

