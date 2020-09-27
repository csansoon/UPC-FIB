#include <stdio.h>

typedef struct cell {
int acrossClue;
int downClue;
}clueCell;

void printPuzzle(int size, clueCell puzzle[size]) {
    for (int i = 0; i < size*size; i++) {
    // Not sure what to put here yet	
    }
}

int solve(int size, clueCell puzzle[size]) {
    for each cell in kakuro
	    // guess value 
	    // make guess by start at 1 and go up til valid value based on:
	    // no duplicate value in across/down runs
	    // the sum of the across run
	    // and sum of the down run
	    // if possible value can be found:
		    // move to next location
		    // repeat
	    // if location where can't find valid value
		    // move back into previous location
		    // repeat
	    // if solver makes it to last location and can find value
		    // have succeeded and have solution
	    // if go back to 1st location and can't find legal value
		    // have failed and unsolvable
}

int main() {
    int size; // store size given as input
    if (size < 2 || size > 12) {
	    printf("Invalid board size, Cross Sums terminating\n");
	    return 1;
    }
    printf("\n");
    printf("******************\n");
    printf("**  CROSS SUMS  **\n");
    printf("******************\n");
    printf("\n");
    clueCell puzzle[size*size];
    int i = 0; 				// need for indexing array
    for each line in stdin # read in puzzle
	    acrossClue = num / 100;
	    downClue = num % 100;
	    if (num == 0 || (1 <= acrossClue <= 45 || acrossClue == 99) ||
	(1 <= downClue <= 45 || downClue == 99)) {
		    clueCell new;
		    new.acrossClue = acrossClue;
		    new.downClue = downClue;
		    array[i] = new;
		    i++;
		    continue
	}
	printf("Illegal input value, Cross Sums terminating\n");
	return 1;
    printf("Initial Puzzle\n");
    printf("\n");
    printPuzzle(size*size, puzzle[size*size]);
    printf("\n");
    int s = solve(puzzle);
    if s == 1: // puzzle solvable
	    printf("Final Puzzle\n");
	    printf("\n");
	    printPuzzle(size*size, puzzle[size*size]);
	    printf("\n");
	    return 1:
    if s == 0: // unsolvable
	    printf("Impossible Puzzle\n");
	    return 1;
}