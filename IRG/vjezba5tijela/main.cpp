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
#include "glm/glm/glm.hpp"
#include "Vector.h"

int sirina = 400, visina = 400;
int misX = 0, misY = 0;

struct Vertex3D {
    double x, y, z;
};

struct Face3D {
    int indexes[3];
    double a, b, c, d;
};

class ObjectModel {
public:
    std::vector<Vertex3D> vertices;
    std::vector<Face3D> faces;
    ObjectModel(std::vector<Vertex3D> v, std::vector<Face3D> f) : vertices(v), faces(f) {
        izracunajKoeficijente();
    }
    ObjectModel copy() {
        return ObjectModel(vertices, faces);
    }
    
    std::string dumpToOBJ() {
        std::string s;
        for(int i = 0; i < (int)vertices.size(); ++i) {
            s += "v " + std::to_string(vertices[i].x) + " " + std::to_string(vertices[i].y) + " " + std::to_string(vertices[i].z) + "\n";
        }
        for(int i = 0; i < (int)faces.size(); ++i) {
            s += "f " + std::to_string(faces[i].indexes[0] + 1) + " " + std::to_string(faces[i].indexes[1] + 1) + " " + std::to_string(faces[i].indexes[2] + 1) + "\n";
        }
        return s;
    }
    
    void normalize() {
        double xmin = vertices[0].x, xmax = vertices[0].x,
        ymin = vertices[0].y, ymax = vertices[0].y,
        zmin = vertices[0].z, zmax = vertices[0].z;
        
        for(int i = 1; i < (int)vertices.size(); ++i) {
            if(vertices[i].x < xmin) xmin = vertices[i].x;
            if(vertices[i].x > xmax) xmax = vertices[i].x;
            if(vertices[i].y < ymin) ymin = vertices[i].y;
            if(vertices[i].y > ymax) ymax = vertices[i].y;
            if(vertices[i].z < zmin) zmin = vertices[i].z;
            if(vertices[i].z > zmax) zmax = vertices[i].z;
        }
        
        double sredisteX = (xmin + xmax) / 2.0;
        double sredisteY = (ymin + ymax) / 2.0;
        double sredisteZ = (zmin + zmax) / 2.0;
        
        double M = std::max(xmax - xmin, std::max(ymax - ymin, zmax - zmin));
        
        for(int i = 1; i < (int)vertices.size(); ++i) {
            vertices[i].x = (vertices[i].x - sredisteX) * 2/M;
            vertices[i].y = (vertices[i].y - sredisteY) * 2/M;
            vertices[i].z = (vertices[i].z - sredisteZ) * 2/M;
        }
    }
    
    void izracunajKoeficijente() {
        for(int i = 0; i < (int)faces.size(); ++i) {
            int i0 = faces[i].indexes[0];
            int i1 = faces[i].indexes[1];
            int i2 = faces[i].indexes[2];
            IVector *v1 = new Vector(new double[3]{vertices[i1].x - vertices[i0].x, vertices[i1].y - vertices[i0].y, vertices[i1].z - vertices[i0].z }, 3);
            IVector *v2 = new Vector(new double[3]{vertices[i2].x - vertices[i0].x, vertices[i2].y - vertices[i0].y, vertices[i2].z - vertices[i0].z }, 3);
            IVector *n = v1->nVectorProduct(v2);
            faces[i].a = n->get(0);
            faces[i].b = n->get(1);
            faces[i].c = n->get(2);
            faces[i].d = -faces[i].a * vertices[i1].x - faces[i].b * vertices[i1].y - faces[i].c * vertices[i1].z;
        }
    }
};


Vertex3D ociste, glediste;
int n;
glm::mat4 T, P;
ObjectModel *obj;

void reshape(int, int);
void display();
void renderScene();
void mousePressedOrReleased(int, int, int, int);
void mouseMoved(int, int);
void keyPressed(unsigned char, int, int);

