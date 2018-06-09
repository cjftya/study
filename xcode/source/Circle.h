#ifndef AT_Circle_h
#define AT_Circle_h

#include "Shape.h"

#define CIRCLE_POINT_NUM 15

class Circle : public Shape {
private:
    Vector3d color;
    Vector2d dynamicPos[CIRCLE_POINT_NUM];
    Vector2d fixedPos[CIRCLE_POINT_NUM];
    float radius;
    
    void syncObject() {
        for(int i=0;i<CIRCLE_POINT_NUM;i++) {
            dynamicPos[i].set(fixedPos[i] + pos);
        }
    }
    
    virtual void syncShapeMap() {
        guide[0].set(centroid.x, centroid.y);
        guide[1].set(centroid.x + radius, centroid.y);
    }
public:
    Circle(){}
    Circle(float x, float y, float radius, float angle, Vector3d color){
        this->color.set(color);
        
        pos.set(x, y);
        setRadius(radius);
        syncObject();
        
        guide = std::vector<Vector2d>(2);
        vertex = std::vector<Vector2d>(2);
        syncShapeMap();
        
        this->angle = angle2Rad(angle);
        initialize(pos, this->angle);
    }
    
    void setColor(float r, float g, float b) {
        color.set(r, g, b);
    }
    
    void setRadius(float radius) {
        this->radius = radius;
        float oneSlice = (2 * M_PI) / CIRCLE_POINT_NUM;
        for(int i=0;i<CIRCLE_POINT_NUM;i++) {
            fixedPos[i].set(radius * cosf(i*oneSlice), radius * sinf(i*oneSlice));
            dynamicPos[i].set(fixedPos[i].x + pos.x, fixedPos[i].y + pos.y);
        }
    }
    
    float getRadius() {
        return radius;
    }
    
    virtual void update(float delta) {
        updateMain(delta);
        syncObject();
    }
    
    virtual void draw() {
        glColor3f(color.x, color.y, color.z);
        glBegin(GL_POLYGON);
        for(int i=0;i<CIRCLE_POINT_NUM;i++) {
            glVertex3f(dynamicPos[i].x, dynamicPos[i].y, 0.0f);
        }
        glEnd();
        
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);
        for(int i=0;i<vertex.size();i++) {
            glVertex3f(vertex[i].x, vertex[i].y, 0.0f);
        }
        glEnd();
    }
};


#endif
