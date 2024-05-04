public class Node<T> {
    private T data;
    private Node<T> next;

    public Node(T data, Node<T> next) {            // Initializes data and the next node.
        this.data = data;
        this.next = next;
    }

    public T getData() {            //Getter to get data in the node.
        return data;
    }

    public Node<T> getNext() {      //Getter to get next in node.
        return next;
    }

    public void setNext(Node<T> next) { //Setter to set the next node.
        this.next = next;
    }
}



