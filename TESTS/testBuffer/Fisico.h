#ifndef FISICO_H
#define FISICO_H

#include "AbstractProduct.h"

class Fisico : public AbstractProduct {
private:
    bool usato;
public:
    Fisico(const unsigned int i, float p, std::string n, std::string path, std::string description, bool usato = false);
    bool getUsato() const;
    Fisico& setUsato(bool u);
    virtual void accept(IVisitor& v);
    virtual void accept(IConstVisitor& v);
};

#endif // FISICO_H
