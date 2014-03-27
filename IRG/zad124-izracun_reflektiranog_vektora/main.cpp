//
//  main.cpp
//  zad124-izracun_reflektiranog_vektora
//
//  Created by Nino Uzelac on 26/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include <iostream>
#include "Vector.h"

int main(int argc, const char * argv[])
{
    printf("Dimenzija? ");
    int dim;
    scanf("%d", &dim);
    
    printf("\nPrvi vektor:");
    double *elements = new double[dim];
    IVector *v1 = new Vector(elements, dim);
    for(int i = 0; i < dim; ++i) {
        int x;
        scanf("%d", &x);
        v1->set(i, x);
    }

    IVector *v2 = new Vector(elements, dim);
    printf("\nDrugi vektor:");
    for(int i = 0; i < dim; ++i) {
        int x;
        scanf("%d", &x);
        v2->set(i, x);
    }
    
    v2->normalize();
    
    IVector *r = v1->sub(v2->nScalarMultiply(v1->nScalarMultiply(2)->scalarProduct(v2) / v2->norm()));
    
    printf("Rezultat: %s\n", r->toString().c_str());
    
    return 0;
}

