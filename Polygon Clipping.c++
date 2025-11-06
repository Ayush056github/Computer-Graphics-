//

#include <iostream>
#include <graphics.h>
#include <math.h>
using namespace std;

#define round(a) ((int)(a + 0.5))

float xmin, ymin, xmax, ymax;
float arr[100], temp[100];
int k;

void clipLeft(float x1, float y1, float x2, float y2)
{
    float m;
    if (x2 - x1 != 0)
        m = (y2 - y1) / (x2 - x1);
    else
        m = 100000.0;

    if (x1 >= xmin && x2 >= xmin)
    {
        temp[k++] = x2;
        temp[k++] = y2;
    }
    else if (x1 < xmin && x2 >= xmin)
    {
        temp[k++] = xmin;
        temp[k++] = y1 + m * (xmin - x1);
        temp[k++] = x2;
        temp[k++] = y2;
    }
    else if (x1 >= xmin && x2 < xmin)
    {
        temp[k++] = xmin;
        temp[k++] = y1 + m * (xmin - x1);
    }
}

void clipRight(float x1, float y1, float x2, float y2)
{
    float m;
    if (x2 - x1 != 0)
        m = (y2 - y1) / (x2 - x1);
    else
        m = 100000.0;

    if (x1 <= xmax && x2 <= xmax)
    {
        temp[k++] = x2;
        temp[k++] = y2;
    }
    else if (x1 > xmax && x2 <= xmax)
    {
        temp[k++] = xmax;
        temp[k++] = y1 + m * (xmax - x1);
        temp[k++] = x2;
        temp[k++] = y2;
    }
    else if (x1 <= xmax && x2 > xmax)
    {
        temp[k++] = xmax;
        temp[k++] = y1 + m * (xmax - x1);
    }
}

void clipBottom(float x1, float y1, float x2, float y2)
{
    float m;
    if (x2 - x1 != 0)
        m = (y2 - y1) / (x2 - x1);
    else
        m = 100000.0;

    if (y1 >= ymin && y2 >= ymin)
    {
        temp[k++] = x2;
        temp[k++] = y2;
    }
    else if (y1 < ymin && y2 >= ymin)
    {
        temp[k++] = x1 + (ymin - y1) / m;
        temp[k++] = ymin;
        temp[k++] = x2;
        temp[k++] = y2;
    }
    else if (y1 >= ymin && y2 < ymin)
    {
        temp[k++] = x1 + (ymin - y1) / m;
        temp[k++] = ymin;
    }
}

void clipTop(float x1, float y1, float x2, float y2)
{
    float m;
    if (x2 - x1 != 0)
        m = (y2 - y1) / (x2 - x1);
    else
        m = 100000.0;

    if (y1 <= ymax && y2 <= ymax)
    {
        temp[k++] = x2;
        temp[k++] = y2;
    }
    else if (y1 > ymax && y2 <= ymax)
    {
        temp[k++] = x1 + (ymax - y1) / m;
        temp[k++] = ymax;
        temp[k++] = x2;
        temp[k++] = y2;
    }
    else if (y1 <= ymax && y2 > ymax)
    {
        temp[k++] = x1 + (ymax - y1) / m;
        temp[k++] = ymax;
    }
}

void clipPolygon(float arr[], int n)
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Draw original window and polygon
    rectangle(xmin, ymin, xmax, ymax);
    for (int i = 0; i < n - 2; i += 2)
        line(arr[i], arr[i + 1], arr[i + 2], arr[i + 3]);
    line(arr[n - 2], arr[n - 1], arr[0], arr[1]);

    getch();
    cleardevice();

    // Left clipping
    k = 0;
    for (int i = 0; i < n - 2; i += 2)
        clipLeft(arr[i], arr[i + 1], arr[i + 2], arr[i + 3]);
    clipLeft(arr[n - 2], arr[n - 1], arr[0], arr[1]);
    n = k;
    for (int i = 0; i < n; i++)
        arr[i] = temp[i];

    // Right clipping
    k = 0;
    for (int i = 0; i < n - 2; i += 2)
        clipRight(arr[i], arr[i + 1], arr[i + 2], arr[i + 3]);
    clipRight(arr[n - 2], arr[n - 1], arr[0], arr[1]);
    n = k;
    for (int i = 0; i < n; i++)
        arr[i] = temp[i];

    // Bottom clipping
    k = 0;
    for (int i = 0; i < n - 2; i += 2)
        clipBottom(arr[i], arr[i + 1], arr[i + 2], arr[i + 3]);
    clipBottom(arr[n - 2], arr[n - 1], arr[0], arr[1]);
    n = k;
    for (int i = 0; i < n; i++)
        arr[i] = temp[i];

    // Top clipping
    k = 0;
    for (int i = 0; i < n - 2; i += 2)
        clipTop(arr[i], arr[i + 1], arr[i + 2], arr[i + 3]);
    clipTop(arr[n - 2], arr[n - 1], arr[0], arr[1]);
    n = k;

    // Draw clipped polygon
    cleardevice();
    rectangle(xmin, ymin, xmax, ymax);
    for (int i = 0; i < n - 2; i += 2)
        line(arr[i], arr[i + 1], arr[i + 2], arr[i + 3]);
    line(arr[n - 2], arr[n - 1], arr[0], arr[1]);

    getch();
    closegraph();
}

int main()
{
    int n;
    cout << "Enter window coordinates (xmin, ymin, xmax, ymax): ";
    cin >> xmin >> ymin >> xmax >> ymax;

    cout << "Enter number of polygon vertices: ";
    cin >> n;

    cout << "Enter polygon coordinates (x, y):\n";
    for (int i = 0; i < n * 2; i++)
        cin >> arr[i];

    clipPolygon(arr, n * 2);
    return 0;
}
