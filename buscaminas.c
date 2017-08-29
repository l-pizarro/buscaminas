#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Entrada: - Un puntero a un arreglo bidimensional y su cantidad de filas.
//          - Una lista que contiene las informacion a escribir.
// Salida:  - No posee
// Descipcion: La funcion eliminar_matriz libera la memoria que utiliza una
//             arreglo bidimiencional de n filas, mediante la función free().
void eliminar_matriz(int **matriz, int filas) {
	int i;
	for (i=0; i<filas; i++) {
		free(matriz[i]);
	}
	free(matriz);
}

// Entrada: - Dos números enteros (filas y columnas).
// Salida:  - Un puntero a puntero de entero (arreglo bidimensional)
// Descipcion: La funcion generar_matriz solicita la memoria que utilizará un
//             arreglo bidimiencional de n filas y m columnas mediante la función
//             malloc() y le asigna el valor cero a cada elemento del arreglo.
int** generar_matriz(int filas, int columnas) {

	int **matriz = (int **)malloc(filas * sizeof(int *));
	int i,j;
	for (i=0; i<filas; i++) {
		matriz[i] = (int *)malloc(columnas * sizeof(int));
		for (j=0; j<columnas; j++) {
			matriz[i][j] = 0;
		}
	}
	return matriz;
}

// Entrada: - Dos números enteros (filas y columnas).
// Salida:  - Un puntero a puntero de char (arreglo bidimensional)
// Descipcion: La funcion generar_tablero solicita la memoria que utilizará un
//             arreglo bidimiencional de n filas y m columnas mediante la función
//             malloc() y le asigna el caracter # a cada elemento del arreglo.
char** generar_tablero(int filas, int columnas) {
	char **tablero = (char **)malloc(filas * sizeof(char *));
	int i,j;
	for (i=0; i<filas; i++) {
		tablero[i] = (char *)malloc(columnas * sizeof(char));
		for (j=0; j<columnas; j++) {
			tablero[i][j] = '#';
		}
	}
	return tablero;
}

// Entrada: - Un puntero a puntero de entero y tres números enteros.
// Salida:  - Un numero entero que simula un valor booleano.
// Descipcion: La funcion existe_en recorre un arreglo bidimensional utilizando un ciclo
//             for (ya que solo se utilizará para matrices de nx2) para comprobar si algun
//             elemento concuerda con los numeros enteros recibidos como parametro.
//             De ocurrir lo anterior, la función retorna 1, emulando un booleano verdadero,
//             de lo contario retorn 0.
int existe_en(int **arr, int fila, int columna, int size){
    int i;
    for (i=0; i < size; i++) {
			if (arr[i][0] == fila && arr[i][1] == columna)
				return 1;
    }
    return 0;
}

// Entrada: - Un puntero doble a entero, tres numeros enteros y un puntero a entero (arreglo unidimensional).
// Salida:  - No posee retorno
// Descipcion: La funcion generar_bombas genera una fila y columna aleatoria, la cual es validada
//             para ubicar una mina en la matriz (representada por un -1), lo anterior continúa hasta
//             que todas las minas han sido ubicadas, finalmente se libera la memoria que se utilizó para
//             almacenar las casillas en las que ya se había posicionado una mina.
void generar_bombas(int **matriz, int cantidad_minas, int filas, int columnas, int *primera_casilla) {

	int fila_aleatoria, colu_aleatoria;
	srand(time(NULL));

	int **minas = (int **)malloc(cantidad_minas * sizeof(int*));
	int i;
	for(i=0; i<cantidad_minas; i++) {
		minas[i] = (int *)malloc(2 * sizeof(int));
	}

	int contador = 0;

	while (cantidad_minas > contador) {
		fila_aleatoria = rand() % filas;
		colu_aleatoria = rand() % columnas;
		if (!existe_en(minas, fila_aleatoria, colu_aleatoria ,contador)) {

			if (((fila_aleatoria > (primera_casilla[0]+1)) || (fila_aleatoria < (primera_casilla[0]-1))) || ((colu_aleatoria > (primera_casilla[1]+1)) || (colu_aleatoria < (primera_casilla[1]-1)))){

				minas[contador][0] = fila_aleatoria;
				minas[contador][1] = colu_aleatoria;
				matriz[fila_aleatoria][colu_aleatoria] = 1;
				contador ++;

			}
		}
	}
	eliminar_matriz(minas, cantidad_minas);
}

