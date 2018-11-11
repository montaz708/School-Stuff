package assignment3;

import java.io.PrintWriter;
import java.util.Scanner;
import java.io.File;

public class InternetUsers {
	public static void main(String[] args) throws Exception{
		
		String [] line = new String[201];
		String [] lineSort = new String[201];
		
		Scanner stdin = new Scanner(new File("C:/CountrySortedFormat.txt"));
		PrintWriter out = new PrintWriter("C:/CountryUnsortedFormat.txt"));
		
		for(int k = 0; stdin.hasNextLine(); k++){
			line[k] = stdin.nextLine();
			lineSort[k] = line[k];
			out.println(line[k]);
		}
	}

}
