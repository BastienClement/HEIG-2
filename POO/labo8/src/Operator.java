
public abstract class Operator {
	protected State state;

	Operator(State state) {
		this.state = state;
	}

	public void execute() {
		try {
			if (valid()) run();
		} catch (Exception e) {
			state.setError(e);
		}
	}

	protected boolean valid() throws Exception {
		return !state.hasError();
	}

	protected abstract void run() throws Exception;

	// ========================================================================

	public abstract static class UnaryOperator extends Operator {
		public UnaryOperator(State state) { super(state); }
		abstract protected double op(double a);
		protected void run() {
			double a = state.getDisplay();
			double r = op(a);
			state.setDisplay(r);
		}
	}

	public abstract static class BinaryOperator extends Operator {
		BinaryOperator(State state) { super(state); }
		abstract protected double op(double a, double b);

		protected boolean valid() throws Exception {
			if (state.stackSize() < 1) throw new Exception("Not enough operands");
			return super.valid();
		}

		protected void run() {
			double b = state.getDisplay();
			double a = state.pop();
			double r = op(a, b);
			state.setDisplay(r);
		}
	}

	public abstract static class DisplayOperator extends Operator {
		DisplayOperator(State state) { super(state); }
		abstract protected String apply(String value);
		protected void run() {
			String input = state.getInput();
			String result = apply(input);
			state.setInput(result);
		}
	}

	// ========================================================================

	public static class Add extends BinaryOperator {
		Add(State state) { super(state); }
		public double op(double a, double b) { return a + b; }
	}

	public static class Subtract extends BinaryOperator {
		Subtract(State state) { super(state); }
		protected double op(double a, double b) { return a - b; }
	}

	public static class Multiply extends BinaryOperator {
		Multiply(State state) { super(state); }
		protected double op(double a, double b) { return a * b; }
	}

	public static class Divide extends BinaryOperator {
		Divide(State state) { super(state); }
		protected double op(double a, double b) { return a / b; }
	}

	// ========================================================================

	public static class SquareRoot extends UnaryOperator {
		SquareRoot(State state) { super(state); }
		protected double op(double a) { return Math.sqrt(a); }
	}

	public static class Square extends UnaryOperator {
		Square(State state) { super(state); }
		protected double op(double a) { return a * a; }
	}

	public static class Inverse extends UnaryOperator {
		Inverse(State state) { super(state); }
		protected double op(double a) { return 1.0 / a; }
	}

	public static class Opposite extends UnaryOperator {
		Opposite(State state) { super(state); }
		protected double op(double a) { return -a; }
	}

	// ========================================================================

	public static class Clear extends Operator {
		Clear(State state) { super(state); }
		protected boolean valid() { return true; }
		protected void run() { state.clearAll(); }
	}

	public static class ClearError extends Operator {
		ClearError(State state) { super(state); }
		protected boolean valid() { return true; }
		protected void run() { state.clearError(); }
	}

	// ========================================================================

	public static class MemoryRecall extends Operator {
		MemoryRecall(State state) { super(state); }
		protected void run() { state.setDisplay(state.getMemory()); }
	}

	public static class MemoryStore extends Operator {
		MemoryStore(State state) { super(state); }
		protected void run() { state.setMemory(state.getDisplay()); }
	}

	public static class Enter extends Operator {
		Enter(State state) { super(state); }
		protected void run() { state.pushDisplay(); }
	}

	// ========================================================================

	public static class Backspace extends DisplayOperator {
		Backspace(State state) { super(state); }

		protected String apply(String input) {
			if (input.length() > 0) input = input.substring(0, input.length() - 1);
			return input;
		}
	}

	public static class Digit extends DisplayOperator {
		char digit;

		Digit(State state, char digit) {
			super(state);
			this.digit = digit;
		}

		/*protected boolean valid() throws Exception {
			return super.valid() && state.getInput().length() < 10;
		}*/

		protected String apply(String input) {
			return input + digit;
		}
	}

	public static class Zero extends Digit {
		Zero(State state) { super(state, '0'); }

		protected boolean valid() throws Exception {
			return super.valid() && state.getInput().length() > 0;
		}
	}

	public static class Dot extends Digit {
		Dot(State state) { super(state, '.'); }

		protected boolean valid() throws Exception {
			return super.valid() && state.getInput().indexOf('.') == -1;
		}

		protected String apply(String input) {
			return super.apply(input.length() < 1 ? "0" : input);
		}
	}
}

