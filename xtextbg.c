#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

#include "config.h"

void die(char * f, ...)
{
	va_list ap;
	va_start(ap, f);
	vfprintf(stderr, f, ap);
	va_end(ap);
	exit(1);
}

void usage()
{
	die("usage: xtextbg [x] [y]\n");
}

int estrtol(char * f)
{
	int q;
	char * e;
	q = strtol(f, &e, 10);
	if (*e) usage();
	return q;
}

int main(int argc, char * argv[])
{
	char buf[MAX+1], * line;
	int len, s, x, y, w, h;
	Display * d;
	Window r;
	XWindowAttributes ra;
	XftFont * f;
	XftDraw * drw;
	XftColor xftc, xftbg;
	Pixmap pix;
	XGlyphInfo ext;

	if(argc != 3) usage();
	x = estrtol(argv[1]);
	y = estrtol(argv[2]);

	if(!(d = XOpenDisplay(NULL))) die("cannot open display\n");
	s = DefaultScreen(d);
	r = RootWindow(d, s);
	if(!(f = XftFontOpenName(d, s, font))) die("cannot open font\n");

	len = read(0, buf, MAX);
	buf[len] = '\0';

	XftTextExtentsUtf8(d, f, (XftChar8 *)buf, len, &ext);
	XGetWindowAttributes(d, r, &ra);
	w = ra.width;
	h = ra.height;
	if(!(pix = XCreatePixmap(d, r, w, h, DefaultDepth(d, s)))) die("cannot make pixmap\n");

	drw = XftDrawCreate(d, pix, DefaultVisual(d, s), DefaultColormap(d, s));
	XftColorAllocValue(d, DefaultVisual(d, s), DefaultColormap(d, s), &color, &xftc);
	XftColorAllocValue(d, DefaultVisual(d, s), DefaultColormap(d, s), &bgcolor, &xftbg);
	XftDrawRect(drw, &xftbg, 0, 0, w, h);

	line = strtok(buf, "\n");
	if(!line) line = buf;
	do {
		XftDrawStringUtf8(drw, &xftc, f, x, y, (XftChar8 *)line, strlen(line));
		y += ext.height * line_spacing;
	} while((line = strtok(NULL, "\n")));

	XSetWindowBackgroundPixmap(d, r, pix);
	XClearWindow(d, r);
	XFlush(d);

	XftDrawDestroy(drw);
	XCloseDisplay(d);

	return 0;
}
