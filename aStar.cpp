#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// only need class, winning_position, ai_move, initialize with easy, medium and hard, main

//-----------make a class tictactoe--------------------------------------------
class TicTacToe {

	protected:
		enum Turn { PLAYER = 0, AI = 1 };
		//let's know the current turn
		Turn current_turn;
		//character(ai_char is X and player_char is O)
		char player_char, ai_char;
		char board[5][5];
		//initialize the board and send user choice of difficulty
		void initialize_board (string user_choice);
		//prints the board
		void print_board ();
		//checks if all the blocks in the board are filled
		bool blocks_filled (); 
		//checks and see if ai is winning if not then is user is winning and 
		//return that position
		void winning_position (char playerorai, int &row, int &col);
		//check if user has won 
		bool check_win (char ch);
		//user's move
		void user_move ();
		//AI's move
		void ai_move ();
		//loops the game
		void play_game ();
		//initialize the board with easy move 
		void easy();
		//initialize the board with medium move
		void medium();
		//initialize the board with hard move
		void hard();
	public:
		// Constructor
		TicTacToe () {
			//this values get flipped when game starts
			current_turn = PLAYER;
			player_char = 'X';
			ai_char = 'O'; 
			play_game ();
		}
};

//------------------user play's his move---------------------------------------
void TicTacToe::user_move ()
{
	int row, col;
	//get the row and col from the user
	while(1) {
		cout<< "Enter row you want to play " <<player_char<< " from [1-5]: ";
		cin>> row;
		cout<< "Enter col you want to play " <<player_char<< " form [1-5]: ";
		cin>> col;
		row -= 1;
		col -= 1;
		// check if user entered valid row and col
		if ((row < 0 || row >= 5) || (col < 0 || col >= 5)) {
			cout << "Enter a valid row and column.\n";
		}
		else {
			//move is valid if it is blank
			if (board[row][col] == ' ') {
				break;
			}
			else {
				cout << "This block is occupied.\n";
			}
		}
	}
	//set the player character in that block
	board[row][col] = player_char;
}

//-----------finds winning position for X and blocking position for O----------
void TicTacToe::winning_position (char playerorai, int &row, int &col)
{
	// check if specified character (player or ai) will win along row
	int i, j, char_count, emptyrow, emptycol;
	
	//for loop through rows
	for (i=0; i<5; i++) {

		char_count = 0;
		emptycol = -1;
		
		//for loop through columns 
		for (j=0; j<5; j++) {
			// If the user is occupying the block, increment char count
			if (board[i][j] == playerorai) {
				char_count++;
			}
			// If specified block is blank then column as empty
			else if (board[i][j] == ' ') {
				emptycol = j;
			}
		}
		//If there are two user O in the row and there is a blank, then the 
		//blank is the winning position
		if (char_count == 4 && emptycol != -1) {
			row = i;
			col = emptycol;
			return;
		}		
	}
	
	//same for columns
	for (j=0; j<5; j++) {
		char_count = 0;
		emptyrow = -1;
		for (i=0; i<5; i++) {
			if (board[i][j] == playerorai) {
				char_count++;
			}
			else if (board[i][j] == ' ') {
				emptyrow = i;
			}
		}
		if (char_count == 4 && emptyrow != -1) {
			row = emptyrow;
			col = j;
			return;
		}		
	}
	//Check if user can win diagonally
	char_count = 0;
	emptyrow = -1;
	emptycol = -1;
	//for loop through the diagonal
	for (i=0; i<5; i++) {
		if (board[i][i] == playerorai) {
			char_count ++;
		}
		else if (board[i][i] == ' ') {
			emptyrow = emptycol = i;
		}
	}
	if (char_count == 4 && emptyrow != -1 && emptycol != -1) {
		row = emptyrow;
		col = emptycol;
		return;
	}
	// Check if user can win along anti diagonally
	char_count = 0;
	emptyrow = -1;
	emptycol = -1;
	//for loop through the diagonal
	for (i=0; i<5; i++) {
		if (board[i][4-i] == playerorai) {
			char_count ++;
		}
		else if (board[i][4-i] == ' ') {
			emptyrow = i;
			emptycol = 4 - i;
		}
	}
	if (char_count == 4 && emptyrow != -1 && emptycol != -1){
		row = emptyrow;
		col = emptycol;
		return;
	}
}

