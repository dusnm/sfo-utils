output: main.o read.o parse.o
	gcc main.o read.o parse.o -o sfo-utils -O3

main.o:
	gcc -c main.c

read.o:
	gcc -c src/read/read.c

parse.o:
	gcc -c src/parse/parse.c

clean:
	rm *.o
	rm sfo-utils

install:
	cp sfo-utils $(DESTDIR)$(PREFIX)/bin/sfo-utils

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/sfo-utils