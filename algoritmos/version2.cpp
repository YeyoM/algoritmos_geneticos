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
  for (i = 1; i < n; i++) {
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
  #define NUMERO_DE_CADENAS 99

  /* Inicializando el generador de números aleatorios con el ID del proceso del programa. */
  srand(getpid());

  char auxiliar = '0';

  /* Definiendo el arreglo de cadenas. */
  string binarios[100][100];
  /* Definiendo el arreglo de cadenas. (copia) */
  string binariosCopy[100][100];
  /* Definiendo el arreglo de chars para cuando generamos las cadenas */
  char destino[LONGITUD_DESEADA + 1] = "";

  /* Definiendo el arreglo de números para guardar el número de ceros en cada cadena. */
  int ceros[11];

  // main loop
  for (int k = 1; k <= NUMERO_DE_CADENAS; k++) {

    cout << "--------------------------" << endl;
	  cout << "Generacion " << k << endl;
	  cout << "--------------------------" << endl;

    /* Generando las cadenas aleatorias. (solo en generacion 1)*/
    if (k == 1) {
      // Generamos los 10 primeros individuos (generacion 1)
      for (int i = 1; i <= 10; i++) {
        // Creamos la cadena aleatoria
        cadenaAleatoria(LONGITUD_DESEADA, destino);
        // Guardamos la cadena en el arreglo
        binarios[k][i] = destino;
        // Guardamos la cadena en el arreglo de copias
        binariosCopy[k][i] = binarios[k][i];
        // Contamos el numero de 0's en la cadena
        ceros[i] = countOccurrences(auxiliar, binarios[k][i]);
      }
    } else {
      for (int i = 1; i <= 10; i++) {
    	  int num2 = 1 + rand() % (10 - 1);
        //junto ambas cadenas dependiendo del punto de fusion
        binarios[k][i] = binarios[k-1][i].substr(0, num2) + binarios[k-1][11-i].substr(num2, 9);
        // Guardamos la cadena en el arreglo de copias
        binariosCopy[k][i] = binarios[k][i];
        // ir guardando el numero de 0's en el array
        ceros[i] = countOccurrences(auxiliar, binarios[k][i]);
      }
    }

    // Ordenando
    for (int i = 1; i <= 10; i++) {
      // Obtenemos la cadena con mas 0's
      int max_ceros = largestAmountCeros(ceros, 11);
      // Obtenemos el indice de la cadena con mas 0's
      int index = 0;
      for (int j = 1; j <= 10; j++) {
        if (ceros[j] == max_ceros) {
          index = j;
          break;
        }
      }
      // Guardamos la cadena con mas 0's en el arreglo original
      // usando el indice de la cadena con mas 0's y el arreglo de copias
      binarios[k][i] = binariosCopy[k][index];
      ceros[index] = -1;
    }

    // Imprimimos la generacion
    for (int i = 1; i <= 10; i++) {
      cout << i << ":" << binarios[k][i] << ":";
      //aqui cuento la cantidad de 0 que hay
      cout << countOccurrences(auxiliar, binarios[k][i]) << endl;
    }

    // Imprimimos la suma de los 0's de la generacion
    int suma = 0;
    for (int i = 1; i <= 10; i++) {
      suma += countOccurrences(auxiliar, binarios[k][i]);
    }
    cout << "Suma de 0's: " << suma << endl;
  }
		
  return 0;

}
