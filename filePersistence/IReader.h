#ifndef IREADER_H
#define IREADER_H

// direttive d'inclusione
#include <string>
#include "../model/AbstractProduct.h" 

// direttive d'uso
using std::string;

class IReader {

public:
    virtual ~IReader() {};
    virtual AbstractProduct* read(const string& jsonObject) = 0; 
    // NOTA BENE: in questo metodo virtuale string é solamente
    // un rimpiazzo per quello che sarà alla fine QJsonObject
};

#endif