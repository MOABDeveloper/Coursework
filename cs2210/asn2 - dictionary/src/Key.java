public class Key {
    //Declate the instance variables
    private String label; 
    private int type;

    //A constructor which initializes a new Keyobject with the specified parameters
    public Key(String theLabel, int theType)
    {
        this.label = theLabel.toLowerCase();
        this.type = theType;
    }

    public String getLabel()
    {
        return label;
    }

    public int getType()
    {
        return type;
    }

    //Two Key objects A and B are equal if A.label = B.label and A.type = B.type.
    public int compareTo(Key k) {

        int compared_label = this.label.compareTo(k.getLabel());
    int compared_type = Integer.compare(this.type, k.getType()); // Using Integer.compare for clarity

    // Compare labels first
    if (compared_label < 0) 
    {
        return -1;
    } 
    else if (compared_label > 0) 
    {
        return 1;
    } 
    else 
    {
        // If labels are equal, compare types
        if (compared_type < 0) 
        {
            return -1;
        } 
        else if (compared_type > 0) 
        {
            return 1;
        } 
        // Both label and type are equal
        else 
        {
            return 0; 
        }
    }
}

}


