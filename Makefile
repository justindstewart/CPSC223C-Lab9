
GLIB_CFLAGS=`pkg-config --cflags glib-2.0`
GLIB_LFLAGS=`pkg-config --libs glib-2.0`

traffic: main.o car.o ped.o traveler.o
	clang main.o car.o ped.o traveler.o -o traffic ${GLIB_CFLAGS} ${GLIB_LFLAGS} 

main.o: main.c car.h ped.h traveler.h
	clang -c main.c -o main.o ${GLIB_CFLAGS}

car.o: car.c car.h traveler.h
	clang -c car.c -o car.o ${GLIB_CFLAGS}

ped.o: ped.c ped.h traveler.h
	clang -c ped.c -o ped.o ${GLIB_CFLAGS}

traveler.o: traveler.c traveler.h
	clang -c traveler.c -o traveler.o ${GLIB_CFLAGS}

clean:
	rm -f traffic main.o car.o ped.o traveler.o
