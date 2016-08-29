/******************************************************************************|
 | Ray Freeze                                                                   |
 | CSCE 315                                                                     |
 | Due 5 Jun 2016                                                               |
 | Project 3 Group 1                                                            |
 |******************************************************************************/

package com.example.ray.a5tac2;

import android.content.Context;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;

import java.util.Random;


public class MainActivity extends AppCompatActivity {

    /* DATA STRUCTURES -----------------------------------------------------------*/
    char game_board[] = new char[25] ; // holds the game state
    Button[] game_buttons = new Button[25]; // holds the game buttons
    Spinner ai_type; //determines what AI the user wants
    Spinner difficulty; // determines the difficulty of AI's starting move
    Button new_game;
    TextView game_over_txt;
    Button game_over;
    int[] easy_moves = {1, 2, 3, 5, 9, 10, 14, 15, 19, 21, 22, 23};
    //possible starting moves for easy AI
    int[] medium_moves = {0, 4, 20, 24};//possible starting moves for medium AI
    int middle = 12; // the index of the middle button
    Random randGenerator; // for generating random moves
    public native int Minimax(char[] x);
    public native int aStar(int[] x);

    /* MAIN FUNCTION -------------------------------------------------------------*/
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initializeButtons();
        setAll(false); //buttons are disabled by default
        randGenerator = new Random();
    }

    static {
        System.loadLibrary("hello-android-jni");
    }

    /* HELPER FUNCTIONS ----------------------------------------------------------*/
    //Enables or disables all game buttons
    public void setAll(Boolean x){
        for(int i = 0; i < 25; ++i ) {
            game_buttons[i].setEnabled(x);
        }
    }

    // initializes game buttons, first half
    public void initializeButtons(){
        game_buttons[0]  = (Button) findViewById(R.id.button0);
        game_buttons[1]  = (Button) findViewById(R.id.button1);
        game_buttons[2]  = (Button) findViewById(R.id.button2);
        game_buttons[3]  = (Button) findViewById(R.id.button3);
        game_buttons[4]  = (Button) findViewById(R.id.button4);
        game_buttons[5]  = (Button) findViewById(R.id.button5);
        game_buttons[6]  = (Button) findViewById(R.id.button6);
        game_buttons[7]  = (Button) findViewById(R.id.button7);
        game_buttons[8]  = (Button) findViewById(R.id.button8);
        game_buttons[9]  = (Button) findViewById(R.id.button9);
        game_buttons[10] = (Button) findViewById(R.id.button10);
        game_buttons[11] = (Button) findViewById(R.id.button11);
        game_buttons[12] = (Button) findViewById(R.id.button12);
        game_buttons[13] = (Button) findViewById(R.id.button13);
        game_buttons[14] = (Button) findViewById(R.id.button14);
        game_buttons[15] = (Button) findViewById(R.id.button15);
        game_buttons[16] = (Button) findViewById(R.id.button16);
        game_buttons[17] = (Button) findViewById(R.id.button17);
        game_buttons[18] = (Button) findViewById(R.id.button18);
        game_buttons[19] = (Button) findViewById(R.id.button19);
        game_buttons[20] = (Button) findViewById(R.id.button20);
        initializeButtons2(); //second half of initialization
    }

    // initializes game buttons, second half
    public void initializeButtons2(){  //second half of initialization
        game_buttons[21] = (Button) findViewById(R.id.button21);
        game_buttons[22] = (Button) findViewById(R.id.button22);
        game_buttons[23] = (Button) findViewById(R.id.button23);
        game_buttons[24] = (Button) findViewById(R.id.button24);
        game_over_txt = (TextView) findViewById(R.id.game_over_text);
        game_over_txt.setVisibility(View.INVISIBLE);
        game_over = (Button) findViewById(R.id.game_over);
        game_over.setVisibility(View.INVISIBLE);
        game_over.setEnabled(false);
        ai_type = (Spinner) findViewById(R.id.ai_type);
        difficulty = (Spinner) findViewById(R.id.difficulty_type);
        new_game = (Button) findViewById(R.id.new_game);
    }

    //makes the first move for the AI
    public void makeFirstMove(int x){
        int aiMove = -1;
        if (x == 0){ //Easy game
            int index = randGenerator.nextInt( easy_moves.length );
            aiMove = easy_moves[index];
        }
        else if (x == 1){ //Medium game
            int index = randGenerator.nextInt( medium_moves.length );
            aiMove = medium_moves[index];
        }
        else if (x == 2){
            aiMove = middle;
        }
        game_buttons[aiMove].setText("X");
        game_buttons[aiMove].setEnabled(false);
        game_board[aiMove] = 'X';
    }

    public boolean checkRows(char x){
        Boolean winner = false;
        if (game_board[0] == x && game_board[1] == x && game_board[2] == x &&
                game_board[3] == x && game_board[4] == x)
            winner = true;
        if (game_board[5] == x && game_board[6] == x && game_board[7] == x &&
                game_board[8] == x && game_board[9] == x)
            winner = true;
        if (game_board[10] == x && game_board[11] == x && game_board[12] == x &&
                game_board[13] == x && game_board[14] == x)
            winner = true;
        if (game_board[15] == x && game_board[16] == x && game_board[17] == x &&
                game_board[18] == x && game_board[19] == x)
            winner = true;
        if (game_board[20] == x && game_board[21] == x && game_board[22] == x &&
                game_board[23] == x && game_board[24] == x)
            winner = true;
        if (winner) endGame(x);
        return winner;
    }

    public boolean checkColumns(char x){
        Boolean winner = false;
        if (game_board[0] == x && game_board[5] == x && game_board[10] == x &&
                game_board[15] == x && game_board[20] == x)
            winner = true;
        if (game_board[1] == x && game_board[6] == x && game_board[11] == x &&
                game_board[16] == x && game_board[21] == x)
            winner = true;
        if (game_board[2] == x && game_board[7] == x && game_board[12] == x &&
                game_board[17] == x && game_board[22] == x)
            winner = true;
        if (game_board[3] == x && game_board[8] == x && game_board[13] == x &&
                game_board[18] == x && game_board[23] == x)
            winner = true;
        if (game_board[4] == x && game_board[9] == x && game_board[14] == x &&
                game_board[19] == x && game_board[24] == x)
            winner = true;
        if (winner) endGame(x);
        return winner;
    }

    public boolean checkDiags(char x){
        Boolean winner = false;
        if (game_board[0] == x && game_board[6] == x && game_board[12] == x &&
                game_board[18] == x && game_board[24] == x)
            winner = true;
        if (game_board[4] == x && game_board[8] == x && game_board[12] == x &&
                game_board[16] == x && game_board[20] == x)
            winner = true;
        if (winner) endGame(x);
        return winner;
    }

    public void endGame(char x){
        setAll(false);
        new_game.setEnabled(false);
        game_over_txt.setVisibility(View.VISIBLE);
        game_over.setVisibility(View.VISIBLE);
        game_over.setEnabled(true);
        if (x == 'O'){
            game_over_txt.setText("You Win!");
        }
        else if (x== 'X'){
            game_over_txt.setText("You Lose!");
        }
        else{
            game_over_txt.setText("Cats Game!");
        }
    }

    public void gameOverClick(View v){
        Button current = (Button) v;
        game_over_txt.setVisibility(View.INVISIBLE);
        game_over.setVisibility(View.INVISIBLE);
        game_over.setEnabled(false);
        new_game.setEnabled(true);
    }


    /* FUNCTIONAL METHODS --------------------------------------------------------*/
    //Determines where the AI will move
    public int calculateMove() {
        int newboard[] = new int[25];
        for (int i = 0; i < 25; ++i) {
            if (game_board[i] == ' ') newboard[i] = 0;
            if (game_board[i] == 'X') newboard[i] = -1;
            if (game_board[i] == 'O') newboard[i] = 1;
        }
        if (ai_type.getSelectedItemPosition() == 0) {
            return Minimax(game_board);
        }
        else if (ai_type.getSelectedItemPosition() == 1) {
            return aStar(newboard);
        }
        else{ return 25; }
    }

    //Checks to see if someone has won
    public boolean checkWinner(char player){
        if( checkRows(player) || checkColumns(player) || checkDiags(player) )
            return true;
        else return false;
    }

    //Checks to see if the game is full
    public void checkFull(){
        for(int i = 0; i < 25; ++i) {
            if (game_board[i] == ' ')
                return; //there is an empty place
        }
        endGame(' '); // cats game
    }

    //Method is called when user selects a move
    public void onClick(View v){
        Button current = (Button) v;
        setAll(false); //disable buttons from being clicked while ai thinks
        for(int i = 0; i < 25; ++i) {
            if (current == game_buttons[i]) {
                game_buttons[i].setText("O");
                game_board[i] = 'O';
                if (checkWinner('O')) return;
                int aiMove = calculateMove();
                game_buttons[aiMove].setText("X");
                game_board[aiMove] = 'X';
                if (checkWinner('X')) return;
                checkFull();
            }
        }
        for(int i = 0; i < 25; ++i ){
            if (game_board[i] == ' ') game_buttons[i].setEnabled(true);
            //re-enable buttons that haven't been clicked yet
        }
    }

    //Resets the board
    public void newGame(View v){
        for(int i = 0; i < 25; ++i) {  // initializes an empty board
            game_board[i] = ' ';
            game_buttons[i].setEnabled(true);
            game_buttons[i].setText(" ");
        }
        int x = difficulty.getSelectedItemPosition();
        makeFirstMove(x);
    }

}
