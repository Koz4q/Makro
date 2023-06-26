package lab3;

import java.util.*;
import java.util.concurrent.ThreadLocalRandom;
import java.io.File;
import java.io.*;

public class Main {

	private int[] keys;
    private int[] values;
    private int size;
    private int capacity;
    private int searchHitCount;
    private int searchMissCount;

    public Main(int capacity) {
        this.capacity = capacity;
        this.size = 0;
        this.keys = new int[capacity];
        this.values = new int[capacity];
        this.searchHitCount = 0;
        this.searchMissCount = 0;
    }

    public void insert(int key, int value) {
        int index = hash(key);
        while (keys[index] != 0) {
            if (keys[index] == key) {
                values[index] = value;
                return;
            }
            index = (index + 1) % capacity;
        }
        keys[index] = key;
        values[index] = value;
        size++;
    }
    
    public void insert_d(int key, int value) {
        int index = hash(key);
        int step = step_hash(key);
        while (keys[index] != 0) {
            if (keys[index] == key) {
                values[index] = value;
                return;
            }
            index = (index + step) % capacity;
        }
        keys[index] = key;
        values[index] = value;
        size++;
    }

    public int search(int key) {
	int operations = 0;
    int index = hash(key);
	operations++;
        while (keys[index] != 0) {
            if (keys[index] == key) {
                searchHitCount += operations;
                return values[index];
            }
	    operations++;
            index = (index + 1) % capacity;
        }
        searchMissCount += operations;
        return 0;
    }
    
    public int search_d(int key) {
    	int operations = 0;
        int index = hash(key);
    	int step = step_hash(key);
    	operations++;
            while (keys[index] != 0) {
                if (keys[index] == key) {
                    searchHitCount += operations;
                    return values[index];
                }
    	    operations++;
                index = (index + step) % capacity;
            }
            searchMissCount += operations;
            return 0;
        }

    public void delete(int key) {
        int index = hash(key);
        while (keys[index] != 0) {
            if (keys[index] == key) {
                keys[index] = 0;
                values[index] = 0;
                size--;
                return;
            }
            index = (index + 1) % capacity;
        }
    }
    
    public void delete_d(int key) {
        int index = hash(key);
        int step = step_hash(key);
        while (keys[index] != 0) {
            if (keys[index] == key) {
                keys[index] = 0;
                values[index] = 0;
                size--;
                return;
            }
            index = (index + step) % capacity;
        }
    }

    public int size() {
        return size;
    }

    public int getSearchHitCount() {
        return searchHitCount;
    }

    public int getSearchMissCount() {
        return searchMissCount;
    }

    public int step_hash(int key) {
        return 7 - (key % 7);
    }

    private int hash(int key) {
        return key % capacity;
    }
    
    
	public static long[] data_from_file_long(String filename) throws Exception {
        File file = new File(filename);
        Scanner scanner = new Scanner(file);

        int count = 0;
        while (scanner.hasNextLine()) {
            count++;
            scanner.nextLine();
        }

        long[] arr = new long[count];
        scanner = new Scanner(file);

        for (int i = 0; i < count; i++) {
            arr[i] = scanner.nextLong();
        }

        return arr;
    }
	
	public static int[] data_from_file(String filename) throws Exception {
        File file = new File(filename);
        Scanner scanner = new Scanner(file);

        int count = 0;
        while (scanner.hasNextLine()) {
            count++;
            scanner.nextLine();
        }

        int[] arr = new int[count];
        scanner = new Scanner(file);

        for (int i = 0; i < count; i++) {
            arr[i] = scanner.nextInt();
        }

        return arr;
    }
	
	public static String[] data_from_file_s(String filename) throws Exception {
        File file = new File(filename);
        Scanner scanner = new Scanner(file);

        int count = 0;
        while (scanner.hasNextLine()) {
            count++;
            scanner.nextLine();
        }

        String[] arr = new String[count];
        scanner = new Scanner(file);

        for (int i = 0; i < count; i++) {
            arr[i] = scanner.nextLine();
        }

        return arr;
    }
	
	String[] generateRandomWords(int size)
	{
	    String[] randomStrings = new String[size];
	    Random random = new Random();
	    for(int i = 0; i < size; i++)
	    {
	        char[] word = new char[random.nextInt(8)+3]; 
	        for(int j = 0; j < word.length; j++)
	        {
	            word[j] = (char)('a' + random.nextInt(26));
	        }
	        randomStrings[i] = new String(word);
	    }
	    return randomStrings;
	}
	
	static int[] genran_integer(Integer minVal, Integer maxVal, Integer size) {
		
        int[] arr_test = new int[size];
        for (int i = 0; i < arr_test.length; i++) {
            arr_test[i] = ThreadLocalRandom.current().nextInt(minVal, maxVal);
        }
        return arr_test;
	}
	
	public static void main(String[] args) {
		
		//Main select = new Main();
		//strings_to_file(select, size);
		//integers_to_file();
		
		try {
			double factor = 0.9;
			
			int capacity = 100000;
			int element_count = (int) (factor*capacity);
			
			Main hash = new Main(capacity);
			//long[] arr = data_from_file("set.txt");
			int[] arr = data_from_file("integers.txt");
			long[] str = data_from_file_long("set.txt");
			long[] str_miss = data_from_file_long("set_miss.txt");
			
			System.out.println("test 1");
			for(int i=0;i<element_count;i++) {
				hash.insert(arr[i], arr[i]);

			}
			System.out.println("test 2");

//			System.out.println(hash.search(str[500]));
//			System.out.println(hash.search(str[100000]));

			double hit_search = 0;
			double miss_search = 0;
			
			for(int i=0;i<element_count;i++) {
				
				if(i % (element_count/100) == 0) {
					System.out.println(hash.search(arr[i]));
					hit_search++;
				}
			}
			
			for(int i=0;i<str_miss.length;i++) {
				
				if(i % 100 == 0) {
					System.out.println(hash.search(arr[i]));
					miss_search++;
				}
			}
			
			System.out.println("Marek: "+hash.search(123));
			System.out.println("Marek: "+hash.search(321));
			hash.delete(arr[5]);
			System.out.println("test 3");
			System.out.println("Size: "+hash.size());
			System.out.println("Hit: "+hash.getSearchHitCount()/hit_search);
			System.out.println("Miss: "+hash.getSearchMissCount()/miss_search);
			System.out.println("test 4");
			
        } catch (Exception e) {
            e.printStackTrace();
        }
		
	}

	private static void integers_to_file() {
		int[] numbers = genran_integer(10,1000000,1050000);

	      try {
	         BufferedWriter writer = new BufferedWriter(new FileWriter("integers.txt"));
	         for (int i = 0; i < numbers.length; i++) {
	            writer.write(numbers[i] + "\n");
	         }
	         writer.close();
	      } catch (IOException e) {
	         System.out.println("Error writing integers to file.");
	         e.printStackTrace();
	      }
	}

	private static void strings_to_file(Main select, int size) {
		String[] strings = select.generateRandomWords(size);
		
	      File file = new File("strings.txt");
	      try {
	         FileWriter fileWriter = new FileWriter(file);
	         BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
	         for (String s : strings) {
	            bufferedWriter.write(s);
	            bufferedWriter.newLine();
	         }
	         bufferedWriter.close();
	         fileWriter.close();
	      } catch (IOException e) {
	         e.printStackTrace();
	      }
	}
	

}
