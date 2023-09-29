#ifndef COLORS_H
#define COLORS_H

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
} // namespace colors

#endif
