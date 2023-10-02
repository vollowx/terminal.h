#ifndef COLORS_H
#define COLORS_H

#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

namespace colors {
const string RESET = "\033[0m";
const string BLACK = "\033[30m";   /* Black */
const string RED = "\033[31m";     /* Red */
const string GREEN = "\033[32m";   /* Green */
const string YELLOW = "\033[33m";  /* Yellow */
const string BLUE = "\033[34m";    /* Blue */
const string MAGENTA = "\033[35m"; /* Magenta */
const string CYAN = "\033[36m";    /* Cyan */
const string WHITE = "\033[37m";   /* White */
const string BOLD = "\033[1m";     /* Bold */

inline void set_bg_color(uint8_t R, uint8_t G, uint8_t B) {
  std::cerr << "\033[48;2;" << (int)R << ";" << (int)G << ";" << (int)B << "m";
}

inline void set_color(uint8_t R, uint8_t G, uint8_t B) {
  std::cerr << "\033[38;2;" << (int)R << ";" << (int)G << ";" << (int)B << "m";
}
} // namespace colors

#endif
