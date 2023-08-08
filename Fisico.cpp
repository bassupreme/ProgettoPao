#include "Fisico.h"

Fisico::Fisico(const unsigned int i, float p, string n, bool u) : AbstractProduct(i, p, n), usato(u) {}

bool Fisico::getUsato() const {
    return usato;
}

Fisico& Fisico::setUsato(bool u) {
    usato = u;
    return *this;
}

void Fisico::accept(IProductVisitor* v) {
    v->visit(this);
}

void Fisico::accept(IConstProductVisitor* v) {
    v->visit(this);
}