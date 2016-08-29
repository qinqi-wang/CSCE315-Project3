#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <jni.h>
//#include "jni.h"

using namespace std;

//---------------here is the AI move-------------------------------------------
int ai_move (char board[5][5])
{
    //find best move for ai if none of above is true
    //horizontal check
    int counter_blank=0, counter_x=0, pre_counter_blank=0, pre_counter_x=0, counter_xy=0, counter_blanky=0;
    int pre_counter_blankv=0, counter_blankv, pre_counter_xv, counter_xv;
    int a,b,c,d,e,f,node,row,col;
    vector <int> v1;
    vector <int> v2;

//**************start checking for AI win************
    //horizontal check
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
            if (pre_counter_x == 4 && pre_counter_blank == 1) {
                node = (a)*5 + b;
                return node;
            }
        }
        counter_blank=0;
        counter_x=0;
        pre_counter_blank=0;
        pre_counter_x=0;
    }

    //vertical check
    for(int j=0; j<5; j++){
        for(int i=0; i< 5; i++) {
            if (board[i][j] == 'X') {
                counter_xv++;
                if (pre_counter_xv <= counter_xv) {
                    pre_counter_xv = counter_xv;
                }
            }
            if (board[i][j] == ' ') {
                counter_blankv++;
                if (pre_counter_blankv <= counter_blankv) {
                    pre_counter_blankv = counter_blankv;
                }
                e = i;
                f = j;
            }
        }
        if (pre_counter_xv == 4 && pre_counter_blankv == 1) {
            node = (e)*5 + f;
            return node;
        }
        counter_xv=0;
        counter_blankv=0;
        pre_counter_blankv=0;
        pre_counter_xv=0;
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
        if(counter_x == 4 && counter_blank ==1 ) {
            node = (a)*5 + a;
            return node;
        }
    }
    counter_x =0;
    counter_blank=0;

    //anti diagonal check
    for(int i=0; i<5; i++) {
        if (board[i][4-i] == 'X') {
            counter_xy++;
        }
        if (board[i][4-i] == ' ') {
            counter_blanky++;
            c = i;
            d = 4-i;
        }
        if(counter_xy == 4 && counter_blanky == 1) {
            node = (c)*5 + d;
            return node;
        }
    }
    counter_xy=0;
    counter_blanky=0;

//********start checking for user in***********
    //horizontal check
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            if (board[i][j] == 'O') {
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

            if (pre_counter_x == 4 && pre_counter_blank == 1) {
                node = (a)*5 + b;
                return node;
            }
        }
        counter_blank=0;
        counter_x=0;
        pre_counter_blank=0;
        pre_counter_x=0;
    }

    //vertical check
    for(int j=0; j<5; j++) {
        for(int i=0; i<5; i++) {
            if (board[i][j] == 'O') {
                counter_xv++;
                if (pre_counter_xv <= counter_xv) {
                    pre_counter_xv = counter_xv;
                }
            }
            if (board[i][j] == ' ') {
                counter_blankv++;
                if (pre_counter_blankv <= counter_blankv) {
                    pre_counter_blankv = counter_blankv;
                }
                e = i;
                f = j;
            }
        }
        if (pre_counter_xv ==4 && pre_counter_blankv == 1) {
            node = (e)*5 + f;
            return node;
        }
        counter_xv=0;
        counter_blankv=0;
        pre_counter_blankv=0;
        pre_counter_xv=0;
    }

    //diagonal check
    for(int i=0; i<5; i++){
        if(board[i][i] == 'O') {
            counter_x++;
        }
        if(board[i][i] == ' ') {
            counter_blank++;
            a =i;
        }
        if(counter_x == 4 && counter_blank ==1) {
            node = (a)*5 + a;
            return node;
        }
    }
    counter_x =0;
    counter_blank=0;

    //anti diagonal check
    for(int i =0; i<5; i++) {
        if (board[i][4-i] == 'O') {
            counter_xy++;
        }
        if (board[i][4-i] == ' ') {
            counter_blanky++;
            c = i;
            d = 4-i;
        }
        if(counter_xy == 4 && counter_blanky == 1) {
            node = (c)*5 + d;
            return node;
        }
    }
    counter_xy=0;
    counter_blanky=0;

//**************pick up best move*********
    //find best move for ai if none of above is true
    //horizontal check
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

            if (board[j][i] == 'X') {
                counter_xv++;
                if (pre_counter_xv <= counter_xv) {
                    pre_counter_xv = counter_xv;
                }
            }
            if (board[j][i] == ' ') {
                counter_blankv++;
                if (pre_counter_blankv <= counter_blankv) {
                    pre_counter_blankv = counter_blankv;
                }
                e = j;
                f = i;
            }
        }
        if (pre_counter_x == 3 && pre_counter_blank == 2) {
            node = (a)*5 + b;
            return node;
        }
        if (pre_counter_x == 2 && pre_counter_blank == 3) {
            node = (a)*5 + b;
            return node;
        }
        if (pre_counter_x == 1 && pre_counter_blank == 4) {
            node = (a)*5 + b;
            return node;
        }

        if (pre_counter_xv == 3 && pre_counter_blankv == 2) {
            node = (e)*5 + f;
            return node;
        }
        if (pre_counter_xv == 2 && pre_counter_blankv == 3) {
            node = (e)*5 + f;
            return node;
        }
        if (pre_counter_xv == 1 && pre_counter_blankv == 4) {
            node = (e)*5 + f;
            return node;
        }

        counter_blank=0;
        counter_x=0;
        pre_counter_blank=0;
        pre_counter_x=0;
        counter_xv=0;
        counter_blankv=0;
        pre_counter_blankv=0;
        pre_counter_xv=0;
    }

    //diagonal and anti diagonal check
    for(int i=0; i<5; i++){
        if(board[i][i] == 'X') {
            counter_x++;
        }
        if(board[i][i] == ' ') {
            counter_blank++;
            a =i;
        }

        if (board[i][4-i] == 'X') {
            counter_xy++;
        }
        if (board[i][4-i] == ' ') {
            counter_blanky++;
            c = i;
            d = 4-i;
        }

        if(counter_x == 3 && counter_blank ==2 ) {
            node = (a)*5 + a;
            return node;
        }
        if(counter_x ==2 && counter_blank ==3) {
            node = (a)*5 + a;
            return node;
        }
        if(counter_x ==1 && counter_blank ==4) {
            node = (a)*5 + a;
            return node;
        }

        if (counter_xy == 3 && counter_blanky ==2 ) {
            node = (c)*5 + d;
            return node;
        }
        if (counter_xy ==2 && counter_blanky ==3) {
            node = (c)*5 + d;
            return node;
        }
        if (counter_xy ==1 && counter_blanky ==4) {
            node = (c)*5 + d;
            return node;
        }
    }
    counter_x =0;
    counter_blank=0;
    counter_xy=0;
    counter_blanky=0;

    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            if(board[i][j] == ' ') {
                v1.push_back (i);
                v2.push_back (j);
            }
        }
    }

    int vecsize = v1.size();
    int z;
    row = 0;
    col = 0;
    while(board[row][col] != ' ') {
        z = rand()%vecsize+0;
        row = v1[z];
        col = v2[z];
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
