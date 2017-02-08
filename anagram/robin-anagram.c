#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

char **safeCallocChar(int size) {
	char **ptr = calloc(size, sizeof(char*));
	if (ptr == NULL) {
		printf("\nError: memory allocation failed....abort\n");
		exit(-1);
	}
	for(int i=0; i<size; i++) {
		ptr[i] = calloc(100, sizeof(char));
			if (ptr[i] == NULL) {
				printf("\nError: memory allocation failed....abort\n");
				exit(-1);
			}
	}
	return ptr;
}

int **safeCallocInt(int size) {
	int **ptr = calloc(size, sizeof(int*));
	if (ptr == NULL) {
		printf("\nError: memory allocation failed....abort\n");
		exit(-1);
	}
	for(int i=0; i<size; i++) {
		ptr[i] = calloc(27, sizeof(int));
			if (ptr[i] == NULL) {
				printf("\nError: memory allocation failed....abort\n");
				exit(-1);
			}
	}
	return ptr;
}

void readInput(int size, char **array) {
	for(int i = 0; i < size; i++) {
		scanf("%[^.]%*c", array[i]);
	}
}

void makeHisto(char **string, int size, int **histo) {
	int place;

	for(int i = 0; i < size; i++) {
		for(int j = 0; string[i][j] != 0; j++) {
			if(isalpha(string[i][j])) {
				place = string[i][j] - 'a';
				histo[i][place]++;
				histo[i][26]++;
			} else {
				continue;
			}
		}
	}
}

int isEqual(int *array1, int *array2, int size){
	for(int i = 0; i < size; i++) {
		if (array1[i] == array2[i]) {
			continue;
		} else {
			return FALSE;
		}
	}
	return TRUE;
}

void free2DArrayChar(char **array, int size) {
	for(int i = 0; i < size; i++) {
		free(array[i]);
	}
	free(array);
}

void free2DArrayInt(int **array, int size) {
	for(int i = 0; i < size; i++) {
		free(array[i]);
	}
	free(array);
}

int main(int argc, char *argv[]) {
	int sizeOne = 0;
	int sizeTwo = 0;
	
	scanf("%d", &sizeOne);
	char** str1 = safeCallocChar(sizeOne);
	int** histo1 = safeCallocInt(sizeOne);
	readInput(sizeOne, str1);

	scanf("%d", &sizeTwo);
	char** str2 = safeCallocChar(sizeTwo);
	int** histo2 = safeCallocInt(sizeTwo);
	readInput(sizeTwo, str2);
	
	makeHisto(str1, sizeOne, histo1);
	makeHisto(str2, sizeTwo, histo2);
	
	for(int j = 0; j < sizeTwo; j++) {
//		printf("%d: ", j+1);
		for(int i = 0; i < sizeOne; i++) {
			if (histo1[i][26] == histo2[j][26]) {
				if (isEqual(histo1[i], histo2[j], 26)) {
					printf("%d ", i+1);
				}
			} else {
				continue;
			}
		}
		printf("\n");
	}

	free2DArrayChar(str1, sizeOne);
	free2DArrayChar(str2, sizeTwo);
	free2DArrayInt(histo1, sizeOne);
	free2DArrayInt(histo2, sizeTwo);

	return 0;
}
