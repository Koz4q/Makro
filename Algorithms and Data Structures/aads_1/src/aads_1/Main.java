package aads_1;

import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class Main {

	public static String[] readString​(String[] filePath) throws IOException {
		return null;
	}
	
	
	 void check_if_sorted_i(int arr[]) {
		int i = 1;
		int N = arr.length;
		int is_sorted = 1;
		while ((i < N)) {
			if (arr[i - 1] > arr[i]) {
				is_sorted = 0;
				break;
			}else {
				i++;
			}
		} 
		if(is_sorted == 1 )
			System.out.println("It is sorted.");
		else
			System.out.println("It is not sorted.");
		
		}
	 
	 
	 void check_if_sorted(Comparable[] arr) {
			int i = 1;
			int N = arr.length;
			int is_sorted = 1;
			while ((i < N)) {
				if (arr[i-1].compareTo(arr[i])>0) {
					is_sorted = 0;
					break;
				}else {
					i++;
				}
			} 
			if(is_sorted == 1 )
				System.out.println("It is sorted.");
			else
				System.out.println("It is not sorted.");
			
			}
	
	 int binary_i(int arr[], int key, int low, int high)
		{
		    while (low <= high) {
		        int mid = low + (high - low) / 2;
		        if (key == arr[mid]) {
		        	return mid + 1;
		        }  
		        else if (key > arr[mid]) {
		        	 low = mid + 1;
		        }
		        else {
		        	high = mid - 1;
		        }      
		    }
		 
		    return low;
		}
	 
	 static int binary(Comparable[] arr, Comparable key, int low, int high)
		{
		    while (low <= high) {
		        int mid = low + (high - low) / 2;
		        if (key == arr[mid]) {
		        	return mid + 1;
		        }  
		        else if (key.compareTo(arr[mid])>0) {
		        	 low = mid + 1;
		        }
		        else {
		        	high = mid - 1;
		        }      
		    }
		 
		    return low;
		}
	 
	 public static int partition(Comparable[] arr, int low, int high, int pi) {
	        Comparable pivot = arr[pi];
	        int i = low - 1;
	        swap(arr, pi, high);
	        for (int j = low; j < high; ++j) {
	            if (arr[j].compareTo(pivot) < 0) {
	                ++i;
	                swap(arr, i, j);
	            }
	        }
	        swap(arr, i+1, high);
	        return i+1;
	    }
	 
	 
	 public static void insertionSort(Comparable[] arr, int low, int n)
	    {
	        for (int i = low + 1; i <= n; i++)
	        {
	        	Comparable value = arr[i];
	            int j = i;
	 
	            
	            while (j > low && arr[j - 1].compareTo(value)>0)
	            {
	                arr[j] = arr[j - 1];
	                j--;
	            }
	 
	            arr[j] = value;
	        }
	    }
	 
	 public static void quick_insertion(Comparable[] arr, int low, int high)
	    {
	        while (low < high)
	        {
	            if (high - low < 10)
	            {
	                insertionSort(arr, low, high);
	                break;
	            }
	            else {
	                int pivot = partition(arr, low, high,high);
	 
	                if (pivot - low < high - pivot)
	                {
	                	quick_insertion(arr, low, pivot - 1);
	                    low = pivot + 1;
	                }
	                else {
	                	quick_insertion(arr, pivot + 1, high);
	                    high = pivot - 1;
	                }
	            }
	        }
	    }
	 
	 public static void swap(Comparable[] arr, int i, int j) {
	        Comparable temp = arr[i];
	        arr[i] = arr[j];
	        arr[j] = temp;
	    }
	 
	 public static int pivots(Comparable[] arr, int low, int high, String type) {
	        if (type.equals("first")) {
	            return low;
	        }else if(type.equals("last")) {
	        	return high;
	        } else if (type.equals("random")) {
	            Random rand = new Random();
	            return rand.nextInt(high-low+1) + low;
	        } else if (type.equals("median")) {
	            int mid = (low + high) / 2;
	            if (arr[mid].compareTo(arr[low]) < 0) {
	                swap(arr, low, mid);
	            }
	            if (arr[high].compareTo(arr[low]) < 0) {
	                swap(arr, low, high);
	            }
	            if (arr[mid].compareTo(arr[high]) < 0) {
	                swap(arr, mid, high);
	            }
	            return high;
	        } else {
	            throw new IllegalArgumentException("Invalid pivot type");
	        }
	    }
	 
	 void quick(Comparable[] arr, int low, int high, String type) {
		 if(low<high) {
			 int pi = pivots(arr, low, high, type);
			 pi = partition(arr, low, high, pi);
			 quick(arr, low, pi-1, type);
			 quick(arr, pi+1, high, type);
		 }
	 }
	 
	 void quick_ins(Comparable[] arr, int low, int high) {
		 while(low<high) {
			 if(high-low<10) {
				 insertion(arr);
				 break;
			 }else {
				 int pivot = partition(arr,low,high,0);
				 if(pivot - low < pivot - high) {
					 quick_ins(arr,low,pivot-1);
					 low = pivot+1;
					 
				 }else {
					 quick_ins(arr,low,pivot-1);
					 high = pivot-1;
				 }
			 }
		 }
	 }
	 
	void insertion_imp_i(int arr[]) {
		int n = arr.length;
		int key,j,pos;
		for(int i = 1;i<n;i++) {
			j = i-1;
			key = arr[i];
			pos = binary_i(arr,key,0,j);
			while (j>=pos) {
				arr[j+1] = arr[j];
				j--;
			}
			arr[j+1] = key;
		}
	}
	
	void insertion_imp(Comparable[] arr) {
		int n = arr.length;
		Comparable key;
		for(int i = 1;i<n;i++) {
			int j = i-1;
			key = arr[i];
			int pos = binary(arr,key,0,j);
			while (j>=pos) {
				arr[j+1] = arr[j];
				j--;
			}
			arr[j+1] = key;
		}
	}
	
	void insertion_i(int arr[]) {
		int n = arr.length;
		for(int i = 1; i<n;i++) {
			int key = arr[i];
			int j = i-1;
			while(j>=0 && arr[j]>key) {
				arr[j+1] = arr[j];
				j--;
			}
			arr[j+1]=key;
		}
	}
	
	static void insertion(Comparable []arr) {
		int n = arr.length;
		for(int i = 1; i<n;i++) {
			Comparable key = arr[i];
			int j = i-1;
			while(j>=0 && arr[j].compareTo(key)>0) {
				arr[j+1] = arr[j];
				j--;
			}
			arr[j+1]=key;
		}
	}
	
	void bubble_i(int arr[]) {
		int n = arr.length;
		for(int i = 0;i<n-1;i++) {
			for(int j=0;j<n-1;j++) {
				if(arr[j]>arr[j+1]) {
					int swap = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = swap;
				}
			
			}
		}
	}
	
	void bubble(Comparable[] arr) {
		int n = arr.length;
		for(int i = 0;i<n-1;i++) {
			for(int j=0;j<n-1;j++) {
				if(arr[j].compareTo(arr[j+1])>0) {
					Comparable swap = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = swap;
				}
			
			}
		}
	}
	
	
	// improved bubble 1
	void coctail_i(int arr[]) {
		int n = arr.length;
		int swapped = 1;
		int start = 0;
		while(swapped == 1) {
			swapped = 0;
			for(int i = start;i<n-1;i++) {
				if(arr[i] > arr[i+1]) {
					int swap = arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = swap;
					swapped = 1;
				}
			}
			if(swapped == 0) {
				break;
			}
			swapped = 0;
			n--;
			for(int i = n-1;i>=start;i--) {
				if(arr[i] > arr[i+1]) {
					int swap = arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = swap;
					swapped = 1;
				}
			}
			start++;
		}
	}
	
	void coctail(Comparable[] arr) {
		int n = arr.length;
		int swapped = 1;
		int start = 0;
		while(swapped == 1) {
			swapped = 0;
			for(int i = start;i<n-1;i++) {
				if(arr[i].compareTo(arr[i+1])>0) {
					Comparable swap = arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = swap;
					swapped = 1;
				}
			}
			if(swapped == 0) {
				break;
			}
			swapped = 0;
			n--;
			for(int i = n-1;i>=start;i--) {
				if(arr[i].compareTo(arr[i+1])>0) {
					Comparable swap = arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = swap;
					swapped = 1;
				}
			}
			start++;
		}
	}
	
	//improved bubble 2
	void comb_i(int arr[]) {
		int gap = arr.length;
		int n = arr.length;
		boolean swapped = true;
		while(gap != 1 || swapped == true) {
			swapped = false;
			gap = (gap*10)/13;
			if (gap<1) {
				gap = 1;
			}
			for(int i=0;i<n-gap;i++) {
				if(arr[i]>arr[i+gap]) {
					int swap = arr[i];
					arr[i] = arr[i+gap];
					arr[i+gap] = swap;
					swapped = true;
				}
			}
		}
	}
	
	void comb(Comparable[] array) {
		int gap = array.length;
		int n = array.length;
		boolean swapped = true;
		while(gap != 1 || swapped == true) {
			swapped = false;
			gap = (gap*10)/13;
			if (gap<1) {
				gap = 1;
			}
			for(int i=0;i<n-gap;i++) {
				if(array[i].compareTo(array[i+gap])>0) {
					Comparable swap = array[i];
					array[i] = array[i+gap];
					array[i+gap] = swap;
					swapped = true;
				}
			}
		}
	}
	
	void selection_i(int arr[]) {
		int n = arr.length;
		
		for (int i = 0; i < n-1; i++) 
		{
			int  min_index = i;
			for (int j = i+1; j < n; j++) 
				if (arr[j] < arr[min_index]) 
					min_index = j;
				
			int swap = arr[min_index];
			arr[min_index] = arr[i];
			arr[i] = swap;
			
		}
		
		
	}
	
	void selection(Comparable[] arr) {
		int n = arr.length;
		
		for (int i = 0; i < n-1; i++) 
		{
			int  min_index = i;
			for (int j = i+1; j < n; j++) 
				if (arr[j].compareTo(arr[min_index])<0) 
					min_index = j;
				
			Comparable swap = arr[min_index];
			arr[min_index] = arr[i];
			arr[i] = swap;
			
		}
		
	}
	
	void shell_ori(Comparable arr[]) {
		int n = arr.length;
		for(int gap = n/2; gap>0; gap /= 2) {
			for(int i = gap; i<n; i++) {
				Comparable swap = arr[i];
				int j=i;
				while(j>=gap && arr[j-gap].compareTo(swap)>0) {
					arr[j] = arr[j-gap];
					j = j-gap;
				}
				arr[j]=swap;
			}
		}
	}
	
	void shell_exp(Comparable arr[]) {
		int n = arr.length;
		int h[] = {1,4,10,23,57,301,701};
		for(int gap = h.length-1; gap>0; gap--) {
			int s = h[gap];
			for(int i = s; i<n; i++) {
				Comparable swap = arr[i];
				int j=i;
				while(j>=s && arr[j-s].compareTo(swap)>0) {
					arr[j] = arr[j-s];
					j = j-s;
				}
				arr[j]=swap;
			}
		}
	}
	
	void print_arr(Comparable arr[])
    {
        int n = arr.length;
        for (int i=0; i<n; ++i)
            System.out.print(arr[i]+" ");
        System.out.println();
    }
	
	int[] genran(int minVal, int maxVal, int size) {
		
        int[] arr_test = new int[size];
        for (int i = 0; i < arr_test.length; i++) {
            arr_test[i] = ThreadLocalRandom.current().nextInt(minVal, maxVal);
        }
        return arr_test;
	}
	
	Integer[] genran_integer(Integer minVal, Integer maxVal, Integer size) {
		
        Integer[] arr_test = new Integer[size];
        for (int i = 0; i < arr_test.length; i++) {
            arr_test[i] = ThreadLocalRandom.current().nextInt(minVal, maxVal);
        }
        return arr_test;
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
	
	public static void main(String[] args) throws IOException {
		
		Main select = new Main();
		
		// LAB1
//		run_any_sort(new selection_sorter(),select, select.generateRandomWords(4000), 4000);
//		run_any_sort(new insertion_sorter(),select, select.generateRandomWords(4000), 4000);
//		run_any_sort(new insertion_imp_sorter(),select, select.generateRandomWords(4000), 4000);
//		run_any_sort(new bubble_sorter(),select, select.generateRandomWords(4000), 4000);
//		run_any_sort(new coctail_sorter(),select, select.generateRandomWords(4000), 4000);
//		run_any_sort(new comb_sorter(),select, select.generateRandomWords(4000), 4000);
//		
//		run_any_sort(new selection_sorter(),select, select.genran_integer(0, 2000000, 16000), 16000);
//		run_any_sort(new insertion_sorter(),select, select.genran_integer(0, 2000000, 16000), 16000);
//		run_any_sort(new insertion_imp_sorter(),select, select.genran_integer(0, 2000000, 16000), 16000);
//		run_any_sort(new bubble_sorter(),select, select.genran_integer(0, 2000000, 16000), 16000);
//		run_any_sort(new coctail_sorter(),select, select.genran_integer(0, 2000000, 16000), 16000);
//		run_any_sort(new coctail_sorter(),select, select.genran_integer(0, 2000000, 16000), 16000);
		
		
		//LAB 2
		run_quick(new quick_sorter(),select, select.genran_integer(0, 20000000, 4096000), 4096000,"first");
		run_quick(new quick_sorter(),select, select.genran_integer(0, 20000000, 4096000), 4096000,"random");
		run_quick(new quick_sorter(),select, select.genran_integer(0, 20000000, 4096000), 4096000,"median");
		run_quick(new quick_ins_sorter(),select, select.genran_integer(0, 20000000, 4096000), 4096000,"NONE");
		run_any_sort(new shell_ori_sorter(),select, select.genran_integer(0, 200000000, 4096000), 4096000);
		run_any_sort(new shell_exp_sorter(),select, select.genran_integer(0, 200000000, 4096000), 4096000);
		
		
		run_quick(new quick_sorter(),select, select.generateRandomWords(1024000), 1024000,"first");
		run_quick(new quick_sorter(),select, select.generateRandomWords(1024000), 1024000,"random");
		run_quick(new quick_sorter(),select, select.generateRandomWords(1024000), 1024000,"median");
		run_quick(new quick_ins_sorter(),select, select.generateRandomWords(1024000), 1024000,"NONE");
		run_any_sort(new shell_ori_sorter(),select, select.generateRandomWords(1024000), 1024000);
		run_any_sort(new shell_exp_sorter(),select, select.generateRandomWords(1024000), 1024000);
		
		
		
	}


	private static void run_string(Main select, int size) {
		
		String[] arr_test = select.generateRandomWords(size);
		select.check_if_sorted(arr_test);
        long startTime = System.currentTimeMillis();
        select.insertion_imp(arr_test); 
        long stopTime = System.currentTimeMillis();
        long elapsedTime = stopTime - startTime;
        System.out.println("Time of sotring in ms:  " + elapsedTime);
        select.check_if_sorted(arr_test);
	}
	
	private static void run_int(Main select, int min, int max, int size) {
		
		Integer arr_test[] = select.genran_integer(min, max, size);
		select.check_if_sorted(arr_test);
        long startTime = System.currentTimeMillis();
        select.insertion_imp(arr_test); 
        long stopTime = System.currentTimeMillis();
        long elapsedTime = stopTime - startTime;
        System.out.println("Time of sotring in ms:  " + elapsedTime);
        select.check_if_sorted(arr_test);
	}
	
	private static void run_any_sort(sorter sort, Main select, Comparable[] arr_test, int size) {
		
		System.out.println();
		System.out.println("Sorting class "+sort.getClass().getName()+" type of array "+arr_test.getClass().getComponentType().getName()+" size: "+size);
		select.check_if_sorted(arr_test);
        long startTime = System.currentTimeMillis();
        sort.sort(arr_test); 
        long stopTime = System.currentTimeMillis();
        long elapsedTime = stopTime - startTime;
        System.out.println("Time of sotring in ms:  " + elapsedTime);
        select.check_if_sorted(arr_test);
	}
	
	private static void run_quick(quick_sort sort, Main select, Comparable[] arr_test, int size, String type) {
		
		System.out.println();
		System.out.println("Sorting class "+sort.getClass().getName()+" type of array "+arr_test.getClass().getComponentType().getName()+" size: "+size+" pivot: "+type);
		select.check_if_sorted(arr_test);
        long startTime = System.currentTimeMillis();
        sort.quick(arr_test,0,arr_test.length-1,type); 
        long stopTime = System.currentTimeMillis();
        long elapsedTime = stopTime - startTime;
        System.out.println("Time of sotring in ms:  " + elapsedTime);
        select.check_if_sorted(arr_test);
        
	}
	
	
	private static interface sorter{
		
		void sort(Comparable[] arr);
	}
	
	private static interface quick_sort{
		
		void quick(Comparable[] arr, int low, int high, String type);
	}
	
	private static class quick_sorter implements quick_sort{
		
		public void quick(Comparable[] arr, int low, int high, String type) {
	        if (low < high) {
	            int pi = pivots(arr, low, high, type);
	            pi = partition(arr, low, high, pi);
	            quick(arr, low, pi-1, type);
	            quick(arr, pi+1, high, type);
	        }
	    }
	}
	
	private static class quick_ins_sorter implements quick_sort{
		
		public void quick(Comparable[] arr, int low, int high, String none)
	    {
	        while (low < high)
	        {
	            if (high - low < 10)
	            {
	                insertionSort(arr, low, high);
	                break;
	            }
	            else {
	                int pivot = partition(arr, low, high,high);
	 
	                if (pivot - low < high - pivot)
	                {
	                	quick(arr, low, pivot - 1,none);
	                    low = pivot + 1;
	                }
	                else {
	                	quick(arr, pivot + 1, high,none);
	                    high = pivot - 1;
	                }
	            }
	        }
	    }
	}
	
	private static class bubble_sorter implements sorter{
		
		public void sort(Comparable[] arr) {
			int n = arr.length;
			for(int i = 0;i<n-1;i++) {
				for(int j=0;j<n-1;j++) {
					if(arr[j].compareTo(arr[j+1])>0) {
						Comparable swap = arr[j];
						arr[j] = arr[j+1];
						arr[j+1] = swap;
					}
				
				}
			}
		}
	}
	
	private static class coctail_sorter implements sorter{
	
		public void sort(Comparable[] arr) {
			int n = arr.length;
			int swapped = 1;
			int start = 0;
			while(swapped == 1) {
				swapped = 0;
				for(int i = start;i<n-1;i++) {
					if(arr[i].compareTo(arr[i+1])>0) {
						Comparable swap = arr[i];
						arr[i] = arr[i+1];
						arr[i+1] = swap;
						swapped = 1;
					}
				}
				if(swapped == 0) {
					break;
				}
				swapped = 0;
				n--;
				for(int i = n-1;i>=start;i--) {
					if(arr[i].compareTo(arr[i+1])>0) {
						Comparable swap = arr[i];
						arr[i] = arr[i+1];
						arr[i+1] = swap;
						swapped = 1;
					}
				}
				start++;
			}
		}
		
	}
	
	private static class insertion_sorter implements sorter{
		public void sort(Comparable[] arr) {
			int n = arr.length;
			for(int i = 1; i<n;i++) {
				Comparable key = arr[i];
				int j = i-1;
				while(j>=0 && arr[j].compareTo(key)>0) {
					arr[j+1] = arr[j];
					j--;
				}
				arr[j+1]=key;
			}
			
		}
		
	}
	
	private static class insertion_imp_sorter implements sorter{
		public void sort(Comparable[] arr) {
			int n = arr.length;
			Comparable key;
			for(int i = 1;i<n;i++) {
				int j = i-1;
				key = arr[i];
				int pos = binary(arr,key,0,j);
				while (j>=pos) {
					arr[j+1] = arr[j];
					j--;
				}
				arr[j+1] = key;
			}
			
		}
		
	}
	
	private static class comb_sorter implements sorter{
		public void sort(Comparable[] array) {
			int gap = array.length;
			int n = array.length;
			boolean swapped = true;
			while(gap != 1 || swapped == true) {
				swapped = false;
				gap = (gap*10)/13;
				if (gap<1) {
					gap = 1;
				}
				for(int i=0;i<n-gap;i++) {
					if(array[i].compareTo(array[i+gap])>0) {
						Comparable swap = array[i];
						array[i] = array[i+gap];
						array[i+gap] = swap;
						swapped = true;
					}
				}
			}
			
		}
	
	}
	
	private static class selection_sorter implements sorter{
		public void sort(Comparable[] arr) {
			int n = arr.length;
			
			for (int i = 0; i < n-1; i++) 
			{
				int  min_index = i;
				for (int j = i+1; j < n; j++) 
					if (arr[j].compareTo(arr[min_index])<0) 
						min_index = j;
					
				Comparable swap = arr[min_index];
				arr[min_index] = arr[i];
				arr[i] = swap;
				
			}
			
		}
	
	}
	
	private static class shell_ori_sorter implements sorter{
		public void sort(Comparable arr[]) {
			int n = arr.length;
			for(int gap = n/2; gap>0; gap /= 2) {
				for(int i = gap; i<n; i++) {
					Comparable swap = arr[i];
					int j=i;
					while(j>=gap && arr[j-gap].compareTo(swap)>0) {
						arr[j] = arr[j-gap];
						j = j-gap;
					}
					arr[j]=swap;
				}
			}
		}
	
	}
	
	private static class shell_exp_sorter implements sorter{
		public void sort(Comparable arr[]) {
			int[] h = {1, 4, 10, 23, 57, 132, 301, 701};
	        for (int h_idx = h.length-1; h_idx >= 0; --h_idx) {
	            int gap = h[h_idx];
	            for (int i = gap; i < arr.length; ++i) {
	                Comparable temp = arr[i];
	                int j=i;
	                while (j >= gap && arr[j-gap].compareTo(temp)>0) {
	                    arr[j] = arr[j-gap];
	                    j -= gap;
	                }
	                arr[j] = temp;
	            }
	        }
		}
	
	}
	
}
