#include "mesh.hpp"
#include "tbb/parallel_for.h"
using namespace std;
using namespace Eigen;
using namespace tbb;
#define PI 3.14159265
#define AMBIENT_LIGHT 0.2
#define MATERIAL_COLOR 1.0
#define LIGHT_INTENSITY 1.0
#define PHONG_EXP 10

mesh::mesh(string file, int y_char, int x_char, int y_pixel, int x_pixel)
{
    this->x_pixel = x_pixel;
    this->y_pixel = y_pixel;
    this->x_char = x_char;
    this->y_char = y_char;
    this->pixel_per_char_x = (float)x_pixel / (float)x_char;
    this->pixel_per_char_y = (float)y_pixel / (float)y_char;
    aspect_ratio = (float)y_pixel / (float)x_pixel;

    mask.reserve(y_char);
    for (unsigned int i = 0; i < y_pixel; i++)
    {
        vector<int> holder(x_pixel, 0);
        mask.push_back(holder);
    }

    scaling = 1.0;
    loadOff(file);
    computeMask();
}

Matrix3Xf mesh::returnPoints()
{
    return points;
}
Matrix3Xf mesh::returnNormals()
{
    return normals;
}
Matrix3Xi mesh::returnFaces()
{
    return faces;
}

vector<vector<int>> mesh::returnMask()
{
    return mask;
}

void mesh::rotateX(bool if_increase)
{
    float rx = (if_increase ? 20 : -20) * PI / 180;
    Matrix3Xf rotx(3, 3);
    rotx << 1, 0, 0,
        0, cos(rx), sin(rx),
        0, -sin(rx), cos(rx);
    parallelMatrixMultiplication(rotx, points);
    // normals = rotx * normals;
    computeMask();
}

void mesh::rotateY(bool if_increase)
{
    float ry = (if_increase ? 20 : -20) * PI / 180;
    Matrix3Xf roty(3, 3);
    roty << cos(ry), 0, -sin(ry),
        0, 1, 0,
        sin(ry), 0, cos(ry);
    parallelMatrixMultiplication(roty, points);
    // normals = roty * normals;
    computeMask();
}

void mesh::scale(bool if_increase)
{
    if (if_increase)
    {
        scaling += 0.05;
        if (scaling > 1.4)
        {
            scaling = 1.4;
        }
    }
    else
    {
        scaling -= 0.05;
        if (scaling < 0.4)
        {
            scaling = 0.4;
        }
    }
    computeMask();
}

Vector3f mesh::computeNormal(Vector3f a, Vector3f b, Vector3f c)
{
    Vector3f n = (b - a).cross(c - a).normalized();
    return n;
}

float mesh::sign(Vector3f p1, Vector3f p2, Vector3f p3)
{
    return (p1(0) - p3(0)) * (p2(1) - p3(1)) - (p2(0) - p3(0)) * (p1(1) - p3(1));
}

