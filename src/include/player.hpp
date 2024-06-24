#ifndef player_hpp
#define player_hpp

class Player {
public:
    Player();
    ~Player();
    void init(float xPos, float yPos, float initAngle, float initSpeed);
    void setAngle(double newAngle) { angle = newAngle; }
    void setSpeed(double newSpeed) { speed = newSpeed; }
    float getX() { return x; }
    float getY() { return y; }
    float getAngle() { return angle; }
    void move(int f, int s);
private:
    double x;
    double y;
    float angle;
    float speed;
};
#endif