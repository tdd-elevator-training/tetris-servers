#include <iostream>

#include <TetrisLib/WebClient.h>
#include <TetrisLib/WebSocketEndPoint.h>

#include <MySolver/MySolver.h>

int main()
{
  const std::string server_url = "ws://tetrisj.jvmhost.net:12270/tetris-contest/ws";
  const std::string user_name = "qwe";  // TODO: insert your name here

  try
  {
    tetris::WebSocketEndPoint endpoint(server_url, user_name);
    MySolver solver;
    tetris::WebClient client(endpoint, solver);
    client.Run();
    return 0;
  }
  catch (const std::exception &e)
  {
    std::cerr << "ERROR: " << e.what() << std::endl;
    return 1;
  }
}