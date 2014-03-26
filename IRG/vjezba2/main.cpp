//
//  main.cpp
//  vjezba2
//
//  Created by Nino Uzelac on 26/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include <cstdio>
#include <cstdlib>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// model podataka
enum Boja { CRVENA, ZELENA, PLAVA, CIJAN, ZUTA, MAGENTA };
Boja boje[] = { CRVENA, ZELENA, PLAVA, CIJAN, ZUTA, MAGENTA };
int trenutnaBoja = 0;

struct Trokut {
    pair<int, int> tocke[3];
    Boja boja;
};
vector<Trokut> trokuti;

vector< pair<int, int> > trenutniTrokut;
int sirina = 400, visina = 400;
int misX = 0, misY = 0;

void reshape(int, int);
void display();
void renderScene();
void mousePressedOrReleased(int, int, int, int);
void mouseMoved(int, int);
void keyPressed(unsigned char, int, int);
void nacrtajKvadratic();
void nacrtajPostojeceTrokute();
void nacrtajNoviTrokut();
void postaviBoju(Boja);


int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(sirina, visina);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Vjezba 2");
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
    glClear(GL_COLOR_BUFFER_BIT);
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
    
    nacrtajKvadratic();
    nacrtajPostojeceTrokute();
    nacrtajNoviTrokut();
    
//    glBegin(GL_POINTS);
//    glVertex2i(0, 0);
//    glVertex2i(2, 2);
//    glVertex2i(4, 4);
//    glEnd();
//    glBegin(GL_LINE_STRIP);
//    glVertex2i(50, 50);
//    glVertex2i(150, 150);
//    glVertex2i(50, 150);
//    glVertex2i(50, 50);
//    glEnd();
}

void nacrtajKvadratic() {
    postaviBoju(boje[trenutnaBoja]);
    glBegin(GL_QUADS);
    glVertex2i(sirina - 6, 0);
    glVertex2i(sirina - 1, 0);
    glVertex2i(sirina - 1, 5);
    glVertex2i(sirina - 6, 5);
    glEnd();
}

void nacrtajPostojeceTrokute() {
    for(int i = 0; i < (int)trokuti.size(); ++i) {
        Trokut trokut = trokuti[i];
        postaviBoju(trokut.boja);
        glBegin(GL_TRIANGLES);
        for(int j = 0 ; j < 3; ++j) {
            glVertex2i(trokut.tocke[j].first, trokut.tocke[j].second);
        }
        glEnd();
    }
}

void nacrtajNoviTrokut() {
    postaviBoju(boje[trenutnaBoja]);
    if(trenutniTrokut.size() == 1) {
        glBegin(GL_LINES);
        glVertex2i(trenutniTrokut[0].first, trenutniTrokut[0].second);
        glVertex2i(misX, misY);
        glEnd();
    } else if(trenutniTrokut.size() == 2) {
        glBegin(GL_TRIANGLES);
        glVertex2i(trenutniTrokut[0].first, trenutniTrokut[0].second);
        glVertex2i(trenutniTrokut[1].first, trenutniTrokut[1].second);
        glVertex2i(misX, misY);
        glEnd();
    }
}

void postaviBoju(Boja boja) {
    switch(boja) {
        case CRVENA:
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        case ZELENA:
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        case PLAVA:
            glColor3f(0.0f, 0.0f, 1.0f);
            break;
        case CIJAN:
            glColor3f(0.0f, 1.0f, 1.0f);
            break;
        case ZUTA:
            glColor3f(1.0f, 1.0f, 0.0f);
            break;
        case MAGENTA:
            glColor3f(1.0f, 0.0f, 1.0f);
            break;
    }
    
}



void mousePressedOrReleased(int button, int state, int x, int y) {
    if(state == GLUT_DOWN) {
        trenutniTrokut.push_back(make_pair(x, y));
        if(trenutniTrokut.size() == 3) {
            Trokut trokut;
            trokut.boja = boje[trenutnaBoja];
            for(int i = 0; i < 3; ++i) {
                trokut.tocke[i] = trenutniTrokut[i];
            }
            trokuti.push_back(trokut);
            trenutniTrokut.clear();
        }
        glutPostRedisplay();
    }
}

void keyPressed(unsigned char key, int x, int y) {
    if(key == 'n') {
        ++trenutnaBoja;
        if(trenutnaBoja == 6) trenutnaBoja = 0;
        glutPostRedisplay();
    } else if(key == 'p') {
        --trenutnaBoja;
        if(trenutnaBoja == -1) trenutnaBoja = 5;
        glutPostRedisplay();
    }
}

void mouseMoved(int x, int y) {
    misX = x;
    misY = y;
    glutPostRedisplay();
}
