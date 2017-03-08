
/* Tic Tac Toe -- Version 2

   This is a simple program to play Tic-tac-toe.  It
   uses minimax with alpha-beta pruning.  The default
   depth of the pruning is 4.  See function max and
   min for more details.
*/

#include <stdio.h>
#include<stdlib.h>


/* Each operator acts on a certain row and certain column */

typedef struct _Operator {
    int row, col;
} Operator;

/*
   Each call to max or to min returns a Move structure.
   The "op" field of the Move structure contains the best
   operation or worst operation for the computer.  The
   value field indicates how bad or how good the "op"
   is the computer.
*/

typedef struct _Move {
    Operator op;
    int value;
} Move;

/* The state of the game is represented by showing
   the state of each cell.  If the cell contains a 0,
   we assume it is a blank, if the cell contains a 1,
   we assume it is an X, if the cell contains a 2, we
   assume it contains an O.  User is X, program is O.
*/

typedef struct _State {
    int cell[3][3];
} State;

/* In this program, the human always plays first (X), the
   computer plays second (O)
*/

#define	BLANK	0
#define	Prog	1
#define	PROGRAM	2
#define TIE     3
#define MAXEVAL 1000

Move max ( State s, int d, int alpha, int beta );
Move min ( State s, int d, int alpha, int beta );
void initialize_state ( State *s );
int isTerminal ( State s );
int isValid ( State s, Operator O );
int makeMove ( State *s, Operator O, int who );
void print_state ( State s );


/* The main program.  Here is the algorithm for the main program:

   1.  Intialize the current state to all blanks.
   2.  Find out who goes first.
   3.  Repeat
          If it is the user's turn
               Ask the user for move.
               Make the move (if valid), to get new current state.
               Next turn for program

          Else it is the program's turn
               Determine best move
               Make move
               Next turn to user

          Print new state

          If Terminal state, then state winner, or tie.  Stop.

       Until current state is terminal.
*/

int main (int argc, char*argv[]) {

    State current;
    Operator O;
    Move m;
    int done;
    int turn;

    initialize_state ( &current );

    do {
       printf("Who should go first?  (1=Prog 2=Program): ");
       scanf("%d", &turn);
    } while ( ( turn != Prog ) && ( turn != PROGRAM ) );

   // print_state ( current );

    do {
    	
        if (turn == Prog) {

          /* do {
  	       printf("Please input your move: ");

	       printf("Row (1-3): ");
	       scanf("%d", &O.row);

	       printf("Column (1-3): ");
	       scanf("%d", &O.col);

	       O.row--;
	       O.col--;
	   } while ( ! isValid ( current, O ) );*/

  	       m = max ( current, 0, -MAXEVAL, MAXEVAL );

   	   makeMove ( &current, m.op, Prog );

           turn = PROGRAM;
	}

        else {        /* program's turn */

           m = max ( current, 0, -MAXEVAL, MAXEVAL );

   	   makeMove ( &current, m.op, PROGRAM );

           turn = Prog;

	}

        print_state ( current );

	if ( done = isTerminal ( current ) ) {
            if ( done == Prog )
    	         printf("System 1 wins!\n");
            else if ( done == PROGRAM )
                 printf("System 2 wins!\n"); 
            else
                 printf("Tie!\n");

            print_state ( current );
	    exit(0);
	}

    } while ( ! isTerminal ( current ) );

}


/* Function initialize_state: Initializes all cells to BLANK */

void initialize_state ( State *current ){
    int i, j;

    for (i=0; i<3; i++)
	for (j=0;j<3;j++)
	    current->cell[i][j] = BLANK;
}


/* Function isValid: returns 1 if move is valid, 0 otherwise */

int isValid ( State s, Operator O ){

    if ( ( O.row > 2 ) || ( O.row < 0 ) ||
        ( O.col > 2 ) || ( O.col < 0 ) )
	return 0;

    if ( s.cell[O.row][O.col] == BLANK )
	return 1;
    else
	return 0;
}


/* Function makeMove: makes the indicated move.  Returns 1 if
   successful, 0 otherwise.
*/

