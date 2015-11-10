package util;

import hanoi.*;
import hanoi.gui.*;

public class Test {

	public static void main(String[] args) {
		
		if(args.length == 1) {
			int s = Integer.parseInt(args[0]);
			Hanoi h = new Hanoi(s);
			h.solve(null);;
		}
		else
		new JHanoi();		
	}

}
