#include <string>
#include <algorithm>    // std::find_if
#include <iostream>
#include <sstream>
#include "../include/library.h"
#include "../include/variables.h"

bool is_number(const std::string& s)
{
    std::istringstream iss(s);
    float f;
    iss >> noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail(); 
}
