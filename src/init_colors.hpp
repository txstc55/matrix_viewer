#pragma once
#include<ncurses.h>

// init all the 10 levels of greeb
void init_greens(){
    init_color(21, 0, 100, 50);
    init_color(22, 0, 200, 100);
    init_color(23, 0, 300, 150);
    init_color(24, 0, 400, 200);
    init_color(25, 0, 500, 250);
    init_color(26, 0, 600, 300);
    init_color(27, 0, 650, 325);
    init_color(28, 0, 700, 350);
    init_color(29, 0, 750, 375);
    init_color(30, 0, 800, 400);
    init_color(30, 0, 900, 450);
    init_color(31, 100, 1000, 500);
    init_color(32, 200, 1000, 450);
    init_color(33, 300, 1000, 450);
    init_color(34, 400, 1000, 450);
    init_color(35, 500, 1000, 500);
    init_color(36, 600, 1000, 600);
    init_color(37, 700, 1000, 700);
    init_color(38, 800, 1000, 800);
    init_color(39, 900, 1000, 900);
    init_color(40, 950, 1000, 950);
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

}