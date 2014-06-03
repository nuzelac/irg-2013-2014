//
//  main.cpp
//  vjezba5
//
//  Created by Nino Uzelac on 08/04/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Vector.h"
#include <algorithm>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

//*********************************************************************************
//	Pokazivac na glavni prozor i pocetna velicina.
//*********************************************************************************

GLuint window;
GLuint width = 300, height = 300;

typedef struct _Ociste {
	GLdouble	x;
	GLdouble	y;
	GLdouble	z;
} Ociste;

typedef struct Izvor {
	GLdouble	x;
	GLdouble	y;
	GLdouble	z;
} Izvor;

Ociste ociste = {3.0, 3.0 ,5.0};
Izvor izvor = {-2.0, 5.0, 2.0};

double Ia = 100;
double Ii = 200;
double ka = 0.5;
double kd = 0.5;

//*********************************************************************************
//	Function Prototypes.
//*********************************************************************************

void myDisplay		();
void myReshape		(int width, int height);
void myMouse		(int button, int state, int x, int y);
void myKeyboard		(unsigned char theKey, int mouseX, int mouseY);
void myObject		();
void zicnaForma     ();
void konstantnoSjencanje();
void GouraudovoSjencanje();
void redisplay_all	(void);

struct Vertex3D {
    double x, y, z;
};

struct Face3D {
    int indexes[3];
    double a, b, c, d;
    
    bool isVisible() {
        double p = a * ociste.x + b * ociste.y + c * ociste.z + d;
        return p > 0;
    }
    
    Vertex3D srediste;
    IVector *normala;
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
        
        for(int i = 0; i < (int)vertices.size(); ++i) {
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
//            printf("%lf %lf %lf %lf\n", faces[i].a, faces[i].b, faces[i].c, faces[i].d);
        }
    }
    
    void izracunajSredista() {
        for(int i = 0; i < (int)faces.size(); ++i) {
            int i0 = faces[i].indexes[0];
            int i1 = faces[i].indexes[1];
            int i2 = faces[i].indexes[2];
            
            double xmin = std::min(vertices[i0].x, std::min(vertices[i1].x, vertices[i2].x));
            double xmax = std::max(vertices[i0].x, std::max(vertices[i1].x, vertices[i2].x));

            double ymin = std::min(vertices[i0].y, std::min(vertices[i1].y, vertices[i2].y));
            double ymax = std::max(vertices[i0].y, std::max(vertices[i1].y, vertices[i2].y));

            double zmin = std::min(vertices[i0].z, std::min(vertices[i1].z, vertices[i2].z));
            double zmax = std::max(vertices[i0].z, std::max(vertices[i1].z, vertices[i2].z));
            
            Vertex3D srediste;
            srediste.x = (xmax+xmin)/2.0;
            srediste.y = (ymax+ymin)/2.0;
            srediste.z = (zmax+zmin)/2.0;
            faces[i].srediste = srediste;
            
//            printf("%lf %lf %lf\n", srediste.x, srediste.y, srediste.z);
        }
    }
    
    void izracunajNormale() {
        for(int i = 0; i < (int)faces.size(); ++i) {
            faces[i].normala = (new Vector(new double[3]{faces[i].a, faces[i].b, faces[i].c }, 3))->normalize();
//            printf("%s\n", faces[i].normala->toString().c_str());
            //printf("%lf %lf %lf\n", srediste.x, srediste.y, srediste.z);
        }
        
    }
};

ObjectModel *obj;

int main(int argc, char * argv[])
{
    //    if(argc != 2) {
    //        printf("Invalid programg arguments\n");
    //        return -1;
    //    }
    
    char *objFilename = "/Users/Nino/Programming/irg/IRG/vjezba7/objekti/concave/teddy.obj";
    
    FILE *f = fopen(objFilename, "r");
    if(f == NULL) {
        printf("Unable to read file %s\n", objFilename);
        return -1;
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
                v.x = x; v.y = y; v.z = z;
                vertices.push_back(v);
            }
        }
    }
    
    obj = new ObjectModel(vertices, faces);
    obj->normalize();
    obj->izracunajKoeficijente();
    obj->izracunajSredista();
    obj->izracunajNormale();
//    printf("dump:\n");
//    printf("%s\n", obj.dumpToOBJ().c_str());
    
    
	// postavljanje dvostrukog spremnika za prikaz (zbog titranja)
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (width, height);
	glutInitWindowPosition (100, 100);
	glutInit(&argc, argv);
    
	window = glutCreateWindow ("Tijelo");
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKeyboard);
	printf("Tipka: l - pomicanje ocista po x os +\n");
	printf("Tipka: k - pomicanje ocista po x os -\n");
	printf("Tipka: r - pocetno stanje\n");
	printf("esc: izlaz iz programa\n");
    
	glutMainLoop();
    
    return 0;
}

//*********************************************************************************
//	Osvjezavanje prikaza.
//*********************************************************************************

