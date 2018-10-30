import java.util.*;

public class Cashiers{
  static String matrix[][] = new String[3][6];
  static int currentSize[] = new int[3];
  static int total = 1;

  //The below method will add the next value to a queue so long as it has space.
  public static boolean enqueue(){
    boolean bool = true;
    int isFull = 0;
    int max = 6;
    int pos = 0;
    int count = 0;
    for(int a = 0; a < currentSize.length; a++){
      if(currentSize[a] == 0 && a == 0){
        max = 0;
        pos = 0;
        break;
      }
      if(currentSize[a] == 6){
        isFull++;
      }
      if(currentSize[a] < max){
        max = currentSize[a];
        pos = a;
      }
    }
    if(isFull == 3){
      bool = false;
      return bool;
    }
    if(pos == 0 && max == 0){
      matrix[0][0] = Integer.toString(total) + "FB";
      total++;
      currentSize[0] += 1;
      return bool;
    }
    for(int a = 0; a < matrix[pos].length; a++){
      if(matrix[pos][a].contains("B")){
        matrix[pos][a] = matrix[pos][a].replace("B","");
        try{
          matrix[pos][a + 1] = Integer.toString(total) + "B";
          total++;
          currentSize[pos] += 1;
          return bool;
        }
        catch(IndexOutOfBoundsException e){
          count = 1;
          if(matrix[pos][0].equals("0")){
            matrix[pos][0] = Integer.toString(total) + "B";
            total++;
            currentSize[pos] += 1;
            return bool;
          }
          else{
            while(!(matrix[pos][count].equals("0")) || !(matrix[pos][count].equals("0F"))){
              count++;
            }
            if(matrix[pos][count].equals("0F")){
              matrix[pos][count] = Integer.toString(total) + "B";
              total++;
              currentSize[pos] += 1;
              return bool;
            }
            else{
              matrix[pos][count] = Integer.toString(total) + "B";
              total++;
              currentSize[pos] += 1;
              return bool;
            }
          }
        }
      }
      else if(currentSize[pos] == 0){
        matrix[pos][0] = Integer.toString(total) + "FB";
        total++;
        currentSize[pos] += 1;
        return bool;
      }
    }
    return bool;
  }
  public static int dequeue(int which){
    int pos = which - 1;
    int popped = 0;
    int count = 0;

    if(currentSize[pos] == 0){
      popped = -1;
      return popped;
    }
    for(int a = 0; a < matrix[pos].length; a++){
      if(matrix[pos][a].contains("F")){
        if(currentSize[pos] != 1){
          popped = Integer.parseInt(matrix[pos][a].replace("F",""));
        }
        else if(currentSize[pos] == 1){
          popped = Integer.parseInt(matrix[pos][a].replace("F","").replace("B",""));
          currentSize[pos] -= 1;
          return popped;
        }
        matrix[pos][a] = "0";
        currentSize[pos] -= 1;
        try{
          matrix[pos][a + 1] = matrix[pos][a + 1] + "F";
          return popped;
        }
        catch(IndexOutOfBoundsException e){
          if(!(matrix[pos][0].equals("0"))){
            matrix[pos][0] = matrix[pos][0]+ "F";
            return popped;
          }
          else{
            if(currentSize[pos] == 0){
              popped = -1;
              return popped;
            }
            count = 1;
            while(matrix[pos][count].equals("0")){
              count++;
            }
            matrix[pos][count] = matrix[pos][count] + "F";
            return popped;
          }
        }
      }
    }
    return popped;
  }

  //Below will reset all the values of the matrix array to 0.
  public static void clear(){
    for(int a = 0; a < matrix.length; a++){
			for(int b = 0; b < matrix[a].length; b++){
				matrix[a][b] = "0";
				if(b == 0){
					matrix[a][b] = matrix[a][b] + "F";
				}
			}
			currentSize[a] = 0;
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
					total++;
					if(b == 0){
						matrix[a][b] = matrix[a][b] + "F";
					}
					if(b == 5){
						matrix[a][b] = matrix[a][b] + "B";
					}
					currentSize[a] += 1;
				}
			}
	}

  public static void main(String [] args){
    Scanner in = new Scanner(System.in);
    String input = null;
    int popped = 0;

    while(input != "Q"){
      display();
      System.out.println("Input command E or 1 or 2 or 3 or F or C or Q");
      input = (in.nextLine()).toUpperCase();
      switch (input){
        case "E":
          if(enqueue() == false){
            System.out.println("All queues are full.\n");
            break;
          }
          break;
        case "1":
          popped = dequeue(1);
          if(popped == -1){
            System.out.println("The queue is already empty\n");
          }
          else{
            System.out.println(popped + " was popped.\n");
          }
          break;
        case "2":
          popped = dequeue(2);
          if(popped == -1){
            System.out.println("The queue is already empty\n");
          }
          else{
            System.out.println(popped + " was popped.\n");
          }
          break;
        case("3"):
          popped = dequeue(3);
          if(popped == -1){
            System.out.println("The queue is already empty\n");
          }
          else{
            System.out.println(popped + " was popped.\n");
          }
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
