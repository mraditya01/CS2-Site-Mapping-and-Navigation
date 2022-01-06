spatialdb: main_menu.o database.o readline.o page.o
	gcc -lm -o spatialdb main_menu.o database.o readline.o page.o

main_menu.o: main_menu.c database.h readline.h item.h 
	gcc -c main_menu.c

readline.o: readline.c readline.h 
	gcc -c readline.c

database.o: database.c database.h item.h readline.h
	gcc -c database.c

page.o: page.c database.h item.h
	gcc -c page.c

clean:
	rm *.o
