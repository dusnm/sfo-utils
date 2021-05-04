output: main.o sforead.o sfoparse.o parson.o
	gcc main.o sforead.o sfoparse.o parson.o -o sfo-utils -O3

main.o: main.c
	gcc -c main.c

sforead.o: sforead.c
	gcc -c sforead.c

sfoparse.o: sfoparse.c
	gcc -c sfoparse.c

parson.o: lib/parson/parson.c
	gcc -c lib/parson/parson.c

clean:
	rm *.o
	rm sfo-utils

install:
	cp sfo-utils $(DESTDIR)$(PREFIX)/bin/sfo-utils

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/sfo-utils
