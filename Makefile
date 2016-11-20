# modify
X11INC=/usr/include/X11
X11LIB=/usr/lib/X11

FT2INC=/usr/include/freetype2/

CC=cc
CFLAGS=-Wall -Werror -pedantic -I$(X11INC) -I$(FT2INC) -L$(X11LIB)
LDFLAGS=-lX11 -lXft

all: drwr

drwr: drwr.c config.h
	$(CC) -o drwr drwr.c $(CFLAGS) $(LDFLAGS)
