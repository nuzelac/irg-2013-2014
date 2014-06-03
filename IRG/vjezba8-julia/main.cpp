//
//  main.cpp
//  vjezba4
//
//  Created by Nino Uzelac on 08/04/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include <iostream>
#include <vector>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <cmath>

int sirina = 400, visina = 400;
int misX = 0, misY = 0;
int eps = 100;
int m = 16;
double umin = -1;
double umax = 1;
double vmin = -1.2;
double vmax = 1.2;
double creal = 0.32;
double cimag = 0.043;

void reshape(int, int);
void display();
void renderScene();
void mousePressedOrReleased(int, int, int, int);
void mouseMoved(int, int);
void keyPressed(unsigned char, int, int);

const int paletteSize = 128;
GLfloat palette[paletteSize][3];

void createPalette(){
    for(int i=0; i < 32; i++){
        palette[i][0] = (8*i)/(GLfloat)255;
        palette[i][1] = (128-4*i)/(GLfloat)255;
        palette[i][2] = (255-8*i)/(GLfloat)255;
    }
    for(int i=0; i < 32; i++){
        palette[32+i][0] = (GLfloat)1;
        palette[32+i][1] = (8*i)/(GLfloat)255;
        palette[32+i][2] = (GLfloat)0;
    }
    for(int i=0; i < 32; i++){
        palette[64+i][0] = (128-4*i)/(GLfloat)255;
        palette[64+i][1] = (GLfloat)1;
        palette[64+i][2] = (8*i)/(GLfloat)255;
    }
    for(int i=0; i < 32; i++){
        palette[96+i][0] = (GLfloat)0;
        palette[96+i][1] = (255-8*i)/(GLfloat)255;
        palette[96+i][2] = (8*i)/(GLfloat)255;
    }
}


int main(int argc, char * argv[])
{
    createPalette();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(sirina, visina);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Vjezba 8");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mousePressedOrReleased);
    glutPassiveMotionFunc(mouseMoved);
    glutKeyboardFunc(keyPressed);
    glutMainLoop();
    return 0;
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // crtanje scene:
    renderScene();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    sirina = width; visina = height;
    
    glDisable(GL_DEPTH_TEST);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width-1, height-1, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
}

void renderScene() {
    glPointSize(1.0f);
    
    glBegin(GL_POINTS);
    for(int x0 = 0; x0 < sirina; ++x0) {
        for(int y0 = 0; y0 < visina; ++y0) {
            double u0 = (umax - umin) * x0 / sirina + umin;
            double v0 = (vmax - vmin) * y0 / visina + vmin;
            
            int k = -1;
            double zreal = u0, zimag = v0;
            double r;
            
            do {
                k = k + 1;
                double zrealnovi = zreal * zreal - zimag * zimag + creal;
                double zimagnovi = 2 * zreal * zimag + cimag;
                zreal = zrealnovi;
                zimag = zimagnovi;
                
                r = sqrt(zreal * zreal + zimag * zimag);
            } while(r < eps && k < m);
            
            double boja = (double)k / m;
            if(boja >= 1) boja = 0.0;
            glColor3d(boja, boja, boja);
            glVertex2i(x0, visina - y0);
        }
    }
    glEnd();
    
}

void mousePressedOrReleased(int button, int state, int x, int y) {
}

void keyPressed(unsigned char key, int x, int y) {
}

void mouseMoved(int x, int y) {
    misX = x;
    misY = y;
    //    glutPostRedisplay();
}