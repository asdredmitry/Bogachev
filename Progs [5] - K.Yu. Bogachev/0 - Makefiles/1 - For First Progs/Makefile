all: main.o func.o
	gcc main.o func.o -lm -o App

main.o: main.c func.h
	gcc main.c -c -o main.o

func.o: func.c func.h
	gcc func.c -c -o func.o

clean:
	rm -f *.o App
