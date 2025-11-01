//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>

void main() {
    float x = 300,y= 200, a =100, b = 75, x1, y1, m, dx, dy, asqr, bsqr, temp1, temp2;
    int gd = DETECT, gmode;

    initgraph(&gd, &gmode, "C:\\TURBOC3\\BGI");

    x1 = 0;
    y1 = b;
    asqr = a * a;
    bsqr = b * b;
    dx = 2 * bsqr * x1; 
    dy = 2 * asqr * y1; 
    m = bsqr - (asqr * b) + (asqr * 0.25); 

    do {
	putpixel(x + x1, y + y1, GREEN);
	putpixel(x - x1, y - y1, GREEN);
	putpixel(x + x1, y - y1, GREEN);
	putpixel(x - x1, y + y1, GREEN);
	if (m < 0) {
	    m = m + dx + bsqr;
        } else {
            y1 = y1 - 1; 
            m = m + dx + bsqr - dy;
            dy = dy - (2 * asqr);
        }
        x1 = x1 + 1; 
        dx = dx + (2 * bsqr);
    } while (dx < dy);

    temp1 = (x1 + 0.5) * (x1 + 0.5); 
    temp2 = (y1 - 1) * (y1 - 1); 
    m = bsqr * temp1 + asqr * temp2 - (asqr * bsqr);

    do {
        putpixel(x + x1, y + y1, GREEN);
        putpixel(x - x1, y - y1, GREEN);
        putpixel(x - x1, y + y1, GREEN);
        putpixel(x + x1, y - y1, GREEN);

        if (m > 0) {
            m = m - dy + asqr;
        } else {
            x1 = x1 + 1; 
            m = m + dx - dy + asqr; 
            dx = dx + (2 * bsqr); 
        }
        y1 = y1 - 1; 
        dy = dy - (2 * asqr);
    } while (y1 > 0); 

    getch(); 
}
