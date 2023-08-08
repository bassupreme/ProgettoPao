#ifndef NOLEGGIO_H 
#define NOLEGGIO_H 
// direttive di inclusione
#include <string>
#include "Fisico.h"

using std::string;

class Noleggio : public Fisico {
private:
    const string noleggiante; // chi mette a noleggio.
    string noleggiatore; // chi prende a noleggio.
public:
    Noleggio(const unsigned int i, float p, bool u, const string note, string nore, string n = "product");
    const string& getNoleggiante() const; // chi mette a noleggio.
    const string& getNoleggiatore() const;
    Noleggio& setNoleggiatore(const string& noleggiatore);
    virtual void accept(IProductVisitor* v);
    virtual void accept(IConstProductVisitor* v);
};

#endif