#include "Memory.h"


Memory& Memory::add(AbstractProduct* product) {
    container.add(product);
    return *this;
}

Memory &Memory::remove(AbstractProduct* product){
    container.remove(product);
    return *this;
}

std::vector<const AbstractProduct *> Memory::search() {
    std::vector<const AbstractProduct*> aux;
    // implementazione con la classe filtro
    return aux;
}


Memory& Memory::clear() {
    container.clear();
    return *this;
}
