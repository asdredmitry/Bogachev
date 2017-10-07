#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rotation.h"

#define MAX_PRINT 10          /* ���������� ���������� ��������� ������� */

void multiply(double *A, double *b, double *c, int n, int m);     /* c = Ab */
double difference(double *a, double *b, int n);          /* ||a-b|| */
double exact_diff(double *x, double *tmp, int n);        /* ||x-������_�������|| */ 
void initialize(double *a, double *b, double *tmp, int n);
void initialize_matrix(double *a, int n);
void print_vector(double *x, int n);

int main(int argc, char *argv[])
{
  double *a, *x, *b, *c;  
  int n, p;
  time_t start, stop;

  if (argc != 3) {
    printf("�������������: %s <������ �������> <����� �����>\n", argv[0]);
    return 0;
  }

  n = (int)strtol(argv[1], 0, 10);
  p = (int)strtol(argv[2], 0, 10);

  printf("����� ���������: %d\n", p);

  if (!(a = (double *)malloc(n * n * sizeof(double)))) {
    printf("�� ������� ������\n");
    return 0;
  }

  if (!(x = (double *)malloc(n * sizeof(double)))) {
    printf("�� ������� ������\n");
    free(a);
    return 0;
  }

  if (!(b = (double *)malloc(n * sizeof(double)))) {
    printf("�� ������� ������\n");
    free(a);
    free(x);
    return 0;
  }

  if (!(c = (double *)malloc(n * sizeof(double)))) {
    printf("�� ������� ������\n");
    free(a);
    free(x);
    free(b);
    return 0;
  }

  /* �������������: � x �������� ������� ��������� ������ */
  initialize(a, x, c, n);   

//  printf("����� �������...\t");

  start = time(0);
  rotation_solve(a, x, n, p);
  stop = time(0);
  printf("\n����������� �������: %d \n", n);
  printf("\n����� ������: %lf \n", difftime(stop, start));

  printf("\n ������ �������:\n");
  print_vector(x, n);

  /* ���������� ������� (��� ����� ������ ���� ������������������� ������) */
  initialize(a, b, c, n);
  multiply(a, x, c, n, n);   /* c = ax */
  printf("\n����� �������: %.10e\n", difference(b, c, n));
  printf("\n����� �������� ����� ��������� (�������� � ���������� ����): %.10e\n", exact_diff(x, c, n));
 
  free(a);
  free(x);
  free(b);
  free(c);
  return 0;
}

/* c = ab */
void multiply(double *a, double *b, double *c, int n, int m)
{
  double *xa, *xb, *xc, sum;
  int i, j;

  for (i = 0, xa = a, xc = c; i < n; i++, xc++) {
    for (j = 0, sum = 0, xb = b; j < m; j++, xa++, xb++)
      sum += (*xa) * (*xb);
    *xc = sum;
  }
}

/* ����� �������� ����� ���������� � ������ ��������� */
double exact_diff(double *x, double *b, int n)
{
  int i;
  for (i = 0; i < n; i++)  /* ���������� � b ������ ������� (1,0,1,0,...) */
    if (i%2)
      b[i] = 0;
    else
      b[i] = 1;
  return difference(x, b, n);
}

/* ����� �������� ����� a � b */
double difference(double *a, double *b, int n)
{
  int i;
  double max;

  for (i = 0, max = fabs(a[0] - b[0]); i < n; i++)
    if (fabs(a[i] - b[i]) > max)
      max = fabs(a[i] - b[i]);

  return max;
}

/* ������������� ������� �� ������� */
void initialize(double *a, double *b, double *x, int n)
{
  int i;

  for (i = 0; i < n; i++)        /* x = (1,0,1,0,...) - ������ ������� */
    if (i%2)
      x[i] = 0;
    else
      x[i] = 1;

  initialize_matrix(a, n);
  
  multiply(a, x, b, n, n);       /* b = a*x - ������� ��������� ������ */
}

void initialize_matrix(double *a, int n)
{
  int i, j;

  for (i = 0; i < n; i++)        /* a - ������� ��������� */
     for (j = 0; j < n; j++)
       a[i*n + j] = 1.0/(i + j + 1);
}

void print_vector(double *x, int n)
{
  int i = 0;
  while (i < n && i < MAX_PRINT)

    printf("%.10e\n", x[i++]);
}
