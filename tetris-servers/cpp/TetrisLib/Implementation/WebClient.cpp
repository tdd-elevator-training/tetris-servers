#include <chrono>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <thread>

#include "../GameStateLoader.h"
#include "../IBlockingEndPoint.h"
#include "../IPieceController.h"
#include "../ISolver.h"
#include "../MessageEncoding.h"
#include "../Problem.h"
#include "../WebClient.h"
#include "../Well.h"

using namespace tetris;

namespace
{
  class ScriptingController
    : public IPieceController
  {
  public:
    virtual void Left() override 
    {
      AppendCommand("left");
    }
    virtual void Right() override 
    {
      AppendCommand("right");
    }
    virtual void Rotate() override 
    {
      AppendCommand("rotate");
    }
    virtual void Drop() override 
    {
      AppendCommand("drop");
    }

    std::string GetScript() const
    {
      std::stringstream script;
      for (auto log_entry: log_)
      {
        if (script.tellp() > 0)
          script << ", ";
        script << log_entry.first << "=" << log_entry.second;
      }
      return script.str();
    }

  private:
    void AppendCommand(const std::string &command)
    {
      if (!log_.empty() && log_.back().first == command)
        ++log_.back().second;
      else
        log_.push_back(std::make_pair(command, 1));
    }

  private:
    std::list<std::pair<std::string, size_t>> log_;
  };

  class EndPointCallback
    : public IBlockingEndPointCallback
  {
  public:
    explicit EndPointCallback(ISolver &solver)
      : solver_(solver)
    {
    }

    virtual void OnReceive(const std::vector<char> &message, IBlockingEndPoint &endpoint) override
    {
      try
      {
        ScriptingController controller;
        GameStateLoader loader(StringFromBytes(message));
        Problem problem(loader.LoadWell(), loader.LoadPiece(), loader.LoadX(), loader.LoadY());
        solver_.Solve(controller, problem);

        endpoint.Send(StringToBytes(controller.GetScript()));
      }
      catch (const std::exception &e)
      {
        std::cerr << "ERROR: " << e.what() << std::endl;
      }
    }

  private:
    ISolver &solver_;
  };
}

class WebClient::Impl
{
public:
  Impl(IBlockingEndPoint &endpoint, ISolver &solver)
    : endpoint_(endpoint)
    , solver_(solver)
  {
  }

  void Run()
  {
    endpoint_.Loop(::EndPointCallback(solver_));
  }

private:
  IBlockingEndPoint &endpoint_;
  ISolver &solver_;
};

WebClient::WebClient(IBlockingEndPoint &endpoint, ISolver &solver)
  : pimpl_(new Impl(endpoint, solver))
{
}

WebClient::~WebClient()
{
  delete pimpl_;
}

void WebClient::Run()
{
  pimpl_->Run();
}