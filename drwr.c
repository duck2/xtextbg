#include <stdio.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

#include "config.h"

int main()
{
	char buf[MAX+1];
	int x, s;
	Display * d;
	Window r;
	XftFont * f;
	XftDraw * drw;
	XRenderColor xrc;
	XftColor xftc;
	
	x = read(0, buf, MAX);
	buf[x] = '\0';
	printf("drwr: read %s\n", buf);

	if (!(d = XOpenDisplay(NULL))) fprintf(stderr, "drwr: cannot open display.\n");
	s = DefaultScreen(d);
	r = RootWindow(d, s);
	if (!(f = XftFontOpenName(d, s, font))) fprintf(stderr, "drwr: could not open font.\n");
	
	drw = XftDrawCreate(d, r, DefaultVisual(d, s), DefaultColormap(d, s));
	xrc.red = 0xFFFF;
	xrc.green = 0;
	xrc.blue = 0;
	xrc.alpha = 0xFFFF;
	XftColorAllocValue(d, DefaultVisual(d, s), DefaultColormap(d, s), &xrc, &xftc);
	XftDrawRect(drw, &xftc, 200, 200, 50, 50);
	XftDrawStringUtf8(drw, &xftc, f, 50, 50, (XftChar8 *)buf, x);

	XFlush(d);
	XSetCloseDownMode(d, RetainPermanent);
	XCloseDisplay(d);

	return 0;
}
