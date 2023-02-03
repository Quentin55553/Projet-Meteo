main.o : main.c meteo.h
	gcc -c main.c -o main.o

AVL.o : AVL.c meteo.h
	gcc -c AVL.c -o AVL.o

ABR.o : ABR.c meteo.h
	gcc -c ABR.c -o ABR.o

Liste.o : Liste.c meteo.h
	gcc -c Liste.c -o Liste.o

exec : main.o AVL.o ABR.o Liste.o
	gcc *.o -o exec

clean :
	rm -f *.o
	rm exec
