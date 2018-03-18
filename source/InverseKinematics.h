#ifndef InverseKinematics_h
#define InverseKinematics_h

#include "Segment.h"

class InverseKinematics {
private:
    std::vector<Segment> segmentPool;
    Vector2d headerPoint;
    Vector2d fixPoint;
    bool isFixed;
    
    void focus(float tx, float ty) {
        segmentPool[segmentPool.size()-1].focus(tx, ty);
        for(int i=segmentPool.size()-2;i>=0;i--) {
            segmentPool[i].focus(segmentPool[i+1].getPin().x, segmentPool[i+1].getPin().y);
        }
    }
    
public:
    InverseKinematics() {
    }
    
    InverseKinematics(Vector2d pos, int segCount, float length, Vector3d color) {
        headerPoint = Vector2d::zero();
        fixPoint = Vector2d::zero();
        isFixed = false;
        
        segmentPool = std::vector<Segment>(segCount);
        for(int i=0;i<segCount;i++) {
            Vector2d p = Vector2d(pos) + Vector2d(length * i, 0);
            segmentPool[i] = Segment(p, 0, length, color);
            if(i == segCount - 1) {
                headerPoint.set(segmentPool[i].getPinOther());
            }
        }
    }
    
    void setFixPoint(Vector2d fix) {
        fixPoint.set(fix);
    }
    
    void enableFixedPoint(bool enable) {
        isFixed = enable;
    }
    
    void target(float tx, float ty) {
        Vector2d d = Vector2d(tx, ty) - headerPoint;
        d.mul(0.3f);
        headerPoint.add(d);
    }
    
    void update() {
        focus(headerPoint.x, headerPoint.y);
        for(int i=0;i<segmentPool.size();i++) {
            segmentPool[i].update();
        }
        if(isFixed) {
            segmentPool[0].setPin(fixPoint);
            for(int i=1;i<segmentPool.size();i++) {
                segmentPool[i].setPin(segmentPool[i-1].getPinOther());
            }
        }
    }
    
    void draw() {
        for(int i=0;i<segmentPool.size();i++) {
            segmentPool[i].draw();
        }
    }
};

#endif
