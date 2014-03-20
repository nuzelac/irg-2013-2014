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

int main(int argc, const char * argv[])
{
//    testVector();
    testMatrix();
    
    return 0;
}

