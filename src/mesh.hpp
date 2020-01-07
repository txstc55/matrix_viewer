#pragma once
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class mesh
{
private:
    int x_pixel, y_pixel;                     // the size of the screen in pixel
    int x_char, y_char;                       // the size of the screen in char
    float pixel_per_char_x, pixel_per_char_y; // how many pixels for the bounding box for each character
    Eigen::Matrix3Xf points;                  // the point positions
    Eigen::Matrix3Xf normals;                 // record the normal for each face;
    Eigen::Matrix3Xi faces;                   //record the face index
    float scaling;                            // record the scaling
    float aspect_ratio;                       // the aspect ratio of the screen

public:
    mesh(std::string file, int y_char, int x_char, int y_pixel, int x_pixel);                                 // init
    void loadOff(std::string file);                                                                           // loading the off object and fill up the info
    Eigen::Vector3f computeNormal(const Eigen::Vector3f a, const Eigen::Vector3f b, const Eigen::Vector3f c); // given triangle, calculate the normal
    void rotateY(bool if_increase);                                                                           // calculate one rotation around Y axis
    void rotateX(bool if_increase);                                                                           // calculate one rotation around x axis
    void scale(bool if_increase);

    Eigen::Matrix3Xf returnPoints();            // return the point coordinates
    Eigen::Matrix3Xf returnNormals();           // return the normals
    Eigen::Matrix3Xi returnFaces();             // return the faces
    std::vector<std::vector<int>> returnMask(); //return the mask overlay

    float sign(const Eigen::Vector3f p1, const Eigen::Vector3f p2, const Eigen::Vector3f p3);                                     // helper function to determine if point inside triangle
    bool PointInTriangle(const Eigen::Vector3f pt, const Eigen::Vector3f v1, const Eigen::Vector3f v2, const Eigen::Vector3f v3); // check if point inside triangle
    int colorMatche(const Eigen::Vector3f hit, const Eigen::Vector3f normal);                                                     // calculate the color, returns 1~10

    std::vector<std::vector<int>> mask; // compute the mask
    void computeMask();                 // compute the mask overlay
};