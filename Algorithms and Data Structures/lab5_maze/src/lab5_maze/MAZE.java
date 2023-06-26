package lab5_maze;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

class MAZE {
    static class Point {
        int x, y;
        
        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
        
        @Override
        public boolean equals(Object obj) {
            if (this == obj)
                return true;
            if (obj == null || getClass() != obj.getClass())
                return false;
            Point other = (Point) obj;
            return x == other.x && y == other.y;
        }
        
        @Override
        public int hashCode() {
            return Objects.hash(x, y);
        }
    }
    
    public static void main(String[] args) {
        output("m8x15.txt");
        
    }

	private static void output(String filePath) {
		
        char[][] maze = readMazeFromFile(filePath);
        List<Point> path = solveMaze(maze);
        
        if (path.isEmpty()) {
            System.out.println("No path found.");
        } else {
            System.out.println("Shortest path:");
            for (Point point : path) {
                System.out.println("[" + point.x + ", " + point.y + "]");
            }
            
            markPathOnMaze(maze, path);
            
            System.out.println("\nSolved maze:");
            printMaze(maze);
            
            int pathLength = path.size();
            System.out.println("Path length: " + pathLength);
        }
	}
    
    private static char[][] readMazeFromFile(String filePath) {
        char[][] maze = null;
        
        try (Scanner scanner = new Scanner(new FileReader(filePath))) {
            int width = scanner.nextInt();
            int height = scanner.nextInt();
            
            maze = new char[height][width];
            scanner.nextLine();
            
            for (int i = 0; i < height; i++) {
                String line = scanner.nextLine();
                for (int j = 0; j < width; j++) {
                    maze[i][j] = line.charAt(j);
                }
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        
        return maze;
    }
    
    private static List<Point> solveMaze(char[][] maze) {
        int[][] directions = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
        int height = maze.length;
        int width = maze[0].length;
        Point start = null;
        Point end = null;
        
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (maze[i][j] == 'I') {
                    start = new Point(j, i);
                } else if (maze[i][j] == 'O') {
                    end = new Point(j, i);
                }
            }
        }
        
        if (start == null || end == null) {
            throw new IllegalArgumentException("Start or end point not found in the maze.");
        }
        
        Map<Point, Point> parentMap = new HashMap<>();
        Queue<Point> queue = new LinkedList<>();
        Set<Point> visited = new HashSet<>();
        
        queue.offer(start);
        visited.add(start);
        
        int iterations = 0; // Variable to count iterations
        
        while (!queue.isEmpty()) {
            iterations++; // Increment the iteration count
            Point current = queue.poll();
            
            if (current.equals(end)) {
                break;
            }
            
            for (int[] dir : directions) {
                int newX = current.x + dir[0];
                int newY = current.y + dir[1];
                
                if (newX >= 0 && newX < width && newY >= 0 && newY < height
                        && (maze[newY][newX] == '.' || maze[newY][newX] == 'O')
                        && !visited.contains(new Point(newX, newY))) {
                    Point neighbor = new Point(newX, newY);
                    parentMap.put(neighbor, current);
                    queue.offer(neighbor);
                    visited.add(neighbor);
                }
            }
        }
        
        System.out.println("Iterations: " + iterations); // Print the iteration count
        
        return reconstructPath(parentMap, start, end);
    }
    
    private static List<Point> reconstructPath(Map<Point, Point> parentMap, Point start, Point end) {
        List<Point> path = new ArrayList<>();
        Point current = end;
        
        while (current != null) {
            path.add(current);
            current = parentMap.get(current);
        }
        
        Collections.reverse(path);
        
        return path;
    }
    
    private static void markPathOnMaze(char[][] maze, List<Point> path) {
        for (Point point : path) {
            maze[point.y][point.x] = '*';
        }
    }
    
    private static void printMaze(char[][] maze) {
        for (char[] row : maze) {
            for (char cell : row) {
                System.out.print(cell);
            }
            System.out.println();
        }
    }
    
    	
}
