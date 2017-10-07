#ifndef __MATRIX_H_INCLUDED__
#define __MATRIX_H_INCLUDED__

int InputMatrix(int n, double* a, int inputMode, FILE* fin);

void PrintMatrix(int n, double* a);

double SolutionError(int n, double* a, double* x);

#endif /* not __MATRIX_H_INCLUDED__ */
