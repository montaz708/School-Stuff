import java.util.*;

public class test{
  public static String carry;
  public static void main (String [] args){
    Scanner kb = new Scanner(System.in);
    LinkedList <LinkedList<String>> masterArr = new LinkedList<LinkedList<String>>();
    LinkedList<String> temp = new LinkedList<String>();
    LinkedList<String> theAnswer = new LinkedList<String>();
    String input = "0";

    System.out.println("Enter numbers you want the sum of, when you're finished, enter -1: ");
    int count = 0;
    while(Integer.parseInt(input) != -1){
        input = kb.nextLine();
        if(!(input.equals("-1"))){
          masterArr.add(count, createLinkedList(input));
        }
    }
    do{
      for(int a = 0; a < masterArr.size(); a++){
        temp.push(masterArr.get(a).pop());
        if (temp.size() == masterArr.size() && masterArr.get(a).peek() != null){
           theAnswer.push(doTheMath(temp));
        }
      }
    }while(masterArr.peek() != null);

    for(int i = 0; i < theAnswer.size(); i++){
      System.out.print(theAnswer.pop());
    }
  }

  /*
  This class takes the user's input and puts it into a LinkedList, with each
  element of the linkedlist representing a digit of the user's input.
  */
  public static LinkedList<String> createLinkedList(String input){
    int i;
    LinkedList<String> aList = new LinkedList<String>();

    for(i = 0; i < input.length(); i++){
      aList.push(input.substring(0, i));
      input = input.substring(0, input.length()-1);
    }
    return aList;
  }

  /*
  The point of this class is to add the elements of the linkedlists created by the user,
  and one by one, return the answer of the sum of first (the elements at position 0) elements of the linkedlist containing
  the user's input. Additionally, this class handles the carry in the arithmetic, to solve the problem
  I initialized carry as a "global" variable, that way it could be accessed from the main method.
  */
  public static String doTheMath(LinkedList<String> digits){
    String sum, dig, carry;

    while(digits.peek() != null){
      dig = digits.pop();
      sum = Integer.toString((Integer.parseInt(sum))+(Integer.parseInt(dig)));
      if(sum.length() > 1 && digits.peek() = null){
        carry = sum.substring(0,1);
        sum = sum.substring(1,sum.length());
      }
    }
    return sum;
  }
}
