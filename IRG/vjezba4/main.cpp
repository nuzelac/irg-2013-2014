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

int sirina = 400, visina = 400;
int misX = 0, misY = 0;
bool konveksnost = false, popunjavanje = false;
int stanje = 1;

void reshape(int, int);
void display();
void renderScene();
void mousePressedOrReleased(int, int, int, int);
void mouseMoved(int, int);
void keyPressed(unsigned char, int, int);

typedef struct {
    int x;
    int y;
} iTocka2D;

typedef struct {
    int a;
    int b;
    int c;
} iBrid2D;

typedef struct {
    iTocka2D Vrh;
    iBrid2D Brid;
    int lijevi;
} iPolyElem;

std::vector<iPolyElem> poligon;

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
    
    if((int)poligon.size() > 0) {
        // obrub poligona - crn
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
        for(int i = 0; i < (int)poligon.size(); ++i) {
            glVertex2i(poligon[i].Vrh.x, poligon[i].Vrh.y);
        }
        glVertex2i(misX, misY);
        glEnd();
    }
    
//    if(odsijecanje) {
//        nacrtajPravokutnik();
//    }
//    nacrtajPostojeceLinije();
//    nacrtajNovuLiniju();
}

void mousePressedOrReleased(int button, int state, int x, int y) {
    if(state == GLUT_DOWN) {
        if(konveksnost) {
            // prvo provjeri jel tocka stvara konkavni poligon
        } else {
            std::cout << "Unio tocku na (" << x << "," << y << ")" << std::endl;
            iPolyElem elem;
            elem.Vrh.x = x;
            elem.Vrh.y = y;
            poligon.push_back(elem);
        }
//        if(unosPrveTocke) {
//            prva.first = x;
//            prva.second = y;
//            unosPrveTocke = false;
//        } else {
//            druga.first = x;
//            druga.second = y;
//            
//            Linija linija;
//            linija.poc = prva;
//            linija.kraj = druga;
//            linije.push_back(linija);
//            unosPrveTocke = true;
//        }
        glutPostRedisplay();
    }
}

void keyPressed(unsigned char key, int x, int y) {
    if(stanje == 1) {
        if(key == 'k'){
            konveksnost = !konveksnost;
            glutPostRedisplay();
        }
        if(key == 'p'){
            popunjavanje = !popunjavanje;
            glutPostRedisplay();
        }
        if(key == 'n'){
            stanje = 2;
            glutPostRedisplay();
        }
    } else if(stanje == 2) {
        if(key == 'n'){
            stanje = 1;
            poligon.clear();
            konveksnost = false;
            popunjavanje = false;
            glutPostRedisplay();
        }
    }
}

void mouseMoved(int x, int y) {
    misX = x;
    misY = y;
    glutPostRedisplay();
}



