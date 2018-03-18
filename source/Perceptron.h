#ifndef AT_Perceptron_h
#define AT_Perceptron_h

#include "Vector.h"

class Perceptron {
private:
    std::vector<float> weightList;
    float c;
    
public:
    Perceptron() {
        
    }
    
    Perceptron(int n, int c) {
        for(int i=0;i<n;i++) {
            weightList.push_back(randomValue(-3, 3));
        }
        this->c = c;
    }
    
    Vector2d feedForward(Vector2d forces[]) {
        Vector2d sum;
        for(int i=0;i<weightList.size();i++) {
            forces[i].mul(weightList[i]);
            sum.add(forces[i]);
        }
        return sum;
    }
    
    void train(Vector2d forces[], Vector2d error) {
        for(int i=0;i<weightList.size();i++) {
            weightList[i] += c * error.x * forces[i].x;
            weightList[i] += c * error.y * forces[i].y;
        }
    }
    
};

#endif
