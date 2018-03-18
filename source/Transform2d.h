#ifndef AT_Transform2d_h
#define AT_Transform2d_h

#include "Vector.h"

struct Transform2d {
public:
    Vector2d t;
    float cos;
    float sin;
    
    Transform2d() {
        identity();
    }
    
    Transform2d(const Vector2d pos, float radian) {
        t = pos;
        cos = cosf(radian);
        sin = sinf(radian);
    }
    
    void set(const Vector2d pos, float radian) {
        t = pos;
        cos = cosf(radian);
        sin = sinf(radian);
    }
    
    void setRotation(float radian) {
        if(radian == 0) {
            cos = 1;
            sin = 0;
        }
        else {
            cos = cosf(radian);
            sin = sinf(radian);
        }
    }
    
    void setPosition(const Vector2d pos) {
        t = pos;
    }
    
    void identity() {
        t = Vector2d().zero();
        cos = 1;
        sin = 0;
    }
    
    Vector2d rotate(const Vector2d v) const {
        return Vector2d(v.x * cos - v.y * sin, 
                        v.x * sin + v.y * cos);
    }
    
    Vector2d transform(const Vector2d v) const {
        return Vector2d(v.x * cos - v.y * sin + t.x,
                        v.x * sin + v.y * cos + t.y);
    }
};

#endif
