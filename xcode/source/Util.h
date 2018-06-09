#ifndef AT_Util_h
#define AT_Util_h

#define _USE_MATH_DEFINES
#include <math.h>

inline float angle2Rad(float v) {
    return (v / 180.0f) * M_PI;
}

inline float rad2Anlge(float v) {
    return (v / M_PI) * 180.0f;
}

inline float clamp(float v, float min_n, float max_n) {
    return v < min_n ? min_n : (v > max_n ? max_n : v);
}

inline int randomValue(int start, int end) {
    srand((unsigned int)time(0));
    //1 ~ 10
    //10 ~ 25
    //-5 ~ 5 == 0 ~ 10
    //-2 ~ 5 == 0 ~ 7
    //0 ~ 10
    int r = (end - start) + 1;
    return (rand() % r) + start;
}
#endif
