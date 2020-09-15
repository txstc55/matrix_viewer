#include <ncurses.h>
#include <iostream>
#include <vector>
#include <random>
#include "init_colors.hpp"
#include "matrix_char.hpp"
#include "mesh.hpp"
#include <cstdlib>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

int main(int argc, char *argv[])
{
    int x_pixel, y_pixel;
    string file_name = "";

    // get the terminal size
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    x_pixel = w.ws_xpixel;
    y_pixel = w.ws_ypixel;

    if (argc > 1)
    {
        file_name = argv[1];
    }
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

    if (argc > 1)
    {
        mesh m;
        m = mesh(file_name, max_y, max_x, y_pixel, x_pixel);

        // control keys logic
        int c;
        while (1)
        {
            c = wgetch(stdscr);
            switch (c)
            {
            case 'w':
                m.rotateX(false);
                break;
            case 's':
                m.rotateX(true);
                break;
            case 'a':
                m.rotateY(true);
                break;
            case 'd':
                m.rotateY(false);
                break;
            case 'k':
                m.scale(true);
                break;
            case 'l':
                m.scale(false);
                break;
            default:
                break;
            }
            for (unsigned int i = 0; i < max_y; i++)
            {
                for (unsigned int j = 0; j < max_x; j++)
                {
                    if (matrix.char_map[i][j] != ' ')
                        attron(COLOR_PAIR(matrix.color_map[i][j] + m.mask[i][j]));
                    addch(matrix.char_map[i][j]);
                    if (matrix.char_map[i][j] != ' ')
                        attroff(COLOR_PAIR(matrix.color_map[i][j] + m.mask[i][j]));
                }
            }
            matrix.nextFrame();
            move(0, 0);
        }
    }
    else
    {
        // int c;
        while (1)
        {
            wgetch(stdscr);
            for (unsigned int i = 0; i < max_y; i++)
            {
                for (unsigned int j = 0; j < max_x; j++)
                {
                    if (matrix.char_map[i][j] != ' ')
                        attron(COLOR_PAIR(matrix.color_map[i][j]));
                    addch(matrix.char_map[i][j]);
                    if (matrix.char_map[i][j] != ' ')
                        attroff(COLOR_PAIR(matrix.color_map[i][j]));
                }
            }
            matrix.nextFrame();
            move(0, 0);
        }
    }

    endwin();
    return 0;
}