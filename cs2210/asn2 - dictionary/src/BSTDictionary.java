public class BSTDictionary implements BSTDictionaryADT {

    private BSTNode root;

    // Constructor to create an empty BSTDictionary with a null root
    public BSTDictionary() 
    {
        this.root = null;
    }

    // Method to insert a Record into the dictionary
    public void put(Record d) throws DictionaryException 
    {
        if (root == null) 
        {
            root = new BSTNode(d);
        } 
        else 
        {
            insertRecursively(root, d);
        }
    }

    private void insertRecursively(BSTNode node, Record d) throws DictionaryException {
        if (node.getRecord() == null) 
        {
            // This is a leaf node, replace with a new internal node
            node.setRecord(d);
            node.setLeftChild(new BSTNode(null)); // Create new leaf nodes
            node.setRightChild(new BSTNode(null));
        } 
        else 
        {
            int comparison = d.getKey().compareTo(node.getRecord().getKey());
            if (comparison < 0) 
            {
                if (node.getLeftChild() == null) 
                {
                    node.setLeftChild(new BSTNode(d));
                    node.getLeftChild().setLeftChild(new BSTNode(null));
                    node.getLeftChild().setRightChild(new BSTNode(null));
                } 
                else 
                {
                    insertRecursively(node.getLeftChild(), d);
                }
            } else if (comparison > 0) {
                if (node.getRightChild() == null) {
                    node.setRightChild(new BSTNode(d));
                    node.getRightChild().setLeftChild(new BSTNode(null));
                    node.getRightChild().setRightChild(new BSTNode(null));
                } 
                else 
                {
                    insertRecursively(node.getRightChild(), d);
                }
            } 
            else 
            {
                throw new DictionaryException("Key already exists in the dictionary");
            }
        }
    }

    // Method to get the Record associated with a given Key
    public Record get(Key k) 
    {
        BSTNode node = getRecursively(root, k);
        if (node != null && node.getRecord() != null)
        {
            return node.getRecord();
        }
        return null; // Key not found
    }

    private BSTNode getRecursively(BSTNode node, Key k) 
    {
        if (node == null || node.getRecord() == null) 
        {
            return null;
        }
        int comparison = k.compareTo(node.getRecord().getKey());

        if (comparison < 0) 
        {
            return getRecursively(node.getLeftChild(), k);
        } 
        else if (comparison > 0) 
        {
            return getRecursively(node.getRightChild(), k);
        } 
        else 
        {
            return node; // Found the node
        }
    }

    // Removes a node with the specified key from the tree
    public void remove(Key k) throws DictionaryException 
    {
    root = removeRecursively(root, k);
    }

    private BSTNode removeRecursively(BSTNode node, Key k) throws DictionaryException 
    {
    if (node == null || node.getRecord() == null) 
    {
        throw new DictionaryException("Key not found in the dictionary");
    }

    int comparison = k.compareTo(node.getRecord().getKey());
    if (comparison < 0) 
    {
        node.setLeftChild(removeRecursively(node.getLeftChild(), k));
    } 
    else if (comparison > 0) 
    {
        node.setRightChild(removeRecursively(node.getRightChild(), k));
    } 
    else 
    {
        // Node with the key found
        if (node.getLeftChild() == null || node.getLeftChild().getRecord() == null) 
        {
            return node.getRightChild(); // Replace with right child if left is null or a leaf
        } 
        else if (node.getRightChild() == null || node.getRightChild().getRecord() == null) 
        {
            return node.getLeftChild(); // Replace with left child if right is null or a leaf
        }

        // Node with two children: Find the smallest node in the right subtree
        BSTNode current = node.getRightChild();
        while (current.getLeftChild() != null && current.getLeftChild().getRecord() != null) 
        {
            current = current.getLeftChild();
        }

        // Replace node's record with the smallest node's record
        node.setRecord(current.getRecord());

        // Remove the smallest node in the right subtree
        node.setRightChild(removeRecursively(node.getRightChild(), current.getRecord().getKey()));
    }

    return node;
    
    }
 

    public Record successor(Key k) 
    {
    BSTNode current = root;
    BSTNode successor = null;

    while (current != null && current.getRecord() != null) 
    {
        int comparison = k.compareTo(current.getRecord().getKey());
        if (comparison < 0) 
        {
            // Possible successor; move to the left subtree
            successor = current;
            current = current.getLeftChild();
        } 
        else 
        {
            // Move to the right subtree
            current = current.getRightChild();
        }
    }

    // If we found a successor, return the associated Record
    if (successor != null) 
    {
        return successor.getRecord();
    }

    return null; // No successor found
}

     // Finds and returns the predecessor Record of the given key
    public Record predecessor(Key k) 
    {
    BSTNode current = root;
    BSTNode predecessor = null;

    while (current != null && current.getRecord() != null) 
    {
        int comparison = k.compareTo(current.getRecord().getKey());
        if (comparison > 0) 
        {
            // Possible predecessor; move to the right subtree
            predecessor = current;
            current = current.getRightChild();
        } 
        else 
        {
            // Move to the left subtree
            current = current.getLeftChild();
        }
    }

    // If we found a predecessor, return the associated Record
    if (predecessor != null) 
    {
        return predecessor.getRecord();
    }

    return null; // No predecessor found
    }

    // Finds and returns the node with the smallest key in the subtree with root r
    public Record smallest() 
    {
        if (root == null || root.getRecord() == null) 
        {
            return null; // Handle empty tree case
        }
        BSTNode current = root;
        while (current.getLeftChild() != null && current.getLeftChild().getRecord() != null) 
        {
            current = current.getLeftChild();
        }

        return current.getRecord(); // Return the smallest node's record
    }
    
    
    public Record largest() 
    {
        if (root == null || root.getRecord() == null) 
        {
            return null; // Handle empty tree case
        }
        BSTNode current = root;
        while (current.getRightChild() != null && current.getRightChild().getRecord() != null) 
        {
            current = current.getRightChild();
        }
        return current.getRecord(); // Return the largest node's record
    }
    
}
