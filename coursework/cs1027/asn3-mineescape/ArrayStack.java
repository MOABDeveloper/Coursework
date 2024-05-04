
public class ArrayStack <T> implements StackADT<T> {
    private T[] array;
    private int top;

    public ArrayStack(){                                //Constructor initialize data.
        this.array = (T[]) new Object[10];
        top = -1;
    }


    public void push(T element) {                       //Add element to top of stack.
        expandCapacity();                               //Expand capacity
        this.array[this.top+1] = element;               //Add element on "top" location.
        top += 1;                                       //Iterate top.

    }


    public T pop() throws StackException {
        if (isEmpty()) {
            throw new StackException("Stack is empty");
        }
        shrinkCapacity();               //Shrink Capacity if needed
        T topStack = array[top];        //For the return statement we return the top of stack.
        array[top] = null;              //Not necessary but delete it.
        top --;                       //Shrink top.

        return topStack;
    }


    public T peek() throws StackException {                 //Returns the top of the ArrayStack.
        if (isEmpty()) {                                    //Checks if its empty first.
            throw new StackException("Stack is empty");     //Throws exception if it is.
        }
        return array[top];
    }

    public boolean isEmpty() {                              //Checks if ArrayStack is empty
        return top == -1;
    }

    public int size() {                                     //Returns size of the ArrayStack
        return top+1;
    }

    public void clear() {                                   //Clears all data in ArrayStack
        while (!isEmpty()){                                 //Pop when it's not empty.
            pop();
        }
        top = -1;                                           //When its empty we reset top
        this.array = (T[]) new Object[10];                  //and initialCapacity of ArrayStack.
    }

    public int getCapacity(){                               //Get total capacity.
        return array.length;
    }

    public int getTop(){                                    //Gettor for private top.
        return top;
    }


    public String toString() {                              //Return the ArrayStack in a string.
        if (isEmpty()) {                                    //Check is empty first and return.
            return "Empty stack.";
        }

        StringBuilder out = new StringBuilder("Stack: ");   //String Builder new String.
        for (int i = top; i >= 0; i--) {                    //Iterate through the ArrayStack.
            out.append(array[i]);                           //Add onto array each time.
            if (i > 0) {                                    //Adds the comma and space on all except last.
                out.append(", ");
            }
        }
        out.append(".");                                    //Add dot at end.
        return out.toString();
    }


    private void expandCapacity( ) {
        //Create a new array, as it to generic data type and then set it to the old array capacity + 10
        if ((double) size() / (double) array.length >= .75) {   //Checks if we are at 75% usage.
            int newCapacity = array.length + 10;
            T[] expandedArray = (T[]) new Object[newCapacity];
            for (int i = 0; i <= top; i++) {        //Duplicates the items in the array.
                expandedArray[i] = array[i];
            }
        this.array = expandedArray;                                   //Makes the old array the expandArray.
        }
    }


    private void shrinkCapacity() {
        //Create a new array, as it to generic data type and then set it to the old array capacity - 10
        if ((double) size() / (double) array.length <= 0.25 && array.length >= 20) {    //Checks if we are at 25% usage and above 20 slots.
            int newCapacity = array.length - 10;
            T[] shrunkArray = (T[]) new Object[newCapacity];
            for (int i = 0; i <= top; i++) {       //Duplicates the items in the array.
                shrunkArray[i] = array[i];
            }
            this.array = shrunkArray;                               //Makes the old array the shrunkArray.
        }
    }
}
