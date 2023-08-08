#ifndef VIRTUAL_H 
#define VIRTUAL_H 
#include "AbstractProduct.h"

class Virtuale : public AbstractProduct {
public:
    Virtuale(const unsigned int i, float p, string n = "product");
    virtual void accept(IProductVisitor* v);
    virtual void accept(IConstProductVisitor* v);
};

#endif