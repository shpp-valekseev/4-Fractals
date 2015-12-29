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
const int GREEN_COLOR_LEAVES = 0x00ff00;
const int BROWN_COLOR_TREE = 0xff7800;
const int DEGREES_DIRECTION_WOOD = 90;
const int NUMBER_OF_TREES_IN_FOREST = 10;
const int HEIGHT_RELATIVE_SCREEN = 15;
const int TILT_GRASS = 30;
const int TILT_TREE = 40;
const double REDUCTION_COEFFICIENT_BRANCH_SIZE = 1.4;


void drawForest(GWindow & window);
void drawGrass(GWindow & window);
void drawTree(int x, int y, GWindow & window, int size, int minSize, int angle);

/* Main method of the program */
int main() {
    GWindow window(WIDTH_WINDOW, HEIGHT_WINDOW);

    drawTree(WIDTH_WINDOW / 2, HEIGHT_WINDOW, window, START_SIZE, MIN_SIZE, DEGREES_DIRECTION_WOOD);
    drawForest(window);
    drawGrass(window);

    return 0;
}

/**
 * Function: drawForest
 * Usage: drawForest(GWindow & window)
 * ___________________________________
 *
 * Draws 10 trees of random sizes in a given range
 *
 * @param window in which will draw image
 */
void drawForest(GWindow & window){
    int stepX = WIDTH_WINDOW / NUMBER_OF_TREES_IN_FOREST;
    for(int i = 1; i < NUMBER_OF_TREES_IN_FOREST; i++){
        int step = stepX * i;
        int heightTree = randomInteger((HEIGHT_WINDOW / HEIGHT_RELATIVE_SCREEN) / 1.2, (HEIGHT_WINDOW / HEIGHT_RELATIVE_SCREEN) * 1.2);

        drawTree(step, HEIGHT_WINDOW, window, heightTree, MIN_SIZE / 4, DEGREES_DIRECTION_WOOD);
    }
}

/**
 * Function: drawGrass
 * Usage: drawGrass(GWindow & window)
 * __________________________________
 *
 * Method draws the grass and this gives aesthetic image
 *
 * @param window in which will draw image
 */
void drawGrass(GWindow & window){
    for(int i = 0; i < window.getWidth(); i += 3){
        window.setColor(GREEN_COLOR_LEAVES);
        int height = randomInteger(HEIGHT_GRASS/3, HEIGHT_GRASS/0.3);
        int angle = randomInteger(-TILT_GRASS, TILT_GRASS);
        window.drawPolarLine(i, HEIGHT_WINDOW, height, angle + DEGREES_DIRECTION_WOOD);
    }
}

/**
 * Function: drawTree
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
        size = size / REDUCTION_COEFFICIENT_BRANCH_SIZE;
        int degree = TILT_TREE;

        window.setColor(BROWN_COLOR_TREE);

        // sets green for small branches
        if (size == minSize || size < minSize * 1.5){
            window.setColor(GREEN_COLOR_LEAVES);
        }

        GPoint p = window.drawPolarLine(x, y, size, angle);

        drawTree(p.getX(), p.getY(), window, size, minSize, angle + degree);
        drawTree(p.getX(), p.getY(), window, size, minSize, angle - degree);

        // randomly selects a third branch of the draw or not. Comment out for full symmetry tree
        if(randomBool())  drawTree(p.getX(), p.getY(), window, size, minSize, angle);
    }

}
