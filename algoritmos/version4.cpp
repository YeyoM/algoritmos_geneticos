/**
 * Algoritmo de mutacion de bits
 * 
 * Inteligencia Artificial UAA
 * 
 * Autores:
 * - Dante Alejandro alegría Romero      
 * - Diego Alberto Aranda                        
 * - Andrea Margarita Balandran Felix  
 * - María Yoselin García Medina                
 * - Moreno Sánchez Diego Emilio        
 * 
 * Fecha: 10/10/2022
 * 
*/

// Librerias
#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <iterator>
#include <cstring>
using namespace std;

///////////////////////////////////////////////////////////////////// FUNCIONES

/**
 * Función para contar el número de veces que aparece un caracter en una cadena
 * @param c Caracter a contar
 * @param str Cadena a buscar
 * @return El número de veces que aparece el caracter c en la cadena str
*/
int countOccurrences(char c, string &str) {
  int count = 0;
  for (char i : str) {
    if (i == c) {
      count++;
    }
  }
  return count;
}

/**
 * Función para generar un número aleatorio entre un rango
 * @param minimo Limite mínimo que se desea generar
 * @param maximo Limite máximo que se desea generar
*/
int aleatorioEnRango(int minimo, int maximo) {
  return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}

/**
 * Función para generar una cadena aleatoria
 * @param longitud La longitud de la cadena a generar
 * @param destino La cadena donde se almacenará la cadena aleatoria
*/
int cadenaAleatoria(int longitud, char *destino) {
  char muestra[] = "01";
  for (int x = 0; x < longitud; x++) {
    int indiceAleatorio = aleatorioEnRango(0, (int) strlen(muestra) - 1);
    destino[x] = muestra[indiceAleatorio];
  }
}

/**
 * Función para obtener el número mayor de ceros en un arreglo
 * @param arr El arreglo de números
 * @param n El número de elementos en el arreglo
 * @return El número mayor de ceros en el arreglo
*/
int maxCeros(int arr[], int n) {
  int i;
  int max = arr[0];
  for (i = 0; i < n; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}

/**
 * Retorna true si el número x está en el arreglo arr, y false en caso contrario
 * 
 * @param arr El arreglo en el que se buscará
 * @param n el número de elementos en el arreglo
 * @param x el número a buscar
 * 
 * @return A boolean value.
 */
bool existeEnArray(int arr[], int n, int x) {
  for (int i = 0; i < n; i++) {
    if (arr[i] == x) {
      return true;
    }
  }
  return false;
}

/**
 * Retorna un índice aleatorio de un arreglo
 * 
 * @param arr El arreglo en el que se buscará si el índice existe
 * @param n El número de elementos en el arreglo
 * 
 * @return El índice del arreglo que no está aun seleccionado
 */
int obtenerIndiceRandom(int arr[], int n) {
  int index = aleatorioEnRango(0, n - 1);
  while (existeEnArray(arr, n, index)) {
    index = aleatorioEnRango(0, n - 1);
  }
  return index;
}

/**
 * Tomando dos cadenas, devuelve una nueva cadena que es una combinación de las dos
 * 
 * @param padre1
 * @param padre2 
 * 
 * @return El hijo de los dos padres
 */
string generarHijo(string &padre1, string &padre2) {
  int index = aleatorioEnRango(0, padre1.length() - 1);
  string hijo = padre1.substr(0, index) + padre2.substr(index, 9);
  return hijo;
}

/**
 * Retorna true si el hijo tiene más ceros que el padre
 * 
 * @param hijo
 * @param padre 
 * 
 * @return true si el hijo tiene más ceros que el padre
 */
bool copararHijoPadre(string &hijo, string &padre) {
  int cerosHijo = countOccurrences('0', hijo);
  int cerosPadre = countOccurrences('0', padre);
  return cerosHijo > cerosPadre;
}

/**
 * Hace el conteo de individuos con 10 ceros en la generacion
 * 
 * @param individuos generacion
 * @param n individuos en la generacion (10)
 * 
 * @return Numero de individuos con 10 ceros
 */
int getIndividuosConDiezCeros(string individuos[], int n) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (countOccurrences('0', individuos[i]) == 10) {
      count++;
    }
  }
  return count;
}

/**
 * Tomando un arreglo de cadenas y un entero como parámetros, imprime las cadenas en el arreglo,
 * junto con el número de ceros en cada cadena
 * 
 * @param individuos (generacion)
 * @param n numero de individuos en la generacion (10)
 * @param k numero de la generacion
 */
