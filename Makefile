myshell: main.o parse.o exec.o
	gcc main.o parse.o exec.o -o myshell

main.o: main.c
	gcc -c -o main.o -I./include main.c

parse.o: parse.c
	gcc -c -o parse.o -I./include parse.c

exec.o: exec.c
	gcc -c -o exec.o -I./include exec.c

signal.o: signal.c
	gcc -c -o signal.o signal.c

.PHONY: clean test

clean:
	rm -f main.o myshell

test:
	./myshell
