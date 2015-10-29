
class Operation {
    public boolean op(boolean a, boolean b) {
        throw new RuntimeException("Not implemented");
    }

    public static Operation and = new And();
    public static Operation or = new Or();
    public static Operation xor = new Xor();
}

class And extends Operation {
    public boolean op(boolean a, boolean b) { return a & b; }
}

class Or extends Operation {
    public boolean op(boolean a, boolean b) { return a | b; }
}

class Xor extends Operation {
    public boolean op(boolean a, boolean b) { return a ^ b; }
}

public class Matrix {
    boolean[][] matrix;

    private Matrix(boolean[][] m) {
        this.matrix = m;
    }

    public Matrix(int size) {
        if (size < 1) {
            throw new IllegalArgumentException("Matrix size must be at least 1");
        }

        matrix = new boolean[size][size];

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] = Math.random() >= 0.5;
            }
        }
    }

    public int getSize() {
        return matrix.length;
    }

    public Matrix op(Operation o, Matrix m) {
        int size = getSize();

        if (size != m.getSize()) {
            throw new IllegalArgumentException("Matrix dimensions must match");
        }

        Matrix r = new Matrix(size);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                r.matrix[i][j] = o.op(this.matrix[i][j], m.matrix[i][j]);
            }
        }

        return r;
    }

    public Matrix and(Matrix m) { return op(Operation.and, m); }
    public Matrix or(Matrix m) { return op(Operation.or, m); }
    public Matrix xor(Matrix m) { return op(Operation.xor, m); }

    public String toString() {
        String str = "";
        int size = matrix.length;
        for (boolean[] line : matrix) {
            for (boolean value : line) {
                str += (value ? "1" : "0") + " ";
            }
            str += "\n";
        }
        return str;
    }

    public static void main(String... args) {
        Matrix one = new Matrix(4);
        Matrix two = new Matrix(4);

        System.out.println("one");
        System.out.println(one);

        System.out.println("two");
        System.out.println(two);

        System.out.println("oneOrTwo = one or two");
        System.out.println(one.or(two));

        System.out.println("oneAndTwo = one and two");
        System.out.println(one.and(two));

        System.out.println("oneXorTwo = one xor two");
        System.out.println(one.xor(two));
    }
}
