#include "Fisico.h"

// costruttore standard
Fisico::Fisico(const unsigned int i, float p, std::string n, std::string path, std::string description, bool usato) : AbstractProduct(i, p, n, path, description), usato(usato) {}

bool Fisico::getUsato() const {
    return usato;
}

Fisico& Fisico::setUsato(bool u) {
    usato = u;
    return *this;
}

void Fisico::accept(IVisitor& v) {
    v.visit(*this);
}

void Fisico::accept(IConstVisitor& v) {
    v.visit(*this);
}
