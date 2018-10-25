import java.util.*;

public class Cashiers{
  static String matrix[][] = new String[3][6];
  static int currentSize[] = new int[3];
  static int total = 1;

  //The below method will add the next value to a queue so long as it has space.
  public static boolean enqueue(){
    int count = 0;
    int max = 6;
    int pos = 0;
    boolean bool = false;

    for(int a = 0; a < currentSize.length; a++){
      if(currentSize[a] == 6){
        count++;
      }
      if(count == 3){
        bool = true;
        System.out.println("All the queues are full.");
        return bool;
        break;
      }
      if(currentSize[a] == max){
        
      }
      if(currentSize[a] < max){
        max = currentSize[a];
        pos = a;
      }

    }





    return bool;
  }
  public static int dequeue(int which){
    int pos = 0;
    int count = 0;
    int popped = 0;
    for(int a = 0; a < matrix[which].length; a++){
      if((matrix[which][a]).contains("F")){
        popped = Integer.parseInt(matrix[which][a].replace("F",""));
        pos = a;
        while(matrix[which][count] == "0"){
          count++;
        }
        matrix[which][count] = matrix[which][count]+"F";
        currentSize[which] = currentSize[which] - 1;
      }
    }
    return popped;
  }

  //Below will reset all the values of the matrix array to 0.
  public static void clear(){
    for(int a = 0; a < matrix.length; a++){
      for(int b = 0; b < matrix[a].length; b++){
        matrix[a][b] = "0";
      }
    }
  }

  //The below will display the contents of the matrix variable.
  public static void display(){
    if(matrix[0][0] == null){
      clear();
    }
    for(int a = 0; a < matrix.length; a++){
      for(int b = 0; b < matrix[a].length; b++){
        System.out.print(matrix[a][b]+ "    ");
      }
      System.out.println();
    }
  }
  //The function below will fill the matrix, from left to right incrementing
  //each element.
  public static void fill(){
    for(int a = 0; a < matrix.length; a++){
      for(int b = 0; b < matrix[a].length; b++){
        matrix[a][b] = Integer.toString(total);
        if(b == 0){
          matrix[a][b] = matrix[a][b] + "F";
        }
        if(b == 5){
          matrix[a][b] = matrix[a][b] + "B";
        }
        total ++;
        currentSize[a] = currentSize[a] + 1;
      }
    }
  }

  public static void main(String [] args){
    Scanner in = new Scanner(System.in);
    String input = null;

    while(input != "Q"){
      display();
      System.out.println("Input command E or 1 or 2 or 3 or F or C or Q");
      input = (in.nextLine()).toUpperCase();
      switch (input){
        case "E":
          enqueue();
          break;
        case "1":
          dequeue(0);
          break;
        case "2":
          dequeue(1);
          break;
        case("3"):
          dequeue(2);
          break;
        case "F":
          fill();
          break;
        case "C":
          clear();
          break;
        case "Q":
          input = "Q";
          break;
        default:
          System.out.println("That's not a valid command, try again:");
      }
    }

  }
}
