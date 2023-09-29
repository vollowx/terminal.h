#ifndef BLOCK_H
#define BLOCK_H

#include "../../colors.h"
#include <string>
#include <vector>

enum BlockType {
  Air,
  Stone,
  Dirt,
  Grass,
  Wood,
  Leaves,
  Water,
  Lava,
  Sand,
  Gravel,
  CoalOre,
  IronOre,
  GoldOre,
  DiamondOre,

  BlockCount // To store the total number of block types
};

class Block {
  unsigned int type;

public:
  Block(BlockType type = Air);
  ~Block();
  std::string name() const { return names[type]; }
  std::string color() const { return colors[type]; }
  char symbol() const { return symbols[type]; }
  void set_type(BlockType type) { this->type = type; }

private:
  std::vector<std::string> names = {
      "Air",      "Stone",    "Dirt",     "Grass",       "Wood",
      "Leaves",   "Water",    "Lava",     "Sand",        "Gravel",
      "Coal Ore", "Iron Ore", "Gold Ore", "Diamond Ore",
  };
  std::vector<std::string> colors = {
      colors::BLACK,  colors::BLACK, colors::BLACK, colors::GREEN,
      colors::YELLOW, colors::GREEN, colors::BLUE,  colors::RED,
      colors::YELLOW, colors::BLACK, colors::BLACK, colors::WHITE,
      colors::YELLOW, colors::CYAN,

  };
  std::vector<char> symbols = {
      ' ', '#', '%', '#', 'W', 'L', '~', '~', 'S', 'G', 'C', 'I', 'G', 'D',
  };
};

#endif
