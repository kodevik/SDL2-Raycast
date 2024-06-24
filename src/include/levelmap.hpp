#ifndef levelmap_hpp
#define levelmap_hpp
#define A_LC(sy, ey) (sy - ey) 
#define B_LC(sx, ex) (ex - sx)
#define C_LC(sx, sy, ex, ey) (-(sx * ey - ex * sy)) // A, B and C are coefficents for Cramer's rule line intersection
#define AREA(sx, sy, ex, ey, cx, cy) (sx * (ey - cy) + ex * (cy - sy) + cx * (sy - ey)) // area of triangle given 3 points

#include "SDL2/SDL.h"
#include <vector>
#include <cmath>

struct Wall {
    double sx;
    double sy;
    double ex;
    double ey;
    int r;
    int g;
    int b;
}; //start and end coordinates of a wall

struct TextureInfo {
    float dist;
    int r;
    int g;
    int b;
}; //distance and colour of raycasted wall

class LevelMap {
public:
    LevelMap();
    ~LevelMap();
    void addWall(double sx, double sy, double ex, double ey, int r, int g, int b);
    TextureInfo getWall(float angle, float cAngle, double cx, double cy);
private:
    std::vector<Wall> walls;
};

#endif