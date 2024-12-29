#pragma once

/* Needed for ballots.cpp */
int countAllOrderings(int a, int b);
int countFavorableOrderings(int a, int b);

/* Needed for balanced.cpp */
#include <string>
bool isBalanced(std::string str);
std::string operatorsFrom(std::string str);
bool operatorsAreMatched(std::string ops);

/* Needed for sierpinski.cpp */
#include "gtypes.h"
#include "gwindow.h"
void drawOrderZero(GWindow& window, GPoint one, GPoint two, GPoint three);
int drawSierpinskiFractal(GWindow& window,
                            GPoint one, GPoint two, GPoint three,
                            int order);
void runInteractiveDemo();

/* Needed for merge.cpp */
#include "queue.h"
#include "vector.h"
Queue<int> binaryMerge(Queue<int> a, Queue<int> b);
Queue<int> naiveMultiMerge(Vector<Queue<int>>& all);
Queue<int> recMultiMerge(Vector<Queue<int>>& all);
