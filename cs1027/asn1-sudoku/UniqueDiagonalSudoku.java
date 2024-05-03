public class UniqueDiagonalSudoku extends Sudoku {

    public UniqueDiagonalSudoku(int[][] numbers) {
        super(numbers);
    }
    @Override
    public boolean isValidSolution() {
        if (!super.isValidSolution()) {                         // Check if base rules of Sudoku are met.
            return false;
        }
        boolean[] diaStorTB = new boolean[getSize()];           //Store the digits we have seen
        boolean[] diaStorBT = new boolean[getSize()];
        boolean isTBValid = true;                               //Keeps track of if the diagonals are valid or not
        boolean isBTValid = true;
        boolean areDiagValid = true;                            //Stores the end result of the diagonals


        for (int i = 0; i < getSize(); i++) {                   // Check Diagonal from top-left to bottom-right
             int digitAt = getGrid()[i][i];
             if ((digitAt < 1) || (digitAt > getSize()) || diaStorTB[digitAt - 1]) {
               isTBValid = false;
               break;
                }
             diaStorTB[digitAt - 1] = true;                     //Mark the digit as seen.
            }

        for (int i = 0; i < getSize(); i++) {                   // Check Diagonal from bottom-left to top-right
             int digitAt = getGrid()[getSize() - 1 - i][i];
             if ((digitAt < 1) || (digitAt > getSize()) || diaStorBT[digitAt - 1]) {
                 isBTValid = false;
                 break;
                }
             diaStorBT[digitAt - 1] = true;                     //Mark the digit as seen.
            }

        if (isTBValid == false && isBTValid == false) {         //Checks if both diagonals are invalid.
            areDiagValid = false;
        }

        return areDiagValid;
    }
}
