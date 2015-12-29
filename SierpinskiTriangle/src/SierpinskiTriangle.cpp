/**
 * This program visualizes the Sierpinski triangle.
 * Building figure made way called "play chaos"
 */

#include <iostream>
#include "gwindow.h"
#include "random.h"
#include "gbufferedimage.h"
using namespace std;

// Constants and function prototypes
const int WIDTH_WINDOW = 600;
const int HEIGHT_WINDOW = 600;
const int COL_ITERATION = 200000;
const int IDENT = 50;
const int BLACK_COLOR = 0x000000;
const int WHITE_COLOR = 0xffffff;

void drawFractal(GBufferedImage* image);

/* Main function of the program*/
int main() {
    GWindow window (WIDTH_WINDOW, HEIGHT_WINDOW);
    GBufferedImage* image = new GBufferedImage(WIDTH_WINDOW, HEIGHT_WINDOW, WHITE_COLOR);
    window.add(image);

    drawFractal(image);
    return 0;
}

/**
 * Function: drawFractal
 * Using: drawFractal(GBufferedImage* image)
 * ________________________________________
 *
 * Function creates three points in the  corners of
 * triangle. Subsequent points draws on the next
 * principle: On a point randomly selects a different
 * point between them draws a new point.
 *
 * @param image - image on the which is painted a fractal
 */
void drawFractal(GBufferedImage* image){
    // It creates a three-point in the range a triangle which will be
    double p1x = IDENT;
    double p1y = HEIGHT_WINDOW - IDENT;
    double p2x = WIDTH_WINDOW - IDENT;
    double p2y = HEIGHT_WINDOW - IDENT;
    double p3x = WIDTH_WINDOW/2;
    double p3y = IDENT;

    double pointX = p1x;
    double pointY = p1y;

    // randomly selected point, and creates a new point midway between the the previous
    for(int i = 0; i < COL_ITERATION; i++){
        image->setRGB(int(pointX), int(pointY), BLACK_COLOR);
        switch(randomInteger(1,3))
        {
        case 1:
            pointX = (pointX + p1x) / 2.0;
            pointY = (pointY + p1y) / 2.0;
            break;
        case 2:
            pointX = (pointX + p2x) / 2.0;
            pointY = (pointY + p2y) / 2.0;
            break;
        case 3:
            pointX = (pointX + p3x) / 2.0;
            pointY = (pointY + p3y) / 2.0;
            break;
        }
    }
}
