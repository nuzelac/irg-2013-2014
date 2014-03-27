//
//  main.cpp
//  bibliotekaDemo
//
//  Created by Nino Uzelac on 26/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include <iostream>
#include "Vector.h"
#include "Matrix.h"

void zad1() {
    IVector *v1 = (Vector::parseSimple("2 3 -4"))->add(Vector::parseSimple("-1 4 -3"));
    printf("v1 = %s\n", v1->toString().c_str());
    
    IVector *s = v1->nAdd(Vector::parseSimple("-1 4 -3"));
    printf("s = %s\n", s->toString().c_str());
    
    IVector *v2 = v1->nVectorProduct(Vector::parseSimple("2 2 4"));
    printf("v2 = %s\n", v2->toString().c_str());
    
    IVector *v3 = v2->normalize();
    printf("v3 = %s\n", v3->toString().c_str());
    
    IVector *v4 = v2->scalarMultiply(-1);
    printf("v4 = %s\n", v4->toString().c_str());
    
    IMatrix *m1 = (Matrix::parseSimple("1 2 3 | 2 1 3 | 4 5 1"))
    ->add(Matrix::parseSimple("-1 2 -3 | 5 -2 7 | -4 -1 3"));
    printf("m1 = %s\n", m1->toString().c_str());
    
    IMatrix *m2 = (Matrix::parseSimple("1 2 3 | 2 1 3 | 4 5 1"))
    ->nMultiply(Matrix::parseSimple("-1 2 -3 | 5 -2 7 | -4 -1 3")->nTranspose(false));
    printf("m2 = %s\n", m2->toString().c_str());
    
    IMatrix *m3 = (Matrix::parseSimple("-24 18 5 | 20 -15 -4 | -5 4 1")->nInvert())
    ->nMultiply(Matrix::parseSimple("1 2 3 | 0 1 4 | 5 6 0")->nInvert());
    printf("m3 = %s\n", m3->toString().c_str());
}

void sustav() {
    IMatrix *a = new Matrix(3, 3);
    IMatrix *r = new Matrix(3, 1);
    
    int x;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            printf("(%d, %d) = ", i, j);
            scanf("%d", &x);
            printf("\n");
            a->set(i, j, x);
        }
        printf("r%d = ", i);
        scanf("%d", &x);
        printf("\n");
        r->set(i, 0, x);
    }
    
    IMatrix *v = a->nInvert()->nMultiply(r);
    
    printf("Rjesenje sustava je:\n");
    printf("%s", v->toString().c_str());

}

void baricentricne() {
    IMatrix *a = new Matrix(3, 3);
    IMatrix *r = new Matrix(3, 1);
    
    int x;
    printf("Unos trokuta\n");
    for(int i = 0; i < 3; ++i) {
        printf("Tocka %d: ", i);
        for(int j = 0; j < 3; ++j) {
            scanf("%d", &x);
            a->set(i, j, x);
        }
        printf("\n");
    }
    
    printf("T = ");
    for(int j = 0; j < 3; ++j) {
        scanf("%d", &x);
        r->set(j, 0, x);
    }
    printf("\n");
    
    IMatrix *v = a->nInvert()->nMultiply(r);
    
    printf("Baricentricne koordinate tocke T s obzirom na trokut su:\n");
    printf("%s", v->toString().c_str());
    
}

int main(int argc, const char * argv[])
{
//    zad1();
//    sustav();
    baricentricne();
    
    return 0;
}

