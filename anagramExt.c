/*
 * Anagram extension 1 by Robin Sommer and Nick Borchers
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const int ALPHNUM = 26; //The number of letters in the alphabet
const int MAXSTRING = 100;



//Extend program functions:
char **allocate2DChar(int rows, int columns){
	char **new;
	int row;
	new = malloc(rows*sizeof(char*));
	assert(new != NULL);
	for(row=0; row<rows; row++){
		new[row] = malloc(columns*sizeof(char));
		assert(new[row] != NULL);
	}
	return new;
}

void free2DChar(char **ar, int rows){
	int row;
	for(row=0; row<rows; row++){
		free(ar[row]);
	}
	free(ar);
}

//Allocate memory for a 2D array
int **allocate2DInt(int rows, int columns){
	int **new;
	int row;
	new = calloc(rows,sizeof(int*));
	assert(new != NULL);
	for(row=0; row<rows; row++){
		new[row] = calloc(columns,sizeof(int));
		assert(new[row] != NULL);
	}
	return new;
}

//Read a sentence from stdin, a histogram is composed immediately. 
//We don't need to read the string.
void readSentence(int *ar, char *charAr, int charLen){
	char c;
	int i;
	c = getchar();
	for(i=0; c != '.'; i++){
		if(c >= 'a' && c <= 'z'){ //Only enter c in the histogram when it is a letter
			ar[c-'a']++;
		}
		if(c != '\n'){
			charAr[i] = c;
		}else{
			i--;
		}
		c = getchar();
	}
	if(i < charLen - 1){
		charAr[i+1] = '\0';
	}
}

//For all rows in ar, read the sentence from stdin.
void readInput(int **histAr, char **charAr, int rows){
	int row;
	for(row=0; row<rows; row++){
		readSentence(histAr[row], charAr[row], MAXSTRING);
	}
}



//Determine whether or not 2 arrays are equal. (all values are the same)
int isEqual(int *ar, int *otherAr, int length){
	int i;
	for(i=0; i<length; i++){
		if(ar[i] != otherAr[i]){
			return 0;
		}
	}
	return 1;
}

//Free a dynamically located 2D int array
void free2DInt(int **ar, int rows){
	int row;
	for(row=0; row<rows; row++){
		free(ar[row]);
	}
	free(ar);
}

int main(int argc, char **argv){
	int n, m, i, j, hasAnagram;
	int **histogramSentences, **histogramTestSentences;
	char **sentences, **testSentences;
	//Read table sentences:
	scanf("%d", &n);
	histogramSentences = allocate2DInt(n, ALPHNUM);
	sentences = allocate2DChar(n, MAXSTRING);
	readInput(histogramSentences, sentences, n);

	//Read test sentences:
	scanf("%d", &m);
	histogramTestSentences = allocate2DInt(m, ALPHNUM);
	testSentences = allocate2DChar(m, MAXSTRING);
	readInput(histogramTestSentences, testSentences, m);

	//Loop over all test sentences and print the matching histogram numbers
	for(i=0; i<m; i++){
		hasAnagram = 0;
		for(j=0; j<n; j++){
			if(isEqual(histogramSentences[j], histogramTestSentences[i], ALPHNUM)){
				hasAnagram++;
				printf("%d(test set) has as anagram %d(table set):\n", i+1, j+1);
				printf("%s. <-> %s.\n", testSentences[i], sentences[j]);
			}
		}
		if(!hasAnagram){
			printf("%d has no anagram\n", i+1);
		}
	}

	//Free all memory used.
	free2DInt(histogramSentences, n);
	free2DInt(histogramTestSentences, m);
	free2DChar(sentences, n);
	free2DChar(testSentences, m);
	return 0;
}
