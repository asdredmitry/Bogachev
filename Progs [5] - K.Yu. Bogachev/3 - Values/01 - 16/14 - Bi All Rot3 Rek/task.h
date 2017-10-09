#ifndef __TASK_H_INCLUDED__
#define __TASK_H_INCLUDED__

void FindValues(int n, double* a, double* values, double eps, int* iterOut);
void Rot3(int n, double* a);
int n_(int n, double* a, double lambda);
double CalcNorm(int n, double* a);

#endif /* not __TASK_H_INCLUDED__ */
