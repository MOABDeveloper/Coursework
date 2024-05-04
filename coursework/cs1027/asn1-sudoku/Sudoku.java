public class Sudoku {
    private int size;
    private int[][] grid;

    public Sudoku(int[][] numbers) {
        this.grid = numbers;                                    // Initalized the grid with numbers.
        size = grid.length;                                     // Find the size of the grid using the length.
    }

    public int getSize() {                                      // Returns the size variable (getter).
        return size;
    }

    public int[][] getGrid() {                                  // Returns the grid variable (getter).
        return grid;
    }

    public int getDigitAt(int row, int col) {
        if (row < 0 || col < 0 && row >= size || col >= size) {  //Checks if either the row or col are out of range.
            return -1;
        }
        return grid[row][col];                                  // Returns the digit if the row and col are in range.
    }

    public boolean isValidRow(int row) {
        boolean[] dupStorRow = new boolean[size];               // Makes array to keep track of the int when going through the puzzle
        for (int i = 0; i < size; i++) {                        // For loop going through each slot in the row.
            int digitAt = grid[row][i];                         // Gets the digit at current location and places it in digitAt.
            if ((digitAt < 1) || (digitAt > size) || dupStorRow[digitAt - 1]) {
                return false;
            }
            dupStorRow[digitAt - 1] = true;                     //Marks as seen.
        }
        return true;
    }

    public boolean isValidCol(int col) {
        boolean[] dupStorCol = new boolean[size];               // Makes array to keep track of the int when going through the puzzle
        for (int i = 0; i < size; i++) {                        // For loop going through each slot in the column.
            int digitAt = grid[i][col];                         // Gets the digit at current location and places it in digitAt.
            if ((digitAt < 1) || (digitAt > size) || dupStorCol[digitAt - 1]) {
                return false;
            }
            dupStorCol[digitAt - 1] = true;                     //Marks as seen.
        }
        return true;
    }

    public boolean isValidBox(int row, int col) {
        if (row < 0 || col < 0 || row >= size - 2 || col >= size - 2) {    // Checks if the row and col are within range on both sides
            return false;
        }
        boolean[] dupStorGrd = new boolean[size];
        for (int i = row; i <= row + 2; i++) {
            for (int j = col; j <= col + 2; j++) {
                int digitAt = grid[i][j];
                if (digitAt < 1 || digitAt > size || dupStorGrd[digitAt-1]) {  //Checks if digit is within range or seen
                    return false;
                }
                dupStorGrd[digitAt - 1] = true;              //Marks as seen.
            }
        }
        return true;
    }

    public boolean isValidSolution() {                       //Validates if the whole Sudoku is correct.
        for (int i = 0; i < size; i++) {                     //Checking for all values of i less than the total size.
            if (!(isValidCol(i) && isValidRow(i))) {         //Checks for any instances where they are not true
                return false;
            }
        }
        if (size == 9) {                                    //Checks 3x3 if the size is 9.
            for (int i = 0; i < size; i += 3) {
                for (int j = 0; j < size; j += 3) {
                    if (!(isValidBox(i, j))) {
                        return false;
                    }
                }
            }
        }
        return true;                                        //The Sudoku is completely Valid.
    }

    public boolean equals(Sudoku other) {
        if (this.size != other.size) {                      //Checks if the sizes are not equal.
            return false;
        }
        int[][] otherGrid = other.getGrid();
        for (int i = 0; i < size; i++) {                    //Compares all the gird slots in both grids.
            for (int j = 0; j < size; j++) {
                if (this.grid[i][j] != otherGrid[i][j]) {
                    return false;
                }
            }
        }
        return true;                                        //The two Sudokus are the same.
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                sb.append(grid[i][j]);                      //Add i and j to string
                sb.append(' ');                             //Add space after each digit
            }
            sb.append('\n');                                //Add new Line.
        }
        return sb.toString();
    }
}