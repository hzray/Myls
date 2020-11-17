all:

	gcc myls.c -o myls -Wall -g -std=c11

clean:
	rm -f myls
