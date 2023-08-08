#ifndef ABSTRACTPRODUCT_H
#define ABSTRACTPRODUCT_H
// direttive di inclusione
#include <iostream>
#include <string>
#include "IProductVisitor.h"
#include "IConstProductVisitor.h"

// direttive d'uso
using std::cout;
using std::endl;
using std::string;

// classe astratta
class AbstractProduct {
private:
    const unsigned int id; 
    float prezzo;
    string nome;
public:
    AbstractProduct(const unsigned int i, float p, string n = "product");
    virtual ~AbstractProduct();
    const unsigned int getId() const; 
    const float& getPrezzo() const; 
    AbstractProduct& setPrezzo(const float& p); 
    const string& getNome() const; 
    AbstractProduct& setNome(const string& n); 
    virtual void accept(IProductVisitor* v) = 0;
    virtual void accept(IConstProductVisitor* v) = 0;
};

#endif