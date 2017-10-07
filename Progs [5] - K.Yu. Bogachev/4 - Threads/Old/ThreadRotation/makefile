prog.exe: main.o rotation.o
	gcc -g -W -Wall main.o rotation.o -lm -lpthread -owork.exe

main.o: main.c rotation.h
	gcc -c -g -W -Wall main.c

rotation.o: rotation.c rotation.h
	gcc -c -g -W -Wall rotation.c

clean:
	rm *.o
	rm *.exe
