package assignment3;
import java.io.PrintWriter;
import java.util.Hashtable;
import java.io.File;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.Random;

public class InternetUsers{
	/*Declare global variable table which will be used to 
	 * store country data, with the key being the hashed value
	 * derived from the country's name*/
	public static Hashtable <Integer, String> table = new Hashtable<Integer, String>(250);
	
	public static void main(String[] args) throws Exception{
		
		
		
		/*Background about variables:
		 * 
		 * lineSort: An array to be loaded with the randomized order of countries' data
		 * 			 where lineSort[0][someNumber] corresponds to the country's name
		 * 			 and where lineSort[1][theSameNumber] corresponds to that country's
		 * 			 percentage representation of Internet usage
		 * 
		 * line: An array containing the initially scanner/alphabetically sorted
		 * 		 country information.
		 * 
		 * build: A string variable used to store tokenized String elements from the String array "line"
		 * 
		 * bool: A boolean variable used as an exit indicator for a while loop
		 * 
		 * rand: A Random object, used to generate random numbers from 1 - 201. This
		 *       variable will be used to randomly select an index of the array "line"
		 *       and check if it contains a non-null string element*/
		
		
		
		
		Scanner stdIn = new Scanner(new File("C:/CountrySortedAlpha.txt"));
		PrintWriter out = new PrintWriter("C:/CountryUnsortedAlpha.txt");
		String [][] lineSort = new String [2][201]; 
		String [] line = new String[201];
		String temp;
		String build;
		boolean bool;
		Random rand = new Random();
		
		/*--------------Begin Randomize part-------------------*/
		
		int where; 													//Used to store the randomized value generated from rand
		
		
		/*Read in items from file, store in line array*/
		for(int a = 0; stdIn.hasNextLine(); a++) {
			line[a] = stdIn.nextLine();
		}
		stdIn.close();
		
		for(int k = line.length - 1; k >= 0; k--) {
			where = rand.nextInt(line.length);
			while(line[where].equals("")) {							//Keep generating random numbers until the index corresponds 
				where = rand.nextInt(line.length);					//to an index that contains a value instead of ""
			}
			temp = line[where];
			out.println(temp);
			StringTokenizer str = new StringTokenizer(temp);
			build = "";												//build will be used to record the tokenized strings that are not integers
			bool = false;
			do {
				try {												//If the token is not of type int, it will throw an exception
					temp = str.nextToken();							//Catch the exception, concatenate the string to "build"
					Integer.parseInt(temp);							//and as soon as an integer is parsed, exit the loop
					lineSort[1][k] = temp;
					bool = true;
				}
				catch(NumberFormatException e) {
					build = build + " " + temp;						//Concatenate non-integer elements into the country's full name
				}
			}while(bool == false);
			lineSort[0][k] = build;
			line[where] = "";										//Set that element index to a null string element or ""
			
		}
		out.close();
		/*--------------End Randomize part--------------------*/
		
		
		
		
		
		
		/*--------------Begin Sorting-------------------------*/
		shellSort(lineSort); //Call the function shellSort
		
		
		//Display the sorted results
		for(int a = 0; a < lineSort[0].length; a++) {
			System.out.println(lineSort[0][a] + "\t" + lineSort[1][a]);
		}
		/*-------------End Sorting----------------------------*/
		
		
		
		
		
		
		/*-------------Begin hashing--------------------------*/
		String str; //A variable containing just the country name
		String strFull; //A variable containing the country's name and its associated numerical value
		
		for(int a = 0; a < lineSort[0].length; a++) {
			str = lineSort[0][a].trim();
			strFull = lineSort[0][a] + " " + lineSort[1][a];
			char[] chars = str.toCharArray();
			int hash = hashCode(chars);
			hash %= 250;
			table.put(hash, str);
			System.out.println(strFull + " keyed to " + hash);
			
		}
		/*-------------End hashing----------------------------*/
		
		
		
		
		/*-------------Begin query phase----------------------*/
		Scanner in = new Scanner(System.in);
		String query = "";
		
		while(!(query.equals("-1"))) {
			System.out.println("Name of country (case sensitive) - type -1 if done: ");
			query = in.nextLine();
			if(!(query.equals("-1"))) {
				getValue(query);
			}
		}
		in.close();
		/*-------------End query phase------------------------*/
	}
	
	// A function that implements shell sort to sort an array containing numerical data
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
	
	
	/*hashCode() takes in an array of characters,
	 *adds them up, and then mods the sum by 250.
	 *In order to check for collision, ensure that
	 *the calculated hash value's index is equal
	 *to null. Otherwise, add one to the hash
	 *value and try again until the index value is
	 *null. Then, return the hash value without modding it*/
	public static int hashCode(char[] chars) {
		int hash = 0;
		
		for(int a = 0; a < chars.length; a++) {
			hash += (int)chars[a];
		}
		if(table.get(hash%250) == null) {
			return hash;
		}
		else {
			do {
				hash++;
			}while(table.get(hash%250) != null);
		}
		return hash;
	}
	
	
	/*Logic of "getValue" function:
	 * 
	 * 1. Take in a String called "country"
	 * 2. Turn the String into a character array
	 * 3. Add the ASCII values of the character array up
	 *    by casting them as int, storing the value in 
	 *    the variable "hash"
	 * 4. Mod the variable "hash" by 250
	 * 5. Check to see if the hash value exists in the
	 *    hash table.
	 *    	i. If it doesn't exist, it will throw
	 *         a NullPointerException, catch the
	 *         exception and print Not found
	 * 6. Print the hash value corresponding to the country name along with the country name*/
	
	public static void getValue(String country) {
		int hash = 0;
		char[] chars = country.toCharArray();
		for(int a = 0; a < chars.length; a++) {
			hash += (int)chars[a];
		}
		
		try {
			if(table.get(hash%250).equals(country)) {
				System.out.println(hash%250 + ": " + table.get(hash%250));
			}
			else {
				do {
					System.out.println(hash%250 + ": " + table.get(hash%250));
					hash++;
				}while(!(table.get(hash%250).equals(country)));
				System.out.println(hash%250 + ": " + table.get(hash%250));
			}
		}
		catch(NullPointerException e) {
			System.out.println("Not found in hash table!");
		}
	}
	
}