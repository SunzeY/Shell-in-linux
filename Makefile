myshell: main.o
	gcc main.o -o myshell

main.o: main.c
	gcc -c main.c -o main.o

.PHONY: clean

clean:
	rm -f main.o myshell

test:
	./myshell
