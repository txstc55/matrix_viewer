#include "matrix_char.hpp"
#include<iostream>
using namespace std;
using namespace tbb;



matrix_char::matrix_char(const int max_y, const int max_x, const int min_length){
    this->max_y = max_y;
    this->max_x = max_x;
    this->min_length = min_length>max_y?max_y:min_length;
    char_map.resize(max_y);
    color_map.resize(max_y);
    first_row.resize(max_x);
    for (unsigned int i=0; i<max_y; i++){
        vector<char> char_holder(max_x);
        vector<int> color_holder(max_x);
        for (unsigned int j=0; j<max_x; j++){
            color_holder[j] = 0;
            char_holder[j] = ' ';
        }
        char_map[i] = char_holder;
        color_map[i] = color_holder;
    }
    for (unsigned int i=0; i<max_x; i++){
        const int random_length = rand()%100>=99?rand()%max_y:-rand()%max_y;
        if (random_length>0&&random_length<min_length){
            first_row[i] = random_length+min_length;
        }else{
            first_row[i] = random_length;
        }
    }
    nextFrame();
    nextFrame();
}


char matrix_char::assignChar(const unsigned int column){
    if (first_row[column]>0){
        color_map[0][column] = assignColor(column);
        // std::cout<<first_row[column];
        first_row[column]--;
        return char_map[0][column]==' '?chars[rand()%chars_length]:char_map[0][column];
    }else if (first_row[column]==0){
        // just finished waiting
        if (char_map[1][column]==' '){
            first_row[column] = rand()%(max_y - min_length)+min_length;
            color_map[0][column] = assignColor(column);
        }else{ // just finished a sequence
            first_row[column] = -rand()%max_y;
            color_map[0][column] = 0;
        }
        return ' ';
    }else{
        first_row[column]++;
        return ' ';
    }
}

int matrix_char::assignColor(const unsigned int column){
    if (color_map[1][column]==0){
        return 40-rand()%15;
    }else{
        int if_decrease = rand()%20>(40-color_map[1][column]);
        return max(color_map[1][column]-if_decrease, 21);
    }
}

void matrix_char::nextFrame(){
    for (unsigned int i=max_y-1; i>0; i--){
        parallel_for (size_t(0), size_t(max_x), [&](size_t j){
            if (color_map[i-1][j]==0 && color_map[i][j]!=0){
                char_map[i][j] = ' ';
            }else if(color_map[i-1][j]!=0 && color_map[i][j]==0){
                char_map[i][j] = chars[rand()%chars_length];
            }
        });
    }
    rotate(color_map.begin(), color_map.begin()+max_y-1, color_map.end());
    color_map[0] = color_map[1];
    parallel_for (size_t(0), size_t(max_x),[&](size_t i){
        char_map[0][i] = assignChar(i);
    });
}