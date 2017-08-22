#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int eliminar_matriz(int **matriz, int filas) {
	int i;
	for (i=0; i<filas; i++) {
		free(matriz[i]);
	}
	free(matriz);
	return 0;
}
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
char** generar_tablero(int filas, int columnas) {
	char **matriz = (char **)malloc(filas * sizeof(char *));
	int i,j;
	for (i=0; i<filas; i++) {
		matriz[i] = (char *)malloc(columnas * sizeof(char));
		for (j=0; j<columnas; j++) {
			matriz[i][j] = '#';
		}
	}
	return matriz;
}
int existe_en(int **arr, int fila, int columna, int size){
    int i;
    for (i=0; i < size; i++) {
			if (arr[i][0] == fila && arr[i][1] == columna)
				return 1;
    }
    return 0;
}
int generar_bombas(int **matriz, int cantidad_minas, int filas, int columnas, int *primera_casilla) {

	int fila_aleatoria, colu_aleatoria;
	srand(time(NULL));

	int **minas = (int **)malloc(cantidad_minas * sizeof(int*));
	int i;
	for(i=0; i<cantidad_minas; i++) {
		minas[i] = (int *)malloc(2 * sizeof(int));
	}

	int contador = 0;

	// LAS BOMBAS NO QUEDAN ADYACENTES A LA PRIMERA JUGADA

	while (cantidad_minas > contador) {
		fila_aleatoria = rand() % filas;
		colu_aleatoria = rand() % columnas;
		if (!existe_en(minas, fila_aleatoria, colu_aleatoria ,contador)) {

			// Validar que la fila y la columna sean adyacentes al mismo tiempo
			if (((fila_aleatoria > (primera_casilla[0]+1)) || (fila_aleatoria < (primera_casilla[0]-1))) || ((colu_aleatoria > (primera_casilla[1]+1)) || (colu_aleatoria < (primera_casilla[1]-1)))){

				minas[contador][0] = fila_aleatoria;
				minas[contador][1] = colu_aleatoria;
				matriz[fila_aleatoria][colu_aleatoria] = 1;
				contador ++;

			}
		}
	}
	eliminar_matriz(minas, cantidad_minas);
	return 0;
}
int mostrar_tablero(char **tablero_usuario, int filas, int columnas) {
	int i,j;
	printf("\n");
	printf("    0   1   2   3   4\n\n");
	for(i =0; i<filas; i++) {
		printf("%i ", i);
		for(j=0; j<columnas; j++) {
			printf("%3c ", tablero_usuario[i][j]);
		}
		printf("\n\n");
	}
	printf("\n\n");
	return 0;
}
int generar_adyacentes(int **matriz, int **adyacentes, int filas, int columnas) {

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
	return 0;
}
int mostrar_bombas(char **tablero_usuario, int **adyacentes, int filas, int columnas) {
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
	return 0;
}
int descubrir(int i, int j, int filas, int columnas, char** tablero_usuario, int **adyacentes) {

	// Validar entrada, sino retornar
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
int jugar() {
	int filas, columnas, cantidad_minas;
	char tipo_jugada;
	int *casilla = (int *)malloc(2 * sizeof(int));
	//Solicitar datos tablero
	printf("Ingrese cantidad de filas y columnas: ");
	scanf("%i %i", &filas, &columnas);
	printf("Ingrese cantidad de minas: ");
	scanf("%i", &cantidad_minas);
	int **matriz = generar_matriz(filas, columnas);
	char** tablero_usuario = generar_tablero(filas, columnas);
	mostrar_tablero(tablero_usuario, filas, columnas);

	// Primera jugada
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
	eliminar_matriz(matriz, filas);

	descubrir(casilla[0], casilla[1], filas, columnas, tablero_usuario, adyacentes);
	mostrar_tablero(tablero_usuario, filas, columnas);
	printf("Comienza el juego...\n");
	getchar();

	int continuar_jugando = 1;
	while (continuar_jugando) {
		printf("Ingrese su jugada: ");
		scanf("%i %i %c", &casilla[0], &casilla[1], &tipo_jugada);

		if (!(tablero_usuario[casilla[0]][casilla[1]] == '#' || tablero_usuario[casilla[0]][casilla[1]] == '!')) {
			printf("No puedes acceder a una casilla ya revelada\n");
		}
		else {
			if (tipo_jugada == 'O') {
				if (adyacentes[casilla[0]][casilla[1]] == -1) {
					mostrar_bombas(tablero_usuario, adyacentes, filas, columnas);
					printf("Perdiste!\n");
					continuar_jugando = 0;
				}
				else if (adyacentes[casilla[0]][casilla[1]] == 0) {
					descubrir(casilla[0], casilla[1], filas, columnas, tablero_usuario, adyacentes);
					mostrar_tablero(tablero_usuario, filas, columnas);
				}
				else {
					tablero_usuario[casilla[0]][casilla[1]] = (char)adyacentes[casilla[0]][casilla[1]] + '0';
					if(contar_minas_escondidas(tablero_usuario, filas, columnas) == cantidad_minas) {
						mostrar_tablero(tablero_usuario, filas, columnas);
						printf("Ganaste!\n");
						getchar();
						continuar_jugando = 0;
					}
					mostrar_tablero(tablero_usuario, filas, columnas);
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
	return 0;
}
int main() {
	jugar();
	return 0;
}
