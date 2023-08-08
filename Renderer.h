#ifndef RENDERER_H
#define RENDERER_H

// direttive di inclusione
#include "IProductVisitor.h"
#include <iostream>

using std::cout;
using std::endl;

class Renderer : public IProductVisitor {
public:
    virtual void visit(Virtuale*);
    virtual void visit(Fisico*);
    virtual void visit(Noleggio*);
};
#endif