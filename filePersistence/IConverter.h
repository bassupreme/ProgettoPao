#ifndef ICONVERTER_H
#define ICONVERTER_H

// direttive d'inclusione
#include "../model/AbstractProduct.h"
#include <string>

// direttive d'uso
using std::string;

// dichiarazioni incomplete
class IReader;

class IConverter { // rinominare ad AbstractConverter (in quanto è una classe astratta)
private:
    IReader& reader;
public:
    virtual ~IConverter() {};
    IConverter(IReader& r) : reader(r) {};
    const IReader& getReader() const { return reader; }; // implementazione di default
    virtual string getJsonFromObject(const AbstractProduct* item) = 0; 
    virtual AbstractProduct* getObjectFromJson(const string& json) = 0;
    // NOTA BENE: in questi due metodi virtuali string é solamente
    // un rimpiazzo per quello che sarà alla fine QJsonObject

}; 

#endif
