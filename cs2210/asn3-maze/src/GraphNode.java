
public class GraphNode {

//	I need 2 variables, name and mark
private int name;
private boolean mark;
	
	public GraphNode(int name) {
		this.name = name;
		this.mark = false;
	}

	
//	setters and getters
	public void mark(boolean mark) {
        this.mark = mark;
	}
	
	public boolean isMarked() {
		return mark;
	}
	
	public int getName() {
		return name;
	}
	
}