int makeMove ( State *s, Operator O, int who ){
    if ( ! isValid ( *s, O ) )
	return 0;

    s->cell[O.row][O.col] = who;

    return 1;
}


/* Function isTerminal:  

       Returns 1 (USER) if the state is a terminal state (human won)
       Returns 2 (PROGRAM) if the state is a terminal state (program won)
       Returns 3 (TIE) if the state is a terminal state (neither won)
       Returns 0 otherwise.

   It checks if any row contains 3 non-BLANK entries of the same type.
   It checks if any col contains 3 non-BLANK entries of the same type.
   If any of the two diagonals contains 3 non-BLANK entries of the same type.
*/

int isTerminal ( State s ){
    int line;
    int row, col;

    for ( line = 0; line < 3; line++ ){

	/* Check for a row completion */

	if ( ( s.cell[line][0] != BLANK ) &&
	    ( s.cell[line][0] == s.cell[line][1] ) &&
	    ( s.cell[line][1] == s.cell[line][2] ) )

	    if ( s.cell[line][0] == 'X')
                 return Prog;
            else
                 return PROGRAM;

	/* Check for a column completion */

	if ( ( s.cell[0][line] != BLANK ) &&
	    ( s.cell[0][line] == s.cell[1][line] ) &&
	    ( s.cell[1][line] == s.cell[2][line] ) )

	    if ( s.cell[0][line] == 'X')
                 return Prog;
            else
                 return PROGRAM;
    }

    /* Check for leading diagonal */

    if ( ( s.cell[0][0] != BLANK ) &&
        ( s.cell[0][0] == s.cell[1][1] ) &&
        ( s.cell[1][1] == s.cell[2][2] ) )

            if ( s.cell[0][line] == 'X')
                return Prog;
            else
                 return PROGRAM;

    /* Check for other diagonal */

    if ( ( s.cell[0][2] != BLANK ) &&
        ( s.cell[0][2] == s.cell[1][1] ) &&
        ( s.cell[1][1] == s.cell[2][0] ) )

	    if ( s.cell[0][line] == 'X')
                 return Prog;
            else
                 return PROGRAM;

    for ( row = 0 ; row < 3; row ++ )
        for ( col = 0 ; col < 3 ; col ++ )
            if ( s.cell[row][col] == BLANK )
                return 0;

    return TIE;
}


/*  function print_state:  prints the status of the board */

void print_state ( State s ){
    int i, j, i1;

    for (i1=0; i1<13; i1++)
	printf("-");

    puts("");

    for (i=0; i<3; i++ ){
	for (j=0;j<3;j++)
	    switch (s.cell[i][j]){
	    case BLANK: 
		printf("|   "); 
		break;
	    case Prog:  
		printf("| X "); 
		break;
	    case PROGRAM: 
		printf("| O ");
		break;
	    }
	printf("|\n");
	for (i1=0; i1<13; i1++)
	    printf("-");

	puts("");
    }
}


/* function eval:  provides information about the "goodness" of state
   for the program.  Is used by max and min function.
*/

int eval ( State s );

int max_depth=4;  /* how deep the search can go */

/* Function undo:  undoes the effect of the given operator */

void undo (State *s, Operator O);

/* Function max:  Takes as input the current state and a depth measure
   d and returns the best Move by looking at all moves within the maximum 
   permitted search depth of max_depth.

   Compare this to the MAX_VALUE function in Russell and Norvig.

   Here is the algorithm for max (min is similar):

   1.  If we have reached the maximum possible depth or if the state is terminal
          return the value of the state
   2.  For each possible row, column pair
       a.  If is valid to place a mark in the (row,column) cell
           A. make the move
           B. call min to find how good the move is
           C. If min says that it is better than the best move so far, note it.
           D. If alpha is greater than beta cutoff, return it
   3.  Return the best move

*/

