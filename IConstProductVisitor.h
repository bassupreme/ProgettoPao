#ifndef ICONSTPRODUCTVISITOR 
#define ICONSTPRODUCTVISITOR 

class Virtuale;
class Fisico;
class Noleggio;

class IConstProductVisitor {
public:
    virtual ~IConstProductVisitor() {};
    virtual void visit(const Virtuale*) = 0;
    virtual void visit(const Fisico*) = 0;
    virtual void visit(const Noleggio*) = 0;
};

#endif