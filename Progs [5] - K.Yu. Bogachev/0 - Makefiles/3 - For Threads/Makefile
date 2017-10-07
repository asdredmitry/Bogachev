all: main.o matrix.o task.o
	gcc main.o matrix.o task.o -lm -lpthread -o App -O2

main.o: main.c matrix.h task.h
	gcc main.c -c -o main.o -O2

matrix.o: matrix.c matrix.h
	gcc matrix.c -c -o matrix.o -O2

task.o: task.c task.h
	gcc task.c -c -o task.o -O2

clean:
	rm -f *.o App
