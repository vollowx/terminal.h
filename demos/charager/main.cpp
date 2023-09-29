#include "../../terminal.h"
#include "board.h"
#include <iostream>

int main() {
  Board *board = new Board{20, 20};
  board->random_generate_land();
  board->render();
  delete board;

  return 0;
}
