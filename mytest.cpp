/*
    Title: mytest.cpp
    Author: Jason Rojas
    Section: 04
    E-mail: jasonr2@umbc.edu
    Date: 9/12/2023
    Description: This is the test file for bingo.cpp
*/

#include "bingo.h"

const string  FAIL_STATEMENT = "*****TEST FAILED: ";
const string  PASS_STATEMENT = "*****TEST PASSED: ";

class Tester{
    public:
    // This function is a sample test function
    // It shows how to write a test case 
    bool assignmentNormal(Bingo & lhs, Bingo & rhs){
        // we expect that lhs object is an exact copy of rhs object 
        bool result = true;
        // we expect that the corresponding cells in lhs and rhs
        //      cards carry the same cell information (exact same copy)
        for (int i=0;i<rhs.m_numRows;i++){
            for (int j=0;j<rhs.m_numCols;j++){
                result = result && (lhs.m_card[i][j] == rhs.m_card[i][j]);
            }
        }
        // we expect that the corresponding cells in lhs and rhs
        //      m_helper carry the same cell information (exact same copy)
        for (int i=0;i<rhs.m_helperSize;i++){
            result = result && (lhs.m_helper[i] == rhs.m_helper[i]);
        }
        // we expect that the corresponding cells in lhs and rhs
        //      m_trackRows carry the same cell information (exact same copy)
        for (int i=0;i<rhs.m_numRows;i++){
            result = result && (lhs.m_trackRows[i] == rhs.m_trackRows[i]);
        }
        // we expect that the corresponding cells in lhs and rhs
        //      m_trackCols carry the same cell information (exact same copy)
        for (int i=0;i<rhs.m_numCols;i++){
            result = result && (lhs.m_trackCols[i] == rhs.m_trackCols[i]);
        }
        result = result && (lhs.m_minBallVal == rhs.m_minBallVal);
        result = result && (lhs.m_maxBallVal == rhs.m_maxBallVal);
        return result;
    }

    bool emptyObjTest(Bingo obj){
        if (obj.m_helperSize == 0){
            return false;
        }
        else{
            return true;
        }
    }

    
    private:
    
    /**********************************************
    * If we need helper functions to be reused in *
    *   test functions they can be declared here!
    **********************************************/
};

int main(){
    Tester tester;

    // TEST CASES FOR OVERLOADED CONSTRUCTOR

    //testing ERROR case of overloaded constructor
    Bingo obj1(-5, 5, MINVAL, MAXVAL);
    if(tester.emptyObjTest(obj1)){
        cout << "Test ERROR case of overloaded constructor msg: created object is initialized " << FAIL_STATEMENT <<endl;
    }
    else{
        cout << "Test ERROR case of overloaded constructor msg: created empty object " << PASS_STATEMENT <<endl;
    }
    cout << endl;
    //testing EDGE case of overloaded constructor
    Bingo obj2(2, 5, MINVAL, MAXVAL);
    if(tester.emptyObjTest(obj2)){
        cout << "Test EDGE case of overloaded constructor msg: created object is initialized " << PASS_STATEMENT <<endl;
    }
    else{
        cout << "Test EDGE case of overloaded constructor msg: created object is initialized " << FAIL_STATEMENT <<endl;
    }
    cout << endl;
    //testing NORMAL case of overloaded constructor
    Bingo obj3(10, 5, MINVAL, MAXVAL);
    if(tester.emptyObjTest(obj3)){
        cout << "Test NORMAL case of overloaded constructor msg: created object is initialized " << PASS_STATEMENT <<endl;
    }
    else{
        cout << "Test NORMAL case of overloaded constructor msg: created object is initialized " << FAIL_STATEMENT <<endl;
    }
    cout << endl;
    //testing NORMAL case of range being divisible by 5
    Bingo obj4(10, 5, 6, 80);
    if(tester.emptyObjTest(obj4)){
        cout << "Test NORMAL case of range being divisible by 5 msg: created object is initialized " << PASS_STATEMENT <<endl;
    }
    else{
        cout << "Test NORMAL case of range being divisible by 5 msg: created object is initialized " << FAIL_STATEMENT <<endl;
    }
    cout << endl;
    //testing ERROR case of range not being divisible by 5
    Bingo obj5(10, 5, 24, 82);
    if(tester.emptyObjTest(obj5)){
        cout << "Test ERROR case of range not being divisible by 5 msg: created object is initialized " << FAIL_STATEMENT <<endl;
    }
    else{
        cout << "Test ERROR case of range not being divisible by 5 msg: created empty object " << PASS_STATEMENT <<endl;
    }
    cout << endl;

    //TEST CASES FOR reCreateCard
    //should return false for invalid parameters
    if (obj1.reCreateCard(-5, -10, MINVAL, MAXVAL)){
        cout << "Test invalid parameter test for reCreateCard msg: created object is initialized " << FAIL_STATEMENT <<endl;
    }
    else{
        cout << "Test invalid parameter test for reCreateCard msg: created object is initialized " << PASS_STATEMENT <<endl;
    }
    cout << endl;
    //Testing edge cases for reCreateCard if obj is initialized it passes
    if (obj1.reCreateCard(2, 5, MINVAL, MAXVAL)){
        cout << "Test edge cases for reCreateCard msg: created object is initialized " << PASS_STATEMENT <<endl;
    }
    else{
        cout << "Test edge cases for reCreateCard msg: created object is empty " << FAIL_STATEMENT <<endl;
    }
    cout << endl;
    //Testing edge cases for reCreateCard if obj is initialized it passes
    if (obj1.reCreateCard(15, 5, MINVAL, MAXVAL)){
        cout << "Test edge cases for reCreateCard msg: created object is initialized " << PASS_STATEMENT <<endl;
    }
    else{
        cout << "Test edge cases for reCreateCard msg: created object is empty " << FAIL_STATEMENT <<endl;
    }
    cout << endl;
    //Testing NORMAL case for reCreateCard
    if (obj1.reCreateCard(10, 5, MINVAL, MAXVAL)){
        cout << "Test NORMAL case for reCreateCard msg: created object is initialized " << PASS_STATEMENT <<endl;
    }
    else{
        cout << "Test NORMAL case for reCreateCard msg: created object is empty " << FAIL_STATEMENT <<endl;
    }
    cout << endl;
    //Testing Col value that isn't 5 should return false to passs
    if (obj1.reCreateCard(10, 6, MINVAL, MAXVAL)){
        cout << "Test Col value that isn't 5 msg: created object is initialized " << FAIL_STATEMENT <<endl;
    }
    else{
        cout << "Test Col value that isn't 5 msg: created object is empty " << PASS_STATEMENT <<endl;
    }
    cout << endl;

    //TEST CASES FOR inItCard()
    //Error cases should return false when given an empty object
    obj1.clear();
    if (obj1.initCard()){
        cout << "Test call inItCard on a blank object msg: obj is initialized " << FAIL_STATEMENT <<endl;
    }
    else{
        cout << "Test call inItCard on a blank object msg: returns False " << PASS_STATEMENT <<endl;
    }
    //NORMAL case should return true when initializing
    if (obj2.initCard()){
        cout << "Test call inItCard on an object msg: obj is initialized " << PASS_STATEMENT <<endl;
    }
    else{
        cout << "Test call inItCard on an object msg: returns False " << FAIL_STATEMENT <<endl;
    }

    //TEST CASES FOR play()
    randNumArr[BALLS];
    for (int i = 0; i < BALLS; i++){
        randNumArr[i] = 0;
    }
    if ()
    //test error case 
    return 0;
}