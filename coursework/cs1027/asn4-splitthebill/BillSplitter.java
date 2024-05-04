import java.util.ArrayList;
import java.util.List;

public class BillSplitter {

    public static UniqueOrderedList<Integer> split(UniqueOrderedList<Integer> items, int target) {
        CopyableIterator<Integer> iterator = items.iterator();              //Store the list of the results
        List<Integer> result = yourSplit(iterator, target);                 //Call your split to find split
        if (result != null) {                                               //If have found a valid solution.
            UniqueOrderedList<Integer> soln = new UniqueOrderedList<>();    //Convert soln to UniqueOrderedList
            for (Integer item : result) {
                soln.add(item);
            }
            return soln;                                                    //Return solution.
        } else {
            return null;                                                    //No solution found return null.
        }
    }

    private static List<Integer> yourSplit(CopyableIterator<Integer> iterator, int target) {
        if (!iterator.hasNext()) {
            if (target == 0) {
                return new ArrayList<>();               //No items left, solution found
            } else {
                return null;                            //No valid solution found
            }
        }

        int currentItem = iterator.next();              // Include the current item in the payment
        List<Integer> withCurrent = yourSplit(iterator.copy(), target - currentItem);

        if (withCurrent != null) {
            withCurrent.add(currentItem);
            return withCurrent;
        }

        List<Integer> withoutCurrent = yourSplit(iterator, target);         //Remove curr and check
        if (withoutCurrent != null) {                                       //Solution without current
            return withoutCurrent;                                          //Return list with current
        } else {
            return null;                                                    // No valid solution found, return null.
        }
    }

}
