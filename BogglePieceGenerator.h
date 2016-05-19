#ifndef BOGGLE_PIECE_GENERATOR_H
#define BOGGLE_PIECE_GENERATOR_H

#include <vector>
#include <string>

using namespace std;

class BogglePieceGenerator
{
 public:
  // methods
  BogglePieceGenerator(int boardSize, int rseed);
  virtual ~BogglePieceGenerator(void);

  // return the next character for the boggle board
  char getNextChar();

  // reset the piece generator in preparation 
  // for generating pieces for another board
  void reSeed(int rseed);

 private:
  // member variables
  size_t index;
  vector<string> cubes;

  // standard boggle cubes for 4x4 and 5x5 boards
  enum{SMALL_BOARD=16, LARGE_BOARD=25, CUBE_SIDES=6};
  static const string cube16pattern[SMALL_BOARD];
  static const string cube25pattern[LARGE_BOARD];
};

#endif // BOGGLE_PIECE_GENERATOR_H
