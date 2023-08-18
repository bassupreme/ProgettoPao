#ifndef VIRTUALE_H
#define VIRTUALE_H

// direttive d'inclusione
#include "AbstractProduct.h"

class Virtuale : public AbstractProduct {
public:
    Virtuale(const unsigned int i, float p, std::string n, std::string path, std::string description);
    virtual void accept(IVisitor& v);
    virtual void accept(IConstVisitor& v);
};

#endif // VIRTUALE_H