void myDisplay(void)
{
	// printf("Pozvan myDisplay()\n");
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f);		         // boja pozadine - bijela
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	myObject();
	glutSwapBuffers();      // iscrtavanje iz dvostrukog spemnika (umjesto glFlush)
}

//*********************************************************************************
//	Promjena velicine prozora.
//	Funkcija gluPerspective i gluLookAt se obavlja
//		transformacija pogleda i projekcija
//*********************************************************************************

void myReshape (int w, int h)
{
	// printf("MR: width=%d, height=%d\n",w,h);
	width=w; height=h;
	glViewport (0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode (GL_PROJECTION);        // aktivirana matrica projekcije
	glLoadIdentity ();
	gluPerspective(45.0, (float)width/height, 0.5, 15.0); // kut pogleda, x/y, prednja i straznja ravnina odsjecanja
	gluLookAt (ociste.x, ociste.y, ociste.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	// ociste x,y,z; glediste x,y,z; up vektor x,y,z
	glMatrixMode (GL_MODELVIEW);         // aktivirana matrica modela
}

void updatePerspective()
{
	glMatrixMode (GL_PROJECTION);        // aktivirana matrica projekcije
	glLoadIdentity ();
	gluPerspective(45.0, (float)width/height, 0.5, 15.0); // kut pogleda, x/y, prednja i straznja ravnina odsjecanja
	gluLookAt (ociste.x, ociste.y, ociste.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	// ociste x,y,z; glediste x,y,z; up vektor x,y,z
	glMatrixMode (GL_MODELVIEW);         // aktivirana matrica modela
}

//*********************************************************************************
//	Crta moj objekt. Ovdje treba naciniti prikaz ucitanog objekta.
//*********************************************************************************

void myObject ()
{
//    zicnaForma();
    konstantnoSjencanje();
//    GouraudovoSjencanje();
}

void zicnaForma() {
    for(int i = 0; i < (int)obj->faces.size(); ++i) {
        if(!obj->faces[i].isVisible()) continue;
        glBegin (GL_LINE_LOOP);
        glColor3ub(255, 0, 0);	glVertex3f(obj->vertices[obj->faces[i].indexes[0]].x, obj->vertices[obj->faces[i].indexes[0]].y, obj->vertices[obj->faces[i].indexes[0]].z);
        glColor3ub(0, 0, 0);	glVertex3f(obj->vertices[obj->faces[i].indexes[1]].x, obj->vertices[obj->faces[i].indexes[1]].y, obj->vertices[obj->faces[i].indexes[1]].z);
        glColor3ub(100, 0, 0);	glVertex3f(obj->vertices[obj->faces[i].indexes[2]].x, obj->vertices[obj->faces[i].indexes[2]].y, obj->vertices[obj->faces[i].indexes[2]].z);
        glEnd();
    }
}

void konstantnoSjencanje() {
    for(int i = 0; i < (int)obj->faces.size(); ++i) {
        if(!obj->faces[i].isVisible()) continue;
        IVector *L = (new Vector(new double[3]{izvor.x - obj->faces[i].srediste.x, izvor.y - obj->faces[i].srediste.y, izvor.z - obj->faces[i].srediste.z}, 3))->normalize();
        
        double I = Ia * ka + Ii * kd * L->scalarProduct(obj->faces[i].normala);
        if(I < 0) I = 0;
        
        glBegin (GL_TRIANGLES);
        glColor3ub(I, 0, 0);	glVertex3f(obj->vertices[obj->faces[i].indexes[0]].x, obj->vertices[obj->faces[i].indexes[0]].y, obj->vertices[obj->faces[i].indexes[0]].z);
        glColor3ub(I, 0, 0);	glVertex3f(obj->vertices[obj->faces[i].indexes[1]].x, obj->vertices[obj->faces[i].indexes[1]].y, obj->vertices[obj->faces[i].indexes[1]].z);
        glColor3ub(I, 0, 0);	glVertex3f(obj->vertices[obj->faces[i].indexes[2]].x, obj->vertices[obj->faces[i].indexes[2]].y, obj->vertices[obj->faces[i].indexes[2]].z);
        glEnd();
    }
}

void GouraudovoSjencanje() {
    
}


//*********************************************************************************
//	Mis.
//*********************************************************************************

void myMouse(int button, int state, int x, int y)
{
	//	Desna tipka - brise canvas.
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		ociste.x=0;
		updatePerspective();
		glutPostRedisplay();
	}
}

//*********************************************************************************
//	Tastatura tipke - esc - izlazi iz programa.
//*********************************************************************************

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
	switch (theKey)
	{
		case 'l': ociste.x = ociste.x+0.1;
            break;
            
		case 'k': ociste.x =ociste.x-0.1;
            break;
            
		case 'r': ociste.x=0.0;
            break;
            
		case 27:  exit(0);
            break;
	}
	updatePerspective();
	glutPostRedisplay();
}

