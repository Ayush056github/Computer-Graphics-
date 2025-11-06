//

//Fractal image
#include <graphics.h>
#include<conio.h>
#include <stdio.h>
#define MAXCOUNT 30

void fractal(float left, float top, float xside, float yside)
{
    float xscale, yscale, zx, zy, cx, tempx, cy;
    int x, y, i, j;
    int maxx, maxy, count;
    // getting maximum value of x-axis and y-axis of screen
    maxx = getmaxx();
    maxy = getmaxy();
    xscale = xside / maxx;
    yscale = yside / maxy;
    rectangle(0, 0, maxx, maxy);
    for (y = 1; y <= maxy - 1; y++) {
        for (x = 1; x <= maxx - 1; x++)
        {
            cx = x * xscale + left;
            cy = y * yscale + top;
            zx = 0;
            zy = 0;
            count = 0;
            while ((zx * zx + zy * zy < 4) && (count < MAXCOUNT))
            {
                tempx = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = tempx;
                count = count + 1;
            }
            // The putpixel function is needed here to draw the fractal.
            // The color depends on the count value.
            putpixel(x, y, count % 16); 
        }
    }
}

int main() {
    int gd = DETECT, gm; // Graphics Driver and Graphics Mode
    
    // Initialize graphics mode
    initgraph(&gd, &gm, (char*)""); 
    
    // Call the fractal function with appropriate parameters for the Mandelbrot set
    fractal(-2.0, -1.2, 3.0, 2.4); 
    
    getch(); // Wait for a key press
    closegraph(); // Close the graphics
    return 0;
}