//----------------------AI_MOVE------------------------------------------------
void TicTacToe::ai_move ()
{
	//Check if AI can win in current move
	int row=-1, col=-1;
	winning_position (ai_char, row, col);
	//play the winning move for ai
	if (row != -1 && col != -1) {
		board[row][col] = ai_char;
		return;
	}
	row = col = -1;
	//block user's win 
	winning_position (player_char, row, col);
	if (row != -1 && col != -1) {
		board[row][col] = ai_char;
		return;
	}

	//find best move for ai if none of above is true
	//horizontal check
	int counter_blank=0, counter_x=0, pre_counter_blank=0, pre_counter_x=0; 
	int a,b;
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			if (board[i][j] == 'X') {
				counter_x++;
				if (pre_counter_x <= counter_x) {
					pre_counter_x = counter_x;
				}
			}
			if (board[i][j] == ' ') { 
				counter_blank++;
				if (pre_counter_blank <= counter_blank) {
					pre_counter_blank = counter_blank;
				}
				a = i;
				b = j;
			}
		}
		if (pre_counter_x == 3 && pre_counter_blank == 2) {
			board[a][b] = ai_char;
			return;
		}
		else if (pre_counter_x == 2 && pre_counter_blank == 3) {
			board[a][b] = ai_char;
			return;
		}
		else if (pre_counter_x == 1 && pre_counter_blank == 4) {
			board[a][b] = ai_char;
			return;
		}
		counter_blank=0;
		counter_x=0;
		pre_counter_blank=0;
		pre_counter_x=0;
	}

	//vertical check
	for (int j=0; j<5; j++) {
		for( int i=0; i<5; i++) {
			if (board[i][j] == 'X') {
				counter_x++;
				if (pre_counter_x <= counter_x) {
					pre_counter_x = counter_x;
				}
			}
			if (board[i][j] == ' ') {
				counter_blank++;
				if (pre_counter_blank <= counter_blank) {
					pre_counter_blank = counter_blank;
				}
				a = i;
				b = j;
			}
		}
		if (pre_counter_x == 3 && pre_counter_blank == 2) {
			board[a][b] = ai_char;
			return;
		}
		else if (pre_counter_x == 2 && pre_counter_blank == 3) {
			board[a][b] = ai_char;
			return;
		}
		else if (pre_counter_x==1 && pre_counter_blank==4) {
			board[a][b] = ai_char;
			return;
		}
		counter_x=0;
		counter_blank=0;
		pre_counter_blank=0;
		pre_counter_x=0;
	}
		
		int i =0,j =0;
 		i = row;
 		j =col;
 		while(board[row][col] != ' ') {
 			row = rand()%25+0;
 			col = rand()%25+0;
 		}		
 		board[row][col] = ai_char;
 		return;
}

//--------------------cheks for win--------------------------------------------
bool TicTacToe::check_win (char ch)
{
	bool win = false;
	//check horizontally 
	int i;
	for (i=0; i<5; i++)
		if (board[i][0] == ch && board[i][1] == ch && board[i][2] == ch 
			&& board[i][3] == ch && board[i][4] == ch) {
			
			win = true;
			break;
		}
	//check vertically
	for (i=0; i<5; i++)
		if (board[0][i] == ch && board[1][i] == ch && board[2][i] == ch 
			&& board[3][i] == ch && board[4][i] == ch) {
			
			win = true;
			break;
		}
	//check diagonally
	if (board[0][0] == ch && board[1][1] == ch && board[2][2] == ch 
		&& board[3][3] == ch && board[4][4] == ch) {
		
		win = true;
	}	
	if (board[0][4] == ch && board[1][3] == ch && board[2][2] == ch 
		&& board[3][1] == ch && board[4][0] == ch) {
		
		win = true;
	}
	return win;
}

