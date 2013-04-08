import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TetrisServlet extends HttpServlet {
    private TetrisSolver solver = new TetrisSolver();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String figure = req.getParameter("figure");
        int x = Integer.parseInt(req.getParameter("x"));
        int y = Integer.parseInt(req.getParameter("y"));
        String glass = req.getParameter("glass");
        String next = req.getParameter("next");
        System.out.println(String.format("Figure: %s, coordinates: (%d, %d), glass %s, next %s", figure, x, y, glass, next));
        resp.getWriter().write(solver.answer(figure, x, y, glass, next));
    }

    public static void main(String[] args) throws Exception {
        new JettyServletRunner().run();
    }
}
