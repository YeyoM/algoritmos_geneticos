//WARNING: Este codigo funciona bien, pero da pena verlo, si estas leyendo esto
//sea quien seas ponte a ver como vergas hacerlo con recursividad
//por que si nos pide que llegue a una generacion donde sea puro 0 o puro 1
//no quiero estar haciendo 250 ciclos pendejadas asi
//librerias
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;
//funcion para saber cuantas veces se repite el 0
/**
 * "Count the number of times a character appears in a string."
 * 
 * The function takes two parameters: a character and a string. It returns the number of times the
 * character appears in the string
 * 
 * @param c The character to count occurrences of.
 * @param str The string to search in.
 * 
 * @return The number of times the character c appears in the string str.
 */
size_t countOccurrences(char c, string &str)
{
    size_t count = 0;

    for (char i : str)
        if (i == c)
            count++;

    return count;
}
/**
 * It returns a random integer in the range [minimo, maximo]
 * 
 * @param minimo The minimum number you want to generate.
 * @param maximo The maximum number you want to generate.
 * 
 * @return a random number between the minimum and maximum values.
 */
int aleatorio_en_rango(int minimo, int maximo) {
    return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}

/**
 * It takes a length and a destination string, and fills the destination string with random characters
 * from the sample string
 * 
 * @param longitud the length of the string to be generated
 * @param destino The string where the random string will be stored.
 */
int cadena_aleatoria(int longitud, char *destino) {
    char muestra[] = "01";
    for (int x = 0; x < longitud; x++) {
        int indiceAleatorio = aleatorio_en_rango(0, (int) strlen(muestra) - 1);
        destino[x] = muestra[indiceAleatorio];
    }
}

