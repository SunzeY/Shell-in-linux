myshell: main.o
	gcc main.o -o myshell

main.o: main.c
	gcc -c -o main.o -I./include main.c

.PHONY: clean test

clean:
	rm -f main.o myshell

test:
	./myshell
