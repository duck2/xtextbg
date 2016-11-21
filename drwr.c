#include <stdio.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xft/Xft.h>

#include "config.h"

int main()
{
	char buf[MAX+1] = "Lorem Ipsum";
	int x, s, w, h;
	Display * d;
	Window r;
	XftFont * f;
	XftDraw * drw;
	XftColor xftc;
	Pixmap pix;

	if (!(d = XOpenDisplay(NULL))) fprintf(stderr, "drwr: cannot open display.\n");
	s = DefaultScreen(d);
	r = RootWindow(d, s);
	if (!(f = XftFontOpenName(d, s, font))) fprintf(stderr, "drwr: could not open font.\n");

	/*
	x = read(0, buf, MAX);
	buf[x] = '\0';
	printf("drwr: read %s\n", buf);
	*/
	x = 12;

	w = 1600;
	h = 900;
	if(!(pix = XCreatePixmap(d, r, w, h, DefaultDepth(d, s)))) fprintf(stderr, "drwr: could not create pixmap.\n");

	drw = XftDrawCreateAlpha(d, pix, DefaultDepth(d, s));
	XftColorAllocValue(d, DefaultVisual(d, s), DefaultColormap(d, s), &color, &xftc);
	XftDrawStringUtf8(drw, &xftc, f, 100, 100, (XftChar8 *)buf, x);
	XftDrawRect(drw, &xftc, 10, 10, 50, 50);

	XSetWindowBackgroundPixmap(d, r, pix);
	XFlush(d);

	XCloseDisplay(d);

	return 0;
}