//--------------------check's if all the block are filled in board-------------
bool TicTacToe::blocks_filled ()
{
	bool is_filled = true;
	for (int i=0; i<5; i++)
	{
		for (int j=0; j < 5; j++) {
			if (board[i][j] == ' ') {
				is_filled = false;
			}
		}
		if (is_filled == false) {
			break;
		}
	}
	
	return is_filled;
}

//------------------print's the board 5x5--------------------------------------
void TicTacToe::print_board ()
{
	cout << "\n";
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			cout << board[i][j] << "\t";
			if (j < 4) {
				cout << "|\t";
			}
		}
		if (i < 4)
			cout << "\n---------------------------------------------------------------------\n";
	}
	cout << "\n";
}

//------------------------intitializes the board with center move--------------
void TicTacToe::hard(){

	//return's the co ordinated for center block
	if (board[2][2] == ' ') {
		board[2][2] = ai_char;

		return;
	}
}

//------------------------intitializes the board with corner move--------------
void TicTacToe::medium(){
	int medium[4][2] = {{0, 0}, {0, 4}, {4, 0}, {4, 4}};
	int row,col;

	//retun's the corner blocks co ordinates
	if (board[0][0] == ' ' || board[0][4] == ' ' || 
		board[4][0] == ' ' || board[4][4] == ' ') {
		
		while(1) {
			
			int corner = rand () % 4+0;
			row = medium[corner][0];
			col = medium[corner][1];
			if (board[row][col] == ' ') {
				board[row][col] = ai_char;
				return;
			}
		}
	}
}

//---------------intitializes the board with edge move with no corner----------
void TicTacToe::easy(){
	int easy[12][2] = {{0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 4}, {2, 0}, {2, 4}, 
					   {3, 0}, {3, 4}, {4, 1}, {4, 2}, {4, 3}};
	int row,col;
	// if any one or more edges are blank
	if (board[0][1] == ' ' || board[0][2] == ' ' || board[0][3] == ' ' || 
		board[1][0] == ' ' || board[1][4] == ' ' || board[2][0] == ' ' || 
		board[2][4] == ' ' || board[3][0] == ' ' || board[3][4] == ' ' || 
		board[4][1] == ' ' || board[4][2] == ' ' || board[4][3] == ' ') {
		//select the edges randomly
		while (1) {
			int edge = rand () % 12+0;
			row = easy[edge][0];
			col = easy[edge][1];
			if (board[row][col] == ' ') {
				board[row][col] = ai_char;
				return;
			}
		}		
	}
}

//-----initialize the board with initial move depending on the difficulties----
void TicTacToe::initialize_board (string uc)
{	
	for (int i = 0; i < 5; i++){
		for (int j=0; j < 5; j++){
			board[i][j] = ' ';
		}
	}

	ai_char = 'X';
	player_char = 'O';
	current_turn = PLAYER;

	if(uc == "E" || uc == "e"){
		easy();
	}
	else if(uc == "M" || uc == "m"){
		medium();
		
	}
	else if(uc == "H" || uc == "h"){
		hard();
	}
	else 
		cout << "Invalid!\n";
}

//---------------loops through game--------------------------------------------
void TicTacToe::play_game ()
{	
	string user_choice;
	//asks user for choice
	cout <<"select difficulty level:\n1)E for Easy\n2)M for Medium\n3)H for Hard\n";
	cin >> user_choice;

	initialize_board (user_choice);

	bool gamefinish = false;
	while (! gamefinish) {
		print_board ();

		if (current_turn == PLAYER) {
			user_move ();
			current_turn = AI;
		}
		else {
			cout << "\nAI Moved: \n";
			ai_move ();
			current_turn = PLAYER;
		}

		if (check_win ('O')) {
			print_board ();
			cout << "\nGame over... O wins\n";
			break;
		}
		else if (check_win ('X')) {
			print_board ();
			cout << "\nGame over... X wins\n";
			break;
		}
		if (blocks_filled ()) {
			print_board ();
			cout << "\nCats Game!!!.\n";
			break;
		}
	}
}

int main ()
{
	// initialize randomizer
	//srand (time (NULL));
	TicTacToe game;
	return 0;
}