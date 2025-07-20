public class BinarySearchTree {

    // Root node of the binary search tree
    private BSTNode root;

    // Constructor to creat an empty tree with a null root
    public BinarySearchTree() {
        this.root = null;
    }

    // Returns the root node of this binary search tree
    public BSTNode getRoot() {
        return root;
    }

    // Adds a record to the binary search tree with root r
    // Throws DictionaryException if the key already exsists
    public void insert(BSTNode r, Record d) throws DictionaryException 
    {
        if (r == null) 
        {
            root = new BSTNode(d);
        } 
        else 
        {
            insertRecursively(r, d);
        }
    }

    // Helper method to insert a record into the tree recursivly
    private void insertRecursively(BSTNode r, Record d) throws DictionaryException 
    {
        // Compare the key of the new record with the key of the current node's record
        if (d.getKey().compareTo(r.getRecord().getKey()) < 0) 
        {
            // If the key of the new record is smaller, check if the left child is null
            if (r.getLeftChild() == null) 
            {
                // If left child is null, insert the new record here
                r.setLeftChild(new BSTNode(d));
            } 
            else 
            {
                // If left child is not null, continue recursion on the left subtree
                insertRecursively(r.getLeftChild(), d);
            }
        } 
        else if (d.getKey().compareTo(r.getRecord().getKey()) > 0) 
        {
            // If the key of the new record is greater, check if the right child is null
            if (r.getRightChild() == null) 
            {
                // If right child is null, insert the new record here
                r.setRightChild(new BSTNode(d));
            } 
            else 
            {
                // If right child is not null, continue recursion on the right subtree
                insertRecursively(r.getRightChild(), d);
            }
        } 
        else
        {
            // If the key of the new record matches the current node's key, throw an exception
            throw new DictionaryException("Key already exsists in the tree");
        }
    }
    
    // Returns the node storing the given key; returns null if the key is not found
    public BSTNode get(BSTNode r, Key k) 
    {
        if (r == null) 
        {
            return null;
        }
        if (k.compareTo(r.getRecord().getKey()) < 0) 
        {
            return get(r.getLeftChild(), k);
        } 
        else if (k.compareTo(r.getRecord().getKey()) > 0) 
        {
            return get(r.getRightChild(), k);
        } 
        else 
        {
            return r;
        }
    }

    // Removes the node with the given key from the tree
    public void remove(BSTNode r, Key k) throws DictionaryException 
    {
        root = removeRecursively(r, k);
    }

    private BSTNode removeRecursively(BSTNode r, Key k) throws DictionaryException 
    {
        if (r == null) 
        {
            throw new DictionaryException("Key not found in the tree");
        }
        if (k.compareTo(r.getRecord().getKey()) < 0) 
        {
            r.setLeftChild(removeRecursively(r.getLeftChild(), k));
        } 
        else if (k.compareTo(r.getRecord().getKey()) > 0) 
        {
            r.setRightChild(removeRecursively(r.getRightChild(), k));
        } 
        else 
        {
            if (r.getLeftChild() == null) 
            {
                return r.getRightChild();
            } 
            else if (r.getRightChild() == null) 
            {
                return r.getLeftChild();
            }
            BSTNode smallestNode = smallest(r.getRightChild());
            r.setRecord(smallestNode.getRecord());
            r.setRightChild(removeRecursively(r.getRightChild(), smallestNode.getRecord().getKey()));
        }
        return r;
    }

    // Returns the node with the smallest key in tree with root r
    public BSTNode smallest(BSTNode r) 
    {
        if (r == null || r.getLeftChild() == null) 
        {
            return r;
        }
        return smallest(r.getLeftChild());
    }

    // Returns the node with the largest key in tree with root r
    public BSTNode largest(BSTNode r) 
    {
        if (r == null || r.getRightChild() == null) 
        {
            return r;
        }
        return largest(r.getRightChild());
    }
}