int main(int argc, char * argv[])
{
    char *objFilename = "/Users/Nino/Programming/irg/IRG/vjezba5tijela/objekti/concave/teddy.obj";
    
    FILE *f = fopen(objFilename, "r");
    if(f == NULL) {
        printf("Unable to read file %s\n", objFilename);
        exit(-1);
    }
    
    char line[1024], tip[20];
    std::vector<Vertex3D> vertices;
    std::vector<Face3D> faces;
    
    while(fgets(line, sizeof line, f)) {
        if(sscanf(line, "%s", tip) == 1) {
            std::string s = tip;
            if(s == "f") {
                int i1, i2, i3;
                sscanf(line, "%*s %d %d %d", &i1, &i2, &i3);
                Face3D f;
                f.indexes[0] = --i1;
                f.indexes[1] = --i2;
                f.indexes[2] = --i3;
                faces.push_back(f);
            } else if(s == "v") {
                double x, y, z;
                sscanf(line, "%*s %lf %lf %lf", &x, &y, &z);
                Vertex3D v;
                v.x = x * 10; v.y = y * 10; v.z = z * 10;
                vertices.push_back(v);
            }
        }
    }
    
    obj = new ObjectModel(vertices, faces);
//    obj->normalize();

    scanf("%lf %lf %lf", &ociste.x, &ociste.y, &ociste.z);
    scanf("%lf %lf %lf", &glediste.x, &glediste.y, &glediste.z);
    
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
    glClear( GL_COLOR_BUFFER_BIT );			//	brisanje pozadine
    glMatrixMode(GL_MODELVIEW);
}

void renderScene() {
    glPointSize(1.0f);
    
    glColor3f(0.0f, 0.0f, 1.0f);
    
    glBegin(GL_LINES);
    for (int i = 0; i < obj->faces.size(); i++) {
//        printf("%lf %lf %lf\n", obj->vertices[obj->faces[i].a].x, obj->vertices[obj->faces[i].a].y, obj->vertices[obj->faces[i].a].z);
//        printf("%lf %lf %lf\n", obj->vertices[obj->faces[i].b].x, obj->vertices[obj->faces[i].b].y, obj->vertices[obj->faces[i].b].z);
//        printf("%lf %lf %lf\n", obj->vertices[obj->faces[i].c].x, obj->vertices[obj->faces[i].c].y, obj->vertices[obj->faces[i].c].z);

        glm::vec4 t1 = P * T * glm::vec4(obj->vertices[obj->faces[i].indexes[0]].x, obj->vertices[obj->faces[i].indexes[0]].y, obj->vertices[obj->faces[i].indexes[0]].z, 1);
        glm::vec4 t2 = P * T * glm::vec4(obj->vertices[obj->faces[i].indexes[1]].x, obj->vertices[obj->faces[i].indexes[1]].y, obj->vertices[obj->faces[i].indexes[1]].z, 1);
        glm::vec4 t3 = P * T * glm::vec4(obj->vertices[obj->faces[i].indexes[2]].x, obj->vertices[obj->faces[i].indexes[2]].y, obj->vertices[obj->faces[i].indexes[2]].z, 1);
        
//        printf("%f %f %f\n", t1[0], t1[1], t1[2]);
//        printf("%f %f %f\n", t2[0], t2[1], t2[2]);
//        printf("%f %f %f\n", t3[0], t3[1], t3[2]);
//        printf("\n");
        
        glVertex2f(t1[0] / t1[3], t1[1] / t1[3]);
        glVertex2f(t2[0] / t2[3], t2[1] / t2[3]);
        
        glVertex2f(t2[0] / t2[3], t2[1] / t2[3]);
        glVertex2f(t3[0] / t3[3], t3[1] / t3[3]);
        
        glVertex2f(t3[0] / t3[3], t3[1] / t3[3]);
        glVertex2f(t1[0] / t1[3], t1[1] / t1[3]);
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
