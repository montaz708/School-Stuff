import java.util.*;

public class Assignment1{
/*
In the below main method, masterArr is a linkedlist composed of linkedlists whose type is Integers.
temp represents a "buffer" like linkedlist which is in charge of popping elements of masterArr's subelements
and using the elements (of temp) to perform the required addition.

digit, sum, and carry are variables used to do the arithmetic where digit represents a singular number to add to the
running total of the sum variable. Once the sum has been calculated the result is pushed onto the linkedlist labelled
theAnswer.

The variable max holds the value of the longest (in terms of digits to a number) number entered by the user during
the prompt stage of this program.
*/
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

    //loop until the user enters -1, this stage populates masterArr with linkedlists
    //of type string containing the numbers entered
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
//The variable max tells the for loop how many times to iterate, this ensures that all elements of all
//the linkedlists are popped and used during the arithmetic stage of this program
    for(int a = 0; a < max; a++){
      for(int b = 0; b < masterArr.size(); b++){
        if(masterArr.get(b).peek() == null){
          temp.push(0);
          continue;
        }
        temp.push(masterArr.get(b).pop());
      }
      //set the sum to 0 every time temp has new digits to do arithmetic with
      //Additionally, the carry variables is evaluted to see if it has a value stored in it
      //after temp has new values passed to it.
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
//loop and pop out all elements of theAnswer until it's empty, output to the console.
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
