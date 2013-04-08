public class TetrisSolver {
    final static int DO_NOT_ROTATE = 0;
    final static int ROTATE_90_CLOCKWISE = 1;
    final static int ROTATE_180_CLOCKWISE = 2;
    final static int ROTATE_90_COUNTERCLOCKWISE = 3;

    public String answer(String figure, int x, int y, String glass, String next) {
        // add "drop" to response when you need to drop a figure
        // for details please check http://codenjoy.com/portal/?p=170#commands
        return "left=4, right=0, rotate=0, drop";
    }
}
