#pragma once

#include <string>

#include "API.h"

namespace tetris
{

  struct IBlockingEndPoint;
  struct ISolver;

  /**
  Class WebClient - executes game logic on the client side
  */
  class TETRIS_API WebClient
  {
  public:
    WebClient(IBlockingEndPoint &endpoint, ISolver &solver);
    ~WebClient();

    /// Runs endpoint's loop, decodes incoming messages and invokes solver
    void Run();

  private:
    // non-copyable
    WebClient(const WebClient &);
    WebClient &operator=(const WebClient &);

  private:
    class Impl;
    Impl *pimpl_;
  };

}