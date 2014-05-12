#include <stdlib.h>

int ***alocaHsvMatriz(int largura, int altura){
	int ***matriz = malloc(largura * sizeof(int **));

	for(int y = 0; y < altura; y++){
		matriz[y] = malloc(largura * sizeof(int *));

		for(int x = 0; x < largura; x++)
			matriz[y][x] = malloc(3 * sizeof(int));
	}

	return matriz;
}

void liberaHsvMatriz(int ***hsvMatriz, int largura, int altura){
	for(int y = 0; y < altura; y++){
		for(int x = 0; x < largura; x++)
			free(hsvMatriz[y][x]);

		free(hsvMatriz[y]);
	}

	free(hsvMatriz);
}