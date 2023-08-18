#include "Noleggio.h"


Noleggio::Noleggio(const unsigned int i, float p, std::string n, std::string path, std::string description, bool usato, std::string noleggiatore, std::string noleggiante)
    : Fisico(i, p, n, path, description, usato),
    noleggiante(noleggiante), noleggiatore(noleggiatore) {}

const std::string& Noleggio::getNoleggiante() const {
    return noleggiante;
}

const std::string& Noleggio::getNoleggiatore() const {
    return noleggiatore;
}

Noleggio& Noleggio::setNoleggiatore(const std::string& n) {
    noleggiatore = n;
    return *this;
}

void Noleggio::accept(IVisitor& v) {
    v.visit(*this);
}

void Noleggio::accept(IConstVisitor& v) {
    v.visit(*this);
}
