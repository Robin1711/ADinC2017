/* recognizeExp.h, Gerard Renardel, 29 January 2014 */

#ifndef RECOGNIZEEXP_H
#define RECOGNIZEEXP_H


int acceptNumber(List *lp);
int acceptIdentifier(List *lp);
int acceptCharacter(List *lp, char c);
int acceptFactor(List *lp);
int acceptTerm(List *lp);
int acceptExpression(List *lp);
int acceptEquation(List *lp);
int isEqual(char *ar1, char*ar2, int size);
int isOneVar(List *lp);
int max(int a, int b);
int degree(List *lp);
void solveEquations();



#endif
