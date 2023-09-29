#ifndef BOARD_H
#define BOARD_H

#include "block.h"
#include <vector>

class Board {
  unsigned int width;
  unsigned int height;
  std::vector<std::vector<Block>> map;

public:
  Board(unsigned int width, unsigned int height);
  ~Board();

  void render();
  void random_generate_land();
};

#endif