int main()
{
	cout<<"--------------------------"<<endl;
	cout<<"primera generacion"<<endl;
	cout<<"--------------------------"<<endl;
	/* Defining the length of the string to be generated. */
    #define LONGITUD_DESEADA 10
	char ch1='0';
/* Seeding the random number generator with the process ID of the program. */
    srand(getpid());
    //aqui mando llamar a la funcion para generar la cadena aleatoria
    //una por una por que no supe llamarlo en un ciclo
    char destino[LONGITUD_DESEADA + 1] = "";
    cadena_aleatoria(LONGITUD_DESEADA, destino);
    string binarios[100][100];
    binarios[1][1]=destino;
    
    char destino2[LONGITUD_DESEADA + 1] = "";
    cadena_aleatoria(LONGITUD_DESEADA, destino2);
    binarios[1][2]=destino2;
    
    char destino3[LONGITUD_DESEADA + 1] = "";
    cadena_aleatoria(LONGITUD_DESEADA, destino3);
    binarios[1][3]=destino3;
    
    char destino4[LONGITUD_DESEADA + 1] = "";
    cadena_aleatoria(LONGITUD_DESEADA, destino4);    
    binarios[1][4]=destino4;

    char destino5[LONGITUD_DESEADA + 1] = "";
    cadena_aleatoria(LONGITUD_DESEADA, destino5);
    binarios[1][5]=destino5;

    char destino6[LONGITUD_DESEADA + 1] = "";
    cadena_aleatoria(LONGITUD_DESEADA, destino6);
    binarios[1][6]=destino6;

    char destino7[LONGITUD_DESEADA + 1] = "";
    cadena_aleatoria(LONGITUD_DESEADA, destino7);
    binarios[1][7]=destino7;

    char destino8[LONGITUD_DESEADA + 1] = "";
    cadena_aleatoria(LONGITUD_DESEADA, destino8);
    binarios[1][8]=destino8;

    char destino9[LONGITUD_DESEADA + 1] = "";
    cadena_aleatoria(LONGITUD_DESEADA, destino9);
    binarios[1][9]=destino9;

    char destino10[LONGITUD_DESEADA + 1] = "";
    cadena_aleatoria(LONGITUD_DESEADA, destino10);
    binarios[1][10]=destino10;
    //aqui imprimo la primera generacion
    for(int i=1;i<=10;i++)
    {
        cout<<i<<":"<<binarios[1][i]<<":";
        //aqui cuento la cantidad de 0 que hay
        cout<<countOccurrences(ch1, binarios[1][i])<<endl;
    }
    cout<<"-------------------------"<<endl;
    cout<<"segunda generacion"<<endl;
    cout<<"-------------------------"<<endl;
    for(int i=1;i<11;i++)
    {
        //randomizo el punto donde se van a "fusionar" las cadenas
    	int num2 = 1 + rand() % (10 - 1);
        //junto ambas cadenas dependiendo del punto de fusion
        binarios[2][i]=binarios[1][i].substr(0,num2)+binarios[1][11-i].substr(num2,9);
        cout<<i<<":"<<binarios[2][i]<<":";
        //aqui sigo contando los 0
        cout<<countOccurrences(ch1, binarios[2][i])<<endl;
    }
	cout<<"--------------------------"<<endl;
	cout<<"tercera generacion"<<endl;
	cout<<"--------------------------"<<endl;
	for(int i=1;i<11;i++)
	{
        //comparo la cantidad de ocurrencias del 0 con ambas generaciones y se lo asigno a la siguiente
		if(countOccurrences(ch1, binarios[1][i])<countOccurrences(ch1, binarios[2][i]))
		{
			binarios[3][i]=binarios[2][i];
		}else{
			binarios[3][i]=binarios[1][i];
		}
		cout<<i<<":"<<binarios[3][i]<<":";
		cout<<countOccurrences(ch1, binarios[3][i])<<endl;
	}
	
//en general es repetir el proceso una y otra vez, reitero este codigo esta hecho con las patas
//hayq que hacer que sea recursivo y que no tenga tanta puta linea

	
	cout<<"-------------------------"<<endl;
    cout<<"cuarta generacion"<<endl;
    cout<<"-------------------------"<<endl;
    for(int i=1;i<11;i++)
    {
        //creo una nueva variable para que no se repita el numero
    	int num4 = 1 + rand() % (10 - 1);
        //y en general es lo mismo pero cambio el 4 por el 2
        binarios[4][i]=binarios[3][i].substr(0,num4)+binarios[3][11-i].substr(num4,9);
        cout<<i<<":"<<binarios[4][i]<<":";
        cout<<countOccurrences(ch1, binarios[4][i])<<endl;
    }
    	cout<<"--------------------------"<<endl;
	cout<<"quinta generacion"<<endl;
	cout<<"--------------------------"<<endl;
	for(int i=1;i<11;i++)
	{
		
		char ch1='0';
		if(countOccurrences(ch1, binarios[4][i])<countOccurrences(ch1, binarios[3][i]))
		{
			binarios[5][i]=binarios[3][i];
		}else{
			binarios[5][i]=binarios[4][i];
		}
		cout<<i<<":"<<binarios[5][i]<<":";
		cout<<countOccurrences(ch1, binarios[5][i])<<endl;
	}
	    cout<<"-------------------------"<<endl;
    cout<<"sexta generacion"<<endl;
    cout<<"-------------------------"<<endl;
    for(int i=1;i<11;i++)
    {
    	int num6 = 1 + rand() % (10 - 1);
        binarios[6][i]=binarios[5][i].substr(0,num6)+binarios[5][11-i].substr(num6,9);
        cout<<i<<":"<<binarios[6][i]<<":";
        cout<<countOccurrences(ch1, binarios[6][i])<<endl;
    }
	cout<<"--------------------------"<<endl;
	cout<<"septima generacion"<<endl;
	cout<<"--------------------------"<<endl;
	for(int i=1;i<11;i++)
	{
		
		if(countOccurrences(ch1, binarios[6][i])<countOccurrences(ch1, binarios[5][i]))
		{
			binarios[7][i]=binarios[5][i];
		}else{
			binarios[7][i]=binarios[6][i];
		}
		cout<<i<<":"<<binarios[7][i]<<":";
		cout<<countOccurrences(ch1, binarios[7][i])<<endl;
	}
	cout<<"-------------------------"<<endl;
    cout<<"octava generacion"<<endl;
    cout<<"-------------------------"<<endl;
    for(int i=1;i<11;i++)
    {
    	int num8 = 1 + rand() % (10 - 1);
        binarios[8][i]=binarios[7][i].substr(0,num8)+binarios[7][11-i].substr(num8,9);
        cout<<i<<":"<<binarios[8][i]<<":";
        cout<<countOccurrences(ch1, binarios[8][i])<<endl;
    }
	cout<<"--------------------------"<<endl;
	cout<<"noveno generacion"<<endl;
	cout<<"--------------------------"<<endl;
	for(int i=1;i<11;i++)
	{
		
		if(countOccurrences(ch1, binarios[8][i])<countOccurrences(ch1, binarios[7][i]))
		{
			binarios[9][i]=binarios[7][i];
		}else{
			binarios[9][i]=binarios[8][i];
		}
		cout<<i<<":"<<binarios[9][i]<<":";
		cout<<countOccurrences(ch1, binarios[9][i])<<endl;
	}
    //si quieren quiten esto, solamente era para ver si el algoritmo funcionaba
    //para ver si si estaba evolucionando
	cout<<"--------------------------"<<endl;
	cout<<"comparacion generacional"<<endl;
	cout<<"--------------------------"<<endl;
		int c1=0;
		int c2=0;
	for(int i=1;i<11;i++)
	{
		c1=c1+countOccurrences(ch1, binarios[1][i]);
		c2=c2+countOccurrences(ch1, binarios[9][i]);
	}
	cout<<"ceros gen1:"<<c1<<endl;
	cout<<"ceros gen2:"<<c2<<endl;
		
}
