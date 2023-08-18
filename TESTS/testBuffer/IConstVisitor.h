#ifndef ICONSTVISITOR_H
#define ICONSTVISITOR_H

// dichiarazioni incomplete.
class Virtuale;
class Fisico;
class Noleggio;

class IConstVisitor {
public:
    virtual void visit(const Virtuale&) = 0;
    virtual void visit(const Fisico&) = 0;
    virtual void visit(const Noleggio&) = 0;
};


#endif // ICONSTVISITOR_H
