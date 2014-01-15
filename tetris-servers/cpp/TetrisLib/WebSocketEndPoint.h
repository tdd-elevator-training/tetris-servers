#pragma once

#include "API.h"
#include "IBlockingEndPoint.h"

namespace tetris
{

  /**
    Class WebSocketEndPoint - implementation of IBlockingEndPoint with web sockets as transport layer
  */
  class TETRIS_API WebSocketEndPoint
    : public IBlockingEndPoint
  {
  public:
    /// Constructor
    /// @param url - URL to the server
    /// @param user_name - name of registered user
    WebSocketEndPoint(const std::string &url, const std::string &user_name);

    ~WebSocketEndPoint();

    /// @see IBlockingEndPoint::Loop
    virtual void Loop(IBlockingEndPointCallback &callback) override;

    /// @see IBlockingEndPoint::Send
    virtual void Send(const std::vector<char> &bytes) override;

  private:
    // non-copyable
    WebSocketEndPoint(const WebSocketEndPoint &);
    WebSocketEndPoint &operator=(const WebSocketEndPoint &);

  private:
    class Impl;
    Impl *pimpl_;
  };

}