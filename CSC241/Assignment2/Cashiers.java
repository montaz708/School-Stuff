public class Cashiers{
  static int matrix[][] = new int[3][6];
  static int currentSize[] = new int[3];
  static int total;

  //The below method will add the next value to a queue so long as it has space.
  public static boolean enqueue(){
    int count = 0;
    int max = 6;
    int pos = 0;
    boolean bool = false;

    /*The idea here is to iterate through currentSize to see if all values
    are equal to the max size of the arrays. Additionally, we will keep
    track of the smallest queue, and if bool is still false, we'll push
    another "customer" onto the queue.*/

    for(int a = 0; a < currentSize.length; a++){
      if(currentSize[a] == 6){
        count++;
      }
      else if(currentSize[a] < max){
        max = currentSize[a];
        pos = a;
      }
      if(currentSize[a] == currentSize[a-1]){
        pos = a-1;
      }
      if(a = 2 && currentSize[a] == currentSize[a-2]){
        pos = a -2;
      }
    }
    if(count == 3){
      bool = true;
      return bool;
    }



    return bool;
  }
  public static int dequeue(int which){

  }

  //Below will reset all the values of the matrix array to 0.
  public static void clear(){
    for(int a = 0; a < matrix.length(); a++){
      for(int b 0; matrix[a].length; b++){
        matrix[a][b] = 0;
      }
    }
  }

  //The below will display the contents of the matrix variable.
  public static void display(){
    for(int a = 0; a < matrix.length(); a++){
      for(int b = 0; b < matrix[a].length(); b++){
        System.out.print(matrix[a][b]+ "    ");
      }
      System.out.println();
    }
  }
  public static void fill(){

  }

  public static void main(String [] args){

  }
}
