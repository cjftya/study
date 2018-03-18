#ifndef AT_FeedObjects_h
#define AT_FeedObjects_h

#include "Agent.h"

class FeedObjects {
private:
    std::vector<Agent> agentList;
    std::vector<Vector2d> foodList;
    std::vector<Vector2d> poisonList;
    
public:
    FeedObjects() {
    }
    
    FeedObjects(int size) {
        srand((unsigned int)time(0));
        
        agentList = std::vector<Agent>(3);
        for(int i=0;i<agentList.size();i++) {
            agentList[i] = Agent(rand()%850 + 50, rand()%550 + 50, 10, 0, 40, Vector3d(1,0,0));
        }
        
        for(int i=0;i<size;i++) {
            foodList.push_back(Vector2d(rand()%850 + 50, rand()%550 + 50));
            poisonList.push_back(Vector2d(rand()%850 + 50, rand()%550 + 50));
        }
    }
    
    int getClosetFood(Vector2d pos) {
        int index = -1;
        int min = 999999;
        for(int i=0;i<foodList.size();i++) {
            if(foodList[i].x == 0) {
                continue;
            }
            
            float dist = Vector2d::lengthSqrt(foodList[i], pos);
            float rsum = agentList[i].getSize() + 10;
            if(dist < rsum * rsum) {
                foodList[i].set(0, 0);
            }
            if(min > dist) {
                min = dist;
                index = i;
            }
        }
        return index;
    }
    
    int getClosetPoison(Vector2d pos) {
        int index = -1;
        int min = 999999;
        for(int i=0;i<poisonList.size();i++) {
            float dist = Vector2d::lengthSqrt(poisonList[i], pos);
            if(min > dist) {
                min = dist;
                index = i;
            }
        }
        return index;
    }
    
    void update() {
        for(int i=0;i<agentList.size();i++){
            int foodIndex = getClosetFood(agentList[i].pos);
            int poisonIndex = getClosetPoison(agentList[i].pos);
            Vector2d foodF = agentList[i].getHandingForce(foodList[foodIndex].x, foodList[foodIndex].y);
            Vector2d poisonF = agentList[i].getHandingForce(poisonList[poisonIndex].x, poisonList[poisonIndex].y);
            
            foodF.mul(agentList[i].dnaValue[0]);
            poisonF.mul(agentList[i].dnaValue[1]);
            
            agentList[i].applyForce(foodF);
            agentList[i].applyForce(poisonF);
            agentList[i].force.maxLimit(4.0f);
        
            agentList[i].update(0);
        }
    }
    
    void draw() {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_POINTS);
        for(Vector2d& p : poisonList) {
            glVertex3f(p.x, p.y, 0.0f);
        }
        glEnd();
        
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_POINTS);
        for(Vector2d& p : foodList) {
            glVertex3f(p.x, p.y, 0.0f);
        }
        glEnd();
        
        for(Agent& a : agentList) {
            a.draw();
        }
    }
    
};

#endif
