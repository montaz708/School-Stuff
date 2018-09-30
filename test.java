import java.util.*;

public class test{

  public static void main (String [] args){
    Scanner kb = new Scanner(System.in);
    LinkedList <LinkedList<String>> masterArr = new LinkedList<LinkedList<String>>();
    LinkedList<String> temp = new LinkedList<String>();
    LinkedList<String> theAnswer = new LinkedList<String>();
    String sum;
    String carry;
    String dig;
    String input = "0";

    System.out.println("Enter numbers you want the sum of, when you're finished, enter -1: ");
    while(!(input.equals("-1"))){
        input = kb.nextLine();
        if(!(input.equals("-1"))){
          masterArr.add(createLinkedList(input));
        }
    }

    while(masterArr.size() != 0){
      for(int a = 0; a < masterArr.size(); a++){
        if(masterArr.get(a).peek() == null){
          masterArr.remove(a);
        }
        temp.push(masterArr.get(a).pop());
      }
      sum = "0";
      carry = "0";
      while(temp.peek() != null){
        dig = temp.pop();
        if(!(carry.equals("0"))){
          dig = Integer.toString(Integer.parseInt(dig) + (Integer.parseInt(carry)));
          carry = "0";
        }
        sum = Integer.toString((Integer.parseInt(sum))+(Integer.parseInt(dig)));
        if(sum.length() > 1){
          carry = sum.substring(0,1);
          sum = sum.substring(1,sum.length());
        }
        theAnswer.push(sum);
      }
    }
    for(int c = 0; c < theAnswer.size(); c++){
      System.out.print(theAnswer.pop());
    }
  }

  /*
  This class takes the user's input and puts it into a LinkedList, with each
  element of the linkedlist representing a digit of the user's input.
  */
  public static LinkedList<String> createLinkedList(String input){
    LinkedList<String> aList = new LinkedList<String>();

    while(!(input.isEmpty())){
      aList.push(input.substring(0,1));
      input = input.substring(1, input.length());
    }
    return aList;
  }
}
