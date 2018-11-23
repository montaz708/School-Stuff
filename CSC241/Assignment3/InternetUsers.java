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
		stdIn.close();
		out.close();
	}

}
