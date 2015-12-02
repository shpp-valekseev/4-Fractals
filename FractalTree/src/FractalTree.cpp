/**
 * The program draws a fractal tree
 */

#include <iostream>
#include "console.h"
#include "gwindow.h"
#include "random.h"

using namespace std;

// Constants and function prototypes
const int WIDTH_WINDOW = 700;
const int HEIGHT_WINDOW = 600;
const int START_SIZE = 220;
const int MIN_SIZE = 10;
const int HEIGHT_GRASS = 10;

void drawForest(GWindow & window);
void drawGrass(GWindow & window);
void drawTree(int x, int y, GWindow & window, int size, int minSize, int angle);

/* Main method of the program */
int main() {
    GWindow window(WIDTH_WINDOW, HEIGHT_WINDOW);

    drawTree(WIDTH_WINDOW/2, HEIGHT_WINDOW, window, START_SIZE, MIN_SIZE, 90);
    drawForest(window);
    drawGrass(window);

    return 0;
}

/**
 * Method: drawForest
 * Usage: drawForest(GWindow & window)
 * ___________________________________
 *
 * Draws 10 trees of random sizes in a given range
 *
 * @param window in which will draw image
 */
void drawForest(GWindow & window){
    int stepX = WIDTH_WINDOW/10;
    for(int i = 1; i < 10; i++){
        int step = stepX * i;
        int heightTree = randomInteger((HEIGHT_WINDOW/15)/1.2, (HEIGHT_WINDOW/15)*1.2);

        drawTree(step, HEIGHT_WINDOW, window, heightTree, MIN_SIZE/4, 90);
    }
}

/**
 * Method: drawGrass
 * Usage: drawGrass(GWindow & window)
 * __________________________________
 *
 * Method draws the grass and this gives aesthetic image
 *
 * @param window in which will draw image
 */
void drawGrass(GWindow & window){
    for(int i = 0; i < window.getWidth(); i += 3){
        window.setColor(0x00ff00);
        int height = randomInteger(HEIGHT_GRASS/3, HEIGHT_GRASS/0.3);
        int angle = randomInteger(-30, 30);
        window.drawPolarLine(i, HEIGHT_WINDOW, height, angle + 90);
    }
}

/**
 * Method: drawTree
 * Usage: drawTree(int x, int y, GWindow & window, int size, int minSize, int angle)
 * ________________________________________________________________________________
 *
 * This method draws fractal tree, reducing the length of the branches, until they
 * reach the minimum specified size
 *
 * @param x - X coordinate of the started point
 * @param y - X coordinate of the started point
 * @param window in which will draw image
 * @param size - starting size of branches
 * @param minSize - minimum allowable size of branches
 * @param angle - allowable rotation angle branches
 */
void drawTree(int x, int y, GWindow & window, int size, int minSize, int angle){
    if(size >= minSize){
        size = size / 1.4;
        int degree = 40;

        window.setColor(0xff7800);

        // sets green for small branches
        if (size == minSize || size < minSize*1.5){
            window.setColor(0x00ff00);
        }

        GPoint p = window.drawPolarLine(x, y, size, angle);

        drawTree(p.getX(), p.getY(), window, size, minSize, angle + degree);
        drawTree(p.getX(), p.getY(), window, size, minSize, angle - degree);

        // randomly selects a third branch of the draw or not. Comment out for full symmetry tree
        if(randomBool())  drawTree(p.getX(), p.getY(), window, size, minSize, angle);
    }

}
