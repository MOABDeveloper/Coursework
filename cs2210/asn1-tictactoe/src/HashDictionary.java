import java.util.LinkedList;

public class HashDictionary implements DictionaryADT {
    // Array LinkedLists to implements chaining for hash collisions
    private LinkedList<Data>[] table;
    private int size;

    //Constructor initalizes hash table with specified size
    public HashDictionary(int size) {
        this.size = size;
        table = (LinkedList<Data>[]) new LinkedList[size];  // Safe cast

        for (int i = 0; i < size; i++) {
            table[i] = new LinkedList<>();
        }
    }

    //Computes the index of a key 
    private int hashFunction(String key) {
        int hash = 0;
        int prime = 10;  // Polynomial hash with a small prime number
        //Generate a hashvalue
        for (int i = 0; i < key.length(); i++) {
            hash = (prime * hash + key.charAt(i)) % size;
        }
        return hash;
    }

    //Adds record to the dictionary
    @Override
    public int put(Data record) throws DictionaryException {
        int index = hashFunction(record.getConfiguration());

        for (int i = 0; i < table[index].size(); i++) {
            // Get element at index i
            Data data = table[index].get(i);  
            if (data.getConfiguration().equals(record.getConfiguration())) {
                // Throw exception if configuration exists in dictionary
                throw new DictionaryException();  
            }
        }
        table[index].add(record);  // Add the new record to the chain
        return table[index].size() > 1 ? 1 : 0;  // Return 1 if there was a collision, 0 otherwise
    }


    @Override
    //Removes record from hashtble
    public void remove(String config) throws DictionaryException {
        int index = hashFunction(config);
    
        //Iterate throught the chain
        for (int i = 0; i < table[index].size(); i++) {
            Data data = table[index].get(i);  // Get each element by index
            if (data.getConfiguration().equals(config)) {   //Compare and each if we found it
                table[index].remove(i);  // Remove element at the current index
                return;  // Exit after removing the element
            }
        }
        throw new DictionaryException();  // Throw exception if config not found
    }
    

    @Override
    //Returns the score given config
    public int get(String config) {
        int index = hashFunction(config);
    
        // Iterate thrugh the chain 
        for (int i = 0; i < table[index].size(); i++) {
            Data data = table[index].get(i);  // Get each element by index
            if (data.getConfiguration().equals(config)) {
                return data.getScore();  // Return the score if found
            }
        }
        return -1;  // Configuration not found
    }
    

    @Override
    //Number of objects in the dictionary
    public int numRecords() {
        int numRecords =0;  //intialize numRecords
        //Iterate throught the table
        for (int i = 0; i < table.length; i++){
            //Add the size when not null
            if (table[i] != null){ 
                numRecords += table[i].size();
            }
        }

        return numRecords;//Return the total size.
    }
}
