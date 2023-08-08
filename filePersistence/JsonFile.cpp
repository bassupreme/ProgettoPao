// direttive d'inclusione
#include "JsonFile.h"

JsonFile::JsonFile(const string p) : IFile(p) {} // implementazione costruttore di default

vector<AbstractProduct*> JsonFile::ReadFrom(const IConverter& converter) {
    
};

IFile& JsonFile::WriteTo(const vector<AbstractProduct*>& prodotti, const IConverter& converter) {

}; // implementazione specifica