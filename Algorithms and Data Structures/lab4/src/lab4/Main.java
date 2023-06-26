package lab4;

public class Main {

	
	public static void longest_common_subsequenc(String A, String B) {
	    int m = A.length();
	    int n = B.length();
	    int[][] dp = new int[m+1][n+1];
	    
	    for (int i = 0; i <= m; i++) {
	        dp[i][0] = 0;
	    }
	    for (int j = 0; j <= n; j++) {
	        dp[0][j] = 0;
	    }
	    
	    for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 || j == 0)
                    dp[i][j] = 0;
                else if (A.charAt(i - 1) == B.charAt(j - 1))
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
	    
	    print_lcs(A, B);    
	}

	private static void print_lcs(String A, String B) {
		int m = A.length();
	    int n = B.length();
	    int[][] dp = new int[m+1][n+1];
		int index = dp[m][n];
        int temp = index;
        
 
        char[] lcs = new char[index + 1];
        
        while (m > 0 && n > 0) {
            
            if (A.charAt(m - 1) == B.charAt(n - 1)) {
                
                lcs[index -1] = A.charAt(m - 1);
                m--;
                n--;
                index--;
            } else if (dp[m - 1][n] > dp[m][n - 1]) {
            	m--;
            }else {
            	n--;
            }
 
        }
        System.out.print("LCS of "+A+" and "+B+" is ");
        for (int i = 0; i <= temp; i++) {
        	System.out.print(lcs[i]);
        }
        System.out.print(" - Length of LCS = "+(lcs.length-1));
        System.out.println();
	}
	
	public static int editDistanceDP(String a, String b) {
        int m = a.length();
        int n = b.length();
        int[][] dp = new int[m + 1][n + 1];
 
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0) {
                    dp[i][j] = j;
                } else if (j == 0) {
                    dp[i][j] = i;
                } else if (a.charAt(i - 1) == b.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + Math.min(dp[i][j - 1], Math.min(dp[i - 1][j], dp[i - 1][j - 1]));
                }
            }
        }
 
        return dp[m][n];
    }
	
	public static int[][] edit_dist(String str1, String str2) {
		 int m = str1.length();
		    int n = str2.length();
		    int[][] dp = new int[m + 1][n + 1];
		    String[][] sol = new String[m + 1][n + 1];
		    int count = 0;
		    for (int i = 0; i <= m; i++) {
		        for (int j = 0; j <= n; j++) {
		        	count++;
		            if (i == 0) {
		                dp[i][j] = j;
		                if (j != 0) {
		                    sol[i][j] = "insert " + str2.charAt(j - 1);
		                }
		            } else if (j == 0) {
		                dp[i][j] = i;
		                if (i != 0) {
		                    sol[i][j] = "delete " + str1.charAt(i - 1);
		                }
		            } else if (str1.charAt(i - 1) == str2.charAt(j - 1)) {
		                dp[i][j] = dp[i - 1][j - 1];
		                sol[i][j] = "no operation";
		            } else {
		                dp[i][j] = 1 + Math.min(dp[i][j - 1], Math.min(dp[i - 1][j], dp[i - 1][j - 1]));
		                if (dp[i][j] == dp[i][j - 1] + 1) {
		                    sol[i][j] = "insert " + str2.charAt(j - 1);
		                } else if (dp[i][j] == dp[i - 1][j] + 1) {
		                    sol[i][j] = "delete " + str1.charAt(i - 1);
		                } else {
		                    sol[i][j] = "replace " + str1.charAt(i - 1) + " with " + str2.charAt(j - 1);
		                }
		            }
		        }
		    }


	    System.out.println("Iterations: " + count); // print the iteration counter
	    System.out.println("Edit Distance Matrix:");
	    for (int i = 0; i <= m; i++) {
	        for (int j = 0; j <= n; j++) {
	            System.out.print(dp[i][j] + " ");
	        }
	        System.out.println();
	    }
	    System.out.println("Solution Matrix:");
	    for (int i = 0; i <= m; i++) {
	        for (int j = 0; j <= n; j++) {
	            System.out.print(sol[i][j] + " ");
	        }
	        System.out.println();
	    }
	    return dp;
	}
	
	
	public static void main(String[] args) {
	
		String[] a = new String[4];
		String[] b = new String[4];
		a[0] = "ABCDGH";
		a[1] = "AGGTAB";
		a[2] = "ABCBDAB";
		a[3] = "XMJYAUZ";
		
		b[0] = "AEDFHR";
		b[1] = "GXTXAYB";
		b[2] = "BDCABA";
		b[3] = "MZJAWXU";
		
		String[] x = new String[4];
		String[] y = new String[4];
		x[0] = "INTENTION";
		x[1] = "SUNDAY";
		x[2] = "CART";
		x[3] = "QUARANTINE";
		
		y[0] = "EXECUTION";
		y[1] = "SATURDAY";
		y[2] = "MARCH";
		y[3] = "RUNTIME";
		
		// ** TEST **
		String str1 = "OLA";
	    String str2 = "AGA";

	    //int[][] dp = edit_dist(x[0], y[0]);
	    //System.out.println("Edit Distance: " + dp[x[0].length()][y[0].length()]);
		// ** TEST **
		
		for(int i=0;i<a.length;i++) {
			//edit_distance(x[i],y[i]);
			longest_common_subsequenc(a[i],b[i]);
			//System.out.println("Edit Distance: " + editDistanceDP(x[i], y[i]));
			
			
		}
		
		
		 

	}

	private static void edit_distance(String a, String b) {
		
		int[][] distance = new int[a.length() + 1][b.length() + 1];
		String[][] solution = new String[a.length() + 1][b.length() + 1];
		
		for (int i = 1; i <= a.length(); i++) {
		    for (int j = 1; j <= b.length(); j++) {
		        int del = distance[i - 1][j] + 1;
		        int ins = distance[i][j - 1] + 1;
		        int sub = distance[i - 1][j - 1] + ((a.charAt(i - 1) == b.charAt(j - 1)) ? 0 : 1);
		        distance[i][j] = Math.min(Math.min(del, ins), sub);
		        if (distance[i][j] == del) {
		            solution[i][j] = "up";
		        } else if (distance[i][j] == ins) {
		            solution[i][j] = "left";
		        } else {
		            solution[i][j] = "up-left";
		        }
		    }
		}
		
	    for (int i = 0; i <= a.length(); i++) {
	        for (int j = 0; j <= b.length(); j++) {
	            System.out.print(distance[i][j] + " ");
	        }
	        System.out.println();
	    }
	    
	    for (int i = 0; i <= a.length(); i++) {
	        for (int j = 0; j <= b.length(); j++) {
	            System.out.print(solution[i][j] + " ");
	        }
	        System.out.println();
	    }
		System.out.println();
	}

}
