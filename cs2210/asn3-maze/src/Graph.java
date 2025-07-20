import java.util.*;

public class Graph implements GraphADT {

    private Map<GraphNode, List<GraphEdge>> adjacencyList; // Adjacency list
    private Map<Integer, GraphNode> nodes; // Map to store nodes by their names

    // Constructor: initializes the graph with n nodes and no edges
    public Graph(int n) {
        adjacencyList = new HashMap<>();
        nodes = new HashMap<>();
        for (int i = 0; i < n; i++) {
            GraphNode node = new GraphNode(i);
            adjacencyList.put(node, new ArrayList<>());
            nodes.put(i, node);
        }
    }

    // Inserts an edge connecting nodes u and v
	@Override
	public void insertEdge(GraphNode u, GraphNode v, int edgeType, String label) throws GraphException {
		if (!nodes.containsKey(u.getName()) || !nodes.containsKey(v.getName())) {
			throw new GraphException("One or both nodes do not exist.");
		}
	
		for (GraphEdge edge : adjacencyList.get(u)) {
			if (edge.secondEndpoint().equals(v)) {
				throw new GraphException("Edge already exists between these nodes.");
			}
		}
	
		GraphEdge edge = new GraphEdge(u, v, edgeType, label);
		adjacencyList.get(u).add(edge);
		adjacencyList.get(v).add(edge); // Add to both nodes' lists for undirected graph
	}
	

    // Returns the node with the specified name
    @Override
    public GraphNode getNode(int name) throws GraphException {
        if (!nodes.containsKey(name)) {
            throw new GraphException("Node does not exist.");
        }
        return nodes.get(name);
    }

    // Returns an iterator of all edges incident on the node u
    @Override
    public Iterator<GraphEdge> incidentEdges(GraphNode u) throws GraphException {
        if (!nodes.containsKey(u.getName())) {
            throw new GraphException("Node does not exist.");
        }

        List<GraphEdge> edges = adjacencyList.get(u);
        if (edges.isEmpty()) {
            return null; // No incident edges
        }
        return edges.iterator();
    }

    // Returns the edge connecting nodes u and v
    @Override
    public GraphEdge getEdge(GraphNode u, GraphNode v) throws GraphException {
        if (!nodes.containsKey(u.getName()) || !nodes.containsKey(v.getName())) {
            throw new GraphException("One or both nodes do not exist.");
        }

        // Search for the edge in u's adjacency list
        for (GraphEdge edge : adjacencyList.get(u)) {
            if (edge.secondEndpoint().equals(v)) {
                return edge;
            }
        }

        throw new GraphException("No edge exists between the given nodes.");
    }

    // Checks if nodes u and v are adjacent
	@Override
	public boolean areAdjacent(GraphNode u, GraphNode v) throws GraphException {
		if (!nodes.containsKey(u.getName()) || !nodes.containsKey(v.getName())) {
			throw new GraphException("One or both nodes do not exist.");
		}
	
		for (GraphEdge edge : adjacencyList.get(u)) {
			if (edge.secondEndpoint().equals(v) || edge.firstEndpoint().equals(v)) {
				return true;
			}
		}
	
		return false;
	}
	
}
