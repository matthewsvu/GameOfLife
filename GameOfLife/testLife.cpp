/*
Unit tests for the game of life
*/

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

//import functions from main.cpp
vector<vector<int> > nextBoardState(vector<vector <int> > input, int width, int height);
void render(vector <vector<int> > const &input);

void testGame()
{
    vector<vector<int> > initialState1(20, vector<int> (30, 0)); // vector for all dead cells in matrix
    vector<vector<int> > initialState2 = { { 0, 0, 1 }, // vector for exactly 3 alive cells around a dead cell
                                           { 0, 1, 1 },
                                           { 0, 0, 0 }
    };
    vector<vector<int> > initialState3 = { { 0, 0, 0 }, // vector for a single live cell becoming dead
                                           { 0, 1, 0 },
                                           { 0, 0, 0 }
    };
    vector<vector<int> > initialState4 = { { 0, 1, 0 }, // vector for more 3 live cells, thus making them dead
                                           { 0, 1, 1 },
                                           { 0, 1, 1 }
    };
    vector<vector<int> > expectedState1 (20, vector<int> (30, 0));// what the game should look like
    vector<vector<int> > expectedState2 = { { 0, 1, 1 },
                                            { 0, 1, 1 },
                                            { 0, 0, 0 }
    };
    vector<vector<int> > expectedState3 = { { 0, 0, 0 },
                                           { 0, 0, 0 },
                                           { 0, 0, 0 }
    };
    vector<vector<int> > expectedState4 = { { 0, 1, 1 },
                                           { 1, 0, 0 },
                                           { 0, 1, 1 }
    };
    vector<vector<int> > actualState1 = nextBoardState(initialState1, 20, 30 );
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
    vector<vector<int> > actualState2 = nextBoardState(initialState2, 3, 3);

    if(expectedState2 == actualState2) {
        cout << "PASSED TEST 2!\n";
    }
    else
    {
        cout << "FAILED TEST 2!\n" << "Expected: \n";
        render(expectedState2);
        cout << "Actual: \n";
        render(actualState2);
        cout << "\n";
    }

    // test for a single alive cell becoming dead
     vector<vector<int> > actualState3 = nextBoardState(initialState3, 3, 3);

    if(expectedState3 == actualState3) {
        cout << "PASSED TEST 3!" << endl;
    }
    else
    {
        cout << "FAILED TEST 3!\n" << "Expected: \n";
        render(expectedState3);
        cout << "Actual: \n";
        render(actualState3);
        cout << "\n";
    }

    // test for more than 3 cells being next to each other causing death to curr cell. Also test for
    vector<vector<int> > actualState4 = nextBoardState(initialState4, 3, 3);

    if(expectedState4 == actualState4) {
        cout << "PASSED TEST 4!\n";
    }
    else
    {
        cout << "FAILED TEST 4!\n" << "Expected: \n";
        render(expectedState4);
        cout << "Actual: \n";
        render(actualState4);
        cout << "\n";
    }

}
