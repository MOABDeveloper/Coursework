public class Data {
    private String config;
    private int score;

    // Constructor to initialize Data objects
    public Data(String config, int score) {
        this.config = config;
        this.score = score;
    }

    // Getter method for configuration, returns the configuration stored in Data object.
    public String getConfiguration() {
        return config;
    }

    // Getter method for score, returns the score in this Data.
    public int getScore() {
        return score;
    }
}
