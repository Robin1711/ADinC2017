/*
 * Anagram by Robin Sommer and Nick Borchers
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int ALPHNUM = 26; //The number of letters in the alphabet

//Allocate memory for a 2D array
int **allocate2D(int rows, int columns){
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
void readSentence(int *ar){
	char c;
	c = getchar();
	while(c != '.'){
		if(c >= 'a' && c <= 'z'){ //Only enter c in the histogram when it is a letter
			ar[c-'a']++;
		}
		c = getchar();
	}
}

//For all rows in ar, read the sentence from stdin.
void readInput(int **ar, int rows){
	int row;
	for(row=0; row<rows; row++){
		readSentence(ar[row]);
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
void free2D(int **ar, int rows){
	int row;
	for(row=0; row<rows; row++){
		free(ar[row]);
	}
	free(ar);
}

int main(int argc, char **argv){
	int n, m, i, j;
	int **sentences, **testSentences;
	//Read table sentences:
	scanf("%d", &n);
	sentences = allocate2D(n, ALPHNUM);
	readInput(sentences, n);
	//Read test sentences:
	scanf("%d", &m);
	testSentences = allocate2D(m, ALPHNUM);
	readInput(testSentences, m);

	//Loop over all test sentences and print the matching histogram numbers
	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			if(isEqual(sentences[j], testSentences[i], ALPHNUM)){
				printf("%d ", j+1);
			}
		}
		printf("\n");
	}

	//Free all memory used.
	free2D(sentences, n);
	free2D(testSentences, m);
	return 0;
}
