all: clean bin/main

bin/main: obj/main.o obj/funciones.o
	gcc -pthread obj/main.o obj/funciones.o -o bin/main -lm
	
obj/main.o:
	gcc -c -Iinclude src/main.c -o obj/main.o
	
obj/funciones.o:
	gcc -c -Iinclude src/funciones.c -o obj/funciones.o

.PHONY: clean

clean:
	rm -f obj/*.o *~ core $(INCDIR)/*~ 
