#include "board.h"
#include "block.h"

#include <iostream>
#include <random>

#include <cmath>
#include <iostream>
#include <random>
#include <vector>

const int BOARD_SIZE = 10;

class PerlinNoise {
public:
  PerlinNoise() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 255);
    for (int i = 0; i < 256; ++i) {
      permutation[i] = dist(gen);
      permutation[256 + i] = permutation[i];
    }
  }

  double noise(double x, double y) const {
    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;

    x -= std::floor(x);
    y -= std::floor(y);

    double u = fade(x);
    double v = fade(y);

    int A = permutation[X] + Y;
    int AA = permutation[A];
    int AB = permutation[A + 1];
    int B = permutation[X + 1] + Y;
    int BA = permutation[B];
    int BB = permutation[B + 1];

    return lerp(
        v,
        lerp(u, grad(permutation[AA], x, y), grad(permutation[BA], x - 1, y)),
        lerp(u, grad(permutation[AB], x, y - 1),
             grad(permutation[BB], x - 1, y - 1)));
  }

private:
  static double fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10); }
  static double lerp(double t, double a, double b) { return a + t * (b - a); }
  static double grad(int hash, double x, double y) {
    int h = hash & 15;
    double grad = 1.0 + (h & 7); // Gradient value 1-8
    if (h & 8)
      grad = -grad; // Randomly invert half of the gradients
    return (h & 1 ? x : -x) + (h & 2 ? y : -y);
  }
  int permutation[512];
};

PerlinNoise perlin;

Board::Board(unsigned int width, unsigned int height) {
  std::cout << "Board constructor started..." << std::endl;

  this->width = width;
  this->height = height;

  map.resize(height);
  for (int i = 0; i < height; i++) {
    map[i].resize(width);
  }

  std::cout << "Board constructor finished..." << std::endl;
}
Board::~Board() {}

void Board::render() {
  std::cout << "Rendering started..." << std::endl;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      std::cout << map[i][j].color() << map[i][j].symbol() << colors::RESET
                << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "Rendering finished..." << std::endl;
}

void Board::random_generate_land() {
  std::cout << "Generating land started..." << std::endl;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      double x = static_cast<double>(i) / BOARD_SIZE;
      double y = static_cast<double>(j) / BOARD_SIZE;

      double noise = -perlin.noise(x, y);

      if (noise > 0.5) {
        map[i][j].set_type(BlockType::Grass);
      } else if (noise > 0.4) {
        map[i][j].set_type(BlockType::Dirt);
      } else if (noise > 0.3) {
        map[i][j].set_type(BlockType::Gravel);
      } else if (noise > 0.2) {
        map[i][j].set_type(BlockType::Sand);
      } else {
        map[i][j].set_type(BlockType::Water);
      }
    }
  }

  std::cout << "Generating land finished..." << std::endl;
}
