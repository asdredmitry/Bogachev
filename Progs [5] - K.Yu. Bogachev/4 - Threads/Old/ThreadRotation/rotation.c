#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "rotation.h"

static void transform(double *sub_a, double *b, int n, int k, int threads_num); /* шаг алгоритма */
static void reverse(double *a, double *b, int n);                     /* обратный ход */
void *process_function(void *pa);

static pthread_t *threads;
static int lines_num;
static int columns_num;
static int N;
static double *cos_phi;
static double *sin_phi;

int rotation_solve(double *a, double *b, int n, int threads_num)
{
  int k;
  double *sub_a;

  N = n;

  if (!(threads = (pthread_t*) malloc (threads_num * sizeof(pthread_t)))) {
    printf("Не хватило памяти для создания задач\n");
    return 1;
  }
  
  if (!(cos_phi = (double*) malloc((n-1)*sizeof(double)))) {
    printf("Не хватило памяти для создания массива косинусов\n");
    free(threads);
    return 1;
  }

  if (!(sin_phi = (double*) malloc((n-1)*sizeof(double)))) {
    printf("Не хватило памяти для создания массива синусов\n");
    free(threads);
    free(cos_phi);
    return 1;
  }

  for (k = 1, sub_a = a; k < n; k++, sub_a += (n+1))
    transform(sub_a, b, n, k, threads_num);
    
  free(threads);
  free(cos_phi);
  free(sin_phi);
  reverse(a, b, n);
  return 0;
}

static void transform(double *a, double *b, int n, int k, int threads_num)
{
  double x, y, tmp, cos_, sin_;
  double *p, *pb, *cosp, *sinp;
  
  int i, l;

  /* заполняем массивы синусов и косинусов углов поворота */
  p = a + n;
  cosp = cos_phi;
  sinp = sin_phi;
  for (i = 1; i <= (n-k); i++, p += n, cosp++, sinp++) {
    x = *a;
    y = *p;
    tmp = sqrt(x*x + y*y);
    *cosp = cos_ = x / tmp;
    *sinp = sin_ = -y / tmp;
    *a = x*cos_ - y*sin_;
    *p = x*sin_ + y*cos_;
  }
  
  /* распараллеливаем */
  lines_num = n - k;
  columns_num = (n - k) / threads_num;
  l = (n - k) % threads_num;

  if (columns_num > 0) {
    p = a + 1;
    for (i = 0; i < threads_num; i++, p += columns_num)
      pthread_create(threads + i, 0, process_function, (void*)p);
   for (i = 0; i < threads_num; i++)
     pthread_join(threads[i], 0);
  }

  if (l > 0) {
    p = a + 1 + columns_num*threads_num;
    columns_num = l;
    process_function((void*)p);
  }

  /* обработать столбец свободных членов */
  cosp = cos_phi;
  sinp = sin_phi;
  p = b + k - 1;
  pb = p + 1;
  for (i = 0; i < lines_num; i++, pb++, cosp++, sinp++) {
    cos_ = *cosp;
    sin_ = *sinp;
    x = *p;
    y = *pb;
    *p = x*cos_ - y*sin_;
    *pb = x*sin_ + y*cos_;
  }
}

void *process_function(void *pa)
{
  int i, j;
  double *a = (double*)pa;
  double *p, *p1, *p2, *cosp = cos_phi, *sinp = sin_phi;
  double cos_, sin_, x, y;
    
  for (i = 0, p = a + N; i < lines_num; i++, p += N, cosp++, sinp++) {
    cos_ = *cosp;
    sin_ = *sinp;
    for (j = 0, p1 = a, p2 = p; j < columns_num; j++, p1++, p2++) {
      x = *p1;
      y = *p2;
      *p1 = x*cos_ - y*sin_;
      *p2 = x*sin_ + y*cos_;
    }
  }
  return 0;
}

static void reverse(double *a, double *b, int n)
{
  int i, j;
  double tmp;
  double *ap1, *ap2, *bp, *bp1;
  
  /* нормировка диагональных элементов */
  for (i = 1, ap1 = a, bp = b; i <= n; i++, ap1 += (n+1), bp++) {
    tmp = *ap1;
    for (j = i, ap2 = ap1+1; j < n; j++, ap2++)
      *ap2 /= tmp;
    *bp /= tmp;
  }
  
  /* обратный ход */
  for (i = 1, ap1 = a + n*(n-1) - 1, bp = b + n - 1; i < n; i++, ap1 -= (n+1), bp--)
    for (j = 1, ap2 = ap1, tmp = *bp, bp1 = bp-1; j <= n-i; j++, bp1--, ap2 -= n)
      *bp1 -= *ap2 * tmp;
}
