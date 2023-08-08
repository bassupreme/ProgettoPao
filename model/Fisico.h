#ifndef FISICO_H
#define FISICO_H
#include "AbstractProduct.h"

class Fisico : public AbstractProduct {
private:
    bool usato;
public:
    Fisico(const unsigned int i, float p, string n = "product", bool usato = false);
    bool getUsato() const;
    Fisico& setUsato(bool u);
    virtual void accept(IProductVisitor* v);
    virtual void accept(IConstProductVisitor* v);
};

#endif