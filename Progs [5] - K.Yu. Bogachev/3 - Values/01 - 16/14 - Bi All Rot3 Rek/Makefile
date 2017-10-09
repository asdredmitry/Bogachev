matrix.o : matrix.c 
	g++ -c matrix.c -o matrix.o
task.o : task.c
	g++ -c task.c -o task.o
main.o : main.c
	g++ -c main.c -o main.o
main : main.o task.o matrix.o
	g++  main.o matrix.o task.o -o main 
