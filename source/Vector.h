#ifndef AT_Vector_h
#define AT_Vector_h

#define _USE_MATH_DEFINES
#include <math.h>

struct Vector2d {
public:
    float x;
    float y;
    
    Vector2d() {
        x = y = 0;
    }
    
    Vector2d(float x, float y) {
        this->x = x;
        this->y = y;
    }
    
    Vector2d(Vector2d const &v) {
        x = v.x;
        y = v.y;
    }

    void set(float x, float y) {
        this->x = x;
        this->y = y;
    }
    
    void set(Vector2d v) {
        x = v.x;
        y = v.y;
    }
    
    static Vector2d zero() {
        return Vector2d();
    }
    
    static Vector2d one() {
        return Vector2d(1, 1);
    }
    
    void inverse() {
        x *= -1;
        y *= -1;
    }
    
    void add(float vx, float vy) {
        x += vx;
        y += vy;
    }
    
    void add(Vector2d v) {
        x += v.x;
        y += v.y;
    }
    
    void mul(float v) {
        x *= v;
        y *= v;
    }
    
    void mul(Vector2d v) {
        x *= v.x;
        y *= v.y;
    }
    
    void minLimit(float limit) {
        float size = dot(Vector2d(x, y));
        if(size < limit * limit) {
            float sq = sqrtf(size);
            x = (x / sq) * limit;
            y = (y / sq) * limit;
        }
    }
    
    void maxLimit(float limit) {
        float size = dot(Vector2d(x, y));
        if(size > limit * limit) {
            float sq = sqrtf(size);
            x = (x / sq) * limit;
            y = (y / sq) * limit;
        }
    }
    
    Vector2d operator+(const Vector2d &v) const {
        return Vector2d(x + v.x, y + v.y);
    }
    
    Vector2d operator-(const Vector2d &v) const {
        return Vector2d(x - v.x, y - v.y);
    }
    
    Vector2d operator*(const float v) const {
        return Vector2d(x * v, y * v);
    }
    
    Vector2d operator/(const float v) const {
        if(v == 0) return Vector2d(0, 0);
        else return Vector2d(x / v, y / v);
    }
    
    static float dot(Vector2d v) {
        return v.x * v.x + v.y * v.y;
    }
    
    static float dot(Vector2d v1, Vector2d v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }
    
    static float cross(Vector2d v1, Vector2d v2) {
        return v1.x * v2.y - v1.y * v2.x;
    }
    
    static float lengthSqrt(Vector2d v1, Vector2d v2) {
        Vector2d d = v1 - v2;
        return d.x * d.x + d.y * d.y;
    }
    
    static float length(Vector2d v1, Vector2d v2) {
        Vector2d d = v1 - v2;
        return sqrtf(d.x * d.x + d.y * d.y);
    }
    
    static Vector2d normalize(Vector2d v) {
        float l = sqrtf(dot(v));
        return Vector2d(v.x / l, v.y / l);
    }
    
    static Vector2d prep(Vector2d v) {
        return Vector2d(-v.y, v.x);
    }
    
    Vector2d prep() const {
        return Vector2d(-y, x);
    }
    
    static Vector2d neg(Vector2d v) {
        return Vector2d(-v.x, -v.y);
    }
    
    Vector2d neg() const {
        return Vector2d(-x, -y);
    }
    
    Vector2d rotate(const Vector2d v, float radian) const {
        float c = cosf(radian);
        float s = sinf(radian);
        return Vector2d(v.x * c - v.y * s, v.x * s + v.y * c);
    }
};

struct Vector3d {
    
public:
    float x, y, z;
    
    Vector3d() {
        x = y = z = 0;
    }
    
    Vector3d(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    Vector3d(Vector3d const &v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    
    void set(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    void set(Vector3d v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
};

#endif
