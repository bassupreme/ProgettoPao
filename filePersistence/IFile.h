#ifndef IFILE_H
#define IFILE_H

// direttive di inclusione
#include <string>
#include <vector>
#include "../model/AbstractProduct.h" 

// direttive d'uso
using std::string;
using std::vector;

// dichiarazioni incomplete
class IConverter; 

class IFile { // rinominare ad AbstractFile
private:
    string path; // ogni file ha un percorso 
public:
    virtual ~IFile() {}; // distruttore virtuale
    IFile(const string p);
    const string& getPath() const { return path; }; // implementazione di default
		// serializzazione
    virtual vector<AbstractProduct*> ReadFrom(const IConverter&) = 0;
    virtual IFile& WriteTo(const vector<AbstractProduct*>&, const IConverter&) = 0;
};

#endif
