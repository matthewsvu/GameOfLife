#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

//import functions from main.cpp
vector<vector<int> > nextBoardState(vector<vector <int> > input);
void render(vector <vector<int> > const &input);

void testGame()
{
    vector<vector<int> > initialState1(20, vector<int> (30, 0)); // vector for all dead cells in matrix
    vector<vector<int> > initialState2 = { { 0, 0, 1 }, // vector for exactly 3 alive cells around a dead cell
                                           { 0, 1, 1 },
                                           { 0, 0, 0 }
    };
    vector<vector<int> > expectedState1 (20, vector<int> (30, 0));// what the game should look like
    vector<vector<int> > expectedState2 = { { 0, 1, 1 },
                                            { 0, 1, 1 },
                                            { 0, 0, 0 }
    };
    vector<vector<int> > actualState1 = nextBoardState(initialState1);
    // test for all dead cells with no live cells at all, should stay dead
    if(expectedState1 == actualState1)
    {
        cout << "PASSED TEST 1!\n";
    }
    else
    {
        cout << "FAILED TEST 1!\n" << "Expected: \n";
        render(expectedState1);
        cout << "Actual: \n";
        render(actualState1);
        cout << "\n";
    }

    // test for exactly 3 alive cells around dead cell, should make it alive
    vector<vector<int> > actualState2 = nextBoardState(initialState2);

    if(expectedState2 == actualState2) {
        cout << "PASSED TEST 2!";
    }
    else
    {
        cout << "FAILED TEST 2!\n" << "Expected: \n";
        render(expectedState2);
        cout << "Actual: \n";
        render(actualState2);
        cout << "\n";
    }

    //
}
