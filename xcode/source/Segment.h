#ifndef AT_Segment_h
#define AT_Segment_h

#include "Shape.h"

#define SEG_POINT_NUM 2

class Segment {
private:
    Vector3d color;
    float radian;
    float length;
    Vector2d pA;
    Vector2d pB;
    
public:
    Segment() {
    }
    
    Segment(Vector2d header, float angle, float length, Vector3d color) {
        pA.set(header);
        solveB();
        
        this->color.set(color);
        this->length = length;
        radian = angle2Rad(angle);
        glLineWidth(2.0f);
    }
    
    Vector2d getPin() {
        return pA;
    }
    
    void setPin(Vector2d pos) {
        pA.set(pos);
        solveB();
    }
    
    Vector2d getPinOther() {
        return pB;
    }
    
    void solveB() {
        pB.set(pA.x + cosf(radian)*length, pA.y + sinf(radian)*length);
    }
    
    void update() {
        solveB();
    }
    
    void focus(float tx, float ty) {
        Vector2d target = Vector2d(tx, ty);
        Vector2d t = target - pA;
        radian = atan2f(t.y, t.x);
        
        Vector2d n = Vector2d::normalize(t);
        n.mul(-length);
        pA.set(target + n);
    }
    
    void draw() {
        glColor3f(color.x, color.y, color.z);
        glBegin(GL_LINES);
        glVertex3f(pA.x, pA.y, 0.0f);
        glVertex3f(pB.x, pB.y, 0.0f);
        glEnd();
    }
};

#endif
