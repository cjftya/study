#ifndef AT_Agent_h
#define AT_Agent_h

#include "Shape.h"
#include "SearchPointDNA.h"

#define AGENT_POINT_NUM 5

class Agent : public Shape
{
private:
    SearchPointDNA *dna;
    Vector2d target;
    Vector3d color;
    float handlingRange;
    float size;
    float maxSpeed;
    float maxForce;
    
    virtual void syncShapeMap() {
        float size3 = size / 3;
        float size5 = size / 5;
        guide[0].set(centroid.x, centroid.y + size);
        guide[1].set(centroid.x - size3, centroid.y - size5);
        guide[2].set(centroid.x, centroid.y);
        guide[3].set(centroid.x + size3, centroid.y - size5);
        guide[4].set(centroid.x, centroid.y + guide[0].y + handlingRange);
    }
public:
    float dnaValue[2];
    
    Agent(){}
    Agent(float x, float y, float size, float angle, float handleRange, Vector3d color){
        this->color.set(color);
        maxSpeed = 4.0f;
        maxForce = 0.1f;
        
        pos.set(x, y);
        this->size = size;
        handlingRange = handleRange;
        
        guide = std::vector<Vector2d>(AGENT_POINT_NUM);
        vertex = std::vector<Vector2d>(AGENT_POINT_NUM);
        syncShapeMap();
        
        glPointSize(3.0f);
        
        this->angle = angle2Rad(angle);
        initialize(pos, this->angle);
        
        dna = new SearchPointDNA();
        
        dnaValue[0] = randomValue(-3, 3) * 0.1f;
        dnaValue[1] = randomValue(-3, 3) * 0.1f;
    }
    
    void fitness() {
        dna->setTargetData(target, pos);
        dna->fitness();
    }
    
    void reset(Vector2d pos) {
        vel = Vector2d::zero();
        accel = Vector2d::zero();
        this->pos.set(pos);
        angle = 0;
        initialize(pos, this->angle);
    }
    
    void simulateUpdate(int lifeCount) {
        Vector2d f = dna->getGenesAt(lifeCount);
        f.maxLimit(0.1f);
        applyForce(f);
        updateMain(0);
        angle = atan2f(vel.y, vel.x) - (M_PI / 2);
    }
    
    virtual void update(float delta) {
        updateMain(delta);
        angle = atan2f(vel.y, vel.x) - (M_PI / 2);
    }
    
    void setColor(Vector3d v) {
        color.set(v);
    }
    
    void targetHandling(float x, float y) {
        Vector2d n = Vector2d::normalize(Vector2d(x, y) - pos);
        Vector2d f = (n * maxSpeed) - vel;
        f.maxLimit(maxForce);
        applyForce(f);
    }
    
    Vector2d getHandingForce(float x, float y) {
        Vector2d n = Vector2d::normalize(Vector2d(x, y) - pos);
        Vector2d f = (n * maxSpeed) - vel;
        f.maxLimit(maxForce);
        return f;
    }
    
    Vector2d getTargetPointer() {
        return vertex[4];
    }
    
    float getSize() {
        return size;
    }
    
    float getMaxSpeed() {
        return maxSpeed;
    }
    
    float getMaxForce() {
        return maxForce;
    }
    
    DNA* getDNA() {
        return dna;
    }
    
    void setTarget(Vector2d t) {
        target.set(t);
    }
    
    virtual void draw() {
        glColor3f(color.x, color.y, color.z);
        glBegin(GL_POLYGON);
        for(int i=0;i<AGENT_POINT_NUM - 1;i++) {
            glVertex3f(vertex[i].x, vertex[i].y, 0.0f);
        }
        glEnd();
    }
};


#endif
