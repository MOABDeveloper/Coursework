public class Record 
{

    // Private fields for storing the key and data associated with the record
    private Key theKey;
    private String data;

    // Constructor to create a new record with a specified key and data
    public Record(Key theKey, String data) 
	{
        this.theKey = theKey;
        this.data = data;
    }

    // Getter method to retrieve the key of the record
    public Key getKey() 
	{
        return theKey;
    }

    // Getter method to retrieve the data associated with the record
    public String getDataItem() 
	{
        return data;
    }
}

