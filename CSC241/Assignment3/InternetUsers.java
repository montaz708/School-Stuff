package assignment3;
import java.io.PrintWriter;
import java.io.File;
import java.util.Scanner;
import java.util.Random;

public class InternetUsers{

	public static void main(String[] args) throws Exception{
		
		String home = System.getProperty("user.home");
		String path = home + File.separator + "Downloads" + File.separator;
		Scanner stdIn = new Scanner(new File(path + "CountrySortedAlpha.txt"));
		PrintWriter out = new PrintWriter(path + "CountryUnsortedAlpha.txt");
		String [] lineSort = new String [201];
		String [] line = new String[201];
		String temp;
		Random rand = new Random();
		
		/*--------------Begin Randomize part-------------------*/
		
		int where;
		
		for(int a = 0; stdIn.hasNextLine(); a++) {
			line[a] = stdIn.nextLine();
		}
		
		for(int k = line.length - 1; k >= 0; k--) {
			where = rand.nextInt(line.length);
			while(line[where].equals("")) {
				where = rand.nextInt(line.length);
			}
			temp = line[where];
			out.println(temp);
			line[where] = "";
			
		}
		/*---------------End Randomize part-------------------*/
		
		
		
		
		stdIn.close();
		out.close();
	}
	
	public static int[] shellSort(int[] arr) {
		int increment = arr.length / 2;
		while(increment> 0) {
			for(int i = increment; i < arr.length; i++) {
				int j = i;
				int temp = arr[i];
				while(j >= increment && arr[j - increment] > temp) {
					arr[j] = arr[j - increment];
					j = j - increment;
				}
				arr[j] = temp;
			}
			if (increment == 2) {
				increment = 1;
			}
			else {
				increment *= (5.0/11);
			}
		}
		return arr;
	}

}
