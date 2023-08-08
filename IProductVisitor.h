#ifndef IPRODUCTVISITOR 
#define IPRODUCTVISITOR 

class Virtuale;
class Fisico;
class Noleggio;

class IProductVisitor {
public:
    virtual void visit(Virtuale*) = 0;
    virtual void visit(Fisico*) = 0;
    virtual void visit(Noleggio*) = 0;
};

#endif