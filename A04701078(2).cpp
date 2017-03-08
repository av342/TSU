

#include <stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
int score,tnodes=0,mo=0;
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


#define	BLANK	0
#define	Prog	1
#define	PROGRAM	2
#define TIE     3
#define MAXEVAL 1000

Move alphabeta (State s, int d, int alpha, int beta, int turn );

void initialize_state ( State *s );
int isTerminal ( State s );
int isValid ( State s, Operator O );
int makeMove ( State *s, Operator O, int who );
void print_state ( State s );



int main (int argc, char*argv[]) {

    State current;
    Operator O;
    Move m;
    int done;
    int turn;

    initialize_state ( &current );

    do {
       printf("Who should go first?  (1=System1 2=System2): ");
       scanf("%d", &turn);
    } while ( ( turn != Prog ) && ( turn != PROGRAM ) );

   // print_state ( current );

    do {
    	
        if (turn == PROGRAM) {

          /* do {
  	       printf("Please input your move: ");

	       printf("Row (1-3): ");
	       scanf("%d", &O.row);

	       printf("Column (1-3): ");
	       scanf("%d", &O.col);

	       O.row--;
	       O.col--;
	   } while ( ! isValid ( current, O ) );*/
		
  	       m = alphabeta ( current, 0, -MAXEVAL, MAXEVAL, turn );

   	   makeMove ( &current, m.op, PROGRAM );

           turn = Prog;
	}

        else {        /* program's turn */
		
           m = alphabeta ( current, 0, -MAXEVAL, MAXEVAL,turn );

   	   makeMove ( &current, m.op, Prog );
		
           turn = PROGRAM;

	}

        print_state ( current );

	if ( done = isTerminal ( current ) ) {
            if ( done == Prog )
    	         printf("System 1 wins!\n");
    	        
            else if ( done == PROGRAM )
                 printf("System 2 wins!\n");
				 
            else
                 printf("Tie!\n");

           // print_state ( current );
           
	    //exit(0);
	}

    } while ( ! isTerminal ( current ) );
	cout << "\n Number of Nodes:  " << mo;
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
	mo++;
	
    return 1;
}



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

int eval1 ( State s );
int eval2 (State s);
int eval3 (State s);
int eval4 (State s);


int max_depth=4;  /* how deep the search can go */

/* Function undo:  undoes the effect of the given operator */

void undo (State *s, Operator O);