bool mesh::PointInTriangle(Vector3f pt, Vector3f v1, Vector3f v2, Vector3f v3)
{
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

int colorMatch(Vector3f hit, Vector3f normal)
{
    float color = 1000 * MATERIAL_COLOR * AMBIENT_LIGHT;
    Vector3f light_in_normal = (Vector3f(2, 2, 2) - hit).normalized();
    Vector3f v = Vector3f(0, 0, -1);
    float diffuse = light_in_normal.transpose() * (normal);
    diffuse = max(diffuse, 0.0f);
    Vector3f h = (v + light_in_normal).normalized();
    float spec = normal.transpose() * h;
    spec = max(spec, 0.0f);
    color += 1000 * (MATERIAL_COLOR * LIGHT_INTENSITY * diffuse + MATERIAL_COLOR * LIGHT_INTENSITY * pow(spec, PHONG_EXP));
    color = int(max(min(floor(color / 100), 10.0f), 0.0f));
    return color;
}

void mesh::computeMask()
{
    parallel_for(size_t(0), size_t(y_char), [&](size_t(i)) {
        fill(mask[i].begin(), mask[i].end(), 0);
    });

    parallel_for(size_t(0), size_t(faces.cols()), [&](size_t(i)) {
        // cout<<normals.col(i)(2)<<"\n";
        // cout<<i<<"\n";
        Vector3f a = scaling * points.col(faces.col(i)(0));
        Vector3f b = scaling * points.col(faces.col(i)(1));
        Vector3f c = scaling * points.col(faces.col(i)(2));
        Vector3f normal = computeNormal(a, b, c);
        if (normal(2) > 0)
        {
            Vector3f center = (a + b + c) / 3;
            a(0) = (1 + a(0) * aspect_ratio) / 2 * x_pixel;
            b(0) = (1 + b(0) * aspect_ratio) / 2 * x_pixel;
            c(0) = (1 + c(0) * aspect_ratio) / 2 * x_pixel;
            a(1) = (1 + a(1)) / 2 * y_pixel;
            b(1) = (1 + b(1)) / 2 * y_pixel;
            c(1) = (1 + c(1)) / 2 * y_pixel;
            int x_min = int(min(a(0), min(b(0), c(0))));
            int x_max = int(max(a(0), max(b(0), c(0))));
            int y_min = int(min(a(1), min(b(1), c(1))));
            int y_max = int(max(a(1), max(b(1), c(1))));
            for (unsigned int i = (int)(y_min / pixel_per_char_y) - 1; i <= (int)(y_max / pixel_per_char_y); i += 1)
            {
                for (unsigned int j = (int)(x_min / pixel_per_char_x) - 1; j <= (int)(x_max / pixel_per_char_x); j += 1)
                {
                    if (PointInTriangle(Vector3f((float)j * pixel_per_char_x, (float)i * pixel_per_char_y, 0), a, b, c))
                    {
                        mask[i][j] = colorMatch(center, normal);
                    }
                }
            }
        }
    });
}

void mesh::loadOff(string file)
{
    ifstream shape_in(file);
    string dummyLine;
    getline(shape_in, dummyLine);
    int num_vert, num_face, num_edge;
    float x_max = -std::numeric_limits<float>::infinity();
    float x_min = std::numeric_limits<float>::infinity();
    float y_max = -std::numeric_limits<float>::infinity();
    float y_min = std::numeric_limits<float>::infinity();
    float z_max = -std::numeric_limits<float>::infinity();
    float z_min = std::numeric_limits<float>::infinity();
    float x_center = 0;
    float y_center = 0;
    float z_center = 0;
    shape_in >> num_vert >> num_face >> num_edge;
    points.resize(3, num_vert);
    normals.resize(3, num_face);
    faces.resize(3, num_face);
    for (unsigned i = 0; i < num_vert; i++)
    {
        // Vector3d point;
        double x, y, z;
        shape_in >> x >> y >> z;
        if (x > x_max)
        {
            x_max = x;
        }
        if (x < x_min)
        {
            x_min = x;
        }
        if (y > y_max)
        {
            y_max = y;
        }
        if (y < y_min)
        {
            y_min = y;
        }
        if (z > z_max)
        {
            z_max = z;
        }
        if (z < z_min)
        {
            z_min = z;
        }
        x_center += x;
        y_center += y;
        z_center += z;

        Vector3f point(x, y, z);
        points.col(i) = point;
    }
    x_center = x_center / (1.0 * num_vert);
    y_center = y_center / (1.0 * num_vert);
    z_center = z_center / (1.0 * num_vert);
    Vector3f shape_center(x_center, y_center, z_center);
    float z_max_scale = std::max(abs(z_max - z_center), abs(z_center - z_min));
    float y_max_scale = std::max(abs(y_max - y_center), abs(y_center - y_min));
    float x_max_scale = std::max(abs(x_max - x_center), abs(x_center - x_min));
    float max_scale = std::max(z_max_scale, std::max(y_max_scale, x_max_scale));
    parallel_for(size_t(0), size_t(num_vert), [&](size_t(i)) {
        points.col(i) = ((points.col(i) - shape_center) / max_scale) / 2;
    });
    for (unsigned i = 0; i < num_face; i++)
    {
        int n_edge;
        int a, b, c;
        shape_in >> n_edge >> a >> b >> c;
        faces.col(i) = Vector3i(a, b, c);
        normals.col(i) = computeNormal(points.col(a), points.col(b), points.col(c));
    }
}

void mesh::parallelMatrixMultiplication(const Matrix3Xf &a, Matrix3Xf &b)
{
    // const Matrix3Xf tmp = b;
    parallel_for(size_t(0), size_t(b.cols()), [&](size_t(i)) {
        b.col(i) = a * b.col(i);
    });
}