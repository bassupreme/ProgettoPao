#include "Noleggio.h"

Noleggio::Noleggio(const unsigned int i, float p, bool u, const string note, string nore, string n) : Fisico(i, p, n, u), noleggiante(note), noleggiatore(nore) {}


const string& Noleggio::getNoleggiante() const {
    return noleggiante;
}

const string& Noleggio::getNoleggiatore() const {
    return noleggiatore;
}

Noleggio& Noleggio::setNoleggiatore(const string& n) {
    noleggiatore = n;
    return *this;
}

void Noleggio::accept(IProductVisitor* v) {
    v->visit(this);
}

void Noleggio::accept(IConstProductVisitor* v) {
    v->visit(this);
}
