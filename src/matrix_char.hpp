#pragma once
#include<vector>
#include<random>
#include <tbb/parallel_for.h>
class matrix_char{
private:
    int max_y, max_x;                         // used to initialize the 2d array
    std::vector<int> first_row;               // if negative then don't generate anything, if positive, then keep decreasing until it's zero
    int density;                              // the density of char on he screen
    const char* chars = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm?.!@#$%&*+-:;";
    const unsigned int chars_length = sizeof(chars)/sizeof(char);


public:
    // init the char map
    matrix_char(const int max_y, const int max_x, const int density);
    // calculate the char and position for next map
    void nextFrame();

    // assign char based on probabiliy
    char assignChar(const unsigned int column);

    // assign color in decreasing order (gets darker)
    int assignColor(const unsigned int column);

    std::vector<std::vector<char> > char_map;           // the char map
    std::vector<std::vector<int> > color_map;  // for each char, assign the color



};