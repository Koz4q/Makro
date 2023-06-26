package lab3;

import java.util.*;
import java.util.concurrent.ThreadLocalRandom;
import java.io.File;
import java.io.*;

public class StringHashTable {

	private String[] keys;
    private int[] values;
    private int size;
    private int capacity;
    private int searchHitCount;
    private int searchMissCount;
    private long insertMissCount;

    public StringHashTable(int capacity) {
        this.capacity = capacity;
        this.size = 0;
        this.keys = new String[capacity];
        this.values = new int[capacity];
        this.searchHitCount = 0;
        this.searchMissCount = 0;
        this.insertMissCount = 0;
    }

    public void insert(String key, int value) {
        int index = hash(key);
        while (keys[index] != null) {
            if (keys[index] == key) {
                values[index] = value;
                return;
            }
            insertMissCount++;
            index = (index + 1) % capacity;
        }
        keys[index] = key;
        values[index] = value;
        size++;
    }
    
    public void insert_d(String key, int value) {
        int index = hash(key);
        int step = step_hash(key);
        while (keys[index] != null) {
            if (keys[index] == key) {
                values[index] = value;
                return;
            }
            insertMissCount++;
            index = (index + step) % capacity;
        }
        keys[index] = key;
        values[index] = value;
        size++;
    }

    public int search(String key) {
    	int operations = 0;
        int index = hash(key);
        int step = step_hash(key);
        operations++;
        while (keys[index] != null) {
        	
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
    
    public int search_d(String key) {
    	int operations = 0;
        int index = hash(key);
        int step = step_hash(key);
        operations++;
        while (keys[index] != null) {
        	
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

    public void delete(String key) {
        int index = hash(key);
        int step = step_hash(key);
        while (keys[index] != null) {
            if (keys[index] == key) {
                keys[index] = null;
                values[index] = 0;
                size--;
                return;
            }
            index = (index + step) % capacity;
        }
    }
    
    public void delete_d(String key) {
        int index = hash(key);
        int step = step_hash(key);
        while (keys[index] != null) {
            if (keys[index] == key) {
                keys[index] = null;
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

    public double getSearchHitCount() {
        return searchHitCount;
    }
    
    public double getinsertMissCount() {
        return insertMissCount;
    }

    public double getSearchMissCount() {
        return searchMissCount;
    }
    
    public int step_hash(String key) {
        return 7 - (key.hashCode() % 7);
    }

//    private int hash(String key) {
//        
//        int h, c; 
//        h = 0;
//        c = 29;
//        for (int i = 0;i<key.length();i++) {
//        	
//        	 h = (c * h + key.charAt(i)) % capacity;
//        }
//        return h;
//    }
    
    private int hash(String key) {
    	
    	int h,c1,c2;
    	
    	h = 0;
    	c1 = 31415;
    	c2 = 27183;
    	
    	 for (int i = 0;i<key.length();i++) {
         	
    		 h = (c1 * h +key.charAt(i)) % capacity;
    	    c1 = (c1 * c2) % (capacity - 1);
        }
        
    	if(h < 0) {
    		
    		return h + capacity;
    	}else {
    		return h;
    	}
    	
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
		
		System.out.println("*** Strings ***");
		linear_probing(0.5,1050000,100,"integers.txt","set.txt","set_miss.txt");
		linear_probing(0.6,1050000,100,"integers.txt","set.txt","set_miss.txt");
		linear_probing(0.7,1050000,100,"integers.txt","set.txt","set_miss.txt");
		linear_probing(0.8,1050000,100,"integers.txt","set.txt","set_miss.txt");
		linear_probing(0.9,1050000,100,"integers.txt","set.txt","set_miss.txt");
		System.out.println();
		double_hashing(0.5,1050000,100,"integers.txt","set.txt","set_miss.txt");
		double_hashing(0.6,1050000,100,"integers.txt","set.txt","set_miss.txt");
		double_hashing(0.7,1050000,100,"integers.txt","set.txt","set_miss.txt");
		double_hashing(0.8,1050000,100,"integers.txt","set.txt","set_miss.txt");
		double_hashing(0.9,1050000,100,"integers.txt","set.txt","set_miss.txt");
		
	}

	private static void linear_probing(double factor, int capacity, int div, String values, String hit, String miss) {
		try {
			
			int element_count = (int) (factor*capacity);
			
			StringHashTable hash = new StringHashTable(capacity);
			int[] arr = data_from_file(values);
			String[] str = data_from_file_s(hit);
			String[] str_miss = data_from_file_s(miss);
			for(int i=0;i<element_count;i++) {
				hash.insert(str[i], arr[i]);
			}

			double hit_search = 0;
			double miss_search = 0;
			
			for(int i=0;i<element_count;i++) {
				
				if(i % (element_count/div) == 0) {
					hash.search(str[i]);
					hit_search++;
				}
			}
			
			for(int i=0;i<str_miss.length;i++) {
				
				if(i % div == 0) {
					hash.search(str_miss[i]);
					miss_search++;
				}
			}
			
			//hash.delete(str[5]);
			System.out.println("Linear probing of size: "+hash.size());
			System.out.println("Factor: "+factor);
			System.out.println("Hit: "+hash.getSearchHitCount()/hit_search);
			System.out.println("Miss: "+hash.getSearchMissCount()/miss_search);
			System.out.println();
			
        } catch (Exception e) {
            e.printStackTrace();
        }
	}
	
	private static void double_hashing(double factor, int capacity, int div, String values, String hit, String miss) {
		try {
			
			int element_count = (int) (factor*capacity);
			
			StringHashTable hash = new StringHashTable(capacity);
			int[] arr = data_from_file(values);
			String[] str = data_from_file_s(hit);
			String[] str_miss = data_from_file_s(miss);
			for(int i=0;i<element_count;i++) {
				hash.insert_d(str[i], arr[i]);
//				if(i % div == 0) {
//					System.out.println("Element = "+i+" 	Iterations: "+hash.insertMissCount);
//				}
			}

			double hit_search = 0;
			double miss_search = 0;
			
			for(int i=0;i<element_count;i++) {
				
				if(i % (element_count/div) == 0) {
					hash.search_d(str[i]);
					hit_search++;
				}
			}
			
			for(int i=0;i<str_miss.length;i++) {
				
				if(i % div == 0) {
					hash.search_d(str_miss[i]);
					miss_search++;
				}
			}
			
			//hash.delete_d(str[5]);
			System.out.println("Double hashing of size: "+hash.size());
			System.out.println("Factor: "+factor);
			System.out.println("Hit: "+hash.getSearchHitCount()/hit_search);
			System.out.println("Miss: "+hash.getSearchMissCount()/miss_search);
			System.out.println();
			
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

	private static void strings_to_file(StringHashTable select, int size) {
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
