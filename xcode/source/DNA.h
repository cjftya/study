
#ifndef AT_DNA_h
#define AT_DNA_h

class DNA {
private:
    
protected:
    float fitnessValue;
    float mutatePercent;
    
public:
    DNA() {
        fitnessValue = 0.0f;
        mutatePercent = 0.0f;
    }
    
    virtual void initialize(int size) {
        
    }
    
    virtual DNA* crossOver(DNA *child, DNA *partner) {
        return 0;
    }
    
    virtual void mutate(float mutatePercent) {
        
    }
    
    virtual void fitness() {
        
    }
    
    virtual void copy(DNA *refDna) {
        
    }
    
    virtual DNA* clone() {
        return 0;
    }
    
    float getFitness() {
        return fitnessValue;
    }
    
    void setFitness(float value) {
        fitnessValue = value;
    }
    
    float getMutateRate() {
        return mutatePercent;
    }
    
    void setMutateRate(float value) {
        mutatePercent = value;
    }
};

#endif
