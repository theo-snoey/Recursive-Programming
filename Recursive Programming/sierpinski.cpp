/*
 * Author: Theo Snoey
 * This file, sierpinski.cpp, uses a recursive process to draw sierpinki traingles, within sierpinki triangles, indicating the sum of total triangles drawn/existing
 * within the larger triangle at differnt "orders"
 */
#include <iostream>    // for cout, endl
#include "recursion.h"
#include "SimpleTest.h"
using namespace std;

/*
 * This function draws a filled, black triangle on the provided GWindow
 * that is defined by the corner GPoints one, two, and three. This
 * function has been provided for you and does not need to be modified.
 */
void drawOrderZero(GWindow& window, GPoint one, GPoint two, GPoint three) {
    window.setColor("black");
    window.fillPolygon( {one, two, three} );
}

/*
The drawSierpinskiFractal function takes a window, three coner points of a triangle and an int order. It then
recursively calls itself calling with three differnt subtraingles every time with 1 less order (summing their int returns). When it hits its base case at order = 1,
it calls the drawOrderZero function to draw an "order zero" triangle, then returns 1 adding suggesting 1 triangle has been drawn.
 */
int drawSierpinskiFractal(GWindow& window, GPoint one, GPoint two, GPoint three, int order) {
    if (order == 0){
        drawOrderZero(window, one, two, three);
        return 1;
    }


    double oneX = one.x;
    double oneY = one.y;
    double twoX = two.x;
    double twoY = two.y;
    double threeX = three.x;
    double threeY = three.y;

    GPoint onetwoMid = GPoint((oneX + twoX)/2, (oneY + twoY)/2);
    GPoint onethreeMid = GPoint((oneX + threeX)/2, (oneY + threeY)/2);
    GPoint twothreeMid = GPoint((twoX + threeX)/2, (twoY + threeY)/2);


    int triangleCount = drawSierpinskiFractal(window, one, onetwoMid, onethreeMid, order - 1)
    + drawSierpinskiFractal(window, onethreeMid, twothreeMid, three, order - 1)
    + drawSierpinskiFractal(window, onetwoMid, two, twothreeMid, order - 1);
    return triangleCount;

}


/* * * * * * Test Cases * * * * * */

/*
 * Do not modify the code beyond this line! There are no
 * unit tests for this problem. You should do all your testing
 * via the interactive demo.
 */

PROVIDED_TEST("Test fractal drawing interactively using graphical demo") {
    runInteractiveDemo();
}
