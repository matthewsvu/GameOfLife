# GameOfLife
 A mathematical zero player game called Conway's game of life. This program simulates it.
 

Cell will die and procreate with each other by a certain set of rules listed below eternally.

    1. Any live cell with 0 or 1 live neighbors becomes dead, because of underpopulation
    
    2. Any live cell with 2 or 3 live neighbors stays alive, because its neighborhood is just right
    
    3. Any live cell with more than 3 live neighbors becomes dead, because of overpopulation
    
    4. Any dead cell with exactly 3 live neighbors becomes alive, by reproduction
 
 Change the const int vars 'WIDTH' and 'HEIGHT' to get a larger or smaller board size.
 
 Change the randomState function to get a higher or lower occurences of alive cells.
 
 Most importantly have fun with your combinations!
