#ifndef MEMORY_H
#define MEMORY_H

// direttive d'inclusione
#include "Container.h"
#include "AbstractProduct.h"
#include "Filter.h"
#include <vector>

class Memory {
private:
    Container<const AbstractProduct*> container;
public:
    Memory& add(AbstractProduct*);
    Memory& remove(AbstractProduct*);
    std::vector<const AbstractProduct*> search(Filter*); // all'interno di search ci va il filtro. come parametro (ancora da implementare come classe
    Memory& clear();
};

#endif // MEMORY_H
