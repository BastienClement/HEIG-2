
public class Labo4 {
    public static int parseInt(String str) throws Exception {
        int val = 0;
        for (int i = str.length() - 1, j = 0; i >= 0; i--, j++) {
            char c = str.charAt(i);
            switch (c) {
                case '0': break;
                case '1': val += 1 * Math.pow(10, j); break;
                case '2': val += 2 * Math.pow(10, j); break;
                case '3': val += 3 * Math.pow(10, j); break;
                case '4': val += 4 * Math.pow(10, j); break;
                case '5': val += 5 * Math.pow(10, j); break;
                case '6': val += 6 * Math.pow(10, j); break;
                case '7': val += 7 * Math.pow(10, j); break;
                case '8': val += 8 * Math.pow(10, j); break;
                case '9': val += 9 * Math.pow(10, j); break;
                case '-': val *= -1; /* no break */
                case '+': if (i == 0) break;
                default: throw new Exception("Invalid character: " + c + " at offset " + i);
            }
        }
        return val;
    }

    public static void sort(int[] array) {
        for (int j = array.length - 1; j >= 1; j--) {
            boolean modified = false;
            for (int i = 0; i < j; i++) {
                if (array[i] > array[i+1]) {
                    int t = array[i+1];
                    array[i+1] = array[i];
                    array[i] = t;
                    modified = true;
                }
            }
            if (!modified) break;
        }
    }

    public static void main(String[] args) throws Exception {
        int[] args_int = new int[args.length];

        for (int i = 0; i < args.length; i++) {
            args_int[i] = parseInt(args[i]);
        }

        sort(args_int);

        for (int arg : args_int) {
            System.out.println(arg);
        }
    }
}
