import java.util.NoSuchElementException;

public class UOLIterator<T extends Comparable<T>> implements CopyableIterator<T> {
    private LinearNode<T> current; // Pointer to the current element in the list

    public UOLIterator(LinearNode<T> startNode) {                   //Constructor
        this.current = startNode;
    }

    @Override
    public boolean hasNext() {                     //Check if there are unvisted elements left.
        return current != null;
    }

    @Override
    public T next() {                               //Returns the next unvisted element in the list.
        if (!hasNext()) {
            throw new NoSuchElementException("iterator empty"); //No more elements
        }

        T data = current.getData();
        current = current.getNext(); // Move the pointer to the next element
        return data;
    }

    @Override
    public CopyableIterator<T> copy() {             //Create copy of iterator.
        return new UOLIterator<>(current);          //New iterator starting at curr.
    }
}

