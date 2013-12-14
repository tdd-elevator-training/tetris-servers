#include <functional>

#include <boost/bind.hpp>
#include <gmock/gmock.h>

#include <TetrisLib/IBlockingEndPoint.h>
#include <TetrisLib/IPieceController.h>
#include <TetrisLib/ISolver.h>
#include <TetrisLib/IField.h>
#include <TetrisLib/MessageEncoding.h>
#include <TetrisLib/Problem.h>
#include <TetrisLib/WebClient.h>

using namespace tetris;
using testing::Invoke;
using testing::Return;
using testing::_;

class FakeBlockingEndPoint
  : public IBlockingEndPoint
{
public:
  MOCK_METHOD1(Loop, void (IBlockingEndPointCallback &callback));
  MOCK_METHOD1(Send, void (const std::vector<char> &message));
};

class FakeSolver
  : public ISolver
{
public:
  MOCK_METHOD2(Solve, void(IPieceController &controller, const Problem &problem));
};

class StubSolver
  : public ISolver
{
public:
  explicit StubSolver(std::function<void (IPieceController &)> delegate)
    : delegate_(delegate)
  {
  }

  virtual void Solve(IPieceController &controller, const Problem& problem) override
  {
    delegate_(controller);
  }

private:
  std::function<void (IPieceController &)> delegate_;
};

std::vector<char> GetTestMessage()
{
  const std::string message = "figure=O&x=4&y=12&glass=    **        **        **        **                                                                                                                                                                    &next=OOOO";
  return StringToBytes(message);
}

class ReceiveOneMessage
{
public:
  ReceiveOneMessage(const std::vector<char> &message, IBlockingEndPoint &endpoint)
    : endpoint_(endpoint)
    , message_(message)
  {
  }

  void Loop(IBlockingEndPointCallback &callback)
  {
    callback.OnReceive(message_, endpoint_);
  }

private:
  std::vector<char> message_;
  IBlockingEndPoint &endpoint_;
};

class WebClientTest: public testing::Test
{
public:
  WebClientTest()
    : receiver(GetTestMessage(), mock_endpoint)
  {
    ON_CALL(mock_endpoint, Loop(_)).WillByDefault(Invoke(boost::bind(&ReceiveOneMessage::Loop, &receiver, _1)));
  }

  FakeBlockingEndPoint mock_endpoint;
  ReceiveOneMessage receiver;
};

TEST_F(WebClientTest, RunShouldSendLeftWhenSolverSaysLeft)
{
  StubSolver stub_solver(
    [](IPieceController &controller) 
    {
      controller.Left();
    });
  EXPECT_CALL(mock_endpoint, Send(StringToBytes("left=1")));

  WebClient client(mock_endpoint, stub_solver);
  client.Run();
}

TEST_F(WebClientTest, RunShouldSendMultipleCommandsWhenSolverSaysSo)
{
  StubSolver stub_solver(
    [](IPieceController &controller) 
    {
      controller.Right();
      controller.Right();
      controller.Rotate();
      controller.Drop();
    });
  EXPECT_CALL(mock_endpoint, Send(StringToBytes("right=2, rotate=1, drop=1")));

  WebClient client(mock_endpoint, stub_solver);
  client.Run();
}
