#ifndef JSONFILE_H
#define JSONFILE_H

// direttive d'inclusione
#include <string> 
#include "IFile.h"
#include "../model/AbstractProduct.h"
// direttive d'uso
using std::string;
 
class JsonFile : public IFile {

public:
    JsonFile(const string p); // implementazione specifica
    virtual vector<AbstractProduct*> ReadFrom(const IConverter&); // implementazione specifica
    virtual IFile& WriteTo(const vector<AbstractProduct*>&, const IConverter&); // implementazione specifica
};

#endif