#include "AbstractProduct.h"

AbstractProduct::AbstractProduct(const unsigned int i, float p, string n) : id(i), prezzo(p), nome(n) {}

AbstractProduct::~AbstractProduct() {}

const unsigned int AbstractProduct::getId() const {
    return id;
};


const float& AbstractProduct::getPrezzo() const {
    return prezzo;
}

AbstractProduct& AbstractProduct::setPrezzo(const float& p)  {
    prezzo = p;
    return *this;
}

const string& AbstractProduct::getNome() const {
    return nome;
}

AbstractProduct& AbstractProduct::setNome(const string& n)  {
    nome = n;
    return *this;
}

void AbstractProduct::accept(IProductVisitor* v) {
}