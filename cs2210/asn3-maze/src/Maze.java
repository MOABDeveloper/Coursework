import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.HashMap;


public class Maze {
    private Graph mazeGraph;                            // stores the maze as a graph
    private HashMap<GraphNode, String> visitedNodes;    // keeps track of nodes alredy visited
    private HashMap<GraphEdge, String> edgeprocesseds;  // stores if edge is 'discovery' or 'back'
    private int entranceNode;                           // the entranc node of the maze
    private int exitNode;                               // exit of the maze
    private int availableCoins;                         // how many coins are available for doors

    public Maze(String inputPath) throws MazeException {
        try {
            BufferedReader reader = new BufferedReader(new FileReader(inputPath));
            readInput(reader);                          // reads the file and parses the maze data
            reader.close();                             // closes the file after reading
            visitedNodes = new HashMap<>();             // initialize map for visited nodes
            edgeprocesseds = new HashMap<>();           // init edge state map
        } catch (Exception e) {
            throw new MazeException("Unable to initialize maze: " + e.getMessage());
        }
    }

    //Check if the graph was made and return an error if it hasn't
    public Graph getGraph() throws MazeException{
        if (mazeGraph != null){
			return mazeGraph;
		}
		return null;
    }

    //Check if there is a solution, if not eturn null
    public Iterator<GraphNode> solve() {
        try {
            return DFS(availableCoins, mazeGraph.getNode(entranceNode));
        } catch (GraphException e) {
            return null;
        }
    }

    private Iterator<GraphNode> DFS(int remainingCoins, GraphNode currentNode) throws GraphException {
        visitedNodes.put(currentNode, "visited"); // marks current node as visited
        List<GraphNode> path = new ArrayList<>(); // list to store path to the exit

        if (currentNode.getName() == exitNode) { // if current node is exit node
            path.add(currentNode); // add the exit node to path
            return path.iterator(); // return the solution path
        }

        Iterator<GraphEdge> edges = mazeGraph.incidentEdges(currentNode); // get all edges connected to the node
        while (edges.hasNext()) { // go through each edge
            GraphEdge edge = edges.next(); // take the next edge
            if (!edgeprocesseds.containsKey(edge) || !edgeprocesseds.get(edge).equals("discovery") && !edgeprocesseds.get(edge).equals("back")) {
                GraphNode adjacentNode;
                if (currentNode == edge.firstEndpoint()) { // get the other endpoint
                    adjacentNode = edge.secondEndpoint();
                } else {
                    adjacentNode = edge.firstEndpoint();
                }

                if (!visitedNodes.containsKey(adjacentNode) || !visitedNodes.get(adjacentNode).equals("visited")) {
                    int coinsLeft = remainingCoins; // coins left for traversal
                    if (edge.getLabel().equals("door")) {
                        coinsLeft -= edge.getType(); // decrease coins if door
                    }
                    edgeprocesseds.put(edge, "discovery"); // mark edge as discovered

                    if (coinsLeft >= 0) { // check if enough coins are left
                        Iterator<GraphNode> subPath = DFS(coinsLeft, adjacentNode); // recursive DFS call
                        if (subPath != null) { // if path is found
                            path.add(currentNode); // add current node to path
                            while (subPath.hasNext()) { // add all nodes from subpath
                                path.add(subPath.next());
                            }
                            visitedNodes.put(currentNode, ""); // reset current node's visited status
                            return path.iterator(); // return the full path
                        }
                    }
                } else {
                    edgeprocesseds.put(edge, "backtrack"); // backtrack edge if already visited
                }
            }
        }

        visitedNodes.put(currentNode, ""); // unmark node when backtracking
        return null; // no path found, return null
    }


    private void readInput(BufferedReader reader) throws IOException, GraphException {
        int width = 0, height = 0; // stores the maze dimensions
        String line = reader.readLine();
        int lineCount = 0, nodeIndex = 0, charIndex = 0, gridLineCounter = 0;

        while (line != null) { // read each line of input
            try {
                if (lineCount == 4) {
                    mazeGraph = new Graph(width * height); // initialize the graph
                }

                if (lineCount == 1) {
                    width = Integer.parseInt(line); // get maze width
                } else if (lineCount == 2) {
                    height = Integer.parseInt(line); // get maze height
                } else if (lineCount == 3) {
                    availableCoins = Integer.parseInt(line); // read coins budget
                } else if (lineCount > 3) { // lines describing rooms and connections
                    charIndex = 0;
                    for (int i = 0; i < line.length(); i++) {
                        char currentChar = line.charAt(i); // read each character
                        if (currentChar == 's') {
                            entranceNode = nodeIndex; // set entrance node
                            nodeIndex++;
                        } else if (currentChar == 'x') {
                            exitNode = nodeIndex; // set exit node
                            nodeIndex++;
                        } else if (currentChar == 'o') {
                            nodeIndex++; // regular room
                        } else if (Character.isDigit(currentChar) || currentChar == 'c') {
                            int start = -1, end = -1; // calculate start and end nodes
                            if (lineCount % 2 == 0) {
                                start = (charIndex - 1) / 2 + gridLineCounter * width;
                                end = (charIndex + 1) / 2 + gridLineCounter * width;
                            } else {
                                start = charIndex / 2 + (gridLineCounter - 1) * width;
                                end = charIndex / 2 + gridLineCounter * width;
                            }

                            if (currentChar == 'c') {
                                insertEdge(start, end, 0, "corridor"); // insert corridor edge
                            } else {
                                insertEdge(start, end, Character.getNumericValue(currentChar), "door"); // insert door edge
                            }
                        }
                        charIndex++;
                    }
                    if (lineCount % 2 == 0) gridLineCounter++; // update grid counter
                }

                line = reader.readLine(); // read next line
                lineCount++;
            } catch (NumberFormatException e) {
                throw new IOException("Invalid input format"); // error if input invalid
            }
        }
    }

    private void insertEdge(int node1, int node2, int cost, String processed) throws GraphException {
		GraphNode nodeu = mazeGraph.getNode(node1);
		GraphNode nodev = mazeGraph.getNode(node2);
        mazeGraph.insertEdge(nodeu, nodev, cost, processed);
    }
}
