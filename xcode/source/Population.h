#ifndef AT_Population_h
#define AT_Population_h

class Population {
private:
    std::vector<DNA*> matingPool;
    std::vector<Agent> population;
    std::vector<DNA*> dnaBuffer;
    
public:
    Population() {
    }
    
    Population(int size, int dnaSize) {
        for(int i=0;i<size;i++) {
            population.push_back(Agent(150, 200, 10, 0, 40, Vector3d(1,0,0)));
            population[i].getDNA()->initialize(dnaSize);
            dnaBuffer.push_back(population[i].getDNA()->clone());
        }
    }
    
    void fitness() {
        for(int i=0;i<population.size();i++) {
            population[i].fitness();
        }
    }
    
    void selection() {
        matingPool.clear();
        for(int i=0;i<population.size();i++) {
            float f = population[i].getDNA()->getFitness();
            int n = f * 10000;
            for(int k=0;k<n;k++) {
                matingPool.push_back(population[i].getDNA());
            }
        }
    }
    
    void repoduction() {
        for(int i=0;i<population.size();i++) {
            int a = rand() % matingPool.size();
            int b = rand() % matingPool.size();
            DNA *partnerA = matingPool[a];
            DNA *partnerB = matingPool[b];
            DNA *child = partnerA->crossOver(dnaBuffer[i], partnerB);
            child->mutate(1.0f);
        }
        for(int i=0;i<population.size();i++) {
            population[i].getDNA()->copy(dnaBuffer[i]);
        }
    }
    
    void update(int lifeCount) {
        for(int i=0;i<population.size();i++) {
            population[i].simulateUpdate(lifeCount);
        }
    }
    
    void setTarget(Vector2d t) {
        for(int i=0;i<population.size();i++) {
            population[i].setTarget(t);
        }
    }
    
    void reset() {
        for(int i=0;i<population.size();i++) {
            population[i].reset(Vector2d(150, 200));
        }
    }
    
    void draw() {
        for(int i=0;i<population.size();i++) {
            population[i].draw();
        }
    }
};

#endif

