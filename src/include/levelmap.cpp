#include "levelmap.hpp"
#include <iostream>

LevelMap::LevelMap() {}
LevelMap::~LevelMap() {}

float round_3dp(double n) {
    return round(n * 1000) / 1000;
}

void LevelMap::addWall(double sx, double sy, double ex, double ey, int r, int g, int b) {
    struct Wall new_wall = { sx, sy, ex, ey, r, g, b };
    walls.push_back(new_wall);
}

TextureInfo LevelMap::getWall(float angle, float cAngle, double cx, double cy)
{
    double cx_angled = cx + std::cos(angle); 
    double cy_angled = cy + std::sin(angle); //center point incremented in direction specified by angle
    TextureInfo ti = { -1.0, 0, 0, 0 }; //default blank wall
    for (auto& i : walls) {
        double area = std::abs(AREA(i.sx, i.sy, i.ex, i.ey, cx, cy)); //triangle formed between player and wall start and end coords
        double a1 = std::abs(AREA(cx_angled, cy_angled, i.sx, i.sy, i.ex, i.ey));
        double a2 = std::abs(AREA(cx_angled, cy_angled, i.sx, i.sy, cx, cy));
        double a3 = std::abs(AREA(cx_angled, cy_angled, i.ex, i.ey, cx, cy)); //triangles formed between incremented coords and other points
        if (round_3dp(area) != round_3dp(a1 + a2 + a3)) continue; //player is facing the point if the areas are equal
        double det = A_LC(i.sy, i.ey) * B_LC(cx_angled, cx) - B_LC(i.sx, i.ex) * A_LC(cy_angled, cy);
        double xDet = C_LC(i.sx, i.sy, i.ex, i.ey) * B_LC(cx_angled, cx) - B_LC(i.sx, i.ex) * C_LC(cx_angled, cy_angled, cx, cy);
        double yDet = A_LC(i.sy, i.ey) * C_LC(cx_angled, cy_angled, cx, cy) - C_LC(i.sx, i.sy, i.ex, i.ey) * A_LC(cy_angled, cy);
        if (det) { // if determinant > 0
            float dist = std::sqrt(std::pow(cx - (xDet / det), 2) + std::pow(cy - (yDet / det), 2)) * std::cos(cAngle - angle); //calculate distance between centerpoint and line intersections, using Cramer's rule
            if (dist < ti.dist || ti.dist == -1.0) ti = { dist, i.r, i.g, i.b }; // if the wall is closer than the current or hasn't been set
        }
    }
    return ti;
}
