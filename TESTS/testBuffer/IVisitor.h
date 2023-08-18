#ifndef IVISITOR_H
#define IVISITOR_H

// dichiarazioni incomplete
class Virtuale;
class Fisico;
class Noleggio;

class IVisitor {
public:
    virtual void visit(Virtuale&) = 0;
    virtual void visit(Fisico&) = 0;
    virtual void visit(Noleggio&) = 0;
};



#endif // IVISITOR_H
