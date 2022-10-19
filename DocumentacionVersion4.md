### Mutacion de bits
Después de todas las modificaciones pertinentes y mucha refactorización, el equipo consiguió llegar al siguiente código, el cual se explica por partes a continuación.
#### Pseudocódigo
```cpp
FOR generacion en maxNumGeneraciones
  IF generacion = 0
    crearGeneracion
  ELSE
    seleccionarSeis
    cruzarSeis
    ingresarCuatroRestantes
    ordenarGeneracion
    contarIndividuosConDiezCeros
    IF individuosConDiezCeros < 0
      mutar
    END IF
  END IF
  ordenarGeneracion
  mostrarGeneracion
  contarCerosGeneracion
  IF contarCerosGeneracion = 100
    EXIT
  END IF
END FOR
```
#### Funciones
A lo largo del código se utilizan muchas funciones para quitar complejidad de la función principal (main) y para que si en algún futuro tenemos que añadir o quitar alguna funcionalidad sea de una manera mucho más sencilla.
##### countOcurrences
 Función para contar el número de veces que aparece un carácter en una cadena.
•	@param c Carácter a contar
•	@param str Cadena a buscar
•	@return - El número de veces que aparece el carácter c en la cadena str
```cpp
int countOcurrences(char c, string str) {
  int count = 0;
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == c) {
      count++;
    }
  }
  return count;
}
```
##### aleatorioEnRango
Función para generar un número aleatorio entre un rango.
•	@param minimo Límite mínimo que se desea generar
•	@param maximo Límite máximo que se desea generar
•	@return numero aleatorio en dicho rango
```cpp
int aleatorioEnRango(int minimo, int maximo) {
  return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}
```
##### cadenaAleatoria
Función para generar una cadena aleatoria
•	@param longitud La longitud de la cadena a generar
•	@param destino La cadena donde se almacenará la cadena aleatoria
```cpp
void cadenaAleatoria(int longitud, string &destino) {
  char muestra[] = "01";
  for (int i = 0; i < longitud; i++) {
    int indiceAleatorio = aleatorioEnRango(0, (int) strlen(muestra) - 1);
    destino[i] += muestra[indiceAleatorio];
  }
}
```
##### maxCeros   
Función para obtener el número mayor de ceros en un arreglo
•	@param arr El arreglo de números
•	 @param n El número de elementos en el arreglo
•	 @return max El número mayor de ceros en el arreglo
```cpp
int maxCeros(int arr[], int n) {
  int max = arr[0];
  for (int i = 1; i < n; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}
```
##### existeEnArray
Retorna true si el número x está en el arreglo arr, y false en caso contrario
•	@param arr El arreglo en el que se buscará
•	 @param n el número de elementos en el arreglo
•	 @param x el número a buscar 
•	 @return El valor en true o false
```cpp
bool existeEnArray(int arr[], int n, int x) {
  for (int i = 0; i < n; i++) {
    if (arr[i] == x) {
      return true;
    }
  }
  return false;
}
```
##### obtenerIndiceRandom
Retorna un índice aleatorio de un arreglo que no se haya seleccionado ya
•	@param arr El arreglo en el que se buscará si el índice existe
•	@param n El número de elementos en el arreglo
•	 @return index El índice del arreglo que no está aún seleccionado
```cpp
int obtenerIndiceRandom(int arr[], int n) {
  int index = aleatorioEnRango(0, n - 1);
  while (existeEnArray(arr, n, index)) {
    index = aleatorioEnRango(0, n - 1);
  }
  return index;
}
```
##### generarHijo
Tomando dos cadenas, devuelve una nueva cadena que es una combinación de las dos
•	@param padre1
•	@param padre2 
•	 @return hijo El hijo de los dos padres
```cpp
string generarHijo(string padre1, string padre2) {
  int index = aleatorioEnRango(0, padre1.length() - 1);
  string hijo = padre1.substr(0, index) + padre2.substr(index, 9);
  return hijo;
}
```
##### copararHijoPadre
Compara los ceros del hijo con los ceros del padre
•	@param hijo
•	@param padre 
•	@return true si el hijo tiene más ceros que el padre
```cpp
bool compararHijoPadre(string &hijo, string &padre) {
  int cerosHijo = countOcurrences('0', hijo);
  int cerosPadre = countOcurrences('0', padre);
  return cerosHijo > cerosPadre;
}
```
##### getIndividuosConDiezCeros
Hace el conteo de individuos con 10 ceros en la generación
•	@param individuos generacion
•	 @param n individuos en la generacion 
•	 @return count Numero de individuos con 10 ceros
```cpp
int getIndividuosConDiezCeros(string individuos[], int n) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (countOcurrences('0', individuos[i]) == 10) {
      count++;
    }
  }
  return count;
}
```
##### mostrarGeneracion
Tomando un arreglo de cadenas y un entero como parámetros, imprime las cadenas en el arreglo, junto con el número de ceros en cada cadena
•	@param individuos (generación)
•	@param n número de individuos en la generación
•	@param k numero de la generación
```cpp
void mostrarGeneracion(string individuos[], int n, int k) {
  int cerosPorIndividuo = 0;
  cout << "-------------------------" << endl;
  cout << "Generacion " << k + 1 << endl;
  cout << "-------------------------" << endl;
  for (int i = 0; i < n; i++) {
    cerosPorIndividuo = countOcurrences('0', individuos[i]);
    cout << i + 1 << ":" << individuos[i] << ":" << cerosPorIndividuo << endl;
  }
}
```
##### sumaCerosGeneracion
Función que cuenta el número de ceros en la población y retorna la suma
•	@param individuos (generación)
•	@param n número de individuos en la generación 
•	@param k numero de la generación
•	@return suma El total de ceros en la generación
```cpp
int sumaCerosGeneracion(string individuos[], int n, int k) {
  int suma = 0;
  for (int i = 0; i < n; i++) {
    suma += countOcurrences('0', individuos[i]);
  }
  if (suma == 100) {
    cout << "La generacion " << k + 1 << " tiene 100 ceros" << endl;
  }
  return suma;
}
```
##### ordenarGeneracion
Tomando un arreglo de cadenas, un arreglo de cadenas(copia del primero) y un arreglo de enteros como parámetros, ordena el primer arreglo de cadenas basado en los enteros en el tercer arreglo.
•	@param generacion Generación que se ordenara
•	@param generacionCopia Generación copia para ordenar la generación original
•	@param ceros Array de enteros que contiene el número de ceros de cada individuo
```cpp
void ordenarGeneracion(string generacion[10], string generacionCopia[10], int ceros[11]) {
  for (int i = 0; i < 10; i++) {
    int max = maxCeros(ceros, 10);
    int index = 0;
    for (int j = 0; j < 10; j++) {
      if (ceros[j] == max) {
        index = j;
        break;
      }
    }
    generacion[i] = generacionCopia[index];
    ceros[index] = -1;
  }
  for (int i = 0; i < 10; i++) {
    generacionCopia[i] = generacion[i];
  }
}
```

