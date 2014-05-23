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
} iTocka2D;

std::vector<iTocka2D> poligon;
int n;
glm::mat4 T, P;

void reshape(int, int);
void display();
void renderScene();
void mousePressedOrReleased(int, int, int, int);
void mouseMoved(int, int);
void keyPressed(unsigned char, int, int);
void compute_factors(int n, int *factors);
void draw_bezier(std::vector<iTocka2D> &v, int divs);

int main(int argc, char * argv[])
{
    freopen("/Users/Nino/Programming/irg/IRG/vjezba6/input.in", "r", stdin);
    scanf("%d", &n);
    for(int i = 0 ; i < n+1; ++i) {
        iTocka2D t;
        scanf("%d %d", &t.x, &t.y);
        poligon.push_back(t);
    }
    
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(sirina, visina);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Vjezba 6");
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
	gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

void renderScene() {
    glPointSize(1.0f);
    
    glColor3f(0.0f, 0.0f, 1.0f);
    
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < poligon.size(); i++) {
        glVertex2f(poligon[i].x, poligon[i].y);
    }
    glEnd();

    draw_bezier(poligon, 100);
    
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

void compute_factors(int n, int *factors) {
    int i, a = 1;
    
    for(i = 1; i <= n+1; i++) {
        factors[i-1] = a;
        a = a * (n-i+1) / i;
    }
}

void draw_bezier(std::vector<iTocka2D> &poligon, int divs) {
    iTocka2D p;
    int n = poligon.size() - 1;
    int *factors = new int[poligon.size()];
    double t, b;
    
    compute_factors(n, factors);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i <= divs; ++i) {
        t = 1.0 / divs * i;
        p.x = 0; p.y = 0;
        for(int j = 0; j <= n; j++) {
            if(j==0) {
                b = factors[j]*pow(1-t, n);
            } else if(j==n) {
                b = factors[j]*pow(t,n);
            } else {
                b = factors[j]*pow(t,j)*pow(1-t, n-j);
            }
            p.x += b * poligon[j].x;
            p.y += b * poligon[j].y;
        }
        glVertex2f(p.x, p.y);
    }
    glEnd();
    free(factors);
}
