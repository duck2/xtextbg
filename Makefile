# modify
X11INC=/usr/include/X11
X11LIB=/usr/lib/X11

FT2INC=/usr/include/freetype2/

PREFIX=/usr

CC=cc
CFLAGS=-Wall -Werror -pedantic -I$(X11INC) -I$(FT2INC) -L$(X11LIB)
LDFLAGS=-lX11 -lXft

all: drwr

drwr: drwr.c config.h
	$(CC) -o drwr drwr.c $(CFLAGS) $(LDFLAGS)

install: all
	@echo installing to ${PREFIX}/bin
	mkdir -p ${PREFIX}/bin
	cp -f drwr ${PREFIX}/bin
	chmod 755 ${PREFIX}/bin/drwr

uninstall:
	@echo removing from ${PREFIX}/bin
	rm -f ${PREFIX}/bin/drwr

clean:
	rm -f drwr

.PHONY: all clean install uninstall