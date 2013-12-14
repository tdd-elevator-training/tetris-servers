#pragma warning(push)
#pragma warning(disable: 4996)  // unsafe localtime()

#include <algorithm>
using std::min;

#include <boost/optional.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include "../MessageEncoding.h"
#include "../WebSocketEndPoint.h"

using namespace tetris;

class WebSocketEndPoint::Impl
{
private:
  typedef websocketpp::client<websocketpp::config::asio_client> client_t;
  typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

public:
  Impl(const std::string &url, const std::string &user_name, IBlockingEndPoint &endpoint)
    : connection_string_(url + "?user=" + user_name)
    , endpoint_(endpoint)
  {
    client_.clear_access_channels(websocketpp::log::alevel::all);
    client_.clear_error_channels(websocketpp::log::elevel::all);
    client_.init_asio();
    client_.set_message_handler(boost::bind(&Impl::OnMessage, this, &client_, ::_1, ::_2));
  }

  void Loop(IBlockingEndPointCallback &callback)
  {
    websocketpp::lib::error_code err;
    client_t::connection_ptr con = client_.get_connection(connection_string_, err);
    if (!con)
      return;

    if (!client_.connect(con))
      return;

    callback_.reset(callback);
    client_.run();
    callback_.reset();
  }

  void Send(const std::vector<char> &bytes)
  {
    if (!connection_handle_)
      throw std::logic_error("uninitialized pconnection_handle_");

    client_.send(*connection_handle_, &bytes[0], bytes.size(), websocketpp::frame::opcode::text);
  }

private:
  void OnMessage(client_t *pclient, websocketpp::connection_hdl hdl, message_ptr pmsg)
  {
    if (!callback_)
      throw std::logic_error("uninitialized pcallback_");

    connection_handle_.reset(hdl);
    callback_->OnReceive(StringToBytes(pmsg->get_payload()), endpoint_);
    connection_handle_.reset();
  }

private:
  client_t client_;
  std::string connection_string_;
  IBlockingEndPoint &endpoint_;
  boost::optional<IBlockingEndPointCallback &> callback_;
  boost::optional<websocketpp::connection_hdl> connection_handle_;
};

WebSocketEndPoint::WebSocketEndPoint(const std::string &url, const std::string &user_name)
{
  if (url.empty())
    throw std::invalid_argument("URL can't be empty");
  if (url.find("ws://") != 0)
    throw std::invalid_argument("wrong protocol specified");
  if (user_name.empty())
    throw std::invalid_argument("user name can't be empty");

  pimpl_ = new Impl(url, user_name, *this);
}

WebSocketEndPoint::~WebSocketEndPoint()
{
  delete pimpl_;
}

void tetris::WebSocketEndPoint::Send(const std::vector<char> &bytes)
{
  pimpl_->Send(bytes);
}

void tetris::WebSocketEndPoint::Loop(IBlockingEndPointCallback &callback)
{
 pimpl_->Loop(callback);
}

#pragma warning(pop)