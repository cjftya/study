#ifndef AT_Evolution_h
#define AT_Evolution_h

#include "Population.h"

class Evolution {
private:
    int generation;
    int lifeCount;
    int lifeTime;
    Population population;
    Vector2d target;
    
public:
    Evolution() {
        generation = 1;
        lifeTime = 300;
        lifeCount = 0;
        
        population = Population(50, lifeTime);
    }
    
    void update() {
        if(lifeCount < lifeTime) {
            population.update(lifeCount);
            lifeCount++;
        }
        else {
            population.fitness();
            population.selection();
            population.repoduction();
            population.reset();
            lifeCount = 0;
            generation++;
        }
    }
    
    void setTarget(float x, float y) {
        target.set(x, y);
        population.setTarget(Vector2d(x, y));
    }

    
    void draw() {
        glColor3f(0.0f, 1.0f, 1.0f);
        glBegin(GL_POINTS);
        glVertex3f(target.x, target.y, 0.0f);
        glEnd();
        population.draw();
    }
};

#endif
