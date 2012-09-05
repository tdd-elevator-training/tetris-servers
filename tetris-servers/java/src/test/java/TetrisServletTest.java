import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class TetrisServletTest {

    private final TetrisServlet servlet = new TetrisServlet();

    @Test
    public void should_accept_missing_input() {
        assertEquals("left=0, right=0, rotate=0", servlet.answer("I", 4, 18, ""));
    }

}
