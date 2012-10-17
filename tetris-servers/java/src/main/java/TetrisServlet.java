import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.File;
import java.io.IOException;

public class TetrisServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String figure = req.getParameter("figure");
        int x = Integer.parseInt(req.getParameter("x"));
        int y = Integer.parseInt(req.getParameter("y"));
        String glass = req.getParameter("glass");
        System.out.println(String.format("Figure: %s, coordinates: (%d, %d), glass %s", figure, x, y, glass));
        resp.getWriter().write(answer(figure, x, y, glass));
    }

    String answer(String figure, int x, int y, String glass) {
        //add "drop" to response when you need to drop a figure
        return "left=0, right=0, rotate=0";
    }

    public static void main(String[] args) throws Exception {
        new JettyServletRunner().run();
    }
}
