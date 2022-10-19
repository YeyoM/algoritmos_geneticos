/**
 * Algoritmo de cruzamiento de bits
 * 
 * Inteligencia Artificial UAA
 * 
 * Autores:
 * - Dante Alejandro alegría Romero      
 * - Diego Alberto Aranda                        
 * - Andrea Margarita Balandran Felix  
 * - María Yoselin García Medina                
 * - Moreno Sánchez Diego Emilio @YeyoM        
 * 
 * Fecha: 26/09/2022
 * 
 * Descripción:
 * 
*/

// Librerias
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <iterator>
#include <cstring>
using namespace std;

/**
 * Función para contar el número de veces que aparece un caracter en una cadena
 * @param c Caracter a contar
 * @param str Cadena a buscar
 * @return El número de veces que aparece el caracter c en la cadena str
*/
size_t countOccurrences(char c, string &str) {
  size_t count = 0;
  for (char i : str) {
    if (i == c) {
      count++;
    }
  }
  return count;
}

/**
 * Función para generar un número aleatorio entre un rango
 * @param minimo El número mínimo que se desea generar
 * @param maximo El número máximo que se desea generar
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
int largestAmountCeros(int arr[], int n) {
  int i;
  int max = arr[0];
  for (i = 0; i < n; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}

int main() {

  /* Definiendo la longitud de la cadena a generar. */
  #define LONGITUD_DESEADA 10
  /* Definiendo el número de individuos a generar. */
  #define NUMERO_DE_CADENAS 250

  /* Inicializando el generador de números aleatorios con el ID del proceso del programa. */
  srand(getpid());

  char auxiliar = '0';

  /* Definiendo el arreglo de cadenas. */
  string binarios1[(NUMERO_DE_CADENAS / 2) + 1][(NUMERO_DE_CADENAS / 2) + 1];
  /* Definiendo el arreglo de cadenas. */
  string binarios2[(NUMERO_DE_CADENAS / 2) + 1][(NUMERO_DE_CADENAS / 2) + 1];

  /* Definiendo el arreglo de cadenas. (copia) */
  string binariosCopy1[(NUMERO_DE_CADENAS / 2) + 1][(NUMERO_DE_CADENAS / 2) + 1];
  string binariosCopy2[(NUMERO_DE_CADENAS / 2) + 1][(NUMERO_DE_CADENAS / 2) + 1];

  /* Definiendo el arreglo de chars para cuando generamos las cadenas */
  char destino[LONGITUD_DESEADA + 1] = "";

  /* Definiendo el arreglo de números para guardar el número de ceros en cada cadena. */
  int ceros[LONGITUD_DESEADA + 1];

  // main loop 1
  for (int k = 0; k < NUMERO_DE_CADENAS / 2; k++) {

    cout << "--------------------------" << endl;
	  cout << "Generacion " << k + 1 << endl;
	  cout << "--------------------------" << endl;

    /* Generando las cadenas aleatorias. (solo en generacion 1)*/
    if (k == 0) {
      // Generamos los 10 primeros individuos (generacion 1)
      for (int i = 0; i < 10; i++) {
        // Creamos la cadena aleatoria
        cadenaAleatoria(LONGITUD_DESEADA, destino);
        // Guardamos la cadena en el arreglo
        binarios1[k][i] = destino;
        // Guardamos la cadena en el arreglo de copias
        binariosCopy1[k][i] = binarios1[k][i];
        // Contamos el numero de 0's en la cadena
        ceros[i] = countOccurrences(auxiliar, binarios1[k][i]);
      }
    } else {
      // Seleccionamos 6 elementos al azar de la generacion anterior y los 4
      int indicesAleatorios[6];
      int seleccionados = 0;
      int iterador = 0;

      while (seleccionados < 6) {
        int indiceAleatorio = aleatorioEnRango(0, 9);
        bool exists = std::find(std::begin(indicesAleatorios), std::end(indicesAleatorios), indiceAleatorio) != std::end(indicesAleatorios);
        if (!exists) {
          indicesAleatorios[iterador] = indiceAleatorio;
          iterador++;
          seleccionados++;
        }
      }
      
      for (int i = 0; i < 6; i++) {
        int num2 = 1 + rand() % (10 - 1);
        binarios1[k][i] = binarios1[k-1][indicesAleatorios[i]].substr(0, num2) + binarios1[k-1][indicesAleatorios[6-i]].substr(num2, 9);
        binariosCopy1[k][i] = binarios1[k][i];
        ceros[i] = countOccurrences(auxiliar, binarios1[k][i]);
      }

      int indicesNoAleatorios[4];
      int noSeleccionados = 0;
      int iterador2 = 0;
      // Ingresar los 4 elementos que no se seleccionaron
      for (int j = 0; j < 10; j++) {
        bool exists = std::find(std::begin(indicesAleatorios), std::end(indicesAleatorios), j) != std::end(indicesAleatorios);
        if (!exists) {
          indicesNoAleatorios[iterador2] = j;
          iterador2++;
          noSeleccionados++;
        }
      }

      for (int i = 6; i < 10; i++) {
        binarios1[k][i] = binarios1[k-1][indicesNoAleatorios[i-6]];
        binariosCopy1[k][i] = binarios1[k][i];
        ceros[i] = countOccurrences(auxiliar, binarios1[k][i]);
      }

    }

    // Ordenando
    for (int i = 0; i < 10; i++) {
      // Obtenemos la cadena con mas 0's
      int max_ceros = largestAmountCeros(ceros, 10);
      // Obtenemos el indice de la cadena con mas 0's
      int index = 0;
      for (int j = 0; j < 10; j++) {
        if (ceros[j] == max_ceros) {
          index = j;
          break;
        }
      }
      // Guardamos la cadena con mas 0's en el arreglo original
      // usando el indice de la cadena con mas 0's y el arreglo de copias
      binarios1[k][i] = binariosCopy1[k][index];
      ceros[index] = -1;
    }

    // Imprimimos la generacion
    for (int i = 0; i < 10; i++) {
      cout << i + 1 << ":" << binarios1[k][i] << ":";
      //aqui cuento la cantidad de 0 que hay
      cout << countOccurrences(auxiliar, binarios1[k][i]) << endl;
    }

    // Si algun integrante de la generacion llega 10 ceros se detiene el programa
    for (int i = 0; i < 10; i++) {
      if (countOccurrences(auxiliar, binarios1[k][i]) == LONGITUD_DESEADA) {
        cout << "Se encontro la cadena con 10 ceros en la generacion " << k + 1 << endl;
        return 0;
      }
    }

    // Imprimimos la suma de los 0's de la generacion
    int suma = 0;
    for (int i = 0; i < 10; i++) {
      suma += countOccurrences(auxiliar, binarios1[k][i]);
    }
    cout << "Suma de 0's: " << suma << endl;
  }

  // main loop 2
  for (int k = 0; k < NUMERO_DE_CADENAS / 2; k++) {

    cout << "--------------------------" << endl;
	  cout << "Generacion " << NUMERO_DE_CADENAS / 2 + k + 1 << endl;
	  cout << "--------------------------" << endl;

    if (k == 0) {
      // Seleccionamos 6 elementos al azar de la generacion anterior y los 4
      int indicesAleatorios[6];
      int seleccionados = 0;
      int iterador = 0;

      while (seleccionados < 6) {
        int indiceAleatorio = aleatorioEnRango(0, 9);
        bool exists = std::find(std::begin(indicesAleatorios), std::end(indicesAleatorios), indiceAleatorio) != std::end(indicesAleatorios);
        if (!exists) {
          indicesAleatorios[iterador] = indiceAleatorio;
          iterador++;
          seleccionados++;
        }
      }
      
      for (int i = 0; i < 6; i++) {
        int num2 = 1 + rand() % (10 - 1);
        binarios2[k][i] = binarios1[NUMERO_DE_CADENAS / 2 - 1][indicesAleatorios[i]].substr(0, num2) + binarios1[NUMERO_DE_CADENAS / 2 - 1][indicesAleatorios[5-i]].substr(num2, 9);
        binariosCopy2[k][i] = binarios2[k][i];
        ceros[i] = countOccurrences(auxiliar, binarios2[k][i]);
      }

      int indicesNoAleatorios[4];
      int noSeleccionados = 0;
      int iterador2 = 0;
      // Ingresar los 4 elementos que no se seleccionaron
      for (int j = 0; j < 10; j++) {
        bool exists = std::find(std::begin(indicesAleatorios), std::end(indicesAleatorios), j) != std::end(indicesAleatorios);
        if (!exists) {
          indicesNoAleatorios[iterador2] = j;
          iterador2++;
          noSeleccionados++;
        }
      }

      for (int i = 6; i < 10; i++) {
        binarios2[k][i] = binarios1[NUMERO_DE_CADENAS / 2 - 1][indicesNoAleatorios[i-6]];
        binariosCopy2[k][i] = binarios2[k][i];
        ceros[i] = countOccurrences(auxiliar, binarios2[k][i]);
      }

    } else {
      // Seleccionamos 6 elementos al azar de la generacion anterior y los 4
      int indicesAleatorios[6];
      int seleccionados = 0;
      int iterador = 0;

      while (seleccionados < 6) {
        int indiceAleatorio = aleatorioEnRango(0, 9);
        bool exists = std::find(std::begin(indicesAleatorios), std::end(indicesAleatorios), indiceAleatorio) != std::end(indicesAleatorios);
        if (!exists) {
          indicesAleatorios[iterador] = indiceAleatorio;
          iterador++;
          seleccionados++;
        }
      }
      
      for (int i = 0; i < 6; i++) {
        int num2 = 1 + rand() % (10 - 1);
        binarios2[k][i] = binarios2[k-1][indicesAleatorios[i]].substr(0, num2) + binarios2[k-1][indicesAleatorios[5-i]].substr(num2, 9);
        binariosCopy2[k][i] = binarios2[k][i];
        ceros[i] = countOccurrences(auxiliar, binarios2[k][i]);
      }

      int indicesNoAleatorios[4];
      int noSeleccionados = 0;
      int iterador2 = 0;
      // Ingresar los 4 elementos que no se seleccionaron
      for (int j = 0; j < 10; j++) {
        bool exists = std::find(std::begin(indicesAleatorios), std::end(indicesAleatorios), j) != std::end(indicesAleatorios);
        if (!exists) {
          indicesNoAleatorios[iterador2] = j;
          iterador2++;
          noSeleccionados++;
        }
      }

      for (int i = 6; i < 10; i++) {
        binarios2[k][i] = binarios2[k-1][indicesNoAleatorios[i-6]];
        binariosCopy2[k][i] = binarios2[k][i];
        ceros[i] = countOccurrences(auxiliar, binarios2[k][i]);
      }

    }

    // Ordenando
    for (int i = 0; i < 10; i++) {
      // Obtenemos la cadena con mas 0's
      int max_ceros = largestAmountCeros(ceros, 10);
      // Obtenemos el indice de la cadena con mas 0's
      int index = 0;
      for (int j = 0; j < 10; j++) {
        if (ceros[j] == max_ceros) {
          index = j;
          break;
        }
      }
      // Guardamos la cadena con mas 0's en el arreglo original
      // usando el indice de la cadena con mas 0's y el arreglo de copias
      binarios2[k][i] = binariosCopy2[k][index];
      ceros[index] = -1;
    }

    // Imprimimos la generacion
    for (int i = 0; i < 10; i++) {
      cout << i + 1 << ":" << binarios2[k][i] << ":";
      //aqui cuento la cantidad de 0 que hay
      cout << countOccurrences(auxiliar, binarios2[k][i]) << endl;
    }

    // Si algun integrante de la generacion llega 10 ceros se detiene el programa
    for (int i = 0; i < 10; i++) {
      if (countOccurrences(auxiliar, binarios2[k][i]) == LONGITUD_DESEADA) {
        cout << "Se encontro la cadena con 10 ceros en la generacion " << k + 1 << endl;
        return 0;
      }
    }

    // Imprimimos la suma de los 0's de la generacion
    int suma = 0;
    for (int i = 0; i < 10; i++) {
      suma += countOccurrences(auxiliar, binarios2[k][i]);
    }
    cout << "Suma de 0's: " << suma << endl;
  }
		
  return 0;

}
