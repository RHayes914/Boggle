#include "BogglePieceGenerator.h"
#include <algorithm>


BogglePieceGenerator::BogglePieceGenerator(int boardSize, int rseed){
  this->index = 0;

  // 1. choose the set of boggle cubes
  if( boardSize <= SMALL_BOARD ){
    this->cubes = vector<string>(this->cube16pattern, this->cube16pattern + SMALL_BOARD);
  }else{
    this->cubes = vector<string>(this->cube25pattern, this->cube25pattern + LARGE_BOARD);
  }

  // 2. Setup the random number generator
  srand(rseed);
}

BogglePieceGenerator::~BogglePieceGenerator(void){

}

char BogglePieceGenerator::getNextChar(){
  // if its the first time we are selecting a cube
  // randomly shuffle the cubes
  if( index == 0 ){
    random_shuffle(cubes.begin(), cubes.end());
  }

  int cubeSide = rand() % CUBE_SIDES;
  char result = cubes[index].at(cubeSide);

  // look at the next cube
  // handle wrap around
  index++;
  if( index >= cubes.size() ){
    index -= cubes.size();
  }

  return result;
}

void BogglePieceGenerator::reSeed(int rseed){
  this->index = 0;
  srand(rseed);
}

const string BogglePieceGenerator::cube16pattern[] = {
  "aaeegn", "abbjoo", "achops", "affkps",
  "aoottw", "cimotu", "deilrx", "delrvy",
  "distty", "eeghnw", "eeinsu", "ehrtvw", 
  "eiosst", "elrtty", "himnqu", "hlnnrz"
};

const string BogglePieceGenerator::cube25pattern[] = {
  "aafirs", "adennn", "aaafrs", "aeegmu", "aaeeee",
  "aeeeem", "afirsy", "aegmnn", "bjkqxz", "ceipst", 
  "ceiilt", "ccnstw", "ceilpt", "ddlonr", "dhlnor",
  "dhhlor", "dhhnot", "ensssu", "emottt", "eiiitt", 
  "fiprsy", "gorrvw", "hiprry", "nootuw", "ooottu"
};
