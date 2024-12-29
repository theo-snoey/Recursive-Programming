/*
 * Author: Theo Snoey
 * This file uses iterative, as well as recursive methods to sort and organize (merge) multiple queues into single sorted queues.
 */
#include <iostream>    // for cout, endl
#include "queue.h"
#include "SimpleTest.h"
using namespace std;


/*
This function checkQueueSorted takes a queue 'a' of integers and returns true if it sorted in ascending order
false otherwise
*/
bool checkQueueSorted(Queue<int> a){
    int lastNum = 0;

    if (!a.isEmpty()){
        lastNum = a.peek();
    }

    else {
        return true;
    }

    while (!a.isEmpty()){
        if (a.peek() < lastNum){
            return false;
        }
        lastNum = a.dequeue();
    }
    return true;
}


/*
 This function, binaryMerge takes a sorted queue 'a' and a queue 'b' containing ints and returns a sorted
queue combining both of their elements. It calls the checkQueueSorted helper function in order to determine
whether or not the inputs are sorted.
 */
Queue<int> binaryMerge(Queue<int> a, Queue<int> b) {
    Queue<int> result;

    // error calls for queues not sorted in ascending order

    if (!checkQueueSorted(a)){
        error("Queue 'a' not sorted in ascending order");
    }

    if (!checkQueueSorted(b)){
        error("Queue 'a' not sorted in ascending order");
    }

    // loop through queue a, if b is empty add to result, if b not empty compare and add smallest value between the two

    while (!a.isEmpty()){

        if (b.isEmpty()){
            int NumA = a.dequeue();
            result.enqueue(NumA);
        }

        else {

            if (a.peek() <= b.peek()){
                int NumA = a.dequeue();
                result.enqueue(NumA);
            }

            else {
                int NumB = b.dequeue();
                result.enqueue(NumB);
            }

        }
    }

    // loop through queue b if it is not fully empty and add the remaining elements of that queue
    // to the result

    while (!b.isEmpty()){
        int NumB = b.dequeue();
        result.enqueue(NumB);
    }

    return result;
}

/*
 * The function naiveMultiMerge assumes you have a correctly working
 * binaryMerge function, which this function calls to iteratively
 * merge a collection of sequences, starting off with an empty sequence
 * and repeatedly merging in an additional sequence until all are merged.
 * The code below is provided to you is implemented correctly and you
 * should not need to modify it.
 */
Queue<int> naiveMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;

    for (Queue<int>& q : all) {
        result = binaryMerge(q, result);
    }
    return result;
}

/*
 * This function, recMultiMerge uses recursion to go through a vector of queues by continually
 * splitting a larger vector into two vectors, calling the same function on each smaller vector.
 * When base conditions are met,(we are left with 0 or 1 queues), the function returns calling
 * binary merge(our previous iterative function) for every step merging the recursive
 * sublists v1, v2
 */
Queue<int> recMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;

    if (all.size() == 0){
        return result;
    }
    if (all.size() == 1){
        return all[0];
    }

    Vector<Queue<int>> v1 = all.subList(0, all.size() / 2);
    Vector<Queue<int>> v2 = all.subList(all.size() / 2);

    Queue<int> v1Merged = recMultiMerge(v1);
    Queue<int> v2Merged = recMultiMerge(v2);

    return binaryMerge(v1Merged, v2Merged);
}


/* * * * * * Test Cases * * * * * */

Queue<int> createSequence(int size);
void distribute(Queue<int> input, Vector<Queue<int>>& all);


//____________________________STUDENT_TESTS______________________________________


STUDENT_TEST("Multiple time trials of recMultiMerge on increasing input sizes, fixed K increasing N") {
    for (int i = 1; i <= 32; i *= 2){
        int n = i * 1000000;
        int k = 10;
        Queue<int> input = createSequence(n);
        Vector<Queue<int>> all(k);
        distribute(input, all);
        TIME_OPERATION(input.size(), recMultiMerge(all));
    }
}

STUDENT_TEST("Multiple time trials of recMultiMerge on increasing input sizes, fixed N increasing K") {
    for (int i = 1; i <= 625; i *= 5){
        int n = 3500000;
        int k = 10 * i;
        Queue<int> input = createSequence(n);
        Vector<Queue<int>> all(k);
        distribute(input, all);
        TIME_OPERATION(input.size(), recMultiMerge(all));
    }
}


STUDENT_TEST("expect nativeMerge to be equal to output of recMultiMerge") {
    Vector<Queue<int>> all = {{-10, -3, 1, 4, 8},
    {5, 90},
    {},
    {},
    {1, 2},
    {3402, 5000}};
    EXPECT_EQUAL(naiveMultiMerge(all), recMultiMerge(all));
}

STUDENT_TEST("expect nativeMerge to be equal to output of recMultiMerge") {
    Vector<Queue<int>> all = {{-10, -6, -5, 0, 0},
                              {9, 12},
                              {},
                              {},
                              {1, 2},
                              {3402}};
    EXPECT_EQUAL(naiveMultiMerge(all), recMultiMerge(all));
}

