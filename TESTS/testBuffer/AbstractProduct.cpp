#include "AbstractProduct.h"


AbstractProduct::AbstractProduct(const unsigned int i, float p, std::string n, std::string path, std::string description = "") : id(i), prezzo(p), nome(n), imagePath(path), description(description) {}

AbstractProduct::~AbstractProduct() {}

const unsigned int AbstractProduct::getId() const {
    return id;
}


const float& AbstractProduct::getPrezzo() const {
    return prezzo;
}

AbstractProduct& AbstractProduct::setPrezzo(const float& p)  {
    prezzo = p;
    return *this;
}

const std::string& AbstractProduct::getNome() const {
    return nome;
}

AbstractProduct& AbstractProduct::setNome(const std::string& n)  {
    nome = n;
    return *this;
}

const std::string& AbstractProduct::getImagePath() const {
    return imagePath;
}

AbstractProduct& AbstractProduct::setImagePath(const std::string& path) {
    imagePath = path;
    return *this;
}

const std::string& AbstractProduct::getDescription() const {
    return description;
}

AbstractProduct& AbstractProduct::setDescription(const std::string& des) {
    description = des;
    return *this;
}
