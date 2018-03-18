#ifndef AT_Load_h
#define AT_Load_h

#include "Vector.h"

class Load {
private:
    std::vector<Vector2d> drawPoint;
    Vector2d startP;
    Vector2d endP;
    Vector2d normal;
    Vector2d projPoint;
    Vector3d color;
    float radius;
    float length;
    
public:
    Load(){}
    Load(Vector2d start, Vector2d end, float radius, Vector3d color) {
        startP.set(start);
        endP.set(end);
        this->color = color;
        projPoint = startP;
        
        Vector2d d = end - start;
        normal = Vector2d::normalize(d);
        length = Vector2d::length(startP, endP);
        this->radius = radius;
        
        Vector2d prepNormal = normal.prep();
        drawPoint = std::vector<Vector2d>(4);
        drawPoint[0] = start + (prepNormal * -radius);
        drawPoint[1] = start + (prepNormal * radius);
        drawPoint[2] = end + (prepNormal * radius);
        drawPoint[3] = end + (prepNormal * -radius);
    }
    
    Vector2d getProjectionPoint(float x, float y) {
        Vector2d d = Vector2d(x, y) - startP;
        float dist = Vector2d::dot(d, normal);
        if(dist < 0) {
            return startP;
        } else if(dist > length) {
            return endP;
        } else {
            return startP + (normal * dist);
        }
    }
    
    void update(Agent* agent) {
        Vector2d agentPoint = agent->getTargetPointer();
        projPoint = getProjectionPoint(agentPoint.x, agentPoint.y);
        float dist = Vector2d::lengthSqrt(agentPoint, projPoint);
        float size = radius - 5;

        if(dist > size * size) {
            agent->targetHandling(projPoint.x, projPoint.y);
        } else {
            agent->vel.minLimit(agent->getMaxSpeed());
        }
    }
    
    void draw() {
        glColor3f(color.x, color.y, color.z);
        glBegin(GL_POLYGON);
        for(int i=0;i<drawPoint.size();i++) {
            glVertex3f(drawPoint[i].x, drawPoint[i].y, 0.0f);
        }
        glEnd();
        
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POINTS);
        glVertex3f(projPoint.x, projPoint.y, 0.0f);
        glEnd();
    }
};

#endif
