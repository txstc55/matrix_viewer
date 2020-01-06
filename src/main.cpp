#include <ncurses.h>
#include <iostream>
#include <vector>
#include <random>
#include "init_colors.hpp"
#include "matrix_char.hpp"
using namespace std;

int main()
{
    // initialize screen
    initscr();
    // do not echo user input
    noecho();
    // can use control + c to break
    cbreak();

    timeout(50);

    curs_set(0);

    // get the maximum window size
    int max_x, max_y;
    // max_x = 200;
    // max_y = 66;
    getmaxyx(stdscr, max_y, max_x);

    // endwin();
    // // cout<<max_x<<"\n"<<max_y<<"\n";
    int c;

    // check if color is available
    if (has_colors())
    {
        // start using color
        start_color();
        // keep the default color
        use_default_colors();
        init_greens();
    }
    unsigned int density = 10;
    matrix_char matrix = matrix_char(max_y, max_x, 20);

    unsigned int loop = 0;
    while (1)
    {
        c = wgetch(stdscr);
        for (unsigned int i = 0; i < max_y; i++)
        {
            for (unsigned int j = 0; j < max_x; j++)
            {
                attron(COLOR_PAIR(matrix.color_map[i][j]));
                addch(matrix.char_map[i][j]);
                attroff(COLOR_PAIR(matrix.color_map[i][j]));
            }
        }
        // attroff(COLOR_PAIR(30));
        matrix.nextFrame();
        move(0, 0);
    }

    endwin();
    return 0;
}