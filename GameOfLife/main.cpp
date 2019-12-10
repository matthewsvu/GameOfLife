#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

const int WIDTH = 10; // constant variable for height and width
const int HEIGHT = 10;
const int BLOCK_ASCII_SYMBOL = 254;

vector <vector<int> > deadState(int width, int height)   // creates initial board with zero in all positions
{
    vector<vector<int> > state(width, vector<int> (height, 0)); // initialized vector;
    for(int i = 0; i < width; i++)   // adds 0 to positions
    {
        for(int j = 0; j < height; j++)
        {
            state[i][j] = 0;
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
                cellState = 0;
            }
            else
            {
                cellState = 1;
            }
            state[i][j] = cellState; // set state equal 0 or 1
        }
    }
    return state;
}

void render(vector <vector<int> > const &input, int width, int height)   // function to render the game takes in the state functions
{
    cout << endl; // newline
    for(int i = 0; i < width; i++) // loops through 2d array
    {
        for(int j = 0; j < height; j++)
        {
            if(j == 0) // outputs every row for formatting
            {
                cout << '|';
            }

            if(input[i][j] == 0) { // outputs d for dead
            cout << 'd' << " ";
            }
            else if (input[i][j] == 1) // outputs a block ascill symbol if alive
            {
                cout << (char)(BLOCK_ASCII_SYMBOL) << " ";
            }
            if(j+1 == height) // outputs every row before end of columns
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
    render(randomState(30, 30), 30, 30); // prints random state

    return 0;
}
