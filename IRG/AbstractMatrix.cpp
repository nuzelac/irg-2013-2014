//
//  AbstractMatrix.cpp
//  IRG
//
//  Created by Nino Uzelac on 16/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include "AbstractMatrix.h"
#include "MatrixTransposeView.h"
#include "MatrixSubMatrixView.h"

//virtual IVector* toVector(bool);

IMatrix* AbstractMatrix::nTranspose(bool live) {
    
    IMatrix *mat;
    
    if(live) {
        mat = new MatrixTransposeView(this);
    } else {
        mat = this->newInstance(this->getColsCount(), this->getRowsCount());
        
        for(int i = 0; i < this->getRowsCount(); ++i) {
            for(int j = 0; j < this->getColsCount(); ++j) {
                mat->set(j, i, this->get(i, j));
            }
        }
    }
    
    return mat;
}

IMatrix* AbstractMatrix::add(IMatrix *other) {
    if(this->getRowsCount() != other->getRowsCount()
       || this->getColsCount() != other->getColsCount())
        throw "Incompatible operands";
    
    for(int i = 0; i < this->getRowsCount(); ++i) {
        for(int j = 0; j < this->getColsCount(); ++j) {
            double val = this->get(i, j) + other->get(i, j);
            this->set(i, j, val);
        }
    }
    
    return this;
}

IMatrix* AbstractMatrix::nAdd(IMatrix *other) {
    if(this->getRowsCount() != other->getRowsCount()
       || this->getColsCount() != other->getColsCount())
        throw "Incompatible operands";
    
    IMatrix *mat = this->newInstance(this->getRowsCount(), this->getColsCount());
    
    for(int i = 0; i < this->getRowsCount(); ++i) {
        for(int j = 0; j < this->getColsCount(); ++j) {
            double val = this->get(i, j) + other->get(i, j);
            mat->set(i, j, val);
        }
    }
    
    return mat;
}

IMatrix* AbstractMatrix::sub(IMatrix *other) {
    if(this->getRowsCount() != other->getRowsCount()
       || this->getColsCount() != other->getColsCount())
        throw "Incompatible operands";
    
    for(int i = 0; i < this->getRowsCount(); ++i) {
        for(int j = 0; j < this->getColsCount(); ++j) {
            double val = this->get(i, j) - other->get(i, j);
            this->set(i, j, val);
        }
    }
    
    return this;
}

IMatrix* AbstractMatrix::nSub(IMatrix *other) {
    if(this->getRowsCount() != other->getRowsCount()
       || this->getColsCount() != other->getColsCount())
        throw "Incompatible operands";
    
    IMatrix *mat = this->newInstance(this->getRowsCount(), this->getColsCount());
    
    for(int i = 0; i < this->getRowsCount(); ++i) {
        for(int j = 0; j < this->getColsCount(); ++j) {
            double val = this->get(i, j) - other->get(i, j);
            mat->set(i, j, val);
        }
    }
    
    return mat;
}

IMatrix* AbstractMatrix::nMultiply(IMatrix *other) {
    if(this->getColsCount() != other->getRowsCount())
        throw "Incompatible operands";
    
    IMatrix *mat = this->newInstance(this->getRowsCount(), this->getColsCount());
    
    for(int i = 0; i < this->getRowsCount(); ++i) {
        for(int j = 0; j < other->getColsCount(); ++j) {
            double val = 0;
            for(int k = 0; k < this->getColsCount(); ++k) {
                val += this->get(i, k) * other->get(k, j);
            }
            mat->set(i, j, val);
        }
    }
    
    return mat;
}

double AbstractMatrix::determinant() {
    if(this->getColsCount() != this->getRowsCount())
        throw "Cannot calculate determinant for non-square matrix";
    
    double det = 0;
    if(this->getRowsCount() == 2) {
        det = this->get(0, 0) * this->get(1, 1)
              - this->get(0, 1) * this->get(1, 0);
    } else {
        int sign = 1;
        for(int j = 0; j < this->getColsCount(); ++j) {
            det += sign * this->get(0, j) * this->subMatrix(0, j, true)->determinant();
            sign = -sign;
        }
    }
    
    return det;
}

IMatrix* AbstractMatrix::subMatrix(int r, int c, bool live) {
    IMatrix *mat;
    
    if(live) {
        mat = new MatrixSubMatrixView(this, r, c);
    } else {
        IMatrix *helper = new MatrixSubMatrixView(this, r, c);
        mat = helper->copy();
        delete helper;
    }
    
    return mat;
}

IMatrix* AbstractMatrix::nInvert() {
    if(this->getColsCount() != this->getRowsCount())
        throw "Cannot calculate inverse matrix for non-square matrix";

    double det = this->determinant();
    if(det < 1e-6)
        throw "Determinant is 0 (zero)";
    
    IMatrix *mat = this->newInstance(this->getRowsCount(), this->getColsCount());
    
    for(int i = 0; i < this->getRowsCount(); ++i) {
        for(int j = 0; j < this->getColsCount(); ++j) {
            double cofactor = this->subMatrix(i, j, false)->determinant();
            mat->set(i, j, cofactor / det);
        }
    }
    
    return mat;
}

double** AbstractMatrix::toArray() {
    double **arr;
    
    arr = new double*[this->getRowsCount()];
    for(int i = 0; i < this->getRowsCount(); ++i) {
        arr[i] = new double[this->getColsCount()];
        
        for(int j = 0; j < this->getColsCount(); ++j) {
            arr[i][j] = this->get(i, j);
        }
    }
    
    return arr;
}

std::string AbstractMatrix::toString() {
    return this->toString(3);
}

std::string AbstractMatrix::toString(int precision) {
    std::string s;
    char buff[100];
    
    for(int i = 0; i < this->getRowsCount(); ++i) {
        for(int j = 0; j < this->getColsCount(); ++j) {
            memset(buff, 0, sizeof(buff));
            sprintf(buff, "%.*lf", precision, this->get(i, j));
            s += buff;
        }
    }
    
    return s;
}
