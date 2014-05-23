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
#include "glm/glm.hpp"

int sirina = 400, visina = 400;
int misX = 0, misY = 0;

typedef struct {
    int x;
    int y;
    int z;
} iTocka3D;

std::vector<iTocka3D> poligon;
iTocka3D ociste, glediste;
int n;
glm::mat4 T, P;

void reshape(int, int);
void display();
void renderScene();
void mousePressedOrReleased(int, int, int, int);
void mouseMoved(int, int);
void keyPressed(unsigned char, int, int);

int main(int argc, char * argv[])
{
    freopen("/Users/Nino/Programming/irg/IRG/vjezba5poligon/test1.in", "r", stdin);
    scanf("%d %d %d", &ociste.x, &ociste.y, &ociste.z);
    scanf("%d %d %d", &glediste.x, &glediste.y, &glediste.z);
    scanf("%d", &n);
    for(int i = 0 ; i < n; ++i) {
        iTocka3D t;
        scanf("%d %d %d", &t.x, &t.y, &t.z);
        poligon.push_back(t);
    }
    
    glm::vec4 G = glm::vec4(glediste.x, glediste.y, glediste.z, 1);
    
    glm::mat4x4 T1 = glm::mat4x4(1, 0, 0, 0,
                               0, 1, 0, 0,
                               0, 0, 1, 0,
                               -ociste.x, -ociste.y, -ociste.z, 1);
    
    glm::vec4 G1 = T1 * G;
    
    double sina = G1[1] / sqrt(G1[0]*G1[0] + G1[1]*G1[1]);
    double cosa = G1[0] / sqrt(G1[0]*G1[0] + G1[1]*G1[1]);
    
    glm::mat4x4 T2 = glm::mat4x4(cosa, -sina, 0, 0,
                                 sina, cosa, 0, 0,
                                 0, 0, 1, 0,
                                 0, 0, 0, 1);
    
    glm::vec4 G2 = T2 * G1;
    
    double sinb = G2[0] / sqrt(G2[0]*G2[0] + G2[2]*G2[2]);
    double cosb = G2[2] / sqrt(G2[0]*G2[0] + G2[2]*G2[2]);
    
    glm::mat4x4 T3 = glm::mat4(cosb, 0, sinb, 0,
                               0, 1, 0, 0,
                               -sinb, 0, cosb, 0,
                               0, 0, 0, 1);
    
    glm::vec4 G3 = T3 * G2;
    
    glm::mat4 T4 = glm::mat4x4( 0, -1, 0, 0,
                               1, 0, 0, 0,
                               0, 0, 1, 0,
                               0, 0, 0, 1);
    
    glm::mat4 T5 = glm::mat4x4( -1, 0, 0, 0,
                               0, 1, 0, 0,
                               0, 0, 1, 0,
                               0, 0, 0, 1);
    
    T = T5 * T4 * T3 * T2 * T1;
    
    double H = G3[2];
    P = glm::mat4x4( 1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 0, 1/H,
                    0, 0, 0, 0);
    
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(sirina, visina);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Vjezba 5");
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
//    glLoadIdentity();
    // crtanje scene:
    renderScene();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    sirina = width; visina = height;
    
    glDisable(GL_DEPTH_TEST);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
	gluOrtho2D(-width/2, width/2, -height/2, height/2);
    glMatrixMode(GL_MODELVIEW);
}

void renderScene() {
    glPointSize(1.0f);
    
    glColor3f(0.0f, 0.0f, 1.0f);
    
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glm::vec4 t = glm::vec4(poligon[i].x, poligon[i].y, poligon[i].z, 1) * T * P;
        printf("%f %f %f\n", t[0], t[1], t[2]);
        glVertex3f(t[0], t[1], t[2]);
    }
    glEnd();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    
    glFlush();
}

void mousePressedOrReleased(int button, int state, int x, int y) {
}

void keyPressed(unsigned char key, int x, int y) {
}

void mouseMoved(int x, int y) {
    misX = x;
    misY = y;
    glutPostRedisplay();
}
