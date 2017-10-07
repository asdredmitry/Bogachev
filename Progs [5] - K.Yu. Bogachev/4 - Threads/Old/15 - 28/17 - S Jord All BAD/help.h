#ifndef __HELP_H_INCLUDED__
#define __HELP_H_INCLUDED__

double f(int i, int j);

void InputMatrix(int n, double *a, double *b, int mode, FILE *input);

void OutputMatrix(int n, double *a, double *b);

void OutputVector(int n, double *x);

double TestSolution(int n, double *a, double *b, double *x);

double SolAccuracy(int n, double *x);

long int get_time(void);

long int get_full_time(void);

#endif /* __HELP_H_INCLUDED__ */
