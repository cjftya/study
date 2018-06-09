#ifndef AT_Shape_h
#define AT_Shape_h

#include "Vector.h"
#include "Transform2d.h"

class Shape {
public:
    Transform2d trans;
    std::vector<Vector2d> guide;
    std::vector<Vector2d> vertex;
    Vector2d centroid;
    Vector2d pos;
    Vector2d vel;
    Vector2d accel;
    Vector2d force;
    float friction;
    float angle;
    float angleVel;
    float angleFriction;
    float mass;
    float invMass;
    
    Shape() {
        angle = 0;
        angleVel = 0;
        mass = 1;
        invMass = 1;
        friction = 0.995f;
        angleFriction = 0.95f;
        centroid = Vector2d::zero();
        vel = Vector2d::zero();
        accel = Vector2d::zero();
        force = Vector2d::zero();
    }
    
    virtual void syncShapeMap() = 0;
    virtual void draw() = 0;
    virtual void update(float delta) = 0;
    
    void initialize(Vector2d pos, float angle) {
        trans = Transform2d(pos, angle);
        syncBody();
    }
    
    void applyForce(Vector2d v) {
        accel.add(v * invMass);
    }

    void updateMain(float deleta) {
        angleVel *= angleFriction;
        angle += angleVel;
        
        vel.add(accel);
   //     vel.mul(friction);
        pos.add(vel);
        
        accel = Vector2d::zero();
        
        syncBody();
    }
    
private:
    void syncBody() {
        trans.setRotation(angle);
        trans.setPosition(pos - trans.rotate(centroid));
        for(int i=0;i<vertex.size();i++) {
            vertex[i].set(trans.transform(guide[i]));
        }
    }
    
protected:
};

#endif
