import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

/**
 * User: serhiy.zelenin
 * Date: 10/2/12
 * Time: 5:27 PM
 */
public class JettyServletRunner {

    public void run() throws Exception {
        Server server = new Server(8888);
        ServletContextHandler context = new ServletContextHandler(server, "/");
        context.addServlet(new ServletHolder(new TetrisServlet()), "/*");
        server.setHandler(context);
        server.start();
    }
}
