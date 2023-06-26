package lab4;


public class lcs {

	private static int iter;
	private static int iter_rec;
	
	public lcs() {
        this.iter = 0;
        this.iter_rec = 0;
        
    }
	
	public static void main(String[] args) {
		String[] A = {"ABCDGH", "AGGTAB", "ABCBDAB", "XMJYAUZ", "QWERTY", "MLPNKO", "ZXCVBN", "IKUJYH"};
        String[] B = {"AEDFHR", "GXTXAYB", "BDCABA", "MZJAWXU", "ASDRTY", "MLBHOP", "ZASXDCV", "IOLKYJH"};
		lcs_out(A, B);
        
    }

	private static void lcs_out(String[] A, String[] B) {
		lcs LCS = new lcs();
        int[][] table = new int[A.length][A.length];
        int[] length = new int[A.length];
        
        for(int i =0;i<A.length;i++) {
        	table = lcs_table(A[i], B[i]);
        	length[i] = table[A[i].length()][B[i].length()];
        	String lcs = lcs_string(table, A[i], B[i]);
        	String lcs_rec = lcs_rec(A[i], B[i]);
        	System.out.println("A: "+A[i]+"    B: "+B[i]+"    Length of LCS: " + length[i] + "    LCS: " + lcs + "    Iterations: " + LCS.iter() + "    Recursive Iteraions: "+ LCS.iter_rec());
        	iter = 0;
        	iter_rec = 0;
        }
	}
    
    public static int[][] lcs_table(String A, String B) {
        int m = A.length();
        int n = B.length();
        int[][] table = new int[m + 1][n + 1];
        
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 || j == 0) {
                    table[i][j] = 0;
                } else if (A.charAt(i - 1) == B.charAt(j - 1)) {
                    table[i][j] = table[i - 1][j - 1] + 1;
                } else {
                    table[i][j] = Math.max(table[i - 1][j], table[i][j - 1]);
                }
                iter += 1;
            }
            
        }
        return table;
    }
    
    public static String lcs_string(int[][] table, String A, String B) {
        StringBuilder lcs = new StringBuilder();
        int i = A.length();
        int j = B.length();
        
        while (i > 0 && j > 0) {
            if (A.charAt(i - 1) == B.charAt(j - 1)) {
                lcs.append(A.charAt(i - 1));
                i--;
                j--;
            } else if (table[i - 1][j] > table[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        return lcs.reverse().toString();
    }
    
    public long iter() {
        return iter;
    }
    
    public long iter_rec() {
        return iter_rec;
    }
	
    public static String lcs_rec(String A, String B) {
        int m = A.length() - 1;
        int n = B.length() - 1;
        iter_rec += 1;
        if (m < 0 || n < 0) {
        	return "";
        }
            
        
        if (A.charAt(m)==B.charAt(n)) {
            return lcs_rec(A.substring(0, m), B.substring(0, n)) + A.substring(m);
        } 
        else {
            String s1 = lcs_rec(A, B.substring(0, n));
            String s2 = lcs_rec(A.substring(0, m), B);
            if (s1.length() > s2.length()) {
                return s1;
            } else {
                return s2;
            }
        }
    }
}
