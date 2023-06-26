package lab5;

import java.io.*;

public class FloydWarshall {
    private static final int INF = Integer.MAX_VALUE;
    private static int iter;
    private static int routes;
    
    public FloydWarshall() {
        this.iter = 0;
        this.routes = 0;
        
    }
    
    public static void main(String[] args) {
        output("g1000.txt", "g1000_out.txt");
        System.out.println("Iterations: "+iter+" Routes: "+routes);
    }

	private static void output(String input, String output) {

        try {
            BufferedReader br = new BufferedReader(new FileReader(input));
            BufferedWriter bw = new BufferedWriter(new FileWriter(output));

            String line = br.readLine();
            String[] tokens = line.split(" ");
            int nodes = Integer.parseInt(tokens[0]); 
            int edges = Integer.parseInt(tokens[1]); 

            // initialize the graph using inf value
            int[][] graph = new int[nodes + 1][nodes + 1];
            for (int i = 1; i <= nodes; i++) {
                for (int j = 1; j <= nodes; j++) {
                    if (i == j) {
                        graph[i][j] = 0;
                    } else {
                        graph[i][j] = INF;
                    }
                }
                
            }
            
            // edges and weights from input
            for (int i = 0; i < edges; i++) {
                line = br.readLine();
                tokens = line.split(" ");
                int source = Integer.parseInt(tokens[0]);
                int target = Integer.parseInt(tokens[1]);
                int weight = Integer.parseInt(tokens[2]);
                graph[source][target] = weight;
            }

            floyd_w(graph, nodes, bw);

            br.close();
            bw.close();

         
            for (int i = 1; i <= nodes; i++) {
                for (int j = 1; j <= nodes; j++) {
                	if (graph[i][j] == INF) {
                	    System.out.print("INF\t");
                	} else {
                	    System.out.print(graph[i][j] + "\t");
                	}
                }
                System.out.println();
            }
            
            System.out.println("\nOutput written to " + output);
        } catch (IOException e) {
            e.printStackTrace();
        }
	}

    private static void floyd_w(int[][] graph, int nodes, BufferedWriter bw) throws IOException {
        int[][] dist = new int[nodes + 1][nodes + 1];
        int[][] next = new int[nodes + 1][nodes + 1];
        
        for (int i = 1; i <= nodes; i++) {
            for (int j = 1; j <= nodes; j++) {
                dist[i][j] = graph[i][j];
                if (dist[i][j] != INF && i != j) {
                    next[i][j] = j;
                } else {
                    next[i][j] = -1;
                }
            }
        }
        
        for (int k = 1; k <= nodes; k++) {
            for (int i = 1; i <= nodes; i++) {
                for (int j = 1; j <= nodes; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                    iter++;
                }
            }
        }

        for (int i = 1; i <= nodes; i++) {
            for (int j = 1; j <= nodes; j++) {
                if (dist[i][j] == INF) {
                    bw.write("d[" + i + "," + j + "] = INF, No path\n");
                } else if(i != j){
                    bw.write("d[" + i + "," + j + "] = " + dist[i][j] + " PATH: " + get_path(i, j, next) + "\n");
                    routes++;
                }
            }
        }
    }

    private static String get_path(int i, int j, int[][] next) {
        if (next[i][j] == -1) {
            return i + "-" + j;
        }

        StringBuilder path = new StringBuilder();
        path.append(i);

        while (i != j) {
            i = next[i][j];
            path.append("-");
            path.append(i);
        }

        return path.toString();
    }
    
    public long iter() {
        return iter;
    }
    
    public long routes() {
        return routes;
    }
    
}


