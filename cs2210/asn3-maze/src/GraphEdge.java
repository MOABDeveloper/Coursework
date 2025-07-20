
public class GraphEdge {
	private GraphNode origin;
	private GraphNode dest;
	private int type;
	private String label;
		
	// Constructor to initialize an edge with endpoints, type, and label
	public GraphEdge(GraphNode origin, GraphNode destination, int type, String label) {
		this.origin = origin;
		this.dest = destination;
		this.type = type;
		this.label = label;
	}

	// Returns the first endpoint of the edge
	public GraphNode firstEndpoint() {
		return this.origin;
	}

	// Returns the second endpoint of the edge
	public GraphNode secondEndpoint() {
		return this.dest;
	}

	// Returns the type of the edge
	public int getType() {
		return this.type;
	}

	// Sets the type of the edge
	public void setType(int type) {
		this.type = type;
	}

	// Returns the label of the edge
	public String getLabel() {
		return this.label;
	}

	// Sets the label of the edge
	public void setLabel(String label) {
		this.label = label;
	}
	}