// Entrada: - Un puntero doble a caracter, tres numeros enteros y un puntero a entero (arreglo unidimensional).
// Salida:  - No posee retorno
// Descipcion: La funcion generar_bombas genera una fila y columna aleatoria, la cual es validada
//             para ubicar una mina en la matriz (representada por un -1), lo anterior continúa hasta
//             que todas las minas han sido ubicadas, finalmente se libera la memoria que se utilizó para
//             almacenar las casillas en las que ya se había posicionado una mina.
void mostrar_tablero(char **tablero_usuario, int filas, int columnas) {
	int i, j, k;
    
	printf("\n");
    printf(" ");
    for (i=0; i<columnas; i++) {
        printf("%4d", i);
    }
    printf("\n\n");
    
	for (j =0; j<filas; j++) {
		printf("%i ", j);
		for(k=0; k<columnas; k++) {
			printf("%3c ", tablero_usuario[j][k]);
		}
		printf("\n\n");
	}
	printf("\n\n");
}

// Entrada: - Dos punteros dobles a entero y dos números enteros.
// Salida:  - No posee retorno
// Descipcion: La funcion generar_adyacentes recorre una matriz con las minas posicionadas y
//             verifica para cada casilla que no sea una mina si en las casillas adyacentes hay alguna
//             si esto sucede el numero entero de la segunda matriz ingresada aumenta en 1.
//             En caso de que la posicion corresponda a una mina el valor en la segunda matriz se reemplaza
//             por un -1.
void generar_adyacentes(int **matriz, int **adyacentes, int filas, int columnas) {

	int i,j;
	for(i =0; i<filas; i++) {
		for(j=0; j<columnas; j++) {

			if(matriz[i][j] == 1) {
				adyacentes[i][j] = -1;
				continue;
			}
			// Norte
			if (i>0 && matriz[i-1][j] == 1)
				adyacentes[i][j] = adyacentes[i][j] + 1;
			// Noroeste
			if (i>0 && j>0 && matriz[i-1][j-1] == 1)
				adyacentes[i][j] = adyacentes[i][j] + 1;
			// Noreste
			if (i>0 && j<columnas-1 && matriz[i-1][j+1] == 1)
				adyacentes[i][j] = adyacentes[i][j] + 1;
			// Sur
			if (i<filas-1 && matriz[i+1][j] == 1)
				adyacentes[i][j] = adyacentes[i][j] + 1;
			// Suroeste
			if (i<filas-1 && j>0 && matriz[i+1][j-1] == 1)
				adyacentes[i][j] = adyacentes[i][j] + 1;
			// Sureste
			if (i<filas-1 &&j<columnas-1 && matriz[i+1][j+1] == 1)
				adyacentes[i][j] = adyacentes[i][j] + 1;
			// Oeste
			if (j>0 && matriz[i][j-1] == 1)
				adyacentes[i][j] = adyacentes[i][j] + 1;
			// Este
			if (j<columnas-1 && matriz[i][j+1] == 1)
				adyacentes[i][j] = adyacentes[i][j] + 1;
		}
	}
}

// Entrada: - Un punteros doble a caracter, un puntero doble a entero y dos numeros enteros.
// Salida:  - No posee retorno
// Descipcion: La funcion mostrar_minas recorre la matriz que almacena la cantidad de minas adyacentes
//             imprimiendo el caracter @ en cada una de las posiciones en que había una mina. El resto
//             es reemplazado por un espacio vacío o un numero entero para revelar finalmente todo el
//             tablero al usuario.
//             Esta función solo se utiliza en caso de que el usuario haya perdido.
void mostrar_minas(char **tablero_usuario, int **adyacentes, int filas, int columnas) {
	int i,j;
	printf("\n");
	printf("    0   1   2   3   4\n\n");
	for (i =0; i<filas; i++) {
		printf("%i ", i);
		for (j=0; j<columnas; j++) {
			if (adyacentes[i][j] == -1) {
				printf("  @");
			}
			else if (adyacentes[i][j] == -9) {
				printf("   ");
			}

			else {
				printf("%3d ", adyacentes[i][j]);
			}
		}
		printf("\n\n");
	}
	printf("\n\n");
}

