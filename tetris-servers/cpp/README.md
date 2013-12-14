C++ client for Codenjoy Tetris

1. Install Visual Studio 2012 (express+)

2. Download and build third party libraries:
	boost - http://www.boost.org
	gmock - https://code.google.com/p/googlemock
	websocketpp - https://github.com/zaphoyd/websocketpp

3. Set environment variables (or directly modify in .props files):
	LIB_BOOST=path to boost
	LIB_GMOCK=path to gmock
	LIB_WEBSOCKETPP=path to websocketpp

3. Update server settings at TetrisApp/main.cpp

4. Implement game logic in MySolver/MySolver.cpp while adding tests in MySolverTest/

5. Run TetrisApp