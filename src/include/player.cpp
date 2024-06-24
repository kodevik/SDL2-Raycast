#include "player.hpp"
#include <cmath>
#include <iostream>

Player::Player() {}
Player::~Player() {}

void Player::init(float xPos, float yPos, float initAngle, float initSpeed) {
    x = xPos;
    y = yPos;
    angle = initAngle;
    speed = initSpeed;
}

void Player::move(int f, int l) {
    if (f == 0) {
        x -= speed * -l * std::sin(angle);
        y -= speed * l * std::cos(angle);
    }
    else {
        x -= speed * -f * std::cos(-angle);
        y -= speed * f * std::sin(-angle);
    }
}