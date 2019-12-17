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
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

int HEIGHT = 30; // variable for height and width can change
int WIDTH = 30;
double randomFactor = 0.25; // start val for random factor; is changed by user

const int BLOCK_ASCII_SYMBOL = 254; // ascii symbol of a 'solid block'
const int ALIVE = 1; // for alive or dead
const int DEAD = 0;

int testGame(); // import from test life.cpp, remove when final game

vector <vector<int> > deadState(int height, int width)   // creates initial board with zero in all positions
{
    vector<vector<int> > state(height, vector<int> (width, 0)); // initialized vector;
    for(int i = 0; i < height; i++)   // adds 0 to positions
    {
        for(int j = 0; j < width; j++)
        {
            state[i][j] = DEAD;
        }
    }
    return state; // return vector state
}

vector<vector<int> > randomState(int height, int width)   // creates the first random stage of the board.
{
    int cellState; // 0 or 1

    vector<vector<int> > state = deadState(height, width); // calls dead state for vector
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            double randomNum =  (rand() / (float)RAND_MAX); // gets random number between 0 - 1
            if (randomNum >= randomFactor) // change this to get different random percentages.
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

// checks surrounding neighbors for aliveness, passes in the initState, newState, cell val, and current position in the board
void checkNeighbors(vector<vector <int> > initialState, vector<vector<int> > &newState, int currentCellVal, int currPosY, int currPosX)
{
    int countAlive = 0;
    for(int y = currPosY-1; y < currPosY+2; y++) // checks the y values surrounding the curr cell position
    {
        if(y < 0 || y >= HEIGHT) // makes sures y value does not go out of bound
        {
            continue;
        }
        for(int x = currPosX-1; x < currPosX+2; x++) // checks surrounding x values around curr cell pos
        {
            if(x < 0 || x >= WIDTH) // makes sure x does not go out of bound
            {
                continue;
            }
            if(y == currPosY && x == currPosX) // check to make sure we're not including ourself as a neighbor
            {
                continue;
            }
            if(initialState[y][x] == ALIVE) // increment countAlive if the surrounding cell is alive
            {
                countAlive += 1;
            }
        }
    }
    if(currentCellVal == DEAD)
    {
        if(countAlive == 3) // 3 alive cells surrounding it
        {
            newState[currPosY][currPosX] = ALIVE;
        }
    }
    else
    {
        if(countAlive < 2 || countAlive > 3)   // when it fails GOL rules set the current cell to dead
        {
            newState[currPosY][currPosX] = DEAD;
        }
        if (countAlive == 2 || countAlive == 3)  // 2 or 3 alive cells surrounding it
        {
            newState[currPosY][currPosX] = ALIVE;
        }
    }
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
vector<vector<int> > nextBoardState (vector <vector<int> > initialState, int height, int width)
{
    vector<vector<int> > newState = deadState(height, width); // init a state to work with that is separate from init state

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int currentCellVal = initialState[i][j]; // curr cell val will be 0 or 1
            checkNeighbors(initialState, newState, currentCellVal, i, j); // gives y, x coordinates, currentCellVal, and vectors to calculates neighbors
        }
    }
    return newState;
}

void render(vector <vector<int> > const &input)   // function to render the game takes in the state functions widt and height
{
    cout << endl;
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

// Makes program run forever with 100 ms intervals between renders
void runForever(vector<vector <int> > &startState)
{
    while(true)
    {
        startState = nextBoardState(startState, HEIGHT, WIDTH);
        render(startState);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// LOAD BOARD State function that will read from a file and
vector <vector <int> > loadBoardState(string fileName)
{
    ifstream finput;
    int typeCell;


    cout << "Press '1' for the Gosper Gun, '2' for the Toad\n";
    cin >> typeCell;

    switch(typeCell)
    {
    case 1:
        fileName = "gosperGun.txt";
        HEIGHT = 30;
        WIDTH = 38;
        break;
    case 2:
        fileName = "toad.txt";
        HEIGHT = 30;
        WIDTH = 12;
        break;
    default:
        cout << "Error wrong number, must be '1' or '2' \n";
        while(true)
        {
            if(typeCell == 1)
            {
                fileName = "gosperGun.txt";
                HEIGHT = 30;
                WIDTH = 38;
                break;
            }
            else if(typeCell == 2)
            {
                fileName = "toad.txt";
                HEIGHT = 30;
                WIDTH = 12;
                break;
            }
            cout << "Press '1' for the Gosper Gun, '2' for the Toad\n";
            cin >> typeCell;
        }
    }

    vector< vector <int> > fileBoard = deadState(HEIGHT, WIDTH); // creates a board that can be changed by the file content

    finput.open(fileName.c_str());
    if(!finput) // open file and check if it opens or not
    {
        cout << "Error, file \"" << fileName << "\" could not be opened" << endl;
    }
    else
    {

        for(int i = 0; i < HEIGHT; i++)
        {
            for(int j = 0; j < WIDTH; j++)
            {
                finput >> fileBoard[i][j];
            }
        }
    }
    finput.close();

    return fileBoard;
}

//setup function for board size/type and out of bound check
void setup(vector<vector <int> > startState)
{
    char chooseType;
    string fileName;

    // Run game and asks for WIDTH AND HEIGHT
    cout << "What type of board do you want? ('a' or 'b')\n"
         << " a. A randomized board \n"
         << " b. A preset board \n";
    cin >> chooseType;
    switch(chooseType)
    {
    case 'a':
        cout << "Enter the WIDTH of the cell board that is between 10 and 90\n";
        cin >> WIDTH ;
        cout << "Enter the HEIGHT of the cell board that is between 10 and 30\n";
        cin >> HEIGHT;
        if(WIDTH > 90 || WIDTH < 10 || HEIGHT > 30 || HEIGHT < 10)
        {
            while(WIDTH > 90 || WIDTH < 10 || HEIGHT > 30 || HEIGHT < 10)
            {
                cout << "Please try again, you have either a WIDTH out of the range of 10 to 90\n"
                     << "or HEIGHT out of the range of 10 to 30\n";
                cout << "Enter the WIDTH of the cell board that is between 10 and 90\n";
                cin >> WIDTH;
                cout << "Enter the HEIGHT of the cell board that is between 10 and 30\n";
                cin >> HEIGHT;
            }
            runForever(startState);
        }
        else
        {
            runForever(startState);
        }
    default:
        startState = loadBoardState(fileName);
        if(startState == deadState(HEIGHT, WIDTH))
        {
            cout << "File did not open\n";
        }
        else
        {
            runForever(startState);
        }
    }
}

// main function
int main()
{
    vector<vector <int> > startState = randomState(WIDTH, HEIGHT);

    setup(startState);
    // tests the game functionality, not working anymore after changes. fix later? program functions perfectly regardless
    //testGame();
    return 0;
}
