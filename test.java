import java.util.*;

public class test{

  public static void main (String [] args){
    Scanner in = new Scanner(System.in);
    LinkedList<LinkedList<Integer>> masterArr = new LinkedList<LinkedList<Integer>>();
    LinkedList<Integer> temp = new LinkedList<Integer>();
    LinkedList<Integer> theAnswer = new LinkedList<Integer>();
    String input = "0";
    int digit;
    int sum;
    int max = 0;
    int carry = 0;

    System.out.println("Enter the numbers you want the sum of. When you're finished, enter -1");
    while(!(input.equals("-1"))){
      input = in.nextLine();
      if(!(input.equals("-1"))){
        masterArr.push(createLinkedList(input));
        if(input.length() > max){
          max = input.length();
        }
      }
    }

    for(int a = 0; a < max; a++){
      for(int b = 0; b < masterArr.size(); b++){
        if(masterArr.get(b).peek() == null){
          temp.push(0);
          continue;
        }
        temp.push(masterArr.get(b).pop());
      }
      sum = 0;
      while(temp.peek() != null){
        digit = temp.pop();
        if(carry != 0){
          digit = carry + digit;
          carry = 0;
        }
        sum = digit + sum;
      }
      if(a != max){
        if(Integer.toString(sum).length() > 1){
          carry = Integer.parseInt(Integer.toString(sum).substring(0,1));
          sum = Integer.parseInt(Integer.toString(sum).substring(1,Integer.toString(sum).length()));
        }
      }
      theAnswer.push(sum);
    }

    System.out.println("\n The sum is: ");
    while(theAnswer.peek() != null){
      System.out.print(theAnswer.pop());
    }
    System.out.println("");
  }

  /*
  This class takes the user's input and puts it o a LinkedList, with each
  element of the linkedlist representing a digit of the user's input.
  */
  public static LinkedList<Integer> createLinkedList(String input){
    LinkedList<Integer> aList = new LinkedList<Integer>();
     int num;
    while(!(input.isEmpty())){
      num = (input.charAt(0)) - 48;
      input = input.substring(1,input.length());
      aList.push(num);
    }
    return aList;
  }
}
