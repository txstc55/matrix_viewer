#pragma once
#include <ncurses.h>

// init all the 10 levels of greeb
void init_greens()
{
    init_color(21, 0, 100, 50);
    init_color(22, 25, 100, 50);
    init_color(23, 0, 200, 100);
    init_color(24, 25, 200, 100);
    init_color(25, 0, 300, 250);
    init_color(26, 25, 300, 300);
    init_color(27, 0, 400, 325);
    init_color(28, 25, 400, 350);
    init_color(29, 0, 550, 375);
    init_color(30, 25, 550, 400);
    init_color(31, 50, 600, 450);
    init_color(32, 0, 700, 450);
    init_color(33, 50, 700, 450);
    init_color(34, 0, 800, 450);
    init_color(35, 50, 800, 450);
    init_color(36, 0, 850, 450);
    init_color(37, 50, 850, 450);
    init_color(38, 0, 900, 450);
    init_color(39, 0, 950, 450);
    init_color(40, 50, 950, 450);
    init_color(41, 100, 1000, 500);
    init_color(42, 200, 1000, 450);
    init_color(43, 300, 1000, 450);
    init_color(44, 400, 1000, 450);
    init_color(45, 500, 1000, 500);
    init_color(46, 600, 1000, 600);
    init_color(47, 700, 1000, 700);
    init_color(48, 800, 1000, 800);
    init_color(49, 900, 1000, 900);
    init_color(50, 950, 1000, 950);
    init_color(51, 950, 1000, 950);
    init_pair(21, 21, -1);
    init_pair(22, 22, -1);
    init_pair(23, 23, -1);
    init_pair(24, 24, -1);
    init_pair(25, 25, -1);
    init_pair(26, 26, -1);
    init_pair(27, 27, -1);
    init_pair(28, 28, -1);
    init_pair(29, 29, -1);
    init_pair(30, 30, -1);
    init_pair(31, 31, -1);
    init_pair(32, 32, -1);
    init_pair(33, 33, -1);
    init_pair(34, 34, -1);
    init_pair(35, 35, -1);
    init_pair(36, 36, -1);
    init_pair(37, 37, -1);
    init_pair(38, 38, -1);
    init_pair(39, 39, -1);
    init_pair(40, 40, -1);
    init_pair(41, 41, -1);
    init_pair(42, 42, -1);
    init_pair(43, 44, -1);
    init_pair(44, 44, -1);
    init_pair(45, 45, -1);
    init_pair(46, 46, -1);
    init_pair(47, 47, -1);
    init_pair(48, 48, -1);
    init_pair(49, 49, -1);
    init_pair(50, 50, -1);
    init_pair(51, 51, -1);
}