#### Variables Globales
```cpp
#define LONGITUD_DESEADA 10
#define NUMERO_DE_CADENAS 10
string binarios1[NUMERO_DE_CADENAS][NUMERO_DE_CADENAS];
string binariosCopy1[NUMERO_DE_CADENAS][NUMERO_DE_CADENAS];
```

#### Función Principal (main)
##### Inicializamos srand()
Lo utilizaremos para generar las cadenas aleatorias, para elegir índices al azar para mutar y también para cruzar elementos de manera aleatoria
```cpp
int main() {
  srand(time(NULL));
  // ...
}
```
##### Variables locales
Usaremos diferentes variables para manipular las generaciones de una manera más sencilla durante la ejecución del código, a continuación, en el bloque del código se muestra las variables y un comentario significativo que menciona la función que realiza cada variable.
```cpp
int main() {
  // ...
  /* Definiendo el arreglo de chars para cuando generamos las cadenas */
  char destino[LONGITUD_DESEADA + 1] = "";

  /* Definiendo el arreglo de números para guardar el número de ceros en cada cadena. */
  int ceros[LONGITUD_DESEADA + 1];

  /* Cuenta de el numero de individuos con todos ceros en la generacion */
  int individuosCeros = 0;
  
  /* Cuenta de el total de ceros en la generacion k */
  int suma = 0;

  /* Cuenta el numero de ceros en cada individuo dado */
  int cerosIndividuo = 0;

  /* Auxiliar para contar los ceros de cada individuo y de las generaciones */
  char auxiliar = '0';

  /* Variables utilizadas para seleccionar los 6 elementos a cruazar de cada generacion */
  int seleccionados = 0;
  int iterador = 0;

  /* 6 elementos seleccionados para cruzar */
  int indicesAleatorios[6];

  /* 4 elementos que no se seleccionaron */
  int indicesNoAleatorios[4];

  /* Indices de la generacion elegidos para mutar */
  int indicesParaMutacion[2];

  /* Indice de la generacion elegido para mutar */
  int indiceParaMutacion;

  /* Rango de bits entre 10 y 40% para mutar en cada individuo */
  int numBits;

  /* Indice del bit elegido para mutar en el individuo indiceParaMutacion */
  int indiceBit;
  // ...
}
```

