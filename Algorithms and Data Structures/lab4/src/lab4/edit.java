package lab4;

public class edit {

	private static int iter;
	private static int iter_rec;
	
	public edit() {
        this.iter = 0;
        this.iter_rec = 0;
        
    }
	
	public static int edit_distance(String A, String B) {
        int x = A.length();
        int y = B.length();

        int[][] dp = new int[x + 1][y + 1];

        for (int i = 0; i <= x; i++) {
            for (int j = 0; j <= y; j++) {
                if (i == 0) {
                    dp[i][j] = j;
                } else if (j == 0) {
                    dp[i][j] = i;
                } else if (A.charAt(i - 1) == B.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + Math.min(dp[i - 1][j - 1], Math.min(dp[i - 1][j], dp[i][j - 1]));
                }
                iter += 1;
            }
        }
        
        int i = x;
        int j = y;
        StringBuilder operations = new StringBuilder();
        while (i > 0 && j > 0) {
            if (A.charAt(i - 1) == B.charAt(j - 1)) {
            	operations.insert(0, " "+ A.charAt(i-1));
                i--;
                j--;
            } else if (dp[i][j] == dp[i - 1][j] + 1) {
            	operations.insert(0, " del(" + A.charAt(i-1) + ")");
            	i--;
                
            } else if (dp[i][j] == dp[i][j - 1] + 1) {
            	operations.insert(0, " ins(" + B.charAt(j-1) + ")");
                j--;
                
            } else if(dp[i][j] == dp[i - 1][j - 1] + 1){
                operations.insert(0, " sub(" + A.charAt(i-1) + "," + B.charAt(j-1) + ")");
            	i--;
                j--;
               
            }
            
            
        }
        System.out.println("Operations: " + operations.toString());
        return dp[x][y];
    }
	
	public long iter() {
        return iter;
    }
    
    public long iter_rec() {
        return iter_rec;
    }
	
    public static int edit_distance_rec(String A, String B) {
        int x = A.length();
        int y = B.length();
        iter_rec += 1;
        
        if (x == 0) {
            return y;
        } else if (y == 0) {
            return x;
        } else if (A.charAt(x - 1) == B.charAt(y - 1)) {
            return edit_distance_rec(A.substring(0, x - 1), B.substring(0, y - 1));
        } else {
            int delete = edit_distance_rec(A.substring(0, x - 1), B);
            int insert = edit_distance_rec(A, B.substring(0, y - 1));
            int replace = edit_distance_rec(A.substring(0, x - 1), B.substring(0, y - 1));
            return 1 + Math.min(Math.min(delete, insert), replace);
        }
    }

    
	public static void main(String[] args) {
		edit EDIT = new edit();
		String[] A = {"INTENTION", "SUNDAY", "CART", "QUARANTINE", "KITTEN", "COMPUTER", "APPLE", "HORSE"};
        String[] B = {"EXECUTION", "SATURDAY", "MARCH", "RUNTIME", "SITTING", "CUCUMBER", "BANANA", "ROSES"};
		
		edit_out(EDIT, A, B);
	}

	private static void edit_out(edit EDIT, String[] A, String[] B) {
		for(int i=0;i<A.length;i++) {
			
			int ed_rec = edit_distance_rec(A[i], B[i]);
			System.out.println("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
			int ed = edit_distance(A[i], B[i]);
	        System.out.println("Edit Distance: " + ed + " ---- Iteraions: " + EDIT.iter() +" ---- Recursive iterations: "+ EDIT.iter_rec());
	        System.out.println("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	        iter = 0;
	        iter_rec = 0;
		}
	}

}
