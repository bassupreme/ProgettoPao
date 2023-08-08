#ifndef PARSER_H
#define PARSER_H

// direttive d'inclusione
#include <iostream>
#include <map>
#include "../model/AbstractProduct.h" 
#include "JsonFile.h" 

// direttive d'uso
using std::cout;
using std::endl;
using std::map;

class Parser {
private:
    map<const unsigned int, AbstractProduct*> buffer;

public:
    map<const unsigned int, AbstractProduct*> getBuffer() const;
    void readFromFileIntoBuffer(const JsonFile& file);
    void readFromBufferIntoFile(const JsonFile& file);
};
#endif