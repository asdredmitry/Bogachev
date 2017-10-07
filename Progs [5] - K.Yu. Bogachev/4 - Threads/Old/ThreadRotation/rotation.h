#ifndef ROTATION_H_INCLUDED
#define ROTATION_H_INCLUDED

/* ������� ���� Ax = b ������� ��������.
   n - �����������,
   threads_num - ����� �����;
   ������-������� ���������� � b;
   ���������� 0 � ������ ������ � �� 0 � ��������� ������.
   ��������: ��� ���������� ������� ������� A � ������ b ���������� */

int rotation_solve(double A[], double b[], int n, int threads_num);

#endif
