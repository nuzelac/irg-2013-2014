//
//  main.cpp
//  IRG
//
//  Created by Nino Uzelac on 14/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include <iostream>
#include "Vector.h"
#include "Matrix.h"

void testVector() {
    IVector *a = Vector::parseSimple("3 1 3");
    IVector *b = Vector::parseSimple("-2 4 1");
    double n = a->add(Vector::parseSimple("1 1 1"))
    ->add(b)
    ->scalarProduct(Vector::parseSimple("2 3 2"));
    
    printf("%lf\n", n);
}

void testMatrix() {
    IMatrix *m1 = Matrix::parseSimple("1 2 3 | 4 5 6");
    IMatrix *m2 = m1->nTranspose(true);
    
    std::cout << "m1: " << std::endl;
    std::cout << m1->toString() << std::endl;
    std::cout << "m2: " << std::endl;
    std::cout << m2->toString() << std::endl;
    
    m2->set(2, 1, 9);

    std::cout << "m1: " << std::endl;
    std::cout << m1->toString() << std::endl;
    std::cout << "m2: " << std::endl;
    std::cout << m2->toString() << std::endl;
}

void testBarocentricneKoordinate() {
    IVector *a = Vector::parseSimple("1 0 0");
    IVector *b = Vector::parseSimple("5 0 0");
    IVector *c = Vector::parseSimple("3 8 0");
    
    IVector *t = Vector::parseSimple("3 4 0");
    
    double pov = b->nSub(a)->nVectorProduct(c->nSub(a))->norm() / 2.0;
    double povA = b->nSub(t)->nVectorProduct(c->nSub(t))->norm() / 2.0;
    double povB = a->nSub(t)->nVectorProduct(c->nSub(t))->norm() / 2.0;
    double povC = a->nSub(t)->nVectorProduct(b->nSub(t))->norm() / 2.0;
    
    double t1 = povA / pov;
    double t2 = povB / pov;
    double t3 = povC / pov;
    
    printf("Baricentricne koordinate su: (%lf, %lf, %lf)\n", t1, t2, t3);

}

int main(int argc, const char * argv[])
{
//    testVector();
//    testMatrix();
    testBarocentricneKoordinate();
    
    return 0;
}

