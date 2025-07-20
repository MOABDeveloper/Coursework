public class Configurations {
    private char[][] board;     //2D array to show board 
    private int size;           //Size of board 
    private int lengthToWin;    //k needed to win
    private int maxLevels;      //Maxium levels of game tree

    //Constrructor that intialized the game board and the game settings
    public Configurations(int boardSize, int lengthToWin, int maxLevels) {
        //Initalize the variables 
        this.size = boardSize;
        this.lengthToWin = lengthToWin;
        this.maxLevels = maxLevels;
        board = new char[size][size];
        //Make all positions as empty
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j] = ' ';
            }
        }
    }

    //Create hash dictionary of size 
    public HashDictionary createDictionary() {
        return new HashDictionary(6001);  // A prime number size
    }

    //Checks if current configuation of the board is in the table
    public int repeatedConfiguration(HashDictionary hashTable) {
        String config = boardToString();
        //Returns score if found int the table
        return hashTable.get(config);
    }

    //Add current config and score to the table 
    public void addConfiguration(HashDictionary hashTable, int score) {
        String config = boardToString();
        try {
            hashTable.put(new Data(config, score));
        } catch (DictionaryException e) {
            System.out.println(e.getMessage());
        }
    }

    //Places the X or O on the game board at specified loaction 
    public void savePlay(int row, int col, char symbol) {
        board[row][col] = symbol;
    }

    //Checks the selected square is empty. 
    public boolean squareIsEmpty(int row, int col) {
        return board[row][col] == ' ';
    }

    // Check all possible diagonals for a win  
    private boolean checkAllDiagonals(char symbol) {
        // Check all down-right diagonals (from top row and left column)
        for (int i = 0; i < size; i++) {
            if (checkLine(symbol, i, 0, 1, 1) ||  // Diagonals stating from left col
                checkLine(symbol, 0, i, 1, 1)) {  // Diagonals starting from top row
                return true;                                            // Win detected
            }
        }
    
        // Check all down-left diagonals (from top row and right column)
        for (int i = 0; i < size; i++) {
            if (checkLine(symbol, i, size - 1, 1, -1) ||    // Diagonals stating from right col
                checkLine(symbol, 0, i, 1, -1)) {       // Diagonals starting from top row
                return true;                                         // Win detected
            }
        }
        return false;   //Win not found on the diags
    }

    // Checks if the given symbol (X or O) has formed a winning line
    public boolean wins(char symbol) {
        // Check all rows and columns for a win
        for (int i = 0; i < size; i++) {
            if (checkLine(symbol, i, 0, 0, 1) ||  // Check row i
                checkLine(symbol, 0, i, 1, 0)) {  // Check column i
                return true;
            }
        }
    
        // Check all possible diagonals
        return checkAllDiagonals(symbol);
    }

    // Helper method to check a line (row, column, or diagonal) for a win
    private boolean checkLine(char symbol, int row, int col, int deltaRow, int deltaCol) {
        int count = 0;// Count of consecutive symbol     
        while (row >= 0 && row < size && col >= 0 && col < size) {
            if (board[row][col] == symbol) {
                //If symbol matches we increment count 
                count++;
                if (count >= lengthToWin) {
                    //Win foiund
                    return true;
                }
            } else {
                // Reset count if does not match
                count = 0;
            }
            row += deltaRow;
            col += deltaCol;
        }
        // No win detected in this line
        return false;
    }

    //Checks game ends in draw
    public boolean isDraw() {
        //Iterate and check over empty spaces
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                //The board is not empty, not draw 
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        //Game ended in a draw
        return true;
    }

    //Checks the game board and will return the corresponding score
    public int evalBoard() {
        if (wins('O')) return 3;  // Computer wins
        if (wins('X')) return 0;  // Human wins
        if (isDraw()) return 2;         // Draw
        return 1;                       // Undecided
    }

    //Convert board into a string 
    private String boardToString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                sb.append(board[i][j]);
            }
        }
        return sb.toString();
    }
}

