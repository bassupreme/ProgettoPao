#include "Parser.h"

void Parser::readFromFileIntoBuffer(const JsonFile& file) {
    IReader* reader = new JsonReader();
    IConverter* converter = new JsonConverter(*reader);
    IFile* jsonfile = new JsonFile("path");

    // leggere dal file tutti i prodotti 
    vector<AbstractProduct*> res = jsonfile->ReadFrom(*converter);

    for(vector<AbstractProduct*>::iterator it = res.begin();
        it != res.end();
        it++) {
            AbstractProduct* p = (*it);
            buffer[p->getId()] = p;
        }
 

}

void Parser::readFromBufferIntoFile(const JsonFile &file) {
    
}