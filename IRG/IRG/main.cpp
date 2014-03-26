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

void testSustavJdzbi() {
    IMatrix *a = Matrix::parseSimple("3 5 | 2 10");
    IMatrix *r = Matrix::parseSimple("2 | 8");
    printf("a:\n%s", a->toString().c_str());
    printf("Inverz:\n%s", a->nInvert()->toString().c_str());
    IMatrix *v = a->nInvert()->nMultiply(r);
    
    printf("Rjesenje sustava je:\n");
    printf("%s", v->toString().c_str());
}

void testBaricentricneMatrica() {
    IMatrix *a = Matrix::parseSimple("1 5 3 | 0 0 8 | 1 1 1");
    IMatrix *b = Matrix::parseSimple("3 | 4 | 1");
    
    IMatrix *r = a->nInvert()->nMultiply(b);
    
    printf("Rjesenje sustava je\n");
    printf("%s", r->toString().c_str());
}

int main(int argc, const char * argv[])
{
//    testVector();
//    testMatrix();
//    testBarocentricneKoordinate();
//    testSustavJdzbi();
    testBaricentricneMatrica();
    
    return 0;
}

