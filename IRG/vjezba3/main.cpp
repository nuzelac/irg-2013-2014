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
double xmin = sirina/2 - sirina/4
     , ymin = visina/2 - visina/4
     , xmax = sirina/2 + sirina/4
     , ymax = visina/2 + visina/4;

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
void clipping(pair<int, int>, pair<int, int>);

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
    xmin = sirina/2 - sirina/4;
    ymin = visina/2 - visina/4;
    xmax = sirina/2 + sirina/4;
    ymax = visina/2 + visina/4;
    
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
    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);
    glEnd();
}

void nacrtajPostojeceLinije() {
    for(int i = 0; i < (int)linije.size(); ++i) {
        glColor3f(0.0f, 0.0f, 0.0f);
        if(odsijecanje) {
            clipping(linije[i].poc, linije[i].kraj);
        } else {
            glBegin(GL_POINTS);
            bresenham_nacrtaj_cjelobrojni(linije[i].poc, linije[i].kraj);
            glEnd();
        }
        
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
        if(odsijecanje) {
            clipping(prva, make_pair(misX, misY));
        } else {
            glBegin(GL_POINTS);
            bresenham_nacrtaj_cjelobrojni(prva, make_pair(misX, misY));
            glEnd();
        }
        
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

int kod(pair<int, int> tocka) {
    int kod = 0;
    
    if(tocka.second > ymax)
        kod |= 8;
    if(tocka.second < ymin)
        kod |= 4;
    if(tocka.first > xmax)
        kod |= 2;
    if(tocka.first < xmin)
        kod |= 1;
    
    return kod;
}

void clipping(pair<int, int> poc, pair<int, int> kraj) {
    int c1 = kod(poc), c2 = kod(kraj);
    pair<int, int> noviPoc = poc;
    pair<int, int> noviKraj = kraj;
    printf("poc: %d %d\n", noviPoc.first, noviPoc.second);
    printf("kraj: %d %d\n", noviKraj.first, noviKraj.second);
    
    
    while(true) {
    
        printf("bok %d %d\n", c1, c2);
        if(c1 == c2 && c1 == 0) {
            glBegin(GL_POINTS);
            bresenham_nacrtaj_cjelobrojni(noviPoc, noviKraj);
            glEnd();
            return;
        }
        
        if((c1 & c2) != 0) {
            // linija je potpuno izvan prozora
            return;
        }
        
        // ovo racunam ovdje zato sto gore moze biti dijeljenja s nulom
        double a = (double)(kraj.second - poc.second) / (kraj.first - poc.first);
        double b = -a * poc.first + poc.second;
        
        if(c1) {
            if(c1&8) {
                printf("je %lf %lf %lf\n", ymax, a, b);
                noviPoc.first = (ymax - b) / a;
                noviPoc.second = ymax;
            } else if(c1&4) {
                noviPoc.first = (ymin - b) / a;
                noviPoc.second = ymin;
            } else if(c1&2) {
                noviPoc.first = xmax;
                noviPoc.second = a * xmax + b;
            } else if(c1&1) {
                noviPoc.first = xmin;
                noviPoc.second = a * xmin + b;
            }
            
            c1 = kod(noviPoc);
        } else {
            if(c2&8) {
                noviKraj.first = (ymax - b) / a;
                noviKraj.second = ymax;
            } else if(c2&4) {
                noviKraj.first = (ymin - b) / a;
                noviKraj.second = ymin;
            } else if(c2&2) {
                noviKraj.first = xmax;
                noviKraj.second = a * xmax + b;
            } else if(c2&1) {
                noviKraj.first = xmin;
                noviKraj.second = a * xmin + b;
            }
            
            c2 = kod(noviKraj);
        }
    
    printf("noviPoc: %d %d\n", noviPoc.first, noviPoc.second);
    printf("noviKraj: %d %d\n", noviKraj.first, noviKraj.second);
    }
}