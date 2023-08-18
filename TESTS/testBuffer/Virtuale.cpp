#include "Virtuale.h"

Virtuale::Virtuale(const unsigned int i, float p, std::string n, std::string path, std::string description) : AbstractProduct(i, p, n, path, description) {} // costruttore standard

void Virtuale::accept(IVisitor& v) {
    v.visit(*this);
}

void Virtuale::accept(IConstVisitor& v) {
    v.visit(*this);
}
