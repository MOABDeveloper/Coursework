public class Polynomial {
    private OrderedLinkedList<Monomial> terms;

    public Polynomial() {                                          //Creates an empty polynomial.
        terms = new OrderedLinkedList<>();
    }

    public void add(int coefficient, int degree) {                  //Takes two inputs to create monomial.
        if (coefficient != 0) {
            Monomial monomial = new Monomial(coefficient, degree);
            terms.insert(monomial);                                 //Adds monomial to the empty polynomial.
        }
    }

    public Polynomial derivative() {                                //Finds the derivative of the polynomial.
        Polynomial derivative = new Polynomial();
        for (int i = 0; i < terms.getSize(); i++) {                 //Gets terms (degree and coef) for each monomial.
            Monomial crntMono = terms.get(i);
            int crntCoef = crntMono.getCoefficient();
            int crntDegr = crntMono.getExponent();

            if (crntDegr >= 0) {                                    //Does the math for finding derivative.
                int newCoef = crntCoef * crntDegr;
                int newDegr = crntDegr - 1;
                derivative.add(newCoef, newDegr);
            }
        }
        return derivative;
    }

    public double eval(double z) {                                  //Calculates the value of a polynomial at F(Z).
        double result = 0.0;
        for (int i = 0; i < terms.getSize(); i++) {
            Monomial crntMono = terms.get(i);
            double coefficient = crntMono.getCoefficient();
            int degree = crntMono.getExponent();
            result += coefficient * Math.pow(z, degree);          //Coefficient * input z raised to the corresponding degree
        }
        return result;
    }

    @Override
    public String toString() {
        if (terms.getSize() == 0) {                     //Returns empty string if polynomial is empty.
            return "";
        }
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < terms.getSize(); i++) {
            Monomial currentMonomial = terms.get(i);
            int coefficient = currentMonomial.getCoefficient();
            int degree = currentMonomial.getExponent();

            if (i == 0) {                               // Keeps the negative sign if the first coefficient is negative.
                if (coefficient < 0) {
                    sb.append(coefficient);
                } else {
                    sb.append(coefficient);
                }
            } else {                                    // For all other monomials
                if (coefficient < 0) {
                    sb.append(" - ").append(-coefficient);      // Add "-" operator between each monomial if coef is -ve.
                } else {
                    sb.append(" + ").append(coefficient);       // Add "+" operator between each monomial if coef is +ve.
                }
            }
            sb.append("*x^").append(degree);            //Adds the degree and x^ to the coefficient
        }

        return sb.toString();
    }


    public double solve(double x0, double e, int T) throws SolutionNotFound {
        double previous = x0;                                   //Initial guess

        if (derivative().eval(previous) != 0) {                 // Check if the derivative at the initial estimate is not zero.
            double current;                                     //Stores the value of x0+1 after its calculated.
            current = previous - eval(previous) / derivative().eval(previous);  //Newtons method at x0+1.
            int iterations = 0;                                 //Store current iterations.

            while (iterations < T && Math.abs(current - previous) > e) {    //When Difference is greater than tolerance and Max iterations not reached.
                previous = current;
                if (derivative().eval(previous) != 0) {                     //When the derivative x1+ is not zero.
                    current = previous - eval(previous) / derivative().eval(previous);  //Find derivative at next x value.
                } else {
                    throw new SolutionNotFound("divide by zero error");     //If it is zero throw error.
                }

                iterations++;                                   //Increase iterations by 1 each loop.
            }

            if (iterations >= T) {                              //If max number of iterations is reached we throw error.
                throw new SolutionNotFound("maximum iteration exceeded");
            } else {                               //Returns answer for when we have reached max iterations and tolerance is within range
                return current;
            }
        } else {                                   //Throws error for when derivative is zero.
            throw new SolutionNotFound("divide by zero error");
        }
    }

}