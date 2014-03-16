//
//  MatrixTransposeView.cpp
//  IRG
//
//  Created by Nino Uzelac on 16/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include "MatrixTransposeView.h"

MatrixTransposeView::MatrixTransposeView(IMatrix* mat) {
    this->mat = mat;
}

int MatrixTransposeView::getRowsCount() {
    return this->mat->getColsCount();
}

int MatrixTransposeView::getColsCount() {
    return this->mat->getRowsCount();
}

double MatrixTransposeView::get(int i, int j) {
    return this->mat->get(j, i);
}

IMatrix* MatrixTransposeView::set(int i, int j, double val) {
    this->mat->set(j, i, val);
    return this;
}

// what should this method return anyway?
// assuming a transposed Matrix, but non-live
IMatrix* MatrixTransposeView::copy() {
    return this->mat->nTranspose(false);
}

IMatrix* MatrixTransposeView::newInstance(int i, int j) {
    return this->mat->newInstance(i, j);
}

double** MatrixTransposeView::toArray() {
    return this->mat->nTranspose(false)->toArray();
}