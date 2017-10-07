#ifndef ROTATION_H_INCLUDED
#define ROTATION_H_INCLUDED

/* Решение СЛАУ Ax = b методом вращений.
   n - размерность,
   threads_num - число задач;
   вектор-решение помещается в b;
   возвращает 0 в случае успеха и не 0 в противном случае.
   ВНИМАНИЕ: при вычислении решения матрица A и вектор b изменяются */

int rotation_solve(double A[], double b[], int n, int threads_num);

#endif
