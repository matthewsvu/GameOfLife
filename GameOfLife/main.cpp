/**
Program will simulate Conway's Game of Life, a zero player game that has cells that
die and procreate with each other by a certain set of rules listed below eternally.
@Param
    1. Any live cell with 0 or 1 live neighbors becomes dead, because of underpopulation
    2. Any live cell with 2 or 3 live neighbors stays alive, because its neighborhood is just right
    3. Any live cell with more than 3 live neighbors becomes dead, because of overpopulation
    4. Any dead cell with exactly 3 live neighbors becomes alive, by reproduction
*/

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

const int WIDTH = 10; // constant variable for height and width
const int HEIGHT = 10;
const int BLOCK_ASCII_SYMBOL = 254; // ascii symbol of a 'solid block'
const int ALIVE = 1; // for alive or dead
const int DEAD = 0;

int testGame(); // import from test life.cpp, remove when final game
vector <vector<int> > deadState(int width, int height)   // creates initial board with zero in all positions
{
    vector<vector<int> > state(width, vector<int> (height, 0)); // initialized vector;
    for(int i = 0; i < width; i++)   // adds 0 to positions
    {
        for(int j = 0; j < height; j++)
        {
            state[i][j] = DEAD;
        }
    }
    return state; // return vector state
}

vector<vector<int> > randomState(int width, int height)   // creates the first stage of the board.
{
    int cellState; // 0 or 1

    vector<vector<int> > state = deadState(width, height); // calls dead state for vector
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            double randomNum =  (rand() / (float)RAND_MAX); // gets random number between 0 - 1
            if (randomNum >= 0.2) // change this to get different random percentages.
            {
                cellState = DEAD; // set to 0
            }
            else
            {
                cellState = ALIVE; // set to 1
            }
            state[i][j] = cellState; // set state equal 0 or 1
        }
    }
    return state;
}

// Function that calculates the state of the next board using the game of life's rules.
/* @Pseudo code
create a int var called countAlive = 0
Loop through the vector and when it encounters a '1' or alive cell, check the surrounding cells
for a alive cell or dead cell, if it finds an alive cell increment countAlive by 1
After checking the surrounding cells if countAlive is 0-1 set that position in the matrix = to 0 or 'dead'
if countAlive is 2 or 3 then don't do anything
if countAlive is greater than 3 set = to 0 or 'dead'

In the case of a dead cell check if the surrounding cells have 3 alive neighbors
if there are exactly three alive neighbors set it equal to alive or '1'
else do nothing

Have to figure out when a cell is at a corner or edge
*/
vector<vector<int> > nextBoardState (vector <vector<int> > initialState)
{
    vector<vector<int> > newState = deadState(20, 30);

    return newState;
}

void render(vector <vector<int> > const &input)   // function to render the game takes in the state functions width and height
{
    cout << endl; // newline
    for(unsigned int i = 0; i < input.size(); i++) // loops through 2d array
    {
        for(unsigned int j = 0; j < input[i].size(); j++)
        {
            if(j == 0) // outputs a '\' every row for formatting
            {
                cout << '|';
            }

            if(input[i][j] == DEAD)   // outputs a space for dead
            {
                cout << ' ' << " ";
            }
            else if (input[i][j] == ALIVE) // outputs a block ascii symbol if alive
            {
                cout << (char)(BLOCK_ASCII_SYMBOL) << " ";
            }
            if(j+1 == input[i].size() ) // outputs a '|' in every row before end of columns
            {
                cout << '|';
            }
        }
        cout << endl;
    }
}

// main function
int main()
{
    //render(nextBoardState(randomState(20,30)));
    testGame(); // tests the game functionality
    return 0;
}
