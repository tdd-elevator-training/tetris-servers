#pragma once

#include <vector>

#include "API.h"

namespace tetris
{

  struct IBlockingEndPointCallback;

  /**
    Interface IBlockingEndPoint - client's endpoint of the connection to server
  */
  struct TETRIS_API IBlockingEndPoint
  {
    virtual ~IBlockingEndPoint() {}

    /// Runs endless message loop, passing incoming messages to the given callback
    virtual void Loop(IBlockingEndPointCallback &callback) = 0;

    /// Sends outgoing message to the server.
    /// This method is typically called from the callback in response to incoming messages
    virtual void Send(const std::vector<char> &message) = 0;
  };

  /**
    Interface IBlockingEndPointCallback - callback to pass to IBlockingEndPoint::Loop
  */
  struct TETRIS_API IBlockingEndPointCallback
  {
    virtual ~IBlockingEndPointCallback() {}

    /// Called by the endpoint implementation when incoming message is received
    virtual void OnReceive(const std::vector<char> &message, IBlockingEndPoint &endpoint) = 0;
  };

}