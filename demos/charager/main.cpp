#include "../../colors.h"
#include "../../terminal.h"
#include <iostream>

#include <iostream>
#include <random>

#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using namespace colors;

int random_number(int min, int max) { return rand() % (max - min + 1) + min; }

struct tile {
  int ground;
  int object;
};

std::string render_ground(int id) {
  switch (id) {
  case -1: // void
    return RED + '!';
  case 0: // water
    return BLUE + '~';
  case 1: // sand
    return YELLOW + '#';
  case 2: // stone
    return BLACK + '#';
  case 3: // grass
    return GREEN + '#';
  default: // error
    return RED + '!';
  }
}

std::string render_object(int id) {
  switch (id) {
  case 1: // tree
    return GREEN + 't';
  case 2: // rock
    return WHITE + 'O';
  case 3: // coal ore
    return BLACK + 'o';
  case 4: // iron ore
    return WHITE + 'o';
  case 5: // gold ore
    return YELLOW + 'o';
  case 6: // diamond ore
    return CYAN + 'o';
  default: // error
    return RED + '!';
  }
}

std::string render_tile(tile t) {
  if (t.object == 0) {
    return render_ground(t.ground) + RESET + " ";
  } else {
    return render_object(t.object) + RESET + " ";
  }
}

class Board {
  unsigned int width;
  unsigned int height;
  std::vector<std::vector<tile>> map;

public:
  Board(unsigned int width, unsigned int height);
  ~Board();

  void render();
  void generate_ground();
  void generate_objects();
};

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
      std::cout << render_tile(map[i][j]);
    }
    std::cout << std::endl;
  }

  std::cout << "Rendering finished..." << std::endl;
}

void Board::generate_ground() {
  std::cout << "Generating ground started..." << std::endl;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      double x = static_cast<double>(i) / width * 2;
      double y = static_cast<double>(j) / height * 2;

      double noise = -perlin.noise(x, y);

      if (noise > 0.3) {
        map[i][j].ground = 3;
      } else if (noise > 0.2) {
        map[i][j].ground = 2;
      } else if (noise > 0.1) {
        map[i][j].ground = 1;
      } else {
        map[i][j].ground = 0;
      }
    }
  }

  std::cout << "Generating ground finished..." << std::endl;
}

void Board::generate_objects() {
  std::cout << "Generating objects started..." << std::endl;

  for (int i = 0; i < 20; i++) {
    int x = random_number(0, width - 1);
    int y = random_number(0, height - 1);
    int object = random_number(1, 6);

    if (map[x][y].ground >= 1) {
      map[x][y].object = object;
    }
  }

  std::cout << "Generating objects finished..." << std::endl;
}

int main() {
  Board *board = new Board{20, 20};
  board->generate_ground();
  board->generate_objects();
  board->render();
  delete board;

  return 0;
}
