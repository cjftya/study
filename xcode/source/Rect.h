#ifndef AT_Rect_h
#define AT_Rect_h

#include "Shape.h"

#define RECT_POINT_NUM 4

class Rect : public Shape
{
private:
    Vector3d color;
    float w, h;
    float hw, hh;
    
    virtual void syncShapeMap() {
        guide[0].set(centroid.x - hw, centroid.y + hh);
        guide[1].set(centroid.x - hw, centroid.y - hh);
        guide[2].set(centroid.x + hw, centroid.y - hh);
        guide[3].set(centroid.x + hw, centroid.y + hh);
    }
public:
    Rect(){}
    Rect(float x, float y, float width, float height, float angle, Vector3d color){
        this->color.set(color);
        
        pos.set(x, y);
        w = width;
        h = height;
        hw = w / 2;
        hh = h / 2;
        
        guide = std::vector<Vector2d>(RECT_POINT_NUM);
        vertex = std::vector<Vector2d>(RECT_POINT_NUM);
        syncShapeMap();
        
        this->angle = angle2Rad(angle);
        initialize(pos, this->angle);
    }
    
    virtual void update(float delta) {
        updateMain(delta);
    }
    
    void setColor(Vector3d v) {
        color.set(v);
    }
    
    virtual void draw() {
        glColor3f(color.x, color.y, color.z);
        glBegin(GL_POLYGON);
        for(int i=0;i<RECT_POINT_NUM;i++) {
            glVertex3f(vertex[i].x, vertex[i].y, 0.0f);
        }
        glEnd();
    }
};


#endif
