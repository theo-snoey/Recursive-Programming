#include <iostream>
#include "console.h"
#include "SimpleTest.h"
#include "recursion.h"
using namespace std;

/*
 * You are free to edit the main in any way that works
 * for your testing/debugging purposes.
 * We will supply our own main() during grading
 */

int main() {
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }
    cout << endl << "main() completed." << endl;
    return 0;
}


// Do not remove or edit below this line. It is here to confirm that your code
// conforms to the expected function prototypes needed for grading
void confirmFunctionPrototypes() {
    string str;
    int i = 0;
    i = countAllOrderings(i, i);
    i = countFavorableOrderings(i, i);
    if (isBalanced(str)) {}
    str = operatorsFrom(str);
    if (operatorsAreMatched(str)) {}
    GPoint pt;
    GWindow win;
    drawSierpinskiFractal(win, pt, pt, pt, i);
    Queue<int> q;
    Vector<Queue<int>> v;
    q = binaryMerge(q, q);
    q = naiveMultiMerge(v);
    q = recMultiMerge(v);
}
