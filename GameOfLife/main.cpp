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
#include <chrono>
#include <thread>

using namespace std;

int WIDTH = 20; // variable for height and width can change
int HEIGHT = 20;

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

vector<vector<int> > randomState(int width, int height)   // creates the first random stage of the board.
{
    int cellState; // 0 or 1

    vector<vector<int> > state = deadState(width, height); // calls dead state for vector
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            double randomNum =  (rand() / (float)RAND_MAX); // gets random number between 0 - 1
            if (randomNum >= 0.18) // change this to get different random percentages.
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

Have to figure out when a cell is at a corner or edge (3 neighbors or 5 neighbors)
Day 3: Refactor code, add logic for edge cases (literally)
*/
vector<vector<int> > nextBoardState (vector <vector<int> > initialState, int width, int height)
{
    int countAlive; // counts how many cells are alive around the current position

    vector<vector<int> > newState = deadState(width, height); // initializes the a board filled with dead cells that will be used as a reference
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            countAlive = 0;
            bool isDeadCorner = false, isAliveCorner = false; // flag used to find the cell is currently alive or dead in a corner
            int currentCellVal = initialState[i][j];
            // have to check if corner or edge first....
            if(i == 0 || j == 0 || i == width - 1 || j == height - 1)
            {
                if(i == 0 && j == 0 && currentCellVal == DEAD) // checks for a dead cell in the top left corner
                {
                    if(initialState[i+1][j] == ALIVE )
                    {
                        countAlive++;
                    }
                    if(initialState[i][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    isDeadCorner = true;
                }
                if(i == 0 && j == 0 && currentCellVal == ALIVE) // checks for alive cell in top left corner
                {
                    if(initialState[i+1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    isAliveCorner = true;
                }
                if(i == width - 1 && j == 0 && currentCellVal == DEAD) // checks for a dead cell in the top right corner
                {
                    if(initialState[i-1][j] == ALIVE )
                    {
                        countAlive++;
                    }
                    if(initialState[i-1][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    isDeadCorner = true;
                }
                if(i == width - 1 && j == 0 && currentCellVal == ALIVE) // checks for alive cell in top right corner
                {
                    if(initialState[i-1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i-1][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    isAliveCorner = true;
                }
                if(i == 0 && j == height - 1 && currentCellVal == DEAD) // checks for a dead cell in the bottom left corner
                {
                    if(initialState[i][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    isDeadCorner = true;
                }
                if(i == 0 && j == height - 1 && currentCellVal == ALIVE) // checks for alive cell in bottom left corner
                {
                    if(initialState[i][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    isAliveCorner = true;
                }
                if(i == width - 1 && j == height - 1 && currentCellVal == DEAD) // checks for a dead cell in the bottom right corner
                {
                    if(initialState[i-1][j-1] == ALIVE  )
                    {
                        countAlive++;
                    }
                    if(initialState[i-1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    isDeadCorner = true;
                }
                if(i == width - 1 && j == height - 1 && currentCellVal == ALIVE) // checks for alive cell in bottom right corner
                {
                    if(initialState[i-1][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i-1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    isAliveCorner = true;
                }
                // start of edge cases
                if(i == 0 && j > 0 && j < height - 1 )   // dead cell, left hand edge
                {
                    if(initialState[i][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(currentCellVal == DEAD)
                    {
                        isDeadCorner = true;
                    }
                    else
                    {
                        isAliveCorner = true;
                    }
                }
                if(i > 0 && j == 0 && i < width - 1)   // dead cell, upper hand edge
                {
                    if(initialState[i-1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i-1][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(currentCellVal == DEAD)
                    {
                        isDeadCorner = true;
                    }
                    else
                    {
                        isAliveCorner = true;
                    }
                }

                if(i == width - 1 && j > 0 && j < height - 1)   // dead cell, right hand edge
                {
                    if(initialState[i][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i-1][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i-1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i-1][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(currentCellVal == DEAD)
                    {
                        isDeadCorner = true;
                    }
                    else
                    {
                        isAliveCorner = true;
                    }
                }
                if(i > 0 && j == height - 1 && i < width - 1)   // dead cell, bottom hand edge
                {
                    if(initialState[i-1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i-1][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(currentCellVal == DEAD)
                    {
                        isDeadCorner = true;
                    }
                    else
                    {
                        isAliveCorner = true;
                    }
                }
            }

            else // if its a normal case i.e 8 neighbors
            {
                if(currentCellVal == DEAD) // when it finds dead cell in normal case
                {
                    // TODO: Make a function that does what this block of code does.
                    if(initialState[i-1][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i-1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i-1][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(countAlive == 3) // 3 alive cells surrounding it
                    {
                        newState[i][j] = ALIVE;
                    }
                }
                if (currentCellVal == ALIVE) // when it finds alive cell in normal case
                {
                    // TODO: Make a function that does what this block of code does.
                    if(initialState[i-1][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i-1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j-1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i+1][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(initialState[i-1][j+1] == ALIVE)
                    {
                        countAlive++;
                    }
                    if(countAlive == 0 || countAlive == 1 || countAlive > 3)   // when it fails GOL rules set the current cell to dead
                    {
                        newState[i][j] = DEAD;
                    }
                    if (countAlive == 2 || countAlive == 3)  // 2 or 3 alive cells surrounding it
                    {
                        newState[i][j] = ALIVE;
                    }
                }
            }
            if(isDeadCorner == true && isAliveCorner == false)
            {
                if(countAlive == 3) // set current cell to alive when 3 around it are alive
                {
                    newState[i][j] = ALIVE;
                }
            }
            if(isDeadCorner == false && isAliveCorner == true)
            {
                if(countAlive == 0 || countAlive == 1 || countAlive > 3)   // when it fails GOL rules set the current cell to dead
                {
                    newState[i][j] = DEAD;
                }
                if (countAlive == 2 || countAlive == 3)  // 2 or 3 alive cells surrounding it
                {
                    newState[i][j] = ALIVE;
                }
            }
        }
    }
    return newState;
}

void render(vector <vector<int> > const &input)   // function to render the game takes in the state functions width and height
{
    cout << endl; // newline
    for(unsigned int i = 0; i < input.size(); i++) // loops through 2d array
    {
        for(unsigned int j = 0; j < input[i].size(); j++)
        {
            if(input[i][j] == DEAD)   // outputs a space for dead
            {
                cout << ' ';
            }
            else if (input[i][j] == ALIVE) // outputs a block ascii symbol if alive
            {
                cout << (char)(BLOCK_ASCII_SYMBOL);
            }
        }
        cout << endl;
    }
}

// main function
int main()
{
    // TODO: Try to make the gosper gun work.
    vector<vector <int> > gosperGun = {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };
    vector<vector <int> > startState = randomState(WIDTH, HEIGHT);

    // Run game and asks for WIDTH AND HEIGHT
    cout << "Enter the WIDTH of the cell board that is between 15 and 30\n";
    cin >> WIDTH ;
    cout << "Enter the HEIGHT of the cell board that is between 15 and 70\n";
    cin >> HEIGHT;

    if(WIDTH > 30 || WIDTH < 15 || HEIGHT > 70 || HEIGHT < 15)
    {
        while(WIDTH > 30 || WIDTH < 15 || HEIGHT > 70 || HEIGHT < 15) {
            cout << "Please try again, you have a number out of the range of 15 to 70\n";
            cout << "Enter the WIDTH of the cell board that is between 15 and 30\n";
            cin >> WIDTH;
            cout << "Enter the HEIGHT of the cell board that is between 15 and 70\n";
            cin >> HEIGHT;
        }
        while(true) // infinite loop for rendering the next board state
        {
            startState = nextBoardState(startState, WIDTH, HEIGHT);
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            render(startState);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }
    else
    {
        while(true) // infinite loop for rendering the next board state
        {
            startState = nextBoardState(startState, WIDTH, HEIGHT);
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            render(startState);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }

    // tests the game functionality, remove comment if you want to test
    // testGame();
    return 0;
}