Move alphabeta ( State s, int d, int alpha, int beta, int turn ){
    Move m, bestmove;
    Operator O;
    int i, j;
    tnodes++;

    if ( (d == max_depth) || ( isTerminal (s) )){
	m.value = eval4 (s);
	
	return m;
    }

    for (i=0; i<3; i++)
	for (j=0; j<3; j++){
	    O.row = i;
	    O.col = j;
	    if ( isValid (s, O) ){
		makeMove ( &s, O, turn );
		m = alphabeta ( s, d + 1, bestmove.value, beta,turn );
		undo (&s, O );
		if ( m.value > alpha ){
		    alpha = m.value;
		    bestmove.value = alpha;
		    bestmove.op.row = i;
		    bestmove.op.col = j;
                    if ( alpha > beta ){
                        bestmove.value = alpha;
                        return bestmove;
                        
                    }
                    
		}
		if ( m.value < beta ){
		    beta = m.value;
		    bestmove.value = beta;
		    bestmove.op.row = i;
		    bestmove.op.col = j;
                    if ( alpha < beta ){
                        bestmove.value = beta;
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

int eval1 ( State s ) {
    int line;

    for ( line = 0; line < 3; line++ ){

	/* Check for a row completion */

	if ( ( s.cell[line][0] == s.cell[line][1] ) &&
	    ( s.cell[line][1] == s.cell[line][2] ) )
	    if ( s.cell[line][0] == Prog )
		return -5;
	    else if ( s.cell[line][0] == PROGRAM )
		return 5;

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
	    return -15;
	else if ( s.cell[0][0] == PROGRAM )
	    return 15;


    /* Check for other diagonal */

    if ( ( s.cell[0][2] == s.cell[1][1] ) &&
        ( s.cell[1][1] == s.cell[2][0] ) )
	if ( s.cell[1][1] == Prog )
	    return -15;
	else if ( s.cell[1][1] == PROGRAM )
	    return 15;

    if ( s.cell[1][1] == PROGRAM ) 
        return 4;

    if ( s.cell[1][1] == Prog ) 
        return -4;


    for ( line = 0; line < 3; line++ ){

	if ( ( s.cell[line][0] == s.cell[line][1] ) )
	    if ( s.cell[line][0] == Prog )
		return -1;
	    else if ( s.cell[line][0] == PROGRAM )
		return 1;

	if ( ( s.cell[0][line] == s.cell[1][line] ) )
	    if ( s.cell[0][line] == Prog )
		return -1;
	    else if ( s.cell[0][line] == PROGRAM )
		return 1;

	if ( ( s.cell[line][1] == s.cell[line][2] ) )
	    if ( s.cell[line][1] == Prog )
		return -1;
	    else if ( s.cell[line][1] == PROGRAM )
		return 1;

	if ( ( s.cell[1][line] == s.cell[2][line] ) )
	    if ( s.cell[1][line] == Prog )
		return -1;
	    else if ( s.cell[1][line] == PROGRAM )
		return 1;

    }

    return 0;
}


int eval2 ( State s ) {
    int line;

    for ( line = 0; line < 3; line++ ){

	/* Check for a row completion */

	if ( ( s.cell[line][0] == s.cell[line][1] ) &&
	    ( s.cell[line][1] == s.cell[line][2] ) )
	    if ( s.cell[line][0] == Prog )
		return -5;
	    else if ( s.cell[line][0] == PROGRAM )
		return 5;

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
	    return -15;
	else if ( s.cell[0][0] == PROGRAM )
	    return 15;


    /* Check for other diagonal */

    if ( ( s.cell[0][2] == s.cell[1][1] ) &&
        ( s.cell[1][1] == s.cell[2][0] ) )
	if ( s.cell[1][1] == Prog )
	    return -15;
	else if ( s.cell[1][1] == PROGRAM )
	    return 15;

 /*   if ( s.cell[1][1] == PROGRAM ) 
        return 4;

    if ( s.cell[1][1] == Prog ) 
        return -4;*/


    //for ( line = 0; line < 3; line++ ){

	if ( ( s.cell[0][0] == s.cell[0][1] ) )
	    if ( s.cell[0][0] == Prog )
		return -4;
	    else if ( s.cell[0][0] == PROGRAM )
		return 4;
		
	if ( ( s.cell[1][0] == s.cell[1][1] ) )
	    if ( s.cell[1][0] == Prog )
		return -9;
	    else if ( s.cell[1][0] == PROGRAM )
		return 9;

	if ( ( s.cell[2][0] == s.cell[2][1] ) )
	    if ( s.cell[2][0] == Prog )
		return -2;
	    else if ( s.cell[2][0] == PROGRAM )
		return 2;

	if ( ( s.cell[0][1] == s.cell[0][2] ) )
	    if ( s.cell[0][1] == Prog )
		return -8;
	    else if ( s.cell[0][1] == PROGRAM )
		return 8;
		
	if ( ( s.cell[1][1] == s.cell[1][2] ) )
	    if ( s.cell[1][1] == Prog )
		return -1;
	    else if ( s.cell[1][1] == PROGRAM )
		return 1;

	if ( ( s.cell[2][1] == s.cell[2][2] ) )
	    if ( s.cell[2][1] == Prog )
		return -6;
	    else if ( s.cell[2][1] == PROGRAM )
		return 6;

	if ( ( s.cell[0][0] == s.cell[0][2] ) )
	    if ( s.cell[0][0] == Prog )
		return -5;
	    else if ( s.cell[0][0] == PROGRAM )
		return 5;
		
	if ( ( s.cell[1][0] == s.cell[1][2] ) )
	    if ( s.cell[1][0] == Prog )
		return -3;
	    else if ( s.cell[1][0] == PROGRAM )
		return 3;

	if ( ( s.cell[2][0] == s.cell[2][2] ) )
	    if ( s.cell[2][0] == Prog )
		return -7;
	    else if ( s.cell[2][0] == PROGRAM )
		return 7;





	if ( ( s.cell[0][0] == s.cell[1][0] ) )
	    if ( s.cell[0][0] == Prog )
		return -6;
	    else if ( s.cell[0][0] == PROGRAM )
		return 6;

	
	if ( ( s.cell[0][1] == s.cell[1][1] ) )
	    if ( s.cell[0][1] == Prog )
		return -7;
	    else if ( s.cell[0][1] == PROGRAM )
		return 7;

	if ( ( s.cell[0][2] == s.cell[1][2] ) )
	    if ( s.cell[0][2] == Prog )
		return -2;
	    else if ( s.cell[0][2] == PROGRAM )
		return 2;

	if ( ( s.cell[1][0] == s.cell[2][0] ) )
	    if ( s.cell[1][0] == Prog )
		return -8;
	    else if ( s.cell[1][0] == PROGRAM )
		return 8;

	
	if ( ( s.cell[1][1] == s.cell[2][1] ) )
	    if ( s.cell[1][1] == Prog )
		return -3;
	    else if ( s.cell[1][1] == PROGRAM )
		return 3;

	if ( ( s.cell[1][2] == s.cell[2][2] ) )
	    if ( s.cell[1][2] == Prog )
		return -4;
	    else if ( s.cell[1][2] == PROGRAM )
		return 4;

	if ( ( s.cell[0][0] == s.cell[2][0] ) )
	    if ( s.cell[0][0] == Prog )
		return -1;
	    else if ( s.cell[0][0] == PROGRAM )
		return 1;
	
	if ( ( s.cell[0][1] == s.cell[2][1] ) )
	    if ( s.cell[0][1] == Prog )
		return -5;
	    else if ( s.cell[0][1] == PROGRAM )
		return 5;

	if ( ( s.cell[0][2] == s.cell[2][2] ) )
	    if ( s.cell[0][2] == Prog )
		return -9;
	    else if ( s.cell[0][2] == PROGRAM )
		return 9;


    

	if ( ( s.cell[0][0] == s.cell[1][1] ) )
	    if ( s.cell[0][0] == Prog )
		return -2;
	    else if ( s.cell[0][0] == PROGRAM )
		return 2;
	
	if ( ( s.cell[0][0] == s.cell[2][2] ) )
	    if ( s.cell[0][0] == Prog )
		return -5;
	    else if ( s.cell[0][0] == PROGRAM )
		return 5;

	if ( ( s.cell[1][1] == s.cell[2][2] ) )
	    if ( s.cell[1][1] == Prog )
		return -8;
	    else if ( s.cell[1][1] == PROGRAM )
		return 8;

	if ( ( s.cell[0][2] == s.cell[1][1] ) )
	    if ( s.cell[0][2] == Prog )
		return -6;
	    else if ( s.cell[0][2] == PROGRAM )
		return 6;
	
	if ( ( s.cell[1][1] == s.cell[2][0] ) )
	    if ( s.cell[1][1] == Prog )
		return -4;
	    else if ( s.cell[1][1] == PROGRAM )
		return 4;

	if ( ( s.cell[2][0] == s.cell[0][2] ) )
	    if ( s.cell[2][0] == Prog )
		return -5;
	    else if ( s.cell[2][0] == PROGRAM )
		return 5;

    return 0;
}


int eval3 ( State s ) {
    int line;

    for ( line = 0; line < 3; line++ ){

	/* Check for a row completion */

	if ( ( s.cell[line][0] == s.cell[line][1] ) &&
	    ( s.cell[line][1] == s.cell[line][2] ) )
	    if ( s.cell[line][0] == Prog )
		return -5;
	    else if ( s.cell[line][0] == PROGRAM )
		return 5;

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
	    return -15;
	else if ( s.cell[0][0] == PROGRAM )
	    return 15;


    /* Check for other diagonal */

    if ( ( s.cell[0][2] == s.cell[1][1] ) &&
        ( s.cell[1][1] == s.cell[2][0] ) )
	if ( s.cell[1][1] == Prog )
	    return -15;
	else if ( s.cell[1][1] == PROGRAM )
	    return 15;

 /*   if ( s.cell[1][1] == PROGRAM ) 
        return 4;

    if ( s.cell[1][1] == Prog ) 
        return -4;*/


    //for ( line = 0; line < 3; line++ ){


		

	if ( ( s.cell[0][0] == s.cell[1][1] ) )
	    if ( s.cell[0][0] == Prog )
		return -4;
	    else if ( s.cell[0][0] == PROGRAM )
		return 4;
	
	if ( ( s.cell[1][1] == s.cell[2][2] ) )
	    if ( s.cell[1][1] == Prog )
		return -3;
	    else if ( s.cell[1][1] == PROGRAM )
		return 3;

	if ( ( s.cell[0][2] == s.cell[1][1] ) )
	    if ( s.cell[0][2] == Prog )
		return -3;
	    else if ( s.cell[0][2] == PROGRAM )
		return 3;
	
	if ( ( s.cell[1][1] == s.cell[2][0] ) )
	    if ( s.cell[1][1] == Prog )
		return -3;
	    else if ( s.cell[1][1] == PROGRAM )
		return 3;

	
    return 0;
}

int eval4 ( State s ) {
    int line;

    for ( line = 0; line < 3; line++ ){

	/* Check for a row completion */

	if ( ( s.cell[line][0] == s.cell[line][1] ) &&
	    ( s.cell[line][1] == s.cell[line][2] ) )
	    if ( s.cell[line][0] == Prog )
		return -5;
	    else if ( s.cell[line][0] == PROGRAM )
		return 5;

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
	    return -15;
	else if ( s.cell[0][0] == PROGRAM )
	    return 15;


    /* Check for other diagonal */

    if ( ( s.cell[0][2] == s.cell[1][1] ) &&
        ( s.cell[1][1] == s.cell[2][0] ) )
	if ( s.cell[1][1] == Prog )
	    return -15;
	else if ( s.cell[1][1] == PROGRAM )
	    return 15;

 /*   if ( s.cell[1][1] == PROGRAM ) 
        return 4;

    if ( s.cell[1][1] == Prog ) 
        return -4;*/


    //for ( line = 0; line < 3; line++ ){



	if ( ( s.cell[2][0] == s.cell[2][2] ) )
	    if ( s.cell[2][0] == Prog )
		return -1;
	    else if ( s.cell[2][0] == PROGRAM )
		return 1;


	if ( ( s.cell[0][0] == s.cell[2][0] ) )
	    if ( s.cell[0][0] == Prog )
		return -1;
	    else if ( s.cell[0][0] == PROGRAM )
		return 1;

	if ( ( s.cell[0][2] == s.cell[2][2] ) )
	    if ( s.cell[0][2] == Prog )
		return -1;
	    else if ( s.cell[0][2] == PROGRAM )
		return 1;



	if ( ( s.cell[0][0] == s.cell[1][1] ) )
	    if ( s.cell[0][0] == Prog )
		return -1;
	    else if ( s.cell[0][0] == PROGRAM )
		return 1;
	
	if ( ( s.cell[1][1] == s.cell[2][2] ) )
	    if ( s.cell[1][1] == Prog )
		return -1;
	    else if ( s.cell[1][1] == PROGRAM )
		return 1;

	if ( ( s.cell[0][2] == s.cell[1][1] ) )
	    if ( s.cell[0][2] == Prog )
		return -1;
	    else if ( s.cell[0][2] == PROGRAM )
		return 1;
	
	if ( ( s.cell[1][1] == s.cell[2][0] ) )
	    if ( s.cell[1][1] == Prog )
		return -1;
	    else if ( s.cell[1][1] == PROGRAM )
		return 1;

	
    return 0;
}

