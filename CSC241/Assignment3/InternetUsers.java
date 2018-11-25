package assignment3;
import java.io.PrintWriter;
import java.io.File;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.Random;

public class InternetUsers{

	public static void main(String[] args) throws Exception{
		
		String home = System.getProperty("user.home");
		String path = home + File.separator + "Downloads" + File.separator;
		Scanner stdIn = new Scanner(new File(path + "CountrySortedAlpha.txt"));
		PrintWriter out = new PrintWriter(path + "CountryUnsortedAlpha.txt");
		String [][] lineSort = new String [2][201];
		String [] popString = new String [201];
		String [] line = new String[201];
		String temp;
		String build;
		boolean bool;
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
			StringTokenizer str = new StringTokenizer(temp);
			build = "";
			bool = false;
			do {
				try {
					temp = str.nextToken();
					Integer.parseInt(temp);
					lineSort[1][k] = temp;
					bool = true;
				}
				catch(NumberFormatException e) {
					build = build + " " + temp;
				}
			}while(bool == false);
			lineSort[0][k] = build;
			line[where] = "";
			
		}
		/*---------------End Randomize part-------------------*/
		stdIn.close();
		out.close();
		shellSort(lineSort);
		
		for(int a = 0; a < lineSort[0].length; a++) {
			System.out.println(lineSort[0][a] + "\t" + lineSort[1][a]);
		}
		
	}
	
	
	public static void shellSort(String[][] a){
		String elem;
		int j;
		for(int gap = a[1].length/2; gap > 0; gap /=2) {
			for(int i = gap; i < a[1].length; i++) {
				elem = a[0][i];
				int temp = Integer.parseInt(a[1][i]);
				for( j = i; j >= gap && temp > Integer.parseInt(a[1][j - gap]); j-=gap) {
					a[0][j] = a[0][j - gap];
					a[1][j] = a[1][j - gap];
				}
				a[0][j] = elem;
				a[1][j] = Integer.toString(temp);
			}
		}
	}
}