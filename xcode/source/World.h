#ifndef AT_World_h
#define AT_World_h

#define SHAPE_TEST 0
#define AGENT_TEST 0
#define LOAD_TEST 0
#define KINEMATICS_TEST 0
#define EVOLVE_TEST 0
#define FEED_TEST 1

#include "Circle.h"
#include "Rect.h"
#include "Agent.h"
#include "Load.h"
#include "Evolution.h"
#include "InverseKinematics.h"
#include "FeedObjects.h"
#include "Perceptron.h"

class World {
private:
    std::vector<Shape*> shapeList;
    
    Shape *circle;
    Shape *rect;
    Agent *agent;
    InverseKinematics kine;
    Load *load;
    Evolution *evolution;
    FeedObjects feedObjects;
    
    void loaded() {
        #if SHAPE_TEST
        circle = new Circle(400, 400, 20, 20, Vector3d(1,1,0));
        rect = new Rect(100, 100, 30, 30, 80, Vector3d(0,1,1));
        shapeList.push_back(circle);
        shapeList.push_back(rect);
        #endif
        
        #if AGENT_TEST
        agent = new Agent(150, 200, 10, 0, 40, Vector3d(1,0,0));
        shapeList.push_back(agent);
        #endif
        
        #if LOAD_TEST
        agent = new Agent(150, 200, 10, 0, 40, Vector3d(1,0,0));
        shapeList.push_back(agent);
        load = new Load(Vector2d(100, 300), Vector2d(650, 250), 10, Vector3d(0,0,1));
        #endif
        
        #if KINEMATICS_TEST
        kine = InverseKinematics(Vector2d(200,500), 5, 50, Vector3d(1,0,0));
        kine.enableFixedPoint(false);
        kine.setFixPoint(Vector2d(300, 300));
        #endif
        
        #if EVOLVE_TEST
        evolution = new Evolution();
        evolution->setTarget(400, 400);
        #endif
        
        #if FEED_TEST
        feedObjects = FeedObjects(10);
        #endif
    }
    
    void collisionModule() {
    }
    
    void solveModule() {
    }
    
    Vector2d g;
    
public:
    World() {
    }
    
    World(Vector2d gravity) {
        g.set(gravity);
        loaded();
    }
    
    void setGravity(Vector2d gravity) {
        g.set(gravity);
    }
    
    Vector2d getGravity() {
        return g;
    }
    
    void debug() {
        
    }
    
    void debugMouse(float x, float y) {
        #if AGENT_TEST
        agent->targetHandling(x, y);
        #endif
        
        #if KINEMATICS_TEST
        kine.target(x, y);
        #endif
        
        #if LOAD_TEST
        agent->targetHandling(x, y);
        #endif
    }
    
    void update(float delta) {
        #if LOAD_TEST
        for(Shape* s : shapeList) {
            s->update(delta);
        }
        load->update(agent);
        #endif
        
        #if AGENT_TEST
        for(Shape* s : shapeList) {
            s->update(delta);
        }
        #endif
        
        #if SHAPE_TEST
        for(Shape* s : shapeList) {
            s->update(delta);
        }
        #endif

        #if KINEMATICS_TEST
        kine.update();
        #endif
        
        #if EVOLVE_TEST
        evolution->update();
        #endif
        
        #if FEED_TEST
        feedObjects.update();
        #endif
    }
    
    void draw() {
        #if LOAD_TEST
        load->draw();
        for(Shape* s : shapeList) {
            s->draw();
        }
        #endif
        
        #if AGENT_TEST
        for(Shape* s : shapeList) {
            s->draw();
        }
        #endif
        
        #if SHAPE_TEST
        for(Shape* s : shapeList) {
            s->draw();
        }
        #endif
        
        #if KINEMATICS_TEST
        kine.draw();
        #endif
        
        #if EVOLVE_TEST
        evolution->draw();
        #endif
        
        #if FEED_TEST
        feedObjects.draw();
        #endif
    }
};

#endif
