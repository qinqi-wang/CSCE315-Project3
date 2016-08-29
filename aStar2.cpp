#include <iostream>
#include <cstdlib>
#include <ctime>
#include <jni.h>
//#include "jni.h"

using namespace std;

//------------------find winning position or blocking position-----------------
void winning_position (char board[5][5], char playerorai, int row, int col)
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

//---------------here is the AI move-------------------------------------------
int ai_move (char board[5][5])
{
    int node;
    char ai_char = 'X';
    char player_char = 'O';
    int row=-1, col=-1;
    winning_position (board,ai_char, row, col);
    //play the winning move for ai
    if (row != -1 && col != -1) {
        //board[row][col] = ai_char;
        node = (row)*5 + col;
        return node;
    }
    row = col = -1;
    //block user's win
    winning_position (board,player_char, row, col);
    if (row != -1 && col != -1) {
        //board[row][col] = ai_char;
        node = (row)*5 + col;
        return node;
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
            node = (a)*5 + b;
            return node;
        }
        else if (pre_counter_x == 2 && pre_counter_blank == 3) {
            node = (a)*5 + b;
            return node;
        }
        else if (pre_counter_x == 1 && pre_counter_blank == 4) {
            node = (a)*5 + b;
            return node;
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
            node = (a)*5 + b;
            return node;
        }
        else if (pre_counter_x == 2 && pre_counter_blank == 3) {
            node = (a)*5 + b;
            return node;
        }
        else if (pre_counter_x==1 && pre_counter_blank==4) {
            node = (a)*5 + b;
            return node;
        }
        counter_x=0;
        counter_blank=0;
        pre_counter_blank=0;
        pre_counter_x=0;
    }

    //diagonal check
    for(int i=0; i<5; i++){
        if(board[i][i] == 'X') {
            counter_x++;
        }
        if(board[i][i] == ' ') {
            counter_blank++;
            a =i;
        }
        if(counter_x == 3 && counter_blank ==2 ) {
            node = (a)*5 + a;
            return node;
        }
        else if(counter_x ==2 && counter_blank ==3) {
            node = (a)*5 + a;
            return node;
        }
        else if(counter_x ==1 && counter_blank ==4) {
            node = (a)*5 + a;
            return node;
        }
    }
    counter_x =0;
    counter_blank=0;

    //check anti diagonally
    for (int i=0; i<5; i++) {
        if (board[i][4-i] == 'X') {
            counter_x++;
        }
        if (board[i][4-i] == ' ') {
            counter_blank++;
            a = i;
            b = 4-i;
        }
        if (counter_x == 3 && counter_blank ==2 ) {
            node = (a)*5 + b;
            return node;
        }
        else if (counter_x ==2 && counter_blank ==3) {
            node = (a)*5 + a;
            return node;
        }
        else if (counter_x ==1 && counter_blank ==4) {
            node = (a)*5 + a;
            return node;
        }
    }
    counter_x =0;
    counter_blank=0;

    int i =0,j =0;
    i = row;
    j =col;
    while(board[row][col] != ' ') {
        row = rand()%25+0;
        col = rand()%25+0;
    }
    node = (row)*5 + col;
    return node;
}

extern "C" {
JNIEXPORT jint JNICALL
        Java_com_example_ray_a5tac2_MainActivity_aStar(JNIEnv *env, jobject instance, jintArray board);
}

JNIEXPORT jint JNICALL
Java_com_example_ray_a5tac2_MainActivity_aStar(JNIEnv *env, jobject instance, jintArray board)
{
    jint newMove = 0;
    int boardcpp[25];
    jint* boardjava = env->GetIntArrayElements(board, NULL);
    if(boardjava == NULL) {
        return 0; //exception has occurred
    }
    for(int i = 0; i < 25; ++i) {
        boardcpp[i] = boardjava[i];
    }

    char charboard[5][5];
    int k =0;
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j) {
            //char[j][i] charboard;
            if(boardcpp[k] == 0) {
                charboard[i][j] = ' ';
            }
            else if(boardcpp[k] == -1) {
                charboard[i][j] = 'X';
            }
            else if(boardcpp[k] == 1) {
                charboard[i][j] = 'O';
            }
            ++k;
        }
    }

    //TicTacToe* tictactoe = new TicTacToe();
    //newMove = tictactoe->ai_move(charboard);
    newMove = ai_move(charboard);
    //delete tictactoe;
    return newMove;
}

//int main () {return 0;}
