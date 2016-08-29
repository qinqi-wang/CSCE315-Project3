
/*

AI Player : 'X'
Human Player: 'O'
Empty: ' '

*/


char Empty = ' '; 
long Nodes;                             // 32 bit Nodes searched with minimax  
typedef char Board_Type[25]; 

typedef struct { 
    int Square;							// Index in grid 0 - 24 
    int Heuristic; 
} Move_Heuristic_Type;

const int Five_in_a_Row[12][5] = { 
    { 0, 1, 2, 3, 4 }, 
    { 5, 6, 7, 8, 9 }, 
    { 10, 11, 12, 13, 14 }, 
    { 15, 16, 17, 18, 19 }, 
    { 20, 21, 22, 23, 24 }, 
    { 0, 5, 10, 15, 20 }, 
    { 1, 6, 11, 16, 21 },  
    { 2, 7, 12, 17, 22 }, 
	{ 3, 8, 13, 18, 23 },
	{ 4, 9, 14, 19, 24 },
	{ 0, 6, 12, 18, 24 }, 
	{ 4, 8, 12, 16, 20 }, 	
}; 

/* Array used in heuristic formula for each move 
   Rows are the number of X's in a row, columns are the number of O's */ 
const int Heuristic_Array[6][6] = { 
    {     0,   -10,  -100, -1000, -10000, -100000 }, 
    {    10,     0,     0,     0,	   0,		0 }, 
    {   100,     0,     0,     0,      0,       0 }, 
    {  1000,     0,     0,     0,      0,       0 },
	{ 10000,     0,     0,     0,      0,       0 }, 
	{100000,     0,     0,     0,      0,       0 }
}; 


void Play(Board_Type Board, int Square, char Player) { 
    Board[Square] = Player; 
} 

/* Return the other player */ 
char Other(char Player) { 
    return Player == 'X' ? 'O' : 'X'; 
}

/* Return heuristic that determines the order in which the moves are searched 
   and the values of terminal nodes in the heuristic search */ 
int Evaluate(Board_Type Board, char Player) { 
    int I; 
    int Heuristic = 0; 
    for (I = 0; I < 12; I++) { 
        int J; 
        int Players = 0, Others = 0; 
        for (J = 0; J < 5; J++) { 
            char Piece = Board[Five_in_a_Row[I][J]]; 
            if (Piece == Player) 
                Players++; 
            else if (Piece == Other(Player)) 
                Others++; 
        } 
        Heuristic += Heuristic_Array[Players][Others]; 
    } 
    return Heuristic; 
} 


/* Return the score of the move that maximizes the minimum 
   heuristic function Depth moves ahead 
   The square number of the move is returned in *Square */ 
int alphabeta(Board_Type Board, char Player, int *Square, int Move_Nbr, int Depth, int Alpha, int Beta) {
	
    int Best_Square = -1; 
    int Moves = 0; 
    int Index; 
    Move_Heuristic_Type Move_Heuristic[25]; 
    /* Find the heuristic for each move */ 
    for (Index = 0; Index < 25; Index++) 
        if (Board[Index] == Empty) { 
            Play(Board, Index, Player); 
            Move_Heuristic[Moves].Heuristic = Evaluate(Board, Player); 
            Move_Heuristic[Moves].Square = Index; 
            Moves++; 
            Play(Board, Index, Empty); 
        } 
   
    for (Index = 0; Index < Moves; Index++) { 
        int Score; 
        int Sq = Move_Heuristic[Index].Square; 
        Nodes++; 
        /* Make a move and get its score */ 
        Play(Board, Sq, Player); 
        if (Depth == 1) 
            Score = Evaluate(Board, 'X'); 
        else 
            Score = alphabeta(Board, Other(Player), Square, Move_Nbr + 1, Depth - 1, Alpha, Beta); 
        Play(Board, Sq, Empty); 
        /* Perform alpha-beta pruning */ 
        if (Player == 'X') { 
            if (Score >= Beta) { 
                *Square = Sq; 
                return Score; 
            } else if (Score > Alpha) { 
                Alpha = Score; 
                Best_Square = Sq; 
            } 
        } else { 
            if (Score <= Alpha) { 
                *Square = Sq; 
                return Score; 
            } else if (Score < Beta) { 
                Beta = Score; 
                Best_Square = Sq; 
            } 
        } 
    } 
    *Square = Best_Square; 
    if (Player == 'X') 
        return Alpha; 
    else 
        return Beta; 
} 
