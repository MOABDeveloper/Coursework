public class Monomial implements Comparable<Monomial> {
    private int coefficient;
    private int exponent;

    public Monomial(int coefficient, int exponent) { // Initializes the coefficient and exponent of the monomial.
        this.coefficient = coefficient;
        this.exponent = exponent;
    }
    public int getCoefficient() {                   // Getter method to retrieve the coefficient.
        return coefficient;
    }

    public int getExponent() {                      // Getter method to retrieve the exponent.
        return exponent;
    }

    public int compareTo(Monomial m) {
        return this.getExponent() - m.getExponent();
    }
}