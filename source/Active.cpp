#include "Active.h"

void loaded() {
    srand((unsigned int)time(NULL));
    
    outText.fontColor(Vector3d(1.0f, 1.0f, 1.0f));
    outText.fontWeight(0.1f);
    outText.fontWidth(0.3f);
    
    fpsView.initialize();
    
    isClick = false;
    
    //============================
    world = World(Vector2d(0, -0.05f));
}

void initData() {
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1000.0, 0.0, 700.0, 0.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    loaded();
}

void drawScene() {
    //outText.drawText(100, 100, 0, "asdsafsaf1r124");
    world.draw();

    glFlush();
}
/*
 void MyIdle() {
	glutPostRedisplay();
 }
 */

void MyTimer(int value) {
    //fpsView.update();
    world.update(1.0f);
    if(isClick) {
        world.debugMouse(mx, my);
    }
    glutPostRedisplay();
    glutTimerFunc(10,MyTimer,1);
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawScene();
    
    glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'a':
            world.debug();
            break;
        case 'd':
            break;
    }
    glutPostRedisplay();
}

void MyMouseClick(GLint Button, GLint State, GLint x, GLint y) {
    mx = x;
    my = screenHeight - y;
    switch (State) {
        case GLUT_DOWN:
            switch (Button) {
            case GLUT_LEFT_BUTTON:
                isClick = true;
                break;
            case GLUT_RIGHT_BUTTON:
                break;
        }
            break;
        case GLUT_UP:
            switch (Button) {
            case GLUT_LEFT_BUTTON:
                isClick = false;
                break;
            case GLUT_RIGHT_BUTTON:
                break;
        }
        break;
    }
    //	glutPostRedisplay();
}

void MyMouseMove(GLint x, GLint y) {
    if(isClick) {
        mx = x;
        my = screenHeight - y;
    }
    //	glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(screenWidth,screenHeight);
    glutInitWindowPosition(0,0);
    glutCreateWindow("openGL fun");
    
    initData();
    
    glutDisplayFunc(MyDisplay);
    glutMouseFunc(MyMouseClick);
    glutMotionFunc(MyMouseMove);
    glutKeyboardFunc(MyKeyboard);
    //glutIdleFunc(MyIdle);
    glutTimerFunc(10, MyTimer, 1);
    glutMainLoop();
    return 0;
}
