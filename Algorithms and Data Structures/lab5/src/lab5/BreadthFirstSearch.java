package lab5;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class BreadthFirstSearch  {
    private int numberOfNodes;
    private static int iter;
    private static int pathLength;
    private List<List<Integer>> adjacencyList;

    public BreadthFirstSearch (int numberOfNodes) {
        this.numberOfNodes = numberOfNodes;
        this.iter = 0;
        this.pathLength = 0;
        adjacencyList = new ArrayList<>(numberOfNodes);
        for (int i = 0; i < numberOfNodes; i++) {
            adjacencyList.add(new ArrayList<>());
        }
    }
     
    public void addEdge(int source, int target) {
        adjacencyList.get(source - 1).add(target - 1);
    }

    public List<Integer> findShortestPath(int start, int end) {
        boolean[] visited = new boolean[numberOfNodes];
        int[] parent = new int[numberOfNodes];

        Queue<Integer> queue = new LinkedList<>();
        visited[start - 1] = true;
        queue.add(start - 1);

        while (!queue.isEmpty()) {
            int size = queue.size();
            
            for (int i = 0; i < size; i++) {
                int currentNode = queue.poll();

                if (currentNode == end - 1) {
                    List<Integer> path = constructPath(parent, start, end);
                    iter++;
                    return path;
                }

                for (int neighbor : adjacencyList.get(currentNode)) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        parent[neighbor] = currentNode;
                        queue.add(neighbor);
                    }
                    iter++;
                }
                
            }
            
        }

        pathLength = 0;
        iter = 0;
        return Collections.emptyList(); // No path found
    }

    private List<Integer> constructPath(int[] parent, int start, int end) {
        List<Integer> path = new ArrayList<>();
        int currentNode = end - 1;
        while (currentNode != start - 1) {
            path.add(currentNode + 1);
            currentNode = parent[currentNode];
            pathLength++;
        }
        path.add(start);
        pathLength++;
        Collections.reverse(path);
        return path;
    }

    public static void main(String[] args) {
        output("b10.txt",3,9,8,9);
        output("b20.txt",10,11,5,7);
        output("b50.txt",5,7,7,9);
        output("b100.txt",6,9,99,100);
    }

	private static void output(String file, int a, int b, int c, int d) {
		try {
            Scanner scanner = new Scanner(new File(file));
            int numberOfNodes = scanner.nextInt();
            int numberOfEdges = scanner.nextInt();

            BreadthFirstSearch  graph = new BreadthFirstSearch (numberOfNodes);

            for (int i = 0; i < numberOfEdges; i++) {
                int source = scanner.nextInt();
                int target = scanner.nextInt();
                graph.addEdge(source, target);
            }
            System.out.println("File: "+file);
            List<Integer> firstPath = graph.findShortestPath(a, b);
            System.out.println("First path: " + firstPath);
            System.out.println("Length of the first path: " + graph.get_pathLength());
            System.out.println("Iterations for the first path: " + graph.get_iter()+"\n");
            iter = 0;
            pathLength = 0;
            List<Integer> secondPath = graph.findShortestPath(c, d);
            System.out.println("Second path: " + secondPath);
            System.out.println("Length of the second path: " + graph.get_pathLength());
            System.out.println("Iterations for the second path: " + graph.get_iter()+"\n");
            
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
	}
    
    public long get_iter() {
        return iter;
    }
    
    public long get_pathLength() {
        return pathLength;
    }
}




