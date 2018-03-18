#ifndef AT_FPScounter_h
#define AT_FPScounter_h

struct FPScounter {
private:
    int frameCount, currentTime, previousTime;
    float fps;
    
    void calculateFPS() {
        frameCount++;
        currentTime = glutGet(GLUT_ELAPSED_TIME);
        int timeInterval = currentTime - previousTime;
        
        if(timeInterval > 1000) {
            fps = frameCount / (timeInterval / 1000.0f);
            previousTime = currentTime;
            frameCount = 0;
        }
        cout<<fps<<endl;
    }
public:
    void initialize() {
        frameCount = previousTime = currentTime = 0;
        fps = 0;
    }
    
    void update() {
        calculateFPS();
    }
    
    float getFPS() {
        return fps;
    }
};

#endif
