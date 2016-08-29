package com.example.ray.a5tac2;

import android.os.AsyncTask;

import java.util.ArrayList;

/**
 * Created by Ray on 7/4/2016.
 */

class minmaxThread extends AsyncTask<char[], Void, Integer> {
    public native int Minimax(char[] x);
    static {
        System.loadLibrary("hello-android-jni");
    }
    protected Integer doInBackground(char[]... board) {
        int result = 0;
        char[] newboard = board[0];
        //int filledspot = params[0].filledspot;
        result = Minimax(newboard);
        return result;
    }

}

public class aiExtend {
    ArrayList threads = new ArrayList<minmaxThread>();
    ArrayList filledspots = new ArrayList<Integer>();
    public void runMinMax(char[] board) {
        threads.clear();
        filledspots.clear();
        for(int i = 0; i < 25; ++i) {
            if(board[i] == ' ') {
                char[] newboard = board;
                //filledspot = i;
                newboard[i] = 'O';
                filledspots.add(i);
                //taskparams params = new taskparams(board, filledspot);
                threads.add(new minmaxThread().execute(newboard));
            }
        }
    }
    public void runAStar(int[] board) {

    }
    public int checkThreads(int playermove) {
        for(int i = 0; i < 25; ++i) {
            if(playermove == (Integer)filledspots.get(i)) {
                int result = (Integer)threads.get(i);
                return result;
            }
            else return -1;
        }
        return -1;
    }
}
