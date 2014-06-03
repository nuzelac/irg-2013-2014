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
        }
    }
};


int main(int argc, char * argv[])
{
    //    if(argc != 2) {
    //        printf("Invalid programg arguments\n");
    //        return -1;
    //    }
    
    char *objFilename = "/Users/Nino/Programming/irg/IRG/vjezba5/kocka.obj";
    
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
    
    ObjectModel obj(vertices, faces);
    obj.normalize();
    obj.izracunajKoeficijente();
    printf("dump:\n");
    printf("%s\n", obj.dumpToOBJ().c_str());
    
//    printf("Upiti:\n");
//    while(scanf("%s", tip) == 1) {
//        std::string s = tip;
//        if(s == "normiraj") {
//            obj.normalize();
//            printf("Normirani model:\n\n%s\n", obj.dumpToOBJ().c_str());
//        } else if(s == "t"){
//            double x,y,z;
//            scanf("%lf %lf %lf", &x, &y, &z);
//            int iznad = 0, ispod = 0, na = 0;
//            for(int i = 0; i < (int)obj.faces.size(); ++i) {
//                Face3D f = obj.faces[i];
//                double r = x * f.a + y * f.b + z * f.c + f.d;
//                if(fabs(r) < 1e-8) ++na;
//                if(r > 0) ++iznad;
//                if(r < 0) ++ispod;
//            }
//            
//            if(iznad > 0) {
//                printf("Tocka T(%lf, %lf, %lf) je izvan tijela\n", x, y, z);
//            } else if(na > 0) {
//                printf("Tocka T(%lf, %lf, %lf) je na tijelu\n", x, y, z);
//            } else {
//                printf("Tocka T(%lf, %lf, %lf) je unutar tijela\n", x, y, z);
//            }
//        } else if(s == "quit") {
//            printf("Kraj\n");
//            break;
//        }
//    }
    
    return 0;
}

