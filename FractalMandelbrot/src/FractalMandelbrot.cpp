/**
 * This program visualizes fractal Mandelbrot
 */
#include <iostream>

#include "console.h"
#include "gwindow.h"
#include "gbufferedimage.h"

using namespace std;

// Constants and function prototypes
const int WIDTH_WINDOW = 1000;
const int HEIGHT_WINDOW = 600;
const int COL_ITERATION = 500;

void drawFractal(GBufferedImage* image, GWindow window);

/**
 * The main method of the program creates a
 * window and calls the method that draws fractal
 */
int main(){
    GWindow window(WIDTH_WINDOW, HEIGHT_WINDOW);
    GBufferedImage* image = new GBufferedImage(WIDTH_WINDOW,HEIGHT_WINDOW,0xffffff);

    drawFractal(image, window);
    return 0;
}

/**
 * Method: drawFractal
 * Usage: drawFractal(GBufferedImage* image, GWindow window)
 * ________________________________________________________
 *
 * This method produces a mathematical calculation determines
 * the location of a fractal and visualizes it
 *
 * @param image - image of which will be displayed fractal
 * @param window - window for image width fractal
 */
void drawFractal(GBufferedImage* image, GWindow window){
    float ci, cr, zi, zr, tmp;
    int k;
    window.add(image);
    for(int i = 0 - (WIDTH_WINDOW - (WIDTH_WINDOW/4.5)); i < WIDTH_WINDOW/4.5; i++){ // handles all pixel coordinates x
        cr = ((float)i) / (WIDTH_WINDOW/2);                    //  assigns the value of the imaginary part с

        for (int j = 0 - HEIGHT_WINDOW/2; j < HEIGHT_WINDOW/2; j++){  // handles all pixel coordinates y
            ci = ((float)j) / (HEIGHT_WINDOW/2);             //  assigns the value of the real part with
            zi = zr = 0.0;                       //  assigning the real and imaginary parts of z - 0

            for(k = 0; k < COL_ITERATION; k++) {         //  computes the Mandelbrot set
                tmp = zr*zr - zi*zi;
                zi = 2*zr*zi + ci;
                zr = tmp + cr;
                if (zr*zr + zi*zi > 1.0E16)        //  If "z" is too large, the output from the cycle
                    break;

                if ( k == COL_ITERATION-1) {
                    image->setRGB(i+(WIDTH_WINDOW - WIDTH_WINDOW/4.5), j+(HEIGHT_WINDOW/2), 0x000000);  // paints the fractal point in black
                }
            }
        }
    }
}