void mostrarGeneracion(string individuos[], int n, int k) {
  int cerosPorIndividuo = 0;
  cout << "--------------------------" << endl;
	cout << "Generacion " << k + 1 << endl;
	cout << "--------------------------" << endl;
  for (int i = 0; i < n; i++) {
    cout << i + 1 << ":" << individuos[i] << ":";
    cerosPorIndividuo = countOccurrences('0', individuos[i]);
    cout << cerosPorIndividuo << endl;
  }
}

/**
 * Funcion que cuenta el numero de ceros en la poblacion y retorna la suma
 * 
 * @param individuos (generacion)
 * @param n numero de individuos en la generacion (10)
 * @param k numero de la generacion
 * 
 * @return El total de ceros en la generacion
 */
int sumaCerosGeneracion(string individuos[], int n, int k) {
  int suma = 0;
  for (int i = 0; i < n; i++) {
    suma += countOccurrences('0', individuos[i]);
  }
  if (suma == 100) {
    cout << "Se encontro la solucion en la generacion " << k + 1 << endl;
  }
  return suma;
}

/**
 * Tomando un arreglo de cadenas, un arreglo de cadenas(copia del primero) y 
 * un arreglo de enteros como parámetros, ordena el primer arreglo de cadenas 
 * basado en los enteros en el tercer arreglo
 * 
 * @param generacion Generacion que se ordenara
 * @param generacionCopia Generacion copia para ordenar la generacion original
 * @param ceros Array de enteros que contiene el numero de ceros de cada individuo
 */
void ordenarGeneracion(string generacion[10], string generacionCopia[10], int ceros[11]) {
  for (int i = 0; i < 10; i++) {
    int max_ceros = maxCeros(ceros, 10);
    int index = 0;
    for (int j = 0; j < 10; j++) {
      if (ceros[j] == max_ceros) {
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

///////////////////////////////////////////////////////////////////// VARAIBLES GLOBALES
/* Definiendo la longitud de la cadena a generar. */
#define LONGITUD_DESEADA 10

/* Definiendo el número maximo de generaciones. */
#define NUMERO_DE_CADENAS 125

/* Definiendo el arreglo de cadenas. */
string binarios1[NUMERO_DE_CADENAS][NUMERO_DE_CADENAS];

/* Definiendo el arreglo de cadenas. (copia) */
string binariosCopy1[NUMERO_DE_CADENAS][NUMERO_DE_CADENAS];

///////////////////////////////////////////////////////////////////// MAIN
int main() {

  srand(time(NULL));
  srand(getpid());

  ///////////////////////////////////////////////////////////////////// VARAIBLES LOCALES
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
  int indicesAleatorios[7];

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

  ///////////////////////////////////////////////////////////////////// LOOP PRINCIPAL
  for (int k = 0; k < NUMERO_DE_CADENAS; k++) {

    /* Generando las cadenas aleatorias. (solo en generacion 1) */
    if (k == 0) {
      for (int i = 0; i < 10; i++) {
        cadenaAleatoria(LONGITUD_DESEADA, destino); // Se guarda en destino
        binarios1[k][i] = destino;
        binariosCopy1[k][i] = binarios1[k][i];
        ceros[i] = countOccurrences(auxiliar, binarios1[k][i]);
      }
    } else {

      /* Seleccionamos 6 elementos al azar de la generacion anterior */
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

      /* Ingresamos los 4 elementos restantes */
      for (int i = 6; i < 10; i++) {
        binarios1[k][i] = binarios1[k-1][indicesNoAleatorios[i-6]];
        binariosCopy1[k][i] = binarios1[k][i];
        ceros[i] = countOccurrences(auxiliar, binarios1[k][i]);
      }

      /* Ordenando */
      ordenarGeneracion(binarios1[k], binariosCopy1[k], ceros);

      /* Contamos cuantos individuos de la generacion tienen 10 ceros */
      individuosCeros = getIndividuosConDiezCeros(binarios1[k], 10);

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

    /* Ordenando */
    ordenarGeneracion(binarios1[k], binariosCopy1[k], ceros); 

    /* Imprimiendo la generacion */
    mostrarGeneracion(binarios1[k], 10, k);

    /* Obtenemos la suma total de ceros en la generacion */
    suma = sumaCerosGeneracion(binarios1[k], 10, k);

    /* En caso de que suma es igual a 100, se termina el programa */
    if (suma == 100) return 0;
    
    suma = 0;

  }

  return 0;
}
