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
#include <cmath>
#include "Vector.h"

using namespace std;

// model podataka

struct Linija {
    pair<int, int> poc;
    pair<int, int> kraj;
};
vector<Linija> linije;
bool unosPrveTocke = true;
pair<int, int> prva, druga;

int sirina = 400, visina = 400;
int misX = 0, misY = 0;
bool kontrola = true, odsijecanje = true;

void reshape(int, int);
void display();
void renderScene();
void mousePressedOrReleased(int, int, int, int);
void mouseMoved(int, int);
void keyPressed(unsigned char, int, int);
void nacrtajPravokutnik();
void nacrtajPostojeceLinije();
void nacrtajNovuLiniju();
void bresenham_nacrtaj_cjelobrojni(pair<int, int>, pair<int, int>);
void bresenham_nacrtaj_cjelobrojni2(pair<int, int>, pair<int, int>);
void bresenham_nacrtaj_cjelobrojni3(pair<int, int>, pair<int, int>);
void nacrtaj_liniju_opengl(pair<int, int>, pair<int, int>);

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(sirina, visina);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Vjezba 3");
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
    
    if(odsijecanje) {
        nacrtajPravokutnik();
    }
    nacrtajPostojeceLinije();
    nacrtajNovuLiniju();
}

void mousePressedOrReleased(int button, int state, int x, int y) {
    if(state == GLUT_DOWN) {
        if(unosPrveTocke) {
            prva.first = x;
            prva.second = y;
            unosPrveTocke = false;
        } else {
            druga.first = x;
            druga.second = y;
            
            Linija linija;
            linija.poc = prva;
            linija.kraj = druga;
            linije.push_back(linija);
            unosPrveTocke = true;
        }
        glutPostRedisplay();
    }
}

void keyPressed(unsigned char key, int x, int y) {
    if(key == 'o') {
        odsijecanje = !odsijecanje;
        glutPostRedisplay();
    } else if(key == 'k') {
        kontrola = !kontrola;
        glutPostRedisplay();
    }
}

void mouseMoved(int x, int y) {
    misX = x;
    misY = y;
    glutPostRedisplay();
}

void nacrtajPravokutnik() {
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(sirina/2 - sirina/4, visina/2 - visina/4);
    glVertex2i(sirina/2 + sirina/4, visina/2 - visina/4);
    glVertex2i(sirina/2 + sirina/4, visina/2 + visina/4);
    glVertex2i(sirina/2 - sirina/4, visina/2 + visina/4);
    glEnd();
}

void nacrtajPostojeceLinije() {
    for(int i = 0; i < (int)linije.size(); ++i) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_POINTS);
        bresenham_nacrtaj_cjelobrojni(linije[i].poc, linije[i].kraj);
        glEnd();
        
        if(kontrola) {
            double x = linije[i].kraj.first - linije[i].poc.first;
            double y = linije[i].kraj.second - linije[i].poc.second;
            double newx = x * cos(-M_PI_2) - y * sin(-M_PI_2);
            double newy = x * sin(-M_PI_2) + y * cos(-M_PI_2);
            IVector *v = new Vector(new double[2] {newx, newy}, 2);
            v->normalize()->scalarMultiply(5.0);
            x = v->get(0);
            y = v->get(1);
            
            pair<int, int> poc = linije[i].poc;
            poc.first -= x;
            poc.second -= y;
            
            pair<int, int> kraj = linije[i].kraj;
            kraj.first -= x;
            kraj.second -= y;
            
            nacrtaj_liniju_opengl(poc, kraj);
        }
    }
}

void nacrtajNovuLiniju() {
    if(!unosPrveTocke) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_POINTS);
        bresenham_nacrtaj_cjelobrojni(prva, make_pair(misX, misY));
        glEnd();
        
        if(kontrola) {
            double x = misX - prva.first;
            double y = misY - prva.second;
            double newx = x * cos(-M_PI_2) - y * sin(-M_PI_2);
            double newy = x * sin(-M_PI_2) + y * cos(-M_PI_2);
            IVector *v = new Vector(new double[2] {newx, newy}, 2);
            v->normalize()->scalarMultiply(5.0);
            x = v->get(0);
            y = v->get(1);
            
            pair<int, int> poc = prva;
            poc.first -= x;
            poc.second -= y;
            
            pair<int, int> kraj = make_pair(misX, misY);
            kraj.first -= x;
            kraj.second -= y;
            
            nacrtaj_liniju_opengl(poc, kraj);
        }
    }
}

void bresenham_nacrtaj_cjelobrojni(pair<int, int> poc, pair<int, int> kraj) {
    if(poc.first <= kraj.first) {
        if( poc.second <= kraj.second) {
            bresenham_nacrtaj_cjelobrojni2(poc, kraj);
        } else {
            bresenham_nacrtaj_cjelobrojni3(poc, kraj);
        }
    } else {
        if( poc.second >= kraj.second) {
            bresenham_nacrtaj_cjelobrojni2(kraj, poc);
        } else {
            bresenham_nacrtaj_cjelobrojni3(kraj, poc);
        }
        
    }
}

void bresenham_nacrtaj_cjelobrojni2(pair<int, int> poc, pair<int, int> kraj) {
    int x,yc,korekcija;
    int a,yf;
    
    if(kraj.second-poc.second <= kraj.first-poc.first) {
        a = 2*(kraj.second-poc.second);
        yc = poc.second; yf=-(kraj.first-poc.first); korekcija=-2*(kraj.first-poc.first);
        for( x = poc.first; x <= kraj.first; ++x) {
            glVertex2i(x, yc);
            yf = yf + a;
            if(yf >= 0) {
                yf = yf + korekcija;
                yc = yc + 1;
            }
        }
    } else {
        // zamjena x i y koordinata
        swap(kraj.first, kraj.second);
        swap(poc.first, poc.second);
        a = 2*(kraj.second - poc.second);
        yc = poc.second; yf = -(kraj.first - poc.first); korekcija=-2*(kraj.first - poc.first);
        for(x = poc.first; x <= kraj.first; ++x) {
            glVertex2i(yc, x);
            yf = yf+a;
            if(yf>=0) {
                yf = yf+korekcija;
                yc = yc + 1;
            }
        }
    }
}

void bresenham_nacrtaj_cjelobrojni3(pair<int, int> poc, pair<int, int> kraj) {
    int x,yc,korekcija;
    int a,yf;
    
    if(-(kraj.second-poc.second) <= kraj.first-poc.first) {
        a = 2*(kraj.second-poc.second);
        yc = poc.second; yf=(kraj.first-poc.first); korekcija=2*(kraj.first-poc.first);
        for( x = poc.first; x <= kraj.first; ++x) {
            glVertex2i(x, yc);
            yf = yf + a;
            if(yf <= 0) {
                yf = yf + korekcija;
                yc = yc - 1;
            }
        }
    } else {
        // zamjena x i y koordinata
        swap(kraj.first, poc.second);
        swap(poc.first, kraj.second);
        a = 2*(kraj.second - poc.second);
        yc = poc.second; yf = (kraj.first - poc.first); korekcija=2*(kraj.first - poc.first);
        for(x = poc.first; x <= kraj.first; ++x) {
            glVertex2i(yc, x);
            yf = yf+a;
            if(yf<=0) {
                yf = yf+korekcija;
                yc = yc - 1;
            }
        }
    }
}

void nacrtaj_liniju_opengl(pair<int, int> poc, pair<int, int> kraj) {
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2i(poc.first, poc.second);
    glVertex2i(kraj.first, kraj.second);
    glEnd();
}