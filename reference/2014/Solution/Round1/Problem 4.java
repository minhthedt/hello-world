import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

/**
 * @author Taeseong
 * Problem 4
 */
class Word implements Comparable<Word> {

    private String str;
    private int len;

    public void setLen(int len) {
        this.len = len;
    }

    public int getLen() {
        return len;
    }

    public Word(String str) {
        this.str = str;
        this.len = str.length();
    }

    @Override
    public int compareTo(Word o) {
        return str.compareTo(o.str);
    }

    public String getStr() {
        return str;
    }

    @Override
    public String toString() {
        String ret = str;
        int rest = len - str.length();
        while (rest-- != 0) {
            ret += "_";
        }
        return ret;
    }

    public int getStrLen() {
        return str.length();
    }
}

public class Main {

    private static int w;
    private static int c;
    private static ArrayList<Word> list = new ArrayList<Word>();
    private static int line;

    public static void main(String[] args) {
        input();
        process();
        output();
    }

    private static void output() {
        //        Iterator<Word> it = list.iterator();
        //        while (it.hasNext()) {
        //            System.out.println(it.next());
        //        }

        for (int l = 0; l < line; l++) {
            String str = "";
            for (int i = l; i < c; i += line) {
                str += list.get(i) + "__";
            }
            while (str.length() < w + 2) {
                str += "_";
            }
            System.out.println(str.substring(0, str.length() - 2));
        }
    }

    private static void process() {
        Collections.sort(list);

        int max = w + 1;
        line = 0;

        while (max > w) {
            line++;
            max = 0;
            int[] totalLen = new int[line];
            for (int i = 0; i < c; i += line) {
                int longest = 0;
                for (int j = 0; j < line && i + j < c; j++) {
                    longest = Math.max(longest, list.get(i + j).getStrLen());
                }
                for (int j = 0; j < line && i + j < c; j++) {
                    totalLen[j] += longest + 2;
                    list.get(i + j).setLen(longest);
                }
            }
            for (int j = 0; j < line; j++) {
                max = Math.max(totalLen[j], max);
            }
            max -= 2;
        }
    }

    private static void input() {
        Scanner sc = new Scanner(System.in);
        w = sc.nextInt();
        c = sc.nextInt();
        int cnt = c;
        while (cnt-- > 0) {
            String str = sc.next();
            list.add(new Word(str));
        }
        sc.close();
    }

}
