#ifndef __MATRIX_H_INCLUDED__
#define __MATRIX_H_INCLUDED__

int InputMatrix(int n, double* a, double* b, int inputMode, FILE* fin);

void PrintMatrix(int n, double* a, double* b);

void PrintVector(int n, double* x);

double SolutionError(int n, double* a, double* b, double* x);

double SolutionAccuracy(int n, double* x);

#endif /* not __MATRIX_H_INCLUDED__ */
