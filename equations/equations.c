#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

#define TRUE 1
#define FALSE 0

const int ALPHNUM = 26; //The number of letters in the alphabet

int isEquation(List inputList, List variableList, int* degree) {
  return TRUE;
}

List readInput(List li) {
  char c = getchar();
  while (c != '\n') {
    li = addItemFront(c, li);
    c = getchar();
  }
  return reverseList(li);
}

int main(int argc, char *argv[]) {

  while(TRUE) {
    List inputList = newEmptyList();
    inputList = readInput(inputList);

    if (firstItem(inputList) == '!') {
      break;
    }

    List variableList = newEmptyList();
    int degree = 1;
    if (isEquation(inputList, variableList, &degree)) {
      int variables = listLength(variableList);
      if (variables == 1) {
        printf("this is an equation in %d variable of degree %d\n", variables, degree);
      } else {
        printf("this is an equation, but not in 1 variable\n");
      }
    } else {
      printf("this is not an equation\n");
    }

    printList(inputList);
    printf("\n");
    freeList(inputList);
    freeList(variableList);
  }
  printf("we breaked");
  return 0;
}

// grammar:
// <equation> ::= <expression> '=' <expression>
// <expression> ::= <term> {'+' <term> | '-' <term>}
//              | '-' <term> {'+' <term> | '-' <term>}
// <term> ::= <natnum> | <natnum> <identifier> | <natnum> <identifier> '^' natnum
