# Tarea 1 Analisis de Algoritmos

## Compilación

Para compilar el programa se debe ejecutar el siguiente comando:

```bash
g++ -std=c++11 -O0 -o uhr uhr.cpp
```

Esto generará un ejecutable llamado `uhr`.

---

## Ejecución

El programa se ejecuta mediante el siguiente comando:

```bash
./uhr <filename>.csv <runs> <lower> <upper> <step>
```

Donde:

* `<filename>.csv` corresponde al nombre del archivo CSV donde se almacenarán los resultados.
* `<runs>` corresponde a la cantidad de ejecuciones realizadas para cada tamaño de matriz.
* `<lower>` corresponde al tamaño mínimo de las matrices.
* `<upper>` corresponde al tamaño máximo de las matrices.
* `<step>` corresponde al factor de crecimiento entre tamaños consecutivos.

---

## Consideraciones importantes

* Para asegurar que las matrices tengan tamaño potencia de 2, el parámetro `<step>` debe ser igual a `2`.
* Es necesario realizar al menos menos `4` ejecuciones (`runs >= 4`).
* El algoritmo de Strassen implementado requiere matrices cuadradas de tamaño potencia de 2.

---

## Ejemplo de ejecución

```bash
./uhr resultados.csv 4 2 1024 2
```

Este ejemplo ejecuta 4 repeticiones para matrices de tamaño (2^1) hasta (2^{10}), almacenando los resultados en el archivo `resultados.csv`.

## Selección del algoritmo y tipo de matrices

El archivo `uhr.cpp` contiene instrucciones comentadas que permiten modificar fácilmente tanto el algoritmo evaluado como el tipo de matrices utilizadas en los experimentos.

### Selección del algoritmo

Para cambiar el algoritmo a evaluar, es necesario modificar la línea correspondiente dentro de la sección de medición de tiempo:

```cpp id="zcx5e9"
C = matrix_multiplication(A,B);
```

o

```cpp id="upjlwm"
C = Strassen(A,B,A.size());
```

Dependiendo del algoritmo que se quiera probar, se debe comentar una línea y descomentar la otra.

---

### Selección del tipo de matrices

La generación de matrices también puede modificarse directamente en `uhr.cpp`. El archivo incluye bloques de código comentados para distintos tipos de matrices, como por ejemplo:

* matrices aleatorias enteras,
* matrices aleatorias reales,
* matrices identidad,
* matrices sparse.

Para utilizar un tipo específico de matriz, se debe descomentar el bloque correspondiente y comentar el bloque actualmente activo.

### Implementación híbrida de Strassen

El archivo `algorithms.cpp` también permite implementar una versión híbrida del algoritmo de Strassen. Para ello, es necesario modificar el caso base de la recursión dentro de la función `Strassen()`.

La implementación híbrida consiste en definir un umbral de recursión `n0`, de manera que cuando el tamaño de la submatriz cumple `n <= n0`, la multiplicación se realiza utilizando el algoritmo clásico (`matrix_multiplication`) en lugar de continuar con llamadas recursivas de Strassen.

Por ejemplo:

```cpp
if(n <= 32){
    return matrix_multiplication(A,B);
}
```

En este ejemplo, el valor `32` corresponde al umbral de recursión `n0`.