Move max ( State s, int d, int alpha, int beta ){
    Move m, bestmove;
    Operator O;
    int i, j;

    if ( (d == max_depth) || ( isTerminal (s) )){
	m.value = eval (s);
	return m;
    }

    bestmove.value = alpha;

    for (i=0; i<3; i++)
	for (j=0; j<3; j++){
	    O.row = i;
	    O.col = j;
	    if ( isValid (s, O) ){
		makeMove ( &s, O, PROGRAM );
		m = min ( s, d + 1, bestmove.value, beta );
		undo (&s, O );
		if ( m.value > bestmove.value ){
		    bestmove.value=m.value;
		    bestmove.op.row = i;
		    bestmove.op.col = j;
                    if ( m.value > beta ){
                        bestmove.value = beta;
                        return bestmove;
                    }
		}
	    }
	}

    return bestmove;
}


Move min ( State s, int d, int alpha, int beta ){
    Move m, bestmove;
    Operator O;
    int i, j;


    if ( (d == max_depth) || ( isTerminal (s) )){
	m.value = eval (s);
	return m;
    }

    bestmove.value = beta;

    for (i=0; i<3; i++)
	for (j=0; j<3; j++){
	    O.row = i;
	    O.col = j;
	    if ( isValid (s, O) ){
		makeMove ( &s, O, Prog );
		m = max ( s, d + 1, alpha, bestmove.value );
		undo (&s, O );
		if ( m.value < bestmove.value ){
		    bestmove.value=m.value;
		    bestmove.op.row = i;
		    bestmove.op.col = j;
                    if ( m.value < alpha ){
                        bestmove.value = alpha;
                        return bestmove;
                    }
		}
	    }
	}

    return bestmove;
}



void undo ( State *s, Operator O ){
    if ( ( O.row <= 2 ) || ( O.row >= 0 ) ||
        ( O.col <= 2 ) || ( O.col >= 0 ) )
	s->cell[O.row][O.col] = BLANK;
}



/*  How good is the state for the program? */

int eval ( State s ) {
    int line;

    for ( line = 0; line < 3; line++ ){

	/* Check for a row completion */

	if ( ( s.cell[line][0] == s.cell[line][1] ) &&
	    ( s.cell[line][1] == s.cell[line][2] ) )
	    if ( s.cell[line][0] == Prog )
		return -10;
	    else if ( s.cell[line][0] == PROGRAM )
		return 10;

	/* Check for a column completion */

	if ( ( s.cell[0][line] == s.cell[1][line] ) &&
	    ( s.cell[1][line] == s.cell[2][line] ) )
	    if ( s.cell[0][line] == Prog )
		return -10;
	    else if ( s.cell[0][line] == PROGRAM )
		return 10;
    }

    /* Check for leading diagonal */

    if ( ( s.cell[0][0] == s.cell[1][1] ) &&
        ( s.cell[1][1] == s.cell[2][2] ) )
	if ( s.cell[0][0] == Prog )
	    return -10;
	else if ( s.cell[0][0] == PROGRAM )
	    return 10;


    /* Check for other diagonal */

    if ( ( s.cell[0][2] == s.cell[1][1] ) &&
        ( s.cell[1][1] == s.cell[2][0] ) )
	if ( s.cell[1][1] == Prog )
	    return -10;
	else if ( s.cell[1][1] == PROGRAM )
	    return 10;

    if ( s.cell[1][1] == PROGRAM ) 
        return 5;

    if ( s.cell[1][1] == Prog ) 
        return -5;


    for ( line = 0; line < 3; line++ ){

	if ( ( s.cell[line][0] == s.cell[line][1] ) )
	    if ( s.cell[line][0] == Prog )
		return -5;
	    else if ( s.cell[line][0] == PROGRAM )
		return 5;

	if ( ( s.cell[0][line] == s.cell[1][line] ) )
	    if ( s.cell[0][line] == Prog )
		return -5;
	    else if ( s.cell[0][line] == PROGRAM )
		return 5;

	if ( ( s.cell[line][1] == s.cell[line][2] ) )
	    if ( s.cell[line][1] == Prog )
		return -5;
	    else if ( s.cell[line][1] == PROGRAM )
		return 5;

	if ( ( s.cell[1][line] == s.cell[2][line] ) )
	    if ( s.cell[1][line] == Prog )
		return -5;
	    else if ( s.cell[1][line] == PROGRAM )
		return 5;

    }

    return 0;
}




