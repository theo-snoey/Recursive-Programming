/*
 * Author: Theo Snoey
 * This file uses recursive processes to count orderings of possible ballots between candidates
 *
 */
#include "recursion.h"
#include "SimpleTest.h"
using namespace std;

/*
 * this function, countAllOrderings takes two integers (ballot counts), and counts the ways that
 * the ballot votes can be ordered in succession.
 */
int countAllOrderings(int a, int b) {

    if (a == 0 && b == 0){
        return 0;
    }

    if (a == 0 || b == 0){
        return 1;
    }

    return countAllOrderings(a - 1, b) + countAllOrderings(a, b - 1);
}

/*
 * This function countFavorableOrderings takes two ballot counts, a and b, and takes a lead parameter
 * definining the spacing between the ballots cast for a and b--> when a loses the lead, an ordering is no longer
 * deemed favorable
 */
int countFavorableOrderings(int a, int b, int lead) {

    if (a == 0 && b == 0){
        return 0;
    }

    if (a == 0 || b == 0){
        if (lead <= 0){
            return 0;
        }
        return 1;
    }

    return countFavorableOrderings(a - 1, b, lead + 1) + countFavorableOrderings(a, b - 1, lead - 1);
}

/*
 * This wrapper function countFavorableOrderings takes two parameters (instead of 3) and
 * serves to call the recursive countFavorableOrderings function with the lead parameter
 * set up to work. It essentially makes the first call.
 *
 */
int countFavorableOrderings(int a, int b){
    int lead = 0;
    if (a > b){
        return countFavorableOrderings(a - 1, b, lead + 1) + countFavorableOrderings(a, b - 1, lead - 1);
    }
    return 0;
}

/*
 * Function: likelyFavorable
 * -------------------------
 * The likelihood of a favorable ordering is the ratio of the count of
 * favorable orderings over the count of all possible orderings.
 * Both a and b are required to be non-negative values.
 * Do not modify the provided code in the likelyFavorable function!
 */
double likelyFavorable(int a, int b) {
    // apply double typecast to perform real-value division
    return double(countFavorableOrderings(a, b))/countAllOrderings(a, b);
}

/* Function: bertrandTheorem
 * -------------------------
 * Betrand's ballot theorem is a closed form solution for the likelihood of
 * a favorable ordering as described above.
 * Both a and b are required to be non-negative values.
 * Do not modify the provided code in this function!
 */
double bertrandTheorem(int a, int b) {
    if (a <= b) {
        return 0;
    } else {
        return double(a - b)/(a + b);
    }
}


/* * * * * * Test Cases * * * * * */

//_____________________________STUDENT_TESTS______________________________________________

STUDENT_TEST("Bertrand's Theorem expected equal to likelyFavorable"){
    for (int i = 0; i < 6; i ++){
        int a = i * 2;
        int b = (i + 1) * 2;
        EXPECT_EQUAL(likelyFavorable(a, b), bertrandTheorem(a, b));
    }
}

STUDENT_TEST("countAllOrderings, 5 A, two B") {
    EXPECT_EQUAL(countAllOrderings(5, 2), 21);
}

STUDENT_TEST("countAllOrderings, one A, four B") {
    EXPECT_EQUAL(countAllOrderings(1, 4), 5);
}

STUDENT_TEST("countAllOrderings, zero A, zero B") {
    EXPECT_EQUAL(countAllOrderings(0, 0), 0);
}

//_____________________________PROVIDED_TESTS_____________________________________________

PROVIDED_TEST("countAllOrderings, two A one B") {
   EXPECT_EQUAL(countAllOrderings(2, 1), 3);
}

PROVIDED_TEST("countFavorableOrderings, two A one B") {
   EXPECT_EQUAL(countFavorableOrderings(2, 1), 1);
}

