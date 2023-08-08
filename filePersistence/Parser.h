#ifndef PARSER_H
#define PARSER_H

// direttive d'inclusione
#include <iostream>
#include <vector>
#include <map>
#include "../model/AbstractProduct.h" 

#include "IReader.h"
#include "IConverter.h"
#include "IFile.h"
#include "JsonReader.h"
#include "JsonConverter.h"
#include "JsonFile.h"

// direttive d'uso
using std::cout;
using std::endl;
using std::map;
using std::vector;

class Parser {
private:
    map<const unsigned int, AbstractProduct*> buffer;

public:
    Parser();
    map<const unsigned int, AbstractProduct*> getBuffer() const;
    void readFromFileIntoBuffer(const JsonFile& file);
    void readFromBufferIntoFile(const JsonFile& file);
};
#endif