// Entrada: - Una matriz de enteros, una matriz de caracteres y cuatro numeros enteros.
// Salida:  - No posee retorno
// Descipcion: La función descubrir se encarga de realizar cambios en el tablero que es visible al usuario
//             de tal manera que cuando este descubra una casilla vacía se produzca una ramificación dando
//             a conocer todas las casillas adyacentes que también se encuentran vacías.
//
//             Esta función posee cuatro posibilidades:
//
//             1. Que la casilla ingresada en los parametros (i,j) esté fuera de la matriz y por ende
//                retorna un 0;
//             2. Que la casilla ingresada corresponda a una casilla ya revisada anteriormente por la
//                funcion (representado por -9), de ser así retorn un 0;
//             3. La es adyacente a una mina y por lo tanto desde la posicion actual no se debe seguir
//                 descubiriendo. Retorna 0
//             4. Por descarte la casilla corresponde a un espacio vacío y se debe descubrir en 4 direcciones:
//                Norte, Sur, Este y Oeste; retornadas consecutivamente.
int descubrir(int i, int j, int filas, int columnas, char** tablero_usuario, int **adyacentes) {

	if (i>filas-1 || i<0 || j>columnas-1 || j<0)
		return 0;

	if (adyacentes[i][j] == -9)
		return 0;

	if (adyacentes[i][j] > 0) {
		tablero_usuario[i][j] = (char)adyacentes[i][j] + '0';
		return 0;
	}

	adyacentes[i][j] = -9;
	tablero_usuario[i][j] = '~';

	return (
	descubrir(i-1,j,filas,columnas,tablero_usuario,adyacentes) +
	descubrir(i+1,j,filas,columnas,tablero_usuario,adyacentes) +
	descubrir(i,j-1,filas,columnas,tablero_usuario,adyacentes) +
	descubrir(i,j+1,filas,columnas,tablero_usuario,adyacentes));
}

// Entrada: - Una matriz de caracteres y dos numeros enteros (filas y columnas).
// Salida:  - Un numero entero.
// Descipcion: La funcion contar_minas_escondidas recorre el tablero del usuario
//             contando la cantidad de casillas ocultas (representadas por el caracter #)
//             para finalmente retorna es cantidad.
int contar_minas_escondidas(char **tablero_usuario, int filas, int columnas) {
	int i, j, sum;
	sum =0;
	for (i =0; i<filas; i++) {
		for (j=0; j<columnas; j++) {
			if (tablero_usuario[i][j] == '#') {
				sum ++;
			}
		}
	}
	return sum;
}

// Entrada: - Una matriz de enteros y dos numeros enteros (filas y columnas).
// Salida:  - No posee retorno.
// Descipcion: La funcion escribir archivo recorre la matriz con los valores de adyacencia
//             y escribe en el archivo de salida las pistas del juego.
//
//             Pista mina          = fila + espacio + columnas + espacio + "X\n"
//             Pista casilla vacía = fila + espacio + columnas + espacio + "O\n"
void escribir_archivo(int **adyacentes, int filas, int columnas) {
	int i,j;
	FILE *archivo;

	archivo = fopen("solución.out", "w");
	if (archivo == NULL) {
		printf("EL archivo no se pudo abrir\n");
		exit(1);
	}

	for (i=0; i<filas; i++) {
		for (j=0; j<columnas; j++) {
			if (adyacentes[i][j] == -1){
				fprintf(archivo, "%i %i X\n",i,j);
			}
			else {
				fprintf(archivo, "%i %i O\n", i, j);
			}
		}
	}
	fclose(archivo);
}

// Entrada: - No posee parametros de entrada.
// Salida:  - No posee retorno.
// Descipcion: La funcion jugar regula las llamadas a las funciones dependiendo de la etapa
//             en la que se encuentra el videojuego. Partiendo por pedir la cantidad de filas,
//             columnas y minas. Luego genera los dos tableros necesarios y solicita la primera jugada.
//             Una vez que esta es una jugada de "descubrir" se generar las minas del tablero y pasa
//             a pedir las siguientes jugadas, mostrando el tablero cada vez que sea necesario, hasta
//             que se llegue a un resultado final (ganar o perder).
void jugar() {
    
	int filas, columnas, cantidad_minas;
	char tipo_jugada;
	int *casilla = (int *)malloc(2 * sizeof(int));
    printf("\n       -- Buscaminas --\n");
	printf("\nIngrese cantidad de filas y columnas: ");
	scanf("%i %i", &filas, &columnas);
	printf("Ingrese cantidad de minas: ");
	scanf("%i", &cantidad_minas);
    
    while (cantidad_minas > ((filas*columnas)-10)) {
        printf("Ingrese cantidad de minas menor !!: ");
        scanf("%i", &cantidad_minas);
    }
	int **matriz = generar_matriz(filas, columnas);
	char** tablero_usuario = generar_tablero(filas, columnas);
    printf("\nEl tablero\n");
	mostrar_tablero(tablero_usuario, filas, columnas);

	printf("Ingrese su jugada: ");
	scanf("%i %i %c", &casilla[0], &casilla[1], &tipo_jugada);

	while(tipo_jugada == 'X') {
		tablero_usuario[casilla[0]][casilla[1]] = '!';
		mostrar_tablero(tablero_usuario, filas, columnas);
		printf("Ingrese su jugada: ");
		scanf("%i %i %c", &casilla[0], &casilla[1], &tipo_jugada);
	}
    
	generar_bombas(matriz, cantidad_minas, filas, columnas, casilla);

	int **adyacentes = generar_matriz(filas, columnas);
	generar_adyacentes(matriz, adyacentes, filas, columnas);
	adyacentes[casilla[0]][casilla[1]] = 0;
	escribir_archivo(adyacentes, filas, columnas);
	eliminar_matriz(matriz, filas);

	descubrir(casilla[0], casilla[1], filas, columnas, tablero_usuario, adyacentes);
	mostrar_tablero(tablero_usuario, filas, columnas);

	int continuar_jugando = 1;
	while (continuar_jugando) {
		printf("Ingrese su jugada: ");
		scanf("%i %i %c", &casilla[0], &casilla[1], &tipo_jugada);
        
        while ((casilla[0] > filas) || (casilla[1] > columnas)){
            printf("Ingrese una jugada valida!!: ");
            scanf("%i %i %c", &casilla[0], &casilla[1], &tipo_jugada);
        }

		if (!(tablero_usuario[casilla[0]][casilla[1]] == '#' || tablero_usuario[casilla[0]][casilla[1]] == '!')) {
			printf("No puedes acceder a una casilla ya revelada\n");
		}
		else {
			if (tipo_jugada == 'O') {
				if (adyacentes[casilla[0]][casilla[1]] == -1) {
					mostrar_minas(tablero_usuario, adyacentes, filas, columnas);
					printf("Perdiste!\n");
					continuar_jugando = 0;
				}
				else if (adyacentes[casilla[0]][casilla[1]] == 0) {
					descubrir(casilla[0], casilla[1], filas, columnas, tablero_usuario, adyacentes);
					mostrar_tablero(tablero_usuario, filas, columnas);
				}
				else {
					tablero_usuario[casilla[0]][casilla[1]] = (char)adyacentes[casilla[0]][casilla[1]] + '0';
					if (contar_minas_escondidas(tablero_usuario, filas, columnas) == cantidad_minas) {
						mostrar_tablero(tablero_usuario, filas, columnas);
						printf("Ganaste!\n");
						getchar();
						continuar_jugando = 0;
					}
                    else {
                        mostrar_tablero(tablero_usuario, filas, columnas);
                    }
				}
			}
			else if (tipo_jugada == 'X') {
				tablero_usuario[casilla[0]][casilla[1]] = '!';
				mostrar_tablero(tablero_usuario, filas, columnas);
			}
		}
	}
	getchar();
	eliminar_matriz(adyacentes, filas);
	free(casilla);
}

int main() {
	jugar();
	return 0;
}
