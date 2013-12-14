#include <boost/assign.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

#include "../GameStateLoader.h"

using namespace tetris;

namespace
{

  PieceType PieceFromString(const std::string &string)
  {
    static const std::map<std::string, PieceType> map = boost::assign::map_list_of
      ("I", PIECE_I)("O", PIECE_O)("L", PIECE_L)("J", PIECE_J)("S", PIECE_S)("Z", PIECE_Z)("T", PIECE_T);

    auto it = map.find(string);
    if (it == map.cend())
      throw std::runtime_error("can't decode piece");

    return it->second;
  }

  Well WellFromString(const std::string &string)
  {
    const size_t WIDTH = 10, HEIGHT = 20;
    if (string.size() != WIDTH * HEIGHT)
      throw std::runtime_error("can't decode well");

    Well well(WIDTH, HEIGHT);
    auto it = string.cbegin();
    for (size_t y = 0; y < HEIGHT; ++y)
    {
      for (size_t x = 0; x < WIDTH; ++x)
      {
        if (*it == '*')
          well.OccupyCell(x, y);
        ++it;
      }
    }

    return well;
  }
}

class GameStateLoader::Impl
{
public:
  explicit Impl(const std::string &message)
    : message_(message)
  {
  }

  size_t LoadX()
  {
    boost::regex re_x("x=(?<x>\\d+)");
    boost::match_results<std::string::const_iterator> match;

    if (!boost::regex_search(message_, match, re_x) || !match["x"].matched)
      throw std::runtime_error("can't decode x");

    return boost::lexical_cast<size_t>(match.str("x"));
  }

  size_t LoadY()
  {
    boost::regex re_y("y=(?<y>\\d+)");
    boost::match_results<std::string::const_iterator> match;

    if (!boost::regex_search(message_, match, re_y) || !match["y"].matched)
      throw std::runtime_error("can't decode y");

    return boost::lexical_cast<size_t>(match.str("y"));
  }

  PieceType LoadPiece()
  {
    boost::regex re_figure("figure=(?<figure>.)");
    boost::match_results<std::string::const_iterator> match;

    if (!boost::regex_search(message_, match, re_figure) || !match["figure"].matched)
      throw std::runtime_error("can't load piece");

    return PieceFromString(match.str("figure"));
  }

  Well LoadWell()
  {
    boost::regex re_well("glass=(?<well>.{200})");  // 10*20
    boost::match_results<std::string::const_iterator> match;

    if (!boost::regex_search(message_, match, re_well) || !match["well"].matched)
      throw std::runtime_error("can't load well");

    return WellFromString(match.str("well"));
  }

private:
  std::string message_;
};

GameStateLoader::GameStateLoader(const std::string &message)
  : p_impl_(new Impl(message))
{
}

GameStateLoader::~GameStateLoader()
{
  delete p_impl_;
}

PieceType GameStateLoader::LoadPiece()
{
  return p_impl_->LoadPiece();
}

Well GameStateLoader::LoadWell()
{
  return p_impl_->LoadWell();
}

size_t GameStateLoader::LoadX()
{
  return p_impl_->LoadX();
}

size_t GameStateLoader::LoadY()
{
  return p_impl_->LoadY();
}
