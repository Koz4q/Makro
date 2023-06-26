package lab5;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.*;

class MazeSolver {
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
        // Change the file path to match your input file
        String filePath = "m5x5.txt";
        
        char[][] maze = readMazeFromFile(filePath);
        List<Point> path = solveMaze(maze);
        
        if (path.isEmpty()) {
            System.out.println("No path found.");
        } else {
            System.out.println("Shortest path:");
            for (Point point : path) {
                System.out.println("[" + point.x + ", " + point.y + "]");
            }
        }
    }
    
    private static char[][] readMazeFromFile(String filePath) {
        char[][] maze = null;
        
        try (Scanner scanner = new Scanner(new FileReader(filePath))) {
            int width = scanner.nextInt();
            int height = scanner.nextInt();
            
            maze = new char[height][width];
            scanner.nextLine(); // Move to the next line after reading dimensions
            
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
        
        // Find the start and end points
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
        
        while (!queue.isEmpty()) {
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
}