
public class MineEscape {
    private Map map;
    //Counter for how much gold we have picked up along the way.
    public int numGold;
    //Array Storing number of keys.
    private int[] numkeys;

    public MineEscape(String filename)  {       //Initialize variables.
        try {
            this.map = new Map(filename);
            numGold = 0;
            numkeys = new int[3];               //Follows RGB so numKeys[0] = red,numKeys[1] = green, numKeys[2] = blue.

        } catch (Exception e) {                 //Print exception thrown.
            System.out.println(e.getMessage());
        }
    }

    private MapCell findNextCell(MapCell cell) { //For loop for each to check all sides in priority.

        for (int i = 0; i < 4; i++) {
            MapCell neighbor = cell.getNeighbour(i);
            if (neighbor != null && !neighbor.isMarked()) {         //Make sure neighbour is not null or marked.
                if (neighbor.isExit()) {                            //Check if it's an exit.
                    return neighbor;
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            MapCell neighbor = cell.getNeighbour(i);
            if (neighbor != null && !neighbor.isMarked()) {             //Make sure neighbour is not null or marked.
                // Check for key cells
                if (neighbor.isKeyCell() || neighbor.isGoldCell()) {    //Check if it is a key or gold.
                    if (neighbor.isBlue()) {                            //Check color of they key
                        numkeys[2] = numkeys[2] + 1;                    //Add key to corresponding cell in array.
                    }
                    if (neighbor.isGreen()) {
                        numkeys[1] = numkeys[1] + 1;
                    }
                    if (neighbor.isRed()) {
                        numkeys[0] = numkeys[0] + 1;
                    }
                    return neighbor;
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            MapCell neighbor = cell.getNeighbour(i);
            if (neighbor != null && !neighbor.isMarked()) {             //Make sure neighbour is not null or marked.
                if (neighbor.isLockCell()) {                            //Check if it is a lock cell.
                    //Check if we have enough keys to open it and return the first one we have enough for.
                    if ((neighbor.isBlue() && numkeys[2] >= 1) || (neighbor.isRed() && numkeys[0] >= 1) || (neighbor.isGreen() && numkeys[1] >= 1)) {
                        return neighbor;
                    }
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            MapCell neighbor = cell.getNeighbour(i);

            if (neighbor != null && !neighbor.isMarked()) {             //Make sure neighbour is not null or marked.
                if (neighbor.isFloor()) {                               //If it's a floor cell return it
                    cell = neighbor;
                    return cell;
                }
            }
        }
        return null;                                //If non of these is possible than we are stuck and must backtrack.
    }


    public String findEscapePath(){
        ArrayStack<MapCell> s = new ArrayStack<>();     //Stores the Mapcell objects.
        s.push(map.getStart());                         //Add starting position to Stack
        boolean running = true;                         //Program is running
        map.getStart().markInStack();                   //Mark the start of the map as part of path

        //Path string that we store the way out of the map, to be retuned at the end.
        StringBuilder escapeRoute = new StringBuilder("Path: " + map.getStart().getID() + " ");

        while (!s.isEmpty() && running){                //When the program is running and the stack isn't empty.
            MapCell curr = s.peek();
            
            if (curr.isExit()){                                      //Stop the program when on the exit cell.
                running = false;
                break;
            }

            if(curr.isGoldCell()){                                   //If the current cell is a gold cell
                numGold++;                                           //Increase our gold count
                curr.changeToFloor();                                //Change the  cell from gold to floor
            }

            if(curr.isKeyCell()){                                   //Change the key cell to a floor cell after pick up
                curr.changeToFloor();
            }

            for(int i = 0; i <= 3; i++){                              //Checking adjecent cells for lava.
                if(curr.getNeighbour(i) != null) {                    //Make sure neighbour isn't null
                    if (curr.getNeighbour(i).isLava()) {              //If Neighbour is lava, gold is deleted
                        numGold = 0;
                    }
                }
            }

            MapCell next = findNextCell(curr);                       //Find the next cell to go to from current position

            if(next == null){                                        //If findNextCell returns null
                curr = s.pop();                                      //Backtrack and mark outOfStack
                curr.markOutStack();                                 //Repeats until another option is found
            }

            else{                                                     //If it doesn't return null
                escapeRoute.append(next.getID() + " ");                     //Add cell ID to escapePath
                s.push(next);                                         //Add to path arraystack
                next.markInStack();                                   //Mark it as in the Stack (path)
                if (next.isLockCell()){                               //If the cell is a lockCell
                    if(next.isRed() && numkeys[0] >= 1){        //Check each for which color and if we have a key for it
                        next.changeToFloor();                   //If we have the key change the lockCell to a floor
                        numkeys[0] = numkeys[0] -1 ;}           //Reduce the number of corresponding keys by one.
                    if(next.isGreen() && numkeys[1] >= 1){
                        next.changeToFloor();
                        numkeys[1] = numkeys[1] -1 ;}
                    if(next.isBlue() && numkeys[2] >= 1){
                        next.changeToFloor();
                        numkeys[2] = numkeys[2] - 1;}
                }
            }

        }
        if (!running){                                          //When the program stops running
            escapeRoute.append(numGold + "G");                  //Add amount of gold to end of escapeRoute string
            return escapeRoute.toString();
        }
        else {                                                  //If there is not an option for nextCell than NoSolution
            return "No solution found";
        }
    }

    public static void main (String[] args) throws Exception {
        if (args.length != 1) {
            System.out.print("Map file not given in the arguments.");
        }
        else {
            MineEscape search = new MineEscape(args[0]);
            String result = search.findEscapePath();
            System.out.println(result);
        }
    }
}


