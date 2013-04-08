import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class TetrisSolverTest {

    private final TetrisSolver solver = new TetrisSolver();

    @Test
    public void should_accept_missing_input() {
        assertEquals("left=0, right=0, rotate=0", solver.answer("I", 4, 18, "", "ITZO"));
    }

}
