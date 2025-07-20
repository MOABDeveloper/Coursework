public class BSTNode {

    // Attribute Declaration
    private Record node;
    private BSTNode rightChild;
    private BSTNode leftChild;
    private BSTNode parent;

    // Constructor
    public BSTNode(Record node) 
    {
        this.node = node;
        this.rightChild = null;
        this.leftChild = null;
        this.parent = null;
    }

    // Getters
    public Record getRecord() 
    {
        return node;
    }

    public BSTNode getRightChild() 
    {
        return rightChild;
    }

    public BSTNode getLeftChild() 
    {
        return leftChild;
    }

    public BSTNode getParent() 
    {
        return parent;
    }

    // Setters
    public void setRecord(Record node) 
    {
        this.node = node;
    }

    public void setRightChild(BSTNode rightChild) 
    {
        this.rightChild = rightChild;
    }

    public void setLeftChild(BSTNode leftChild) 
    {
        this.leftChild = leftChild;
    }

    public void setParent(BSTNode parent) 
    {
        this.parent = parent;
    }

    // Method to check if the node is a leaf
    public boolean isLeaf() {
        return this.leftChild == null && this.rightChild == null;
    }
}
