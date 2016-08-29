import com.sun.jna.Library;
import com.sun.jna.Native;

public class HelloJNI {
	public interface Hello extends Library {
		public void helloFromC();
		public int minimax( char[] board);
	}

	/* static public void main(String[] args) {
		Hello hello = (Hello) Native.loadLibrary("hello", Hello.class);
		hello.helloFromC();
		int themove = 0;
		int player = 1;
		int depth = 6;
		int[] board = new int[]{
				1,0,-1,-1,-1,0,0,0,0,0,
				1,1,0,0,0,0,0,0,0,0,
				0,0,0,0,0};
		
		themove = hello.minimax(board, player, depth);
		System.out.println("The computer has made a move: ");
		System.out.println(themove);
	} */
	
	static public int MiniMax(char[] board) {
		int newboard[25];
		for(int i=0; i<25; ++i) {
			if(board[i] == ' ') newboard[i] = 0;
			if(board[i] == 'X') newboard[i] = -1;
			if(board[i] == 'O') newboard[i] = 1;
			
		}
		
		Hello hello = (Hello) Native.loadLibrary("hello", Hello.class);
		//hello.helloFromC();
		int theMove = 0;
		int player = -1;
		int depth = 6;
		theMove = hello.minimax(newboard, player, depth);
		System.out.println("The computer has made a move: ");
		System.out.println(theMove);
		return theMove;
	}
	
}