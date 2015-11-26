
public abstract class Operator {
	protected State state;
	protected final int nbOperand;
	
	Operator(State state, int nbOperand){
		this.state = state;
		this.nbOperand = nbOperand;
		
	}

	public void execute() {
		try {
			if(canExecute()) {
				run();
			}
		} catch (OperatorException e) {
			e.printStackTrace();
		}
		
	}
	
	
	public boolean canExecute() throws OperatorException {
		if(state.stackSize() < nbOperand-1)
			throw new OperatorException("Not enough operands");
		return !state.hasError();
	}
	
	protected abstract void run()throws OperatorException;
	
	
	
	@SuppressWarnings("serial")
	public static class OperatorException extends Exception {

		public OperatorException(String string) {
			super(string);
		}
	}
	public abstract static class UnaryOperator extends Operator {
		public UnaryOperator() {
			super(state, 1);
		}
		
		public void run() throws OperatorException {
			state.pushDisplay();
			double b = state.pop();
			double a = state.pop();
			
			double r = op(a);
			
			state.setDisplay(Double.toString(r));
			
			state.push(r);
		}
		
		
		abstract public double op(double a);
	}	
	public abstract static class BinaryOperator extends Operator {

		BinaryOperator(State state) {
			super(state, 2);
		}
		
		public void run() throws OperatorException {
			state.pushDisplay();
			double b = state.pop();
			double a = state.pop();
			
			double r = op(a,b);
			
			state.setDisplay(Double.toString(r));
		}
		
		abstract public double op(double a, double b) ;
	}
	
	public static class Add extends BinaryOperator {

		Add(State state) {
			super(state);
		}

		public double op(double a, double b) {
			return a+b;
		}


	}
	public static class Substract extends BinaryOperator{

		Substract(State state) {
			super(state);			
		}

		public double op(double a, double b) {
			return a-b;
		}		
	 }
	 
	public static class Multiply extends BinaryOperator {

		Multiply(State state) {
			super(state);
		}

		public double op(double a, double b) {
			return a*b;
		}
	}
	
	public static class Divide extends BinaryOperator {

		Divide(State state) {
			super(state);
		}

		public double op(double a, double b) {
			return a/b;
		}		
	}
	
	public static class SquareRoot extends Operator {

		SquareRoot(State state) {
			super(state, 1);
		}

		protected void run() throws OperatorException {
			state.push(Math.sqrt(state.pop()));			
		}
	}
	public static class Square extends Operator {

		Square(State state) {
			super(state, 1);
		}

		protected void run() throws OperatorException {
			state.push(Math.pow(state.pop(), 2));
		}
	}
	
	public static class Inverse extends Operator {

		Inverse(State state) {
			super(state, 1);
		}

		protected void run() throws OperatorException {
			state.push(Math.pow(state.pop(), -1));
		}
	}
	
	public static class Clear extends Operator {

		Clear(State state, int nbOperand) {
			super(state, 0);
		}

		protected void run() throws OperatorException {
			state.setDisplay("");
			state.setError(false);
			state.emptyStack();
		}
		
	}
	
	public static class ClearError extends Operator {
		
		ClearError(State state, int nbOperand) {
			super(state, 0);
		}

		protected void run() throws OperatorException {
			state.setDisplay("");
			state.setError(false);
		}		
	}
	
	public static class MemoryRecall extends Operator {

		MemoryRecall(State state) {
			super(state, 0);
		}

		protected void run() throws OperatorException {			
			state.setDisplay(Double.toString(state.getMemory()));
		}
		
	}
	
	public static class MemoryStore extends Operator {

		MemoryStore(State state) {
			super(state, 0);
		}
		
		protected void run() throws OperatorException {
			state.setMemory(Double.valueOf(state.getDisplay()));
		}		
	}
	
	public static class Backspace extends Operator {

		Backspace(State state) {
			super(state, 0);
		}
		
		protected void run() throws OperatorException {
			String s = state.getDisplay();
			if(s.length() > 0);
				state.setDisplay(s.substring(0, s.length()-1));
		}
	}
	
	public static class Enter extends Operator {

		Enter(State state) {
			super(state, 0);
		}

		protected void run() throws OperatorException {
			state.push(Double.valueOf(state.getDisplay()));
			state.setDisplay("");
		}
		
	}
	public static class Opposite extends Operator {

		Opposite(State state) {
			super(state, 0);
		}

		protected void run() throws OperatorException {
			state.setDisplay(Double.toString((Double.valueOf(state.getDisplay())*-1)));
		}
		
	}
	public static class Number extends Operator {

		int value;
		
		Number(State state, int value) {
			super(state, 0);
			this.value = value;
		}

		protected void run() throws OperatorException {
			
		}
	}
	
	public static class Dot extends Number {

		Dot(State state) {
			super(state);
			// TODO Auto-generated constructor stub
		}}
}