##### Estructura Principal del Programa
La estructura del programa es mas o menos la siguiente, el código principalmente se encuentra dentro de un bucle for, este se repetirá el numero de veces que de generaciones queramos, teniendo en cuenta que el programa terminará en caso de llegar a la condición de paro que es encontrar la generación que todos sus individuos tengan diez ceros. Dentro del bucle tenemos dos principales partes, la primera solo se ejecutará para la primera generación (k = 0), aquí crearemos los individuos de manera totalmente aleatoria, para las demás generaciones se explicará el procedimiento más adelante.
```cpp
int main() {
  // ...
  for (int k = 0; k < 100; k++) {
    if (k == 0) {
      // ...
    } else {
      // ...
    }
  }
  // ...
}
```
##### Generación 0
El procedimiento que se sigue para generar la primera generación es bastante sencillo, simplemente se ejecutan 10 veces la función de cadenaAleatoria y se va guardando en binarios1 y en su copia, de igual manera vamos guardando la cantidad de ceros de cada individuo con countOcurrences.
```cpp
int main() {
  // ...
  if (k == 0) {
    for (int i = 0; i < NUMERO_DE_CADENAS; i++) {
      cadenaAleatoria(destino, LONGITUD_DESEADA);
      binarios1[k][0] = destino;
      binariosCopy1[k][0] = destino;
      ceros[i] = countOcurrences(auxiliar, binarios1[k][0]);
    }
  }
  // ...
}
```
Al terminar este proceso que es solo para la primera generación el siguiente fragmento será ejecutado, lo que hacemos es: ordenar la generación por su cantidad de ceros de mayor a menor, mostrar la generación y un chequeo pequeño en caso de que llegue a la condición de paro.
```cpp
int main() {
  // ...
  if (k == 0) {
    // ...
  } else {

  }
  ordenarGeneracion(binarios1[k], binariosCopy1[k], ceros);
  mostrarGeneracion(binarios1[k]);
  suma = sumaCerosGeneracion(binarios1[k], 10, k);
  if (suma == 100) return 0;
  suma = 0;
}
```
##### Generación 1 en adelante

A continuación, mostraremos en secciones pequeñas de código el algoritmo que seguimos para una mayor comprensión, recordar que en esta sección todo lo que se muestra está dentro del else (generación 1 en adelante).
Elegimos y cruzamos 6 elementos al azar. 
Lo que se hace es seleccionar 6 elementos al azar, luego de esos 6 generamos sus hijos con los padres, estos mismos se comparan y nos quedamos con los individuos mejores (que tengan mayor cantidad de ceros), guardamos en la copia y vamos contando los ceros para luego ordenar.

