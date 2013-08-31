import org.eclipse.jetty.websocket.WebSocket;
import org.eclipse.jetty.websocket.WebSocketClient;
import org.eclipse.jetty.websocket.WebSocketClientFactory;

import java.io.IOException;
import java.net.URI;
import java.util.concurrent.TimeUnit;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * User: serhiy.zelenin
 * Date: 4/8/13
 * Time: 11:42 PM
 */
public class WebSocketTetrisClient {

    private static final String SERVER = "ws://tetrisj.jvmhost.net:12270/tetris-contest/ws";
//    private static final String SERVER = "ws://localhost:8080/tetris-contest/ws";

    private static String userName = "Sergey";

    private static Pattern urlPattern = Pattern.compile("^figure=(\\w+)&x=(\\d+)&y=(\\d+)&glass=(.*)&next=(\\w*)$");
    private static WebSocketTetrisClient client;

    private WebSocket.Connection connection;
    private TetrisSolver solver;
    private WebSocketClientFactory factory;

    public WebSocketTetrisClient(TetrisSolver solver) {
        this.solver = solver;
    }

    public static void main(String[] args) throws Exception {
        client = new WebSocketTetrisClient(new TetrisSolver());
        client.start();
        Runtime.getRuntime().addShutdownHook(new Thread(){
            @Override
            public void run() {
                try {
                    client.stop();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    private void stop() throws Exception {
        connection.close();
        factory.stop();
    }

    private void start() throws Exception {
        factory = new WebSocketClientFactory();
        factory.start();

        WebSocketClient client = factory.newWebSocketClient();
        connection = client.open(new URI(SERVER + "?user=" + userName), new WebSocket.OnTextMessage() {
            public void onOpen(Connection connection) {
                System.out.println("Opened");
            }

            public void onClose(int closeCode, String message) {
                System.out.println("Closed");
            }

            public void onMessage(String data) {
                System.out.println("data = " + data);
                Matcher matcher = urlPattern.matcher(data);
                if ( !matcher.matches()) {
                    throw new RuntimeException("WTF? " + data);
                }
                String answer = solver.answer(matcher.group(1), Integer.parseInt(matcher.group(2)), Integer.parseInt(matcher.group(3)), matcher.group(4), matcher.group(5));
                try {
                    connection.sendMessage(answer);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).get(5000, TimeUnit.MILLISECONDS);
    }
}
