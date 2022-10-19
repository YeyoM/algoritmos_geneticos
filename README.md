<h1 align="center">Algoritmos Genéticos</h1>

#### Inteligencia Artificial
#### Ingeniería en Computación Inteligente UAA

#### Integrantes:
- Dante Alejandro Alegría Romero
- Diego Alberto Aranda
- Andrea Margarita Balandran Felix
- María Yoselin García Medina
- Diego Emilio Moreno Sánchez

Fecha de entrega: 18 de octubre de 2022
*Profesor: Dr. Alejandro Padilla Diaz*

#### Definición del proyecto de un Algoritmo Genético Simple
##### Breve introducción a los algoritmos genéticos
Empecemos por definir lo que es un algoritmo, un algoritmo es una serie de pasos organizados que describe el proceso que se debe seguir, para dar solución a un problema específico. 
Los AGs fueron delineados por un par de científicos norteamericanos, John Holland [1929–] en los años 1970 y presentados en 1989 por David Goldberg [1953–] como un método de optimización de búsqueda global, debido a que este tipo de métodos explora todo el espacio de soluciones del problema permitiendo salir de posibles óptimos locales e ir en busca de óptimos globales. 
Los algoritmos genéticos son llamados así porque se inspiran en la evolución biológica y su base genético-molecular. 
En general, los algoritmos genéticos (AGs) son parte de la llamada inteligencia artificial; es decir, la resolución de problemas mediante el uso de programas de computación que imitan el funcionamiento de la inteligencia natural. 
Un AG consiste en los siguientes pasos. Inicialización: se genera aleatoriamente una población inicial constituida por posibles soluciones del problema, también llamados individuos. Evaluación: aplicación de la función de evaluación a cada uno de los individuos. Evolución: aplicación de operadores genéticos (como son selección, reproducción y mutación). Y término: el AG deberá detenerse cuando se alcance la solución óptima, pero ésta generalmente se desconoce, por lo que se utilizan varios criterios de detención. 
Ahora que ya conocemos lo que es un algoritmo genético podemos comenzar a hablar de los posibles pasos a seguir para recrear a nuestro estilo un algoritmo de este estilo. Cabe recalcar que los códigos que se muestran a continuación se basan en una serie de pasos y estrategias propuestas por nuestro profesor el doctor Alejandro Padilla Diaz, pero los códigos son totalmente de nuestra autoría.
##### ¿Qué casos del algoritmo genético usaste para garantizar la evolución de todos los individuos con el proyecto?
A continuación, dividiremos el contenido por versiones de nuestro código, ya que en cada nueva versión añadimos procesos diferentes para analizar la forma en el que las generaciones evolucionaban
###### Versión 1
Para todos los códigos la generación de la primera generación será por medio del siguiente fragmento del código. En el siguiente código se puede analizar como se crea la cadena con la función cadenaAleatoria y se guarda en una variable auxiliar y esta se guarda en la generación k en el individuo i y se hace la cuenta de los ceros de dicho individuo.
```cpp
for (int i = 1; i <= 10; i++) {
  cadenaAleatoria(LONGITUD_DESEADA, destino);
  binarios[k][i] = destino;
  binariosCopy[k][i] = binarios[k][i];
  ceros[i] = countOccurrences(auxiliar, binarios[k][i]);
}
```
El primer paso en la exploración de los algoritmos genéticos para nosotros fue el proceso conocido como cruzamiento. En pocas palabras, el cruzamiento no es más que la mezcla de dos cadenas padres generando dos nuevo individuos hijos que pasan a la siguiente generación, por convención en un inicio se hace el cruzamiento en 50% del padre 1 y 50% del padre 2 para generar así dos nuevos hijos, de esta forma conseguimos, aunque de manera muy lenta una evolución entre generaciones. Para este caso decidimos ir un poco más lejos tomando ese 50-50 con valores totalmente aleatorios que su suma del 100% (70 y 30 o 60 y 40 por ejemplo).
El pseudocódigo de esta primera versión se ve de la siguiente manera.
```cpp
FOR generacion en bits1
  IF generacion = 1
    crearGeneracion
  ELSE
    cruzarElementos
  END IF
END FOR
```
La parte fundamental de esta primera versión es aprender cómo funciona el cruzamiento y analizar de que forma las generaciones evolucionan con cada iteración que hace nuestro código. A continuación, se encuentra el fragmento de código que en cada iteración se encarga de cruzar todos los elementos.
```cpp
for (int i = 1; i <= 10; i++) {
  int num2 = 1 + rand() % (10 - 1);
  binarios[k][i] = binarios[k-1][i].substr(0, num2) + binarios[k[11-i].substr(num2, 9);
  binariosCopy[k][i] = binarios[k][i];
  ceros[i] = countOccurrences(auxiliar, binarios[k][i]);
}
```
###### Versión 2
La siguiente propuesta por parte de nuestro profesor fue integrar a cada iteración un método para ordenar cada generación de mayor a menor numero de ceros de cada individuo. De esta forma los mejores se cruzarían con los peores dando como resultado mejores hijos cada vez, y la verdad que el cambio se notó mucho. La meta hasta el momento era encontrar un individuo que tuviera 10 ceros.  De esta forma el ordenamiento de la generación se logra con el siguiente fragmento de código.
```cpp
for (int i = 0; i < 10; i++) {
  int max_ceros = largestAmountCeros(ceros, 10);
  int index = 0;
  for (int j = 0; j < 10; j++) {
    if (ceros[j] == max_ceros) {
      index = j;
      break;
    }
  }
  binarios2[k][i] = binariosCopy2[k][index];
  ceros[index] = -1;
}
```
Prácticamente es el único cambio con respecto al primer código. Solo que esta vez el tope máximo de generaciones era de 250 generaciones, por lo que tuvimos que modificar un poco en esta versión para conseguir esas 250 posibles generaciones.
###### Versión 3
Para esta nueva versión del código lo que se implementó fue una manera diferente para cruzar los individuos de la generación, ahora cruzaremos 6 elementos de la generación elegidos de manera aleatoria y los 4 restantes pasarlos sin ningún cambio y al final ordenarlos como lo hicimos desde la versión 2. Hasta este punto si vimos mejoras, pero para llevarlo al siguiente nivel el equipo llegó a la conclusión que nos teníamos que quedar con el mejor elemento siempre, independientemente si era el padre o el hijo, de esta forma vimos un considerable salto en la evolución de nuestro algoritmo. 
```cpp
for (int i = 0; i < 6; i++) {
  int indiceAleatorio = obtenerIndiceRandom(indicesAleatorios, 10);
  indicesAleatorios[i] = indiceAleatorio;
}

for (int i = 0; i < 6; i++) {
  string nuevaCadena = generarHijo(binarios1[k-1][indicesAleator[i]], binarios1[k-1][indicesAleatorios[6-i]]);
  if (copararHijoPadre(nuevaCadena, binarios1[k-1][indicesAleator[i]])) {
    binarios1[k][i] = nuevaCadena;
  } else {
    binarios1[k][i] = binarios1[k-1][indicesAleatorios[i]];
  }
  binariosCopy1[k][i] = binarios1[k][i];
  ceros[i] = countOccurrences(auxiliar, binarios1[k][i]);
}
```
###### Versión 4
La última versión de nuestro código ingresaba un nuevo concepto que fue el detonante para mejorar por completo nuestro código y que la evolución para llegar a esa nueva meta de diez individuos con diez ceros se volviera realista. 
Este nuevo concepto es la mutación, la mutación se encargaría de dar ese último toque a esas generaciones donde teníamos 8 o 9 individuos con 10 ceros y el ultimo tuviera solo 9, como se puede analizar es el último paso. 
La mutación para nuestro código y en este contexto de algoritmos genéticos se refiere a tomar alguna cadena y cambiar algunos ceros por unos o viceversa, pero de manera aleatoria. En comparación a la versión anterior prácticamente lo único que se agregó fue la mutación. 
Nota Importante. Solo mutaremos si la generación tiene menos de 8 individuos con diez ceros. Una vez dicho esto, el procedimiento es seleccionar dos elementos de la generación anterior que no sean individuos con diez ceros, en caso de que tengamos menos de cinco elementos con diez ceros, seleccionaremos los dos de los últimos cinco.
El código por lo tanto queda de la siguiente manera.
```cpp
if (individuosCeros < 8) {
  seleccionados = 0;
  iterador = 0;
  while(seleccionados < 2) {
    if (individuosCeros >= 5) {
      indiceParaMutacion = aleatorioEnRango(individuosCeros, 9);
    } 
    else {
      indiceParaMutacion = aleatorioEnRango(5, 9);
    }
    bool exists = existeEnArray(indicesParaMutacion, indiceParaMutacion);
    if (!exists) {
      indicesParaMutacion[iterador] = indiceParaMutacion;
      iterador++;
      seleccionados++;
    }
  }
  for (int i = 0; i < 2; i++) {
    numBits = aleatorioEnRango(1, 4);
    for (int j = 0; j < numBits; j++) {
      indiceBit = aleatorioEnRango(0, 9);
      if (binarios1[k][indicesParaMutacion[i]][indiceBit] == '0') {
        binarios1[k][indicesParaMutacion[i]][indiceBit] = '1';
        binariosCopy1[k][indicesParaMutacion[i]][indiceBit] = '1';
      } 
      else {
        binarios1[k][indicesParaMutacion[i]][indiceBit] = '0';
        binariosCopy1[k][indicesParaMutacion[i]][indiceBit] = '0';
      }
    }
  }
  for (int i = 0; i < 10; i++) {
    ceros[i] = countOccurrences(auxiliar, binarios1[k][i]);
  }       
}
```
##### ¿Por qué se detecta precisamente un problema si no se ordena o no se genera una evolución en los individuos, y que sucede con el problema por resolver o mejorar con el cruzamiento, ordenamiento de los mejores y la mutación ?, ¿cuál es la justificación?
Sin duda alguna todos estos procesos son importantes para el funcionamiento óptimo de nuestra última versión del código. 
El cruzamiento con la selección del individuo con el mayor número de ceros nos asegura que siempre que juntemos dos individuos el resultante será mejor que el anterior en todos los casos. El ordenamiento es una parte fundamental de igual manera, nos permite tener un mayor orden y control sobre las generaciones y al momento de mutar en cada generación, nos aseguramos de que nunca mutaremos algún elemento que ya tenga el número deseado de ceros.
Por ultimo la mutación era la pieza faltante del rompecabezas en el que prácticamente ya estaba todo resuelto, pero había generaciones en las que simplemente hacía falta un pequeño empujón para lograr el objetivo de la generación con diez individuos con diez ceros cada uno. La mutación ayudó muchísimo en esos momentos y a acelerar los procesos anteriores, los resultados que se muestran en el siguiente apartado justifican estas palabras, la diferencia y el cambio que se genera es increíble.
#### Desarrollo del informe de casos
##### Análisis Algoritmo Evolutivo con Cruzamiento y Algoritmo Evolutivo con Mutación
Durante la elaboración del algoritmo evolutivo, dividimos el algoritmo en dos fases, una donde empleamos el cruzamiento de las generaciones para después solo obtener las que sean mejores y con el apoyo de una función de ordenamiento para volver a cruzar y así hasta que el algoritmo logre encontrar la generación con más ceros, por otro lado, la segunda fase fue agregar a todo esto la función de mutación con la utilidad de mejorar el algoritmo y facilitar la obtención de la mejor generación.
Para esta comparación realizamos una pequeña prueba en ambos códigos con la finalidad de obtener la mayor cantidad de resultados posibles. En la primera fase presentamos un pequeño problema, por más que lo intentamos es muy poco probable que a lo largo de la ejecución se llegara a encontrar una generación con todos los individuos de 10 ceros, es debido a esto que los datos que recolectamos fueron la cantidad de ceros en totalidad, cada una de estas ejecuciones llegaron hasta el límite prestablecido pero aun con todo esto se puede notar que estuvieron lo más cerca de tener a cada uno de sus individuos con los 10 ceros, fueron pocas las que estuvieron a solo un cero de poder lograrlo pero eso dice que como tal si se aumentara nuestro límite de 250 se podría encontrar la mejor generación. Con este análisis se puede demostrar que en este algoritmo se puede conseguir generaciones casi perfectas que estén cerca de los 95 ceros como se muestra su pico más alto, pero también muestra la falta de una función que nos ayude a solucionar el problema de obtener la generación de 100 ceros, siendo esta la función de mutación.
[![graficaCruzamiento][graficaCruzamiento]](#)
Una de las principales observaciones que podemos ver en el algoritmo anterior es en la función de cruzamiento, al depender de números aleatorios puede que estos puedan llegar a repetirse para la siguiente generación y una vez seleccionando a los mejores volvamos a obtener la misma cantidad de ceros que la generación anterior o todo lo contrario y obtengamos una leve mejoría, pero aun así se ha demostrado que esta parte necesita de la mutación para corregir este problema.
Una vez que se implementa la función para la mutación en el algoritmo, se puede mostrar un gran cambio con respecto a la versión anterior, la más visible es el hecho que en ningún momento llego a obtener los resultados en el límite de 250 o en todo caso no llego a faltar más ciclos para encontrar la generación de los 10 ceros. En esta ocasión debido a la implementación de la mutación se puede obtener resultados por debajo de la mitad del límite de 250 generaciones, en consecuencia, de esto el algoritmo puede encontrar más rápido la generación con 10 ceros, analizando la gráfica, se puede ver como la mayoría de los resultados se encuentran acumulados cerca de su pico más alto que es la generación 50, demostrando la eficiencia del algoritmo.
[![graficaMutacion][graficaMutacion]](#)
Anteriormente se mostró que sin la implementación de una función de mutación el algoritmo no era capaz de encontrar la generación con un total de 100 ceros y este requiere una mayor cantidad de ciclos para que existiera la probabilidad de encontrarla, pero una vez que recurrimos al método de la mutación el tiempo y las generaciones se acortaron por dejo de la mitad del límite que establecimos con tal eficiencia el programa no requería de tantos ciclos siendo en muy pocos casos que este llegara a generaciones mayores o iguales a 100, pero también se muestra existe la posibilidad de conseguir resultados en generaciones menores a 20, esto demuestra que si bien lo anterior dicho sobre la eficiencia del algoritmo es buena aún queda cosas para mejorar esta y que sea posible que se puedan obtener resultados por debajo del promedio 51.437 obtenido de esta prueba.
El funcionamiento de las funciones de cruzamiento y mutación son complementarias para este algoritmo, sin una de estas el algoritmo sería capaz de solo presentarnos resultados muy lejos de los necesitados. Por parte del cruzamiento, este selecciona a una cantidad de individuos de una manera aleatoria para que sean partidos en partes y se terminen cruzando el primero con el ultimo y así con cada uno, y así tener como resultado a los que llamaremos hijos que una vez realizando un comparación estos formaran parte de la siguiente generación pero antes de esto son seleccionados los dos menor cantidad de ceros para que muten y puedan ser la diferencia para las siguientes generaciones y así hasta obtener al primer individuo que tenga los 10 ceros y con el conseguir más rápido la mejor generación en la menor cantidad de ciclos.
#### Resolución, lecciones y recomendaciones
##### Análisis de las sentencias obtenidas ¿Qué estrategias usaron para forzar la obtención o mejora de los 10 individuos y por qué?
###### Primera versión
Nuestro primer código lo tomamos como nuestro primer acercamiento a los algoritmos evolutivos. Nos sirvió para el establecimiento de funciones que seguimos usando hasta el algoritmo donde ya se produce una mutación. Y también para comenzar a generar la lógica que seguiremos siguiendo en nuestros demás algoritmos. Como algoritmo evolutivo jamás va a obtener el resultado esperado. Que es la producción de una generación donde sus individuos sean en su totalidad 0, esto debido a la falta de ordenamiento y evolución de estos, y solo integrar un método de cruzamiento y comparación.
Métodos implementados en esta versión del algoritmo: Cruzamiento y comparación
El método de cruzamiento nos sirve para producir generaciones nuevas en base a una generación anterior, esperando obtener individuos con mayor número de 0´s.
El método de comparación nos ayuda a identificar si hubo un punto de mejora entre los hijos y su generación padre. Para poder considerar si un individuo es mejor que su predecesor y saber cuál elegir para la siguiente generación.
- El promedio de 0’s en la generación final es de 62.532
- Su moda es de 63
- Y su mediana es de 62.1646
- Veces encontrando el objetivo: jamás encontrado
###### Segunda versión
Este algoritmo a comparación del otro fue hecho con previos aprendizajes obtenidos del código anteriormente establecido, ahora corriéndolo hasta las 250 generaciones o cuando el programa encuentre a su primer individuo con 0´s en su totalidad.
En busca de mejores resultados a la hora de la evolución generacional, implementamos el método de ordenamiento para poner en las primeras posiciones a los individuos con mayor cantidad de ceros, cruzarlos con los individuos con la menor cantidad y obtener un resultado favorable para los que estén más bajo en la tabla y que la generación crezca conjuntamente
Métodos implementados en esta versión del algoritmo: Ordenamiento
El método de ordenamientos nos ayuda a el crecimiento en conjunto de la generación cruzando a los individuos con mayor cantidad con los de menor, aumentando así los valores más bajos y cada vez realizar los cruzamientos con individuos con mayor número de 0´s
###### Tercera versión
Esta es una evolución de nuestro algoritmo pasado donde ya habíamos implementado el método de ordenación para las generaciones, en busca de obtención de mejores resultados. En este nuevo utilizamos un método donde seleccionábamos seis integrantes y los cruzábamos entre ellos, para después compararlo con cada par de padres y cada par de hijos, después comparar para elegir a los dos mejores y devolverlos a la posición que tenían los padres de ese cruzamiento.
Métodos implementados en este algoritmo: Cruzamiento entre seis valores aleatorios.
Este método nos sirve para a base de la creación de una generación “intermedia” podamos tener otra opción a la hora de la selección y conservar al mejor prospecto
- Su promedio de 0’s en la generación final es de 91.839
- Su moda es de 95
- Su mediana es de 94
- Veces que se encontró el objetivo: Ninguna (Se quedó muy cerca)
###### Cuarta versión
La versión final de nuestro trabajo, donde después de analizar los datos anteriormente obtenidos se puede notar que no siempre encontraba una generación con todos los individuos enteramente de 0´s. Por lo que implementamos el método de mutación, que consiste en intercambiar el valor que tiende del 10% al 40% de 2 de los 5 individuos que están al final de nuestra generación, es decir tengan la menor cantidad de 0´s. Esto para después volver a ordenar y comparar con la generación anterior.
Métodos implementados en este algoritmo: Mutación de bits
Este método es una operación cuyo objetivo es generar nueva información dentro de la población para obtener una mejor exploración del espacio de búsqueda. En este algoritmo siempre se llegó a generación esperada.
##### ¿Qué pudo haber funcionado mejor y por qué?
Tal vez aplicando la mutación en vez de hacerla tomando 2 de los últimos cinco valores, ir descartando aquellos individuos que ya sean totalmente 0´s, y aplicar la mutación solamente a aquellos que aún no cumplen el objetivo.
Esto debido a que dejaríamos de mutar aquellos que no necesitan ser mutados nuevamente.
Otra idea podría ser el generar primeramente la cadena aleatoria, después de eso hacer el mismo proceso de ordenamiento, cruzar, pero solamente los primeros 5 valores de arriba, comparar después esos hijos con los últimos 5 valores de la generación, en caso de ser mejores intercambiarlos y seguir con el mismo proceso. Nos gustaría creer que el cruce de solamente las mejores generaciones podría lograr un objetivo más optimo en menor cantidad de generaciones.
##### Recomendaciones y lecciones
###### ¿Cuáles recomendaciones pueden realizarse en este proyecto?
Ir implementando las mejoras de una por una, ya sea para observar si existe margen de mejora, en caso de que no exista buscar el error y el por qué está ocurriendo ese problema, así cuando queramos implementar otro método sepamos que el anterior es funcional, ya que puede ocurrir que debido a implementar todo desde el inicio, puede fallar y desconocer en que parte del algoritmo está el error.
Correr el algoritmo muchas veces, para poder medir de una mejor manera su eficiencia. Ya que su primera generación se genera de manera aleatoria un resultado no define si nuestro código funciona de una manera adecuada.
###### ¿Qué lecciones se aprendieron en este proyecto?
Gracias a la elaboración de algoritmos evolutivos podemos utilizarlos para solucionar problemas que tengan que estar relacionados con la optimización o la búsqueda de soluciones rápidas.
La mutación es un concepto sumamente importante en los códigos que de ahora de adelante se debe considerar implementar. Existen casos donde por más que queramos no podremos resolverlos, hasta que implementemos una función, es un concepto muy profundo y con mucho aprendizaje por tomar, gran acercamiento a este tema.
##### Referencias
- Algoritmos genéticos. (2018, 21 septiembre). Conogasi. Recuperado 10 de octubre de 2022, de https://conogasi.org/articulos/algoritmos-geneticos/
- Mallawaarachchi, V. (2020, 1 marzo). Introduction to Genetic Algorithms — Including Example Code. Medium. Recuperado 18 de octubre de 2022, de https://towardsdatascience.com/introduction-to-genetic-algorithms-including-example-code-e396e98d8bf3
- Just a moment. . . (s. f.). Recuperado 18 de octubre de 2022, de https://www.sciencedirect.com/topics/engineering/genetic-algorithm


<!-- MARKDOWN LINKS & IMAGES -->
[graficaCruzamiento]: public/graficaCruzamiento.png
[graficaMutacion]: public/graficaMutacion.png