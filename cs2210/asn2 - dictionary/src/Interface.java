import java.io.BufferedReader;
import java.io.File; 
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Interface{


    private static boolean commands(BSTDictionary dictionary, String command, ArrayList<String> splitUserInput)
    {

        if (command.equals("define"))
        {
                // Check size of arguments inputted and print invalid command if less than 2
                if (splitUserInput.size() != 2) 
                {
                    System.out.println("Invalid command.");
                }

                //Get the word we want to add (label) from the input.
                String label = splitUserInput.get(1);
                //Create a new object with the word and the type 1
                Key newKey = new Key(label, 1);
                //Find the newRecord using the key
                Record newRecord = dictionary.get(newKey);
                // Check to see if word exists in dictionary, if not return null. Otherwise return the data stored.
                if(newRecord == null)
                {
                    System.out.println("the word " + label + " is not in the dictionary");

                } else 
                {
                    String data = newRecord.getDataItem();
                    System.out.println(data);
                }
        }
        else if(command.equals("translate"))
        {
            // Check size of arguments inputted and print invalid command if less than 2
            if (splitUserInput.size() != 2) 
            {
                System.out.println("Invalid input");
            }

            //Get the label from the command, add it with the corresponding type and find the key from the dictionary. 
            String label = splitUserInput.get(1);
            Key newkey = new Key(label, 2);
            Record newRecord = dictionary.get(newkey);
        
            //If we dont find the word return a statement. Otherwise output the data we found.
            if(newRecord == null)
            {
                System.out.println("There is no definition for the word " + label);
            } else 
            {
                String data = newRecord.getDataItem();
                System.out.println(data);
            }
        }
        else if (command.equals("sound"))
        {    
            // Check size of arguments inputted and print invalid command if less than 2
            if (splitUserInput.size() != 2) 
            {
                System.out.println("Invalid input");
            }

            //Get the label from the command, add it with the corresponding type and find the key from the dictionary.
            String label = splitUserInput.get(1);
            Key newkey = new Key(label, 3);
            Record newRecord = dictionary.get(newkey);
            
            //If we dont find the file print an error message
            if(newRecord == null)
            {
                System.out.println("There is no sound file for " + label);
            } 
            //If we find the file start playing using SoundPlayer.java
            else 
            {
                String filePath = newRecord.getDataItem();
                SoundPlayer player = new SoundPlayer();
                
                try
                {
                    player.play(filePath);
                } 
                catch (MultimediaException e) 
                {
                    System.out.println(e.getMessage());
                }
            }
        }
        else if(command.equals("play"))
        {
            // Check size of arguments inputted and print invalid command if less than 2
            if (splitUserInput.size() != 2) 
            {
                System.out.println("Invalid input");
            }

            //Get the label from the command, add it with the corresponding type and find the key from the dictionary. 
            String label = splitUserInput.get(1);
            Key finderKey = new Key(label, 4);
            Record newRecord = dictionary.get(finderKey);

            //If we dont find the file print an error message
            if(newRecord == null)
            {
                System.out.println("There is no music file for " + label);
            } 
            else 
            {
                // Play the music file if it exists and handle any exceptions that may arise
                String filePath = newRecord.getDataItem();
                SoundPlayer player = new SoundPlayer();
                try
                {
                    player.play(filePath);
                } 
                catch (MultimediaException e) 
                {
                    System.out.println(e.getMessage());
                }
            }
        }
        else if(command.equals("say"))
        {
            //Check size of arguments inputted and print invalid command if less than 2
            if (splitUserInput.size() != 2) 
            {
                System.out.println("Invalid input");
            }

            //Get the label from the command, add it with the corresponding type and find the key from the dictionary.
            String label = splitUserInput.get(1);
            Key finderKey = new Key(label, 5);
            Record newRecord = dictionary.get(finderKey);

            //When we cant find the file we print an error message. 
            if(newRecord == null)
            {
                System.out.println("There is no voice file for " + label);
            } 
            else 
            {
                // Play the audio file if it exists and handle any exceptions that may happen
                String filePath = newRecord.getDataItem();
                SoundPlayer player = new SoundPlayer();
                try
                {
                    player.play(filePath);
                } 
                catch (MultimediaException e) 
                {
                    System.out.println(e.getMessage());
                }
            }    
        }
        else if (command.equals("show")) 
        {
            
            //Check size of arguments inputted and print invalid command if less than 2
            if (splitUserInput.size() != 2) 
            {
                System.out.println("Invalid input");
            } 
            else 
            {
                //Get the label from the command, add it with the corresponding type and find the key from the dictionary.
                String label = splitUserInput.get(1);
                Key finderKey = new Key(label, 6);
                Record newRecord = dictionary.get(finderKey);
                
                //When we cant find the file we print an error message. 
                if (newRecord == null) 
                {
                    System.out.println("There is no image file for " + label);
                } 
                //If we can find it then we get the picture and open it, handling exceptions that could happen
                else 
                {
                    String filePath = newRecord.getDataItem();
                    PictureViewer viewer = new PictureViewer();
                    try 
                    {
                        viewer.show(filePath);
                    } 
                    catch (MultimediaException e) 
                    {
                        System.out.println(e.getMessage());
                    }
                }
            }
        } 
        else if (command.equals("animate")) {
            // Check if the correct number of arguments is provided
            if (splitUserInput.size() != 2) 
            {
                System.out.println("Invalid command.");
            } 
            else 
            {
                String label = splitUserInput.get(1);
                Key finderKey = new Key(label, 7); // Create a key to search for animated image files
                Record newRecord = dictionary.get(finderKey);
        
                // Check if the animated image file exists in the dictionary
                if (newRecord == null) 
                {
                    System.out.println("There is no animated image file for " + label);
                } 
                else 
                {
                    // Display the animated image if it exists
                    String filePath = newRecord.getDataItem();
                    PictureViewer viewer = new PictureViewer();

                    try {

                        viewer.show(filePath);
                    } 
                    catch (MultimediaException e) 
                    {
                        // Handle any exceptions that occur while showing the file
                        System.out.println(e.getMessage());
                    }
                }
            }
        }
        
        else if (command.equals("browse")) 
        {
        // Check if the correct number of arguments is provided
            if (splitUserInput.size() != 2) 
            {
                System.out.println("Invalid command.");
            } 
            else 
            {
                String label = splitUserInput.get(1);
                Key finderKey = new Key(label, 8); // Create a key to search for a webpage
                Record newRecord = dictionary.get(finderKey);

                // Check if the webpage exists in the dictionary
                if (newRecord == null) 
                {
                    System.out.println("There is no webpage called " + label);
                } 
                else 
                {
                    // Display the webpage if it exists
                    String filePath = newRecord.getDataItem();
                    ShowHTML htmlViewer = new ShowHTML();
                    htmlViewer.show(filePath);
                }
            }
        }
        else if (command.equals("delete")) 
        {
            // Check if the correct number of arguments is provided
            if (splitUserInput.size() != 3) 
            {
                System.out.println("Invalid command.");
            } 
            else 
            {
                // Pull the type from the input
                String label = splitUserInput.get(1);
                int type = Integer.parseInt(splitUserInput.get(2)); 
        
                try 
                {
                    // Attempt to remove the element with the specified key from the dictionary
                    dictionary.remove(new Key(label, type));
                } 
                catch (DictionaryException e) 
                {
                    // Handle any exceptions during the deletion process
                    System.out.println(e.getMessage());
                }
            }
        }
        
        else if (command.equals("add"))
        {
            // Ensure at least 4 elements are provided in the input
            if (splitUserInput.size() < 4) 
            {
                System.out.println("Invalid command.");
            } 
            else 
            {
                String label = splitUserInput.get(1);
                int type = Integer.parseInt(splitUserInput.get(2)); // Parse the type from input
                // Combine the remaining input elements into a single data string
                String data = String.join(" ", splitUserInput.subList(3, splitUserInput.size()));
        
                Key newKey = new Key(label, type);
                Record newRecord = new Record(newKey, data);

                try 
                {
                    // Add the new newRecord to the dictionary
                    dictionary.put(newRecord);
                } 
                catch (DictionaryException e) 
                {
                    // Handle any exception during insertion
                    System.out.println(e.getMessage());
                }
            }
        }
        
        else if (command.equals("list")) 
        {
            // Check if exactly 2 elements are provided in the input
            if (splitUserInput.size() != 2) 
            {
                System.out.println("Invalid command.");
            } 
            else 
            {
                String prefix = splitUserInput.get(1);
                ArrayList<String> matching = new ArrayList<>();
                Key prefixKey = new Key(prefix, 1); // Create a key to search for matching prefixes

                // Check if a newRecord with the exact prefix exists and add it to the list
                if (dictionary.get(prefixKey) != null) 
                {
                    matching.add(prefix);
                }

                // Find and add all successor keys that start with the same prefix
                Record successor = dictionary.successor(prefixKey);
                while (successor != null && successor.getKey().getLabel().startsWith(prefix)) 
                {
                    matching.add(successor.getKey().getLabel());
                    successor = dictionary.successor(successor.getKey());
                }

                // Output matching elements or a message if none are found
                if (matching.isEmpty()) 
                {
                    System.out.println("No label attributes in the ordered dictionary start with prefix " + prefix);
                } 
                else 
                {
                    for (int i = 0; i < matching.size(); i++) 
                    {
                        String word = matching.get(i);
                        if (i < matching.size() - 1) 
                        {
                            System.out.print(word + ", ");
                        } 
                        else 
                        {
                            System.out.println(word);
                        }
                    }
                }
            }
        }

        else if (command.equals("first")) 
        {
            // Check if the command input size is exactly 1, otherwise print "Invalid command"
            if (splitUserInput.size() != 1) {
                System.out.println("Invalid command.");
            } 
            else 
            {
                // Retrieve the smallest newRecord in the dictionary
                Record smallest = dictionary.smallest();
                if (smallest != null) 
                {
                    // If a newRecord exists, retrieve and print its label, type, and data
                    String label = smallest.getKey().getLabel();
                    int type = smallest.getKey().getType();
                    String data = smallest.getDataItem();
                    System.out.println(label + ',' + type + ',' + data + '.');
                }
            }
        } 
        else if (command.equals("last")) 
        {
            // Check if the command input size is exactly 1, otherwise print "Invalid command"
            if (splitUserInput.size() != 1) 
            {
                System.out.println("Invalid command.");
            } 
            else 
            {
                // Retrieve the largest newRecord in the dictionary
                Record largest = dictionary.largest();
                if (largest != null) 
                {
                    // If a newRecord exists, retrieve and print its label, type, and data
                    String label = largest.getKey().getLabel();
                    int type = largest.getKey().getType();
                    String data = largest.getDataItem();
                    System.out.println(label + ',' + type + ',' + data + '.');
                }
            }
        } 
        else if (command.equals("exit")) 
        {
            // Check if the command input size is exactly 1, otherwise print "Invalid command"
            if (splitUserInput.size() != 1) 
            {
                System.out.println("Invalid command.");
            } 
            else 
            {
                // Return true to indicate that the program should exit
                return true;
            }
        } 
        else 
        {
            // Handle any unrecognized commands by printing "Invalid command"
            System.out.println("Invalid command.");
        }
        return false;
}        

    public static void main(String[] args) throws IOException
    {
        BSTDictionary dictionary = new BSTDictionary();
        String filename = args[0];
        try 
        {
            File myObj = new File(filename);
            BufferedReader myReader = new BufferedReader(new FileReader(myObj));
            String label;
            
            while (myReader.ready()) 
            {

                label = myReader.readLine();  
                if (label == null) 
                {
                    break;
                }


                String nextLineData = myReader.readLine();
                if (nextLineData == null) 
                {  
                    break;
	            }

                int type = checkFistLetter(nextLineData);
                String data = nextLineData;

                if (type == 2 || type == 3 || type == 4 || type == 5)
                {
                    data = nextLineData.substring(1);
                }

                Key newKey = new Key(label.toLowerCase(), type);
                Record newRecord = new Record(newKey, data.toLowerCase());

                try
                {
                    dictionary.put(newRecord);
                } 
                catch (DictionaryException e) 
                {
                    System.out.println("Error: Cannot insert data into dictionary key "+ "(" +label.toLowerCase() + ", "+ type +")" +" already exists");
                }
            }
            myReader.close();
        } 
        catch (FileNotFoundException e) 
        {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
        
        while (true) 
        {
            StringReader keyboard = new StringReader();
            String line = keyboard.read("Enter next command: ");
            ArrayList<String> splitUserInput = splitUserInput(line.trim());
            String command = splitUserInput.get(0);

            boolean output = commands(dictionary, command, splitUserInput);
            if (output) break;
        }
    }



    //Checks the index 0 of each line to find out what if statement will be executed. 
    private static int checkFistLetter(String data)
    {
            if(data.charAt(0) == '/')
            {
                //French
                return 2;
            }
            else if(data.charAt(0) == '-')
            {
                //Sound 
                return 3;
            }
            else if(data.charAt(0) == '+')
            {
                //Music 
                return 4;
            }
            else if(data.charAt(0) == '*')
            {
                //Voice
                return 5;
            }

            else if (data.endsWith("jpg"))
            {
                //image
                return 6;
            }
            else if (data.endsWith("gif"))
            {
                //gif
                return 7;
            }
            else if (data.endsWith("html"))
            {
                //browse
                return 8;
            } 
            //define
            return 1;
    }
    
    /**
     * This helper function splitUserInputs an input string into individual words based on spaces.
     * It returns an ArrayList containing each token as a separate element.
     * 
     * @param input The input string to be splitUserInput
     * @return An ArrayList of strings containing each tokn separated with spaces in the input.
     */
    private static ArrayList<String> splitUserInput(String input) {
        // Create an ArrayList to store the splitUserInput tokens from the input string
        ArrayList<String> store = new ArrayList<>();
        // Use a StringTokenizer to splitUserInput the input string by spaces
        StringTokenizer tokenizer = new StringTokenizer(input, " ");
        
        // Iterate threw the tokens and add each to the ArrayList
        while (tokenizer.hasMoreTokens()) 
        {
            store.add(tokenizer.nextToken());
        }

        // Return the list of splitUserInput tokens
        return store;
    }

}