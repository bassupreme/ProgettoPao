#include "Virtuale.h"

Virtuale::Virtuale(const unsigned int i, float p, string n) : AbstractProduct(i, p, n) {}

void Virtuale::accept(IProductVisitor* v) {
    v->visit(this);
}

void Virtuale::accept(IConstProductVisitor* v) {
    v->visit(this);
}