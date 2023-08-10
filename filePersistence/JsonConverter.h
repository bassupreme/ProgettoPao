#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

// direttive d'inclusione
#include "IConverter.h"

class JsonConverter : public IConverter {
public:
    JsonConverter(IReader& r); 
    virtual string getJsonFromObject(const AbstractProduct* item); 
    virtual AbstractProduct* getObjectFromJson(const string& json);
};

#endif
