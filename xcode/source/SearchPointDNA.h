#ifndef AT_SearchPointDNA_h
#define AT_SearchPointDNA_h

#include "DNA.h"

class SearchPointDNA : public DNA {
private:
    std::vector<Vector2d> genes;
    Vector2d target;
    Vector2d location;
    
    Vector2d randomVector() {
        float radian = angle2Rad(rand()%360 + 1);
        float speed = rand()%10 + 1;
        return Vector2d(cosf(radian) * speed, sinf(radian) * speed);
    }
    
public:
    SearchPointDNA() {
    }
    
    Vector2d getGenesAt(int index) {
        return genes[index];
    }
    
    void setTargetData(Vector2d target, Vector2d pos) {
        this->target = target;
        this->location = pos;
    }

    virtual void initialize(int size) {
        fitnessValue = 0.0f;
        mutatePercent = 0.0f;
        genes = std::vector<Vector2d>(size);
        for(int i=0;i<genes.size();i++) {
            genes[i] = randomVector();
        }
    }
    
    virtual void fitness() {
        float dist = Vector2d::length(target, location);
        float v = 1 / dist;
        fitnessValue = v;
    }
    
    virtual DNA* crossOver(DNA *child, DNA *partner) {
        SearchPointDNA *p = static_cast<SearchPointDNA*>(partner);
        SearchPointDNA *c = static_cast<SearchPointDNA*>(child);
        int midPoint = rand() % genes.size();
        for(int i=0;i<genes.size();i++) {
            c->genes[i] = (i > midPoint) ? genes[i] : p->genes[i];
        }
        return c;
    }
    
    virtual void mutate(float mutatePercent) {
        this->mutatePercent = mutatePercent;
        
        for(int i=0;i<genes.size();i++) {
            if((rand() % 100 + 1) <= mutatePercent) {
                genes[i] = randomVector();
            }
        }
    }
    
    virtual DNA* clone() {
        SearchPointDNA *c = new SearchPointDNA();
        c->initialize((int)genes.size());
        c->copy(this);
        return c;
    }
    
    virtual void copy(DNA *refDna) {
        SearchPointDNA *r = static_cast<SearchPointDNA*>(refDna);
        for(int i=0;i<genes.size();i++) {
            genes[i].set(r->genes[i]);
        }
        target = r->target;
        location = r->location;
        setFitness(r->getFitness());
        setMutateRate(r->getMutateRate());
    }
};

#endif
