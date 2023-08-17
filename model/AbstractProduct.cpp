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

const std::string& AbstractProduct::getImagePath() const {
	return imagePath;
}

AbstractProduct& setImagePath(const std::string& path) {
	imagePath = path;
	return *this;
}

const std::string& getDescription() const {
	return description;
}

AbstractProduct& setDescription(const std::string& des) {
	description = des;
	return *this;
}



