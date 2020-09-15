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
#ifdef OK
#undef OK
#include <opencv2/opencv.hpp>
#endif
using namespace std;
using namespace cv;

#define max(x, y) x > y ? x : y
#define min(x, y) x < y ? x : y

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
        if (file_name == "camera")
        {
            VideoCapture cap;
            // set to the real camera
            // user have to figure out which camera to use
            if (!cap.open(1))
            {
                return 0;
            }
            Mat frame, gray;
            cap >> frame;
            int height = frame.rows;
            int width = frame.cols;
            // the frame will not perfectly fit into terminal
            // so we will need to enlarge or shrink it
            // but we will not distort the aspect ratio
            // we will simply crop it
            double terminal_aspect_ratio = x_pixel * 1.0 / (y_pixel * 1.0);
            double camera_aspect_ratio = width * 1.0 / (height * 1.0);

            // the image should be enlarged for this much
            double factor = 1.0;
            // the gap area, since we will put the image in center
            double x_gap = 0.0;
            double y_gap = 0.0;
            if (terminal_aspect_ratio > camera_aspect_ratio)
            {
                factor = y_pixel * 1.0 / (height * 1.0);
                x_gap = max(0.0, (x_pixel - width * factor) / 2);
            }
            else
            {
                factor = x_pixel * 1.0 / (width * 1.0);
                y_gap = max(0.0, (y_pixel - height * factor) / 2);
            }

            double font_width = x_pixel * 1.0 / (max_x * 1.0);
            double font_height = y_pixel * 1.0 / (max_y * 1.0);

            // how many characters the gap translate to
            int x_gap_char = x_gap / font_width;
            int y_gap_char = y_gap / font_height;

            // how many pixels for one char on camera
            int font_occupied_pixel_width = max(1, font_width / factor);
            int font_occupied_pixel_height = max(1, font_height / factor);

            // printf("Console size: %d, %d\nConsole font size: %d, %d\nVideo size %d, %d\nFactor: %f, gap_x: %f, gap_y: %f\n", x_pixel, y_pixel, max_x, max_y, width, height, factor, x_gap, y_gap);
            // printf("font width: %f, font height %f\n", font_width, font_height);
            // printf("x gap char: %d, y gap char: %d\n", x_gap_char, y_gap_char);
            while (1)
            {
                wgetch(stdscr);
                cap >> frame;
                cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
                if (frame.empty())
                {
                    break; // end of video stream
                }
                for (unsigned int i = 0; i < max_y; i++)
                {
                    for (unsigned int j = 0; j < max_x; j++)
                    {
                        if (i < y_gap_char || i >= (max_y - y_gap_char) || j < x_gap_char || j >= (max_x - x_gap_char))
                        {
                            if (matrix.char_map[i][j] != ' ')
                            {
                                attron(COLOR_PAIR(matrix.color_map[i][j]));
                            }
                            addch(matrix.char_map[i][j]);
                            if (matrix.char_map[i][j] != ' ')
                            {
                                attroff(COLOR_PAIR(matrix.color_map[i][j]));
                            }
                        }
                        else
                        {
                            // printf("i: %d, j: %d\n", i, j);
                            int i_min = (i - y_gap_char) * font_height / factor;
                            int i_max = i_min + font_occupied_pixel_height;
                            int j_min = (j - x_gap_char) * font_width / factor;
                            int j_max = j_min + font_occupied_pixel_width;
                            int count = 0;
                            double sum_brightness = 0;
                            // printf("i from %d to %d, j from %d to %d\n", i_min, i_max, j_min, j_max);
                            for (int m = i_min; m <= i_max; m++)
                            {
                                for (int n = width - j_max - 1; n < width - j_min; n++)
                                {
                                    if (m < height && n < width)
                                    {
                                        count++;
                                        sum_brightness += gray.at<uchar>(m, n, 0);
                                    }
                                }
                            }
                            double average_brightness = sum_brightness / count;
                            // printf("average brightness: %f\n", average_brightness);
                            if (matrix.char_map[i][j] != ' ')
                            {
                                attron(COLOR_PAIR(matrix.color_map[i][j]) + int(average_brightness) * 15);
                            }
                            addch(matrix.char_map[i][j]);
                            if (matrix.char_map[i][j] != ' ')
                            {
                                attroff(COLOR_PAIR(matrix.color_map[i][j]) + int(average_brightness) * 15);
                            }
                        }
                    }
                }
                matrix.nextFrame();
                move(0, 0);
            }
        }
        else
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

    // endwin();
    return 0;
}