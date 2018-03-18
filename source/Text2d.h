#ifndef AT_Text2d_h
#define AT_Text2d_h

struct Text2d {
private:
    float size, w;
    Vector3d color;
public:
    void fontWeight(float v) {
        w = v;
    }
    
    void fontWidth(float v) {
        size = v;
    }
    
    void fontColor(Vector3d color_v) {
        color.set(color_v);
    }
    
    void drawText(float x, float y, float z, char *str) {
        glPushMatrix();
        glLineWidth(w);
        glTranslatef(x,y,z);
        glScalef(size, size, size);
        glColor3f(color.x, color.y, color.z);
        
        for(char i=0;i<strlen(str);i++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *(str+i));
        }
        glPopMatrix();
    }
};

#endif
