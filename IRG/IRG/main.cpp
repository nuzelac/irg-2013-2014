//
//  main.cpp
//  IRG
//
//  Created by Nino Uzelac on 14/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include <iostream>
#include "Vector.h"

void testVector() {
    IVector *a = Vector::parseSimple("3 1 3");
    IVector *b = Vector::parseSimple("-2 4 1");
    double n = a->add(Vector::parseSimple("1 1 1"))
    ->add(b)
    ->scalarProduct(Vector::parseSimple("2 3 2"));
    
    printf("%lf\n", n);
}

int main(int argc, const char * argv[])
{
//    testVector();
    
    return 0;
}

