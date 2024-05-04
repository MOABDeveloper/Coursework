public class OrderedLinkedList<T extends Comparable<T>> {
    private Node<T> head;
    private int size;

    public OrderedLinkedList() {        // Initializes an empty linked list
        this.head = null;
        this.size = 0;
    }

    public int getSize() {
        return size;
    }

    public void insert(T element) {     //Inserts the element into the list from largest to smallest.
        Node<T> newNode = new Node<>(element, null);

        if (head == null || element.compareTo(head.getData()) > 0) {
            newNode.setNext(head);  //Insert the start if empty or if element is greater than head.
            head = newNode;
        } else {                    //Go through the list to find the appropriate place to place element.
            Node<T> current = head;
            while (current.getNext() != null && element.compareTo(current.getNext().getData()) < 0) {
                current = current.getNext();
            }
            newNode.setNext(current.getNext());     //Place it when appropriate place is found.
            current.setNext(newNode);
        }
        size++;                                     //Increase list size
    }

    public T get(int index) {
        if (index < 0 || index >= size) {               // Checks if the index is out of bounds
            throw new IndexOutOfBoundsException("Index is out of bounds: " + index);
        }

        Node<T> current = head;
        for (int i = 0; i < index; i++) {           //Goes through the list to find correct i
            current = current.getNext();
        }
        return current.getData();                   //Returns the "i-th" element in the list
    }
}

