import java.util.Stack;

public class State {
	private Stack<Double> stack = new Stack<>();

	private double result;
	private double memory;
	private String input;
	private String error;

	// ========================================================================

	State() { clearAll(); }

	public void clearAll() {
		stack.clear();
		clearError();
		clearDisplay();
		memory = 0.0;
	}

	public void clearDisplay() {
		result = 0.0;
		input = null;
	}

	// ========================================================================

	public String getDisplayString() {
		if (error != null) {
			return error;
		} else if (input != null) {
			return input.length() == 0 ? "0" : input;
		} else {
			long ipart = (long) result;
			double fpart = result - ipart;
			return fpart == 0 ? Long.toString(ipart) : Double.toString(result);
		}
	}

	public Object[] getStackArray() {
		if (stackSize() < 1) {
			return new String[]{"< empty stack >"};
		}

		int size = stack.size();
		Object[] arr = new Object[size];

		for (int i = 0; i < size; i++) {
			arr[size - i - 1] = Double.toString(stack.elementAt(i));
		}

		return arr;
	}

	// ========================================================================

	public double getResult() {
		if (input != null) return Double.valueOf(input);
		else return result;
	}

	public void setResult(Double value) {
		result = value;
		input = null;
	}

	// ========================================================================

	public String getInput() {
		return input == null ? "" : input;
	}

	public void setInput(String i) {
		input = i;
	}

	// ========================================================================

	public void pushResult() {
		stack.push(getResult());
		clearDisplay();
	}

	public double pop() {
		return stack.pop();
	}

	public int stackSize() {
		return stack.size();
	}

	// ========================================================================

	public void setMemory(double d) {
		memory = d;
	}

	public double getMemory() {
		return memory;
	}

	// ========================================================================

	public boolean hasError() {
		return error != null;
	}

	public void setError(String message) {
		error = message;
	}

	public void setError(Exception exception) {
		setError(exception.getMessage());
	}

	public void clearError() {
		error = null;
	}
}
