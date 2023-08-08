#ifndef JSONVISITOR_H
#define JSONVISITOR_H

// direttive di inclusione
#include "IConstProductVisitor.h"

class JsonVisitor: public IConstProductVisitor {
public:
    virtual void visit(const Virtuale*);
    virtual void visit(const Fisico*);
    virtual void visit(const Noleggio*);
};

#endif