STUDENT_TEST("Multiple time trials of nativeMultiMerge on increasing input sizes, fixed K increasing N") {
    for (int i = 1; i <= 16; i *= 2){
        int n = i * 1000000;
        int k = 10;
        Queue<int> input = createSequence(n);
        Vector<Queue<int>> all(k);
        distribute(input, all);
        TIME_OPERATION(input.size(), naiveMultiMerge(all));
    }
}

STUDENT_TEST("Multiple time trials of nativeMultiMerge on increasing input sizes, fixed N increasing K") {
    for (int i = 1; i <= 16; i *= 2){
        int n = 3500000;
        int k = 10 * i;
        Queue<int> input = createSequence(n);
        Vector<Queue<int>> all(k);
        distribute(input, all);
        TIME_OPERATION(input.size(), naiveMultiMerge(all));
    }
}

STUDENT_TEST("naiveMultiMerge, no queues") {
    Vector<Queue<int>> all = {};
    Queue<int> expected = {};
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

STUDENT_TEST("naiveMultiMerge, small collection of short sequences, negatives, zeros") {
    Vector<Queue<int>> all = {{-10, -6, -5, 0, 0},
        {9, 12},
        {},
        {},
        {1, 2},
        {3402}
    };
    Queue<int> expected = {-10, -6, -5, 0, 0, 1, 2, 9, 12, 3402};
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

STUDENT_TEST("Multiple time trials of Binary Merge on increasing input sizes") {
    Queue<int> a = {0};
    Queue<int> b = {0};

    for (int i = 1; i <= 8; i *= 2) {
        for (int j = 0; j < i * 40000000; j++) {
            a.enqueue(j);
            b.enqueue(j + 1);
        }
        TIME_OPERATION(a.size(), binaryMerge(a, b));
        a.clear();
        b.clear();
    }
}

STUDENT_TEST("binaryMerge, one sequence inputted then the next") {
    Queue<int> a = {6, 12, 13};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 3, 3, 6, 12, 13};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}

STUDENT_TEST("binaryMerge, negative numbers") {
    Queue<int> a = {-20, -4, 3};
    Queue<int> b = {-1, 0, 3};
    Queue<int> expected = {-20, -4, -1, 0, 3, 3};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}

STUDENT_TEST("binaryMerge, arguments not sorted") {
    Queue<int> a = {-20, -4, 3};
    Queue<int> b = {-1, 0, -4};
    Queue<int> expected = {-20, -4, -4, -1, 0, 3};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}

STUDENT_TEST("binaryMerge, arguments empty") {
    Queue<int> a = {};
    Queue<int> b = {};
    Queue<int> expected = {};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}

STUDENT_TEST("check Queue sorted, arguments sorted") {
    Queue<int> a = {-20, -4, 3};
    EXPECT(checkQueueSorted(a));
}

STUDENT_TEST("check Queue sorted, arguments not sorted") {
    Queue<int> a = {-20, 3, 1};
    EXPECT(!checkQueueSorted(a));
}

STUDENT_TEST("check Queue sorted, arguments not sorted") {
    Queue<int> a = {-1, 3, 0};
    EXPECT(!checkQueueSorted(a));
}



//____________________________PROVIDED_TESTS_____________________________________

PROVIDED_TEST("binaryMerge, two short sequences") {
    Queue<int> a = {2, 4, 5};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 4, 5};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}

PROVIDED_TEST("naiveMultiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
                             {1, 5, 9, 9, 12},
                             {5},
                             {},
                             {-5, -5},
                             {3402}
                            };
    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

PROVIDED_TEST("recMultiMerge, compare to naiveMultiMerge") {
    int n = 20;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    Queue<int> resultRec = recMultiMerge(all);
    Queue<int> resultNaive = naiveMultiMerge(all);
    EXPECT_EQUAL(resultRec.size(), input.size());
    EXPECT_EQUAL(resultRec, resultNaive);
}

PROVIDED_TEST("Time binaryMerge operation") {
    int n = 1000000;
    Queue<int> a = createSequence(n);
    Queue<int> b = createSequence(n);
    TIME_OPERATION(a.size() + b.size(), binaryMerge(a, b));
}

PROVIDED_TEST("Time naiveMultiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), naiveMultiMerge(all));
}
PROVIDED_TEST("Time recMultiMerge operation") {
    int n = 90000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}


/* Test helper to fill queue with sorted sequence */
Queue<int> createSequence(int size) {
    Queue<int> q;
    for (int i = 0; i < size; i++) {
        q.enqueue(i);
    }
    return q;
}

/* Test helper to distribute elements of sorted sequence across k sequences,
   k is size of Vector */
void distribute(Queue<int> input, Vector<Queue<int>>& all) {
    while (!input.isEmpty()) {
        all[randomInteger(0, all.size()-1)].enqueue(input.dequeue());
    }
}
