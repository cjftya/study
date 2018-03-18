//
//  BasicLine.h
//  Hello
//
//  Created by cjftya on 2014. 9. 25..
//  Copyright (c) 2014년 cjftya. All rights reserved.
//

#ifndef Hello_BasicLine_h
#define Hello_BasicLine_h

#include "Setting.h"

#define line_num 2

struct DrawLine
{
private:
    Vector3d color;
    Vector2d r_pos[line_num];
    float width;
public:
    void DataInit(Vector2d p1, Vector2d p2, float width, Vector3d color_v){
        color.DataInit(color_v);
        r_pos[0].DataInit(p1);
        r_pos[1].DataInit(p2);
        this->width = width;
    }
    
    void SetWidth(float v)
    {
        width = v;
        glLineWidth(width);
    }
    
    void SetColor(Vector3d color_v)
    {
        color.DataInit(color_v);
    }
    
    void SetPos_P1(Vector2d v)
    {
        r_pos[0].DataInit(v.x, v.y);
    }

    void SetPos_P2(Vector2d v)
    {
        r_pos[1].DataInit(v.x, v.y);
    }
    
    void DrawSegment()
    {
        glColor3f(color.x, color.y, color.z);
        glBegin(GL_LINES);
        glVertex3f(r_pos[0].x, r_pos[0].y, 0.0f);
        glVertex3f(r_pos[1].x, r_pos[1].y, 0.0f);
        glEnd();
    }
};

#endif
