output: main.o sforead.o sfoparse.o
	gcc main.o sforead.o sfoparse.o -o sfo-utils -O3

main.o: main.c
	gcc -c main.c

sforead.o: sforead.c
	gcc -c sforead.c

sfoparse.o: sfoparse.c
	gcc -c sfoparse.c

clean:
	rm *.o
	rm sfo-utils

install:
	cp sfo-utils $(DESTDIR)$(PREFIX)/bin/sfo-utils

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/sfo-utils