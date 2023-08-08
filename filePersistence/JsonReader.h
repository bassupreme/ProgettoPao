#ifndef JSONREADER_H
#define JSONREADER_H

// direttive d'inclusione
#include "IReader.h"


class JsonReader : public IReader {
private:
    AbstractProduct* readFisico(const string& jsonObject); 
    AbstractProduct* readVirtuale(const string& jsonObject); 
    AbstractProduct* readNoleggio(const string& jsonObject);
public:
    virtual AbstractProduct* read(const string& jsonObject); 
 
};
#endif