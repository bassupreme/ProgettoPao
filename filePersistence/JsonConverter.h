#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

// direttive d'inclusione
#include "IConverter.h"

class JsonConverter : public IConverter {
public:
    JsonConverter(IReader& r); 
    virtual string fromObject(const AbstractProduct* item); 
    virtual AbstractProduct* toObject(const string& json);
};

#endif