#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

const int WIDTH = 5; // constant variable for height and width
const int HEIGHT = 5;

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
            int randomNum = rand() % 100; // gets random number between 0 - 1
            if (randomNum >= 50) // change this to get different random percentages.
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

void print(vector <vector<int> > const &input)   // function to print a vector
{
    for(int i = 0; i < WIDTH; i++)
    {
        for(int j = 0; j < HEIGHT; j++)
        {
            cout << input[i][j];
        }
        cout << endl;
    }
}

// main function
int main()
{
    print(randomState(WIDTH, HEIGHT)); // prints random state
    return 0;
}
