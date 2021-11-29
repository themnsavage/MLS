all: clean
	gcc main.c MLS.c vector.c -o a.out

clean:
	rm -f main