```cpp
else {
  for (int i = 0; i < 6; i++) {
    int indiceAleatorio = obtenerIndiceRandom(indicesAleatorios, 10);
    indicesAleatorios[i] = indiceAleatorio;
  }

  /* Cruzamos los 6 elementos seleccionados */
  for (int i = 0; i < 6; i++) {
    string nuevaCadena = generarHijo(binarios1[k-1][indicesAleatorios[i]], binarios1[k-1][indicesAleatorios[6-i]]);
    if (copararHijoPadre(nuevaCadena, binarios1[k-1][indicesAleatorios[i]])) {
      binarios1[k][i] = nuevaCadena;
    } else {
      binarios1[k][i] = binarios1[k-1][indicesAleatorios[i]];
    }
    binariosCopy1[k][i] = binarios1[k][i];
    ceros[i] = countOccurrences(auxiliar, binarios1[k][i]);
  }
  seleccionados = 0;
  iterador = 0;

  /* Ingresar los 4 elementos que no se seleccionaron */
  for (int j = 0; j < 10; j++) {
    bool exists = existeEnArray(indicesAleatorios, 10, j);
    if (!exists) {
      indicesNoAleatorios[iterador] = j;
      iterador++;
      seleccionados++;
    }
  }
}
```
Pasar los 4 elementos no elegidos de la generación anterior a la nueva generación sin modificar
Aquí se hace algo similar al paso anterior pero no los cruzamos, simplemente agregamos los elementos que no se cruzaron en el paso anterior
```cpp
else {
  // ...
  seleccionados = 0;
  iterador = 0;

  for (int j = 0; j < 10; j++) {
    bool exists = existeEnArray(indicesAleatorios, 10, j);
    if (!exists) {
      indicesNoAleatorios[iterador] = j;
      iterador++;
      seleccionados++;
    }
  }

  for (int i = 6; i < 10; i++) {
    binarios1[k][i] = binarios1[k-1][indicesNoAleatorios[i-6]];
    binariosCopy1[k][i] = binarios1[k][i];
    ceros[i] = countOccurrences(auxiliar, binarios1[k][i]);
  }
}
```
Ordenar generación y contar cuantos elementos tenemos con 10 ceros previo a la mutación
Este proceso es muy importante para que la mutación sea efectiva y que no mutemos elementos que ya tienen 10 ceros
```cpp
else {
  // ...
  /* Ordenando */
  ordenarGeneracion(binarios1[k], binariosCopy1[k], ceros);

  /* Contamos cuantos individuos de la generacion tienen 10 ceros */
  individuosCeros = getIndividuosConDiezCeros(binarios1[k], 10);
}
```
Mutación parte 1 (seleccionar 2 elementos para mutarlos)
Nota Importante. Solo mutaremos si la generación tiene menos de 8 individuos con diez ceros. Una vez dicho esto, el procedimiento es seleccionar dos elementos de la generación anterior que no sean individuos con diez ceros, en caso de que tengamos menos de cinco elementos con diez ceros, seleccionaremos los dos de los últimos cinco

Mutación parte 2 (Mutar los elementos seleccionados)
Lo que se hace en esta parte es que una vez seleccionados dos individuos se seleccionarán para cada individuo entre un 10 y 40 porciento que serán los bits de cada individuo que se va a mutar, la mutación es simplemente si existe un 1 en la posición x del individuo i se cambiará por un 0 y viceversa.

```cpp
else {
  // ...
  /* Seleccionamos 2 elementos al azar de la generacion anterior de los ultimos 5 o que no tengan 10 ceros */
  if (individuosCeros < 8) {

    seleccionados = 0;
    iterador = 0;

    while(seleccionados < 2) {
          
      /* En caso de que ya existan mas de cinco individuos con 10 ceros */ 
      if (individuosCeros >= 5) {
        indiceParaMutacion = aleatorioEnRango(individuosCeros, 9);
      } 
      /* Caso contrario, se eligen dos de los ultimos cinco */
      else {
        indiceParaMutacion = aleatorioEnRango(5, 9);
      }
      /* Elegimos dos individuos al azar (no repetidos) */
      bool exists = existeEnArray(indicesParaMutacion, 2, indiceParaMutacion);
      if (!exists) {
        indicesParaMutacion[iterador] = indiceParaMutacion;
        iterador++;
        seleccionados++;
      }
    }

    /* Mutamos los 2 elementos seleccionados */
    for (int i = 0; i < 2; i++) {

      /* Seleccionamos un rango entre 10% y 40% (1 y 4) */
      numBits = aleatorioEnRango(1, 4);

      /* Seleccionamos un bit al azar numBits veces */
      for (int j = 0; j < numBits; j++) {
        indiceBit = aleatorioEnRango(0, 9);
            
        /* Si el bit es 0, lo cambiamos a 1 */
        if (binarios1[k][indicesParaMutacion[i]][indiceBit] == '0') {
          binarios1[k][indicesParaMutacion[i]][indiceBit] = '1';
          binariosCopy1[k][indicesParaMutacion[i]][indiceBit] = '1';
        } 
        /* Si el bit es 1, lo cambiamos a 0 */
        else {
          binarios1[k][indicesParaMutacion[i]][indiceBit] = '0';
          binariosCopy1[k][indicesParaMutacion[i]][indiceBit] = '0';
        }
      }
    }

    /* Contando los 0's de cada cadena */
    for (int i = 0; i < 10; i++) {
      ceros[i] = countOccurrences(auxiliar, binarios1[k][i]);
    }       
  }
}
```
Justo después de esto se sigue el mismo código que queda al final y que se ejecuta no importa que generación sea, lo mostraremos aquí de nuevo
