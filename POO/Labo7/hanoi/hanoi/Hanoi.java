package hanoi;

import java.util.Iterator;

import hanoi.gui.JHanoi;
import util.Stack;

public class Hanoi {
	Stack<Integer>[] sticks = new Stack[3];
	int turn = 1;
	boolean finished = false;
	
	public Hanoi(int h) {
		for(int i = 0; i < 3 ; i++)
			sticks[i] = new Stack<Integer>();
		for(;h > 0; h--) {
			sticks[0].push(h);
		}
	}
	
	public void solve(JHanoi frame) {
		printStep();
		if (frame != null) frame.display();
		resolve(frame, sticks[0].size(), sticks[0], sticks[2], sticks[1]);
		finished = true;
	}
	
	
	
	private int resolve(JHanoi frame, int n, Stack<Integer> D, Stack<Integer> A, Stack<Integer> I) {
		if(n == 0)
			return 0;
		
		int steps = 1;
		steps += resolve(frame, n-1, D, I, A);
		A.push(D.pop());
		printStep();
		if (frame != null) frame.display();
		steps += resolve(frame, n-1, I, A, D);
		return steps;
	}
	
	private void printStep() {
		System.out.println("-- Turn: " + turn++);
		System.out.println(this);
	}
	
	public String toString() {
		String s = "One:\t" + sticks[0] + "\n";
		s+= "Two:\t" + sticks[1] + "\n";
		s+="Three:\t" +sticks[2] +"\n";
		
		return s;
	}
	
	
	public int[][] status() {
		int[][] t = new int[3][];
		
		for(int i = 0; i < 3; i++) {
			Stack<Integer> stick = sticks[i];
			t[i] = new int[stick.size()];
			Iterator<Integer> it = stick.iterator();
			for(int j = 0; it.hasNext(); j++) {
				t[i][j] = it.next();
			}
		}
		
		return t;
	}
	
	public boolean finished() {
		return finished;
	}
	
	public int turn() {
		return turn;
	}
	
	
	
}
