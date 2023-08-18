#ifndef ABSTRACTPRODUCT_H
#define ABSTRACTPRODUCT_H
// direttive di inclusione
#include <iostream>
#include <string>
#include "IVisitor.h"
#include "IConstVisitor.h"

// direttive d'uso
using std::cout;
using std::endl;

// classe astratta
class AbstractProduct {
private:
    unsigned int id;
    float prezzo;
    std::string nome;
    std::string imagePath;
    std::string description;
public:
    // costruttore standard e distruttore standard
    AbstractProduct(const unsigned int i, float p, std::string n, std::string path, std::string description);
    virtual ~AbstractProduct();
    // getters e setters
    const unsigned int getId() const;
    const float& getPrezzo() const;
    AbstractProduct& setPrezzo(const float& p);
    const std::string& getNome() const;
    AbstractProduct& setNome(const std::string& n);
    const std::string& getImagePath() const;
    AbstractProduct& setImagePath(const std::string& path);
    const std::string& getDescription() const;
    AbstractProduct& setDescription(const std::string& des);
    // metodi virtuali puri
    virtual void accept(IVisitor& v) = 0;
    virtual void accept(IConstVisitor& v) = 0;
};

#endif
