/*
 * Author: Theo Snoey
 * This file has functions that look at the operators present in a string and work together to determine whether or not the
 * string has balanced (in pairs) brackets, curly braces, and parentheses.
 */
#include <iostream>    // for cout, endl
#include "strlib.h"
#include "recursion.h"
#include "SimpleTest.h"

using namespace std;

/*
 This function operatorsFrom takes a string and uses recursive function calling to strip that string of
its non-operator parts, returning only the sequence of operators as a string
 */
string operatorsFrom(string str) {

    if (str == ""){
        return "";
    }

// if the string contains only 1 character and is an operator return the string, else return an empty string - no operator
    if (str.length() == 1){
        if (str[0] == '{' || str[0] == '}' || str[0] == '(' || str[0] == ')' || str[0] == '[' || str[0] == ']'){
            return str;
        }
        return "";
    }

// check if the first character of the string is an operator, is so call this function recursively without the first string
    if (str[0] == '{' || str[0] == '}' || str[0] == '(' || str[0] == ')' || str[0] == '[' || str[0] == ']'){
        return str[0] + operatorsFrom(str.substr(1));
    }

// if the first char of the string is not an oeprator, call the function recursively without the first char and without saving the fist char
    else{
        return operatorsFrom(str.substr(1));
    }
}



/*
This function, operatorsAreMatched, in given a string of operators and goes through that string and recursively looks for pairs of like
operators removing them from the string upon confirmation and recalling the function with the new substring. When there are no more operators,
ex: the function returns true, any other scenario returns false.
 */
bool operatorsAreMatched(string ops) {

    if (ops == ""){
        return true;
    }

    if (stringContains(ops, "{}")){
        return operatorsAreMatched(ops.erase(stringIndexOf(ops, "{}"), 2));
    }

    if (stringContains(ops, "()")){
        return operatorsAreMatched(ops.erase(stringIndexOf(ops, "()"), 2));
    }

    if (stringContains(ops, "[]")){
        return operatorsAreMatched(ops.erase(stringIndexOf(ops, "[]"), 2));
    }

    return false;
}


/*
 * The isBalanced function assumes correct implementation of
 * the above two functions operatorsFrom and operatorsMatch.
 * It uses operatorsFrom to extract the operator characters
 * from the input string and then confirms that those
 * operators are balanced by using operatorsMatch.
 * You should not modify the provided code in the isBalanced
 * function.  If the previous two functions have been implemented
 * correctly, the provided isBalanced will correctly report whether
 * the input string has balanced bracketing operators.
 */
bool isBalanced(string str) {
    string ops = operatorsFrom(str);
    return operatorsAreMatched(ops);
}


/* * * * * * Test Cases * * * * * */

//_______________________________STUDENT_TESTS_______________________________________

STUDENT_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("{3}{4}{5}"), "{}{}{}");
}

STUDENT_TEST("operatorsFrom on string with no operators") {
    EXPECT_EQUAL(operatorsFrom("17283729832"), "");
}

STUDENT_TEST("operatorsFrom on empty string") {
    EXPECT_EQUAL(operatorsFrom(""), "");
}

STUDENT_TEST("operatorsFrom on edge operators") {
    EXPECT_EQUAL(operatorsFrom("{........}"), "{}");
}

STUDENT_TEST("operatorsAreMatched on simple example") {
    EXPECT(operatorsAreMatched("{([])}"));
}

STUDENT_TEST("!operatorsAreMatched on simple example") {
    EXPECT(!operatorsAreMatched("{[])}"));
}

STUDENT_TEST("!operatorsAreMatched a single bracket") {
    EXPECT(!operatorsAreMatched("{"));
}

STUDENT_TEST("operatorsAreMatched on an empty string") {
    EXPECT(operatorsAreMatched(""));
}


//_______________________________PROVIDED_TESTS______________________________________

PROVIDED_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("vec[3]"), "[]");
}

PROVIDED_TEST("operatorsAreMatched on simple example") {
    EXPECT(operatorsAreMatched("{}"));
}

PROVIDED_TEST("isBalanced on example from writeup") {
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    EXPECT(isBalanced(example));
}

PROVIDED_TEST("isBalanced on non-balanced examples from writeup") {
    EXPECT(!isBalanced("( ( [ a ] )"));
    EXPECT(!isBalanced("3 ) ("));
    EXPECT(!isBalanced("{ ( x } y )"));
}
