import java.util.Stack;

public class State {

	private Stack<Double> s = new Stack<Double>();
	private String display = "0";
	private double memory = 0.0;
	private boolean error = false; 
	private boolean displayHasChanged;

	
	
	public void push(double d){
		s.push(d);
	}
	
	public double pop() {
		return s.pop();
	}
	
	public void pushDisplay() {
		s.push(Double.valueOf(display));
		display = "0";
	}
	
	public int stackSize() {
		return s.size();
	}
	
	public boolean stackEmpty() {
		return s.empty();
	}
	
	public boolean hasError() {
		return error;
	}
	
	public void setError(boolean b) {
		error = b;
	}
	
	public void setDisplay(String string) {
		display = string;
	}
	
	public String getDisplay() {
		return display;
	}
	
	public void emptyStack() {
		while(s.size() != 0) {
			s.pop();
		}
	}
	
	public void setMemory(double d) {
		memory = d;
	}
	
	public double getMemory() {
		return memory;
	}
}
