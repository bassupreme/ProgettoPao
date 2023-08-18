#ifndef NOLEGGIO_H
#define NOLEGGIO_H

#include "Fisico.h"

class Noleggio : public Fisico {
private:
    const std::string noleggiante; // chi mette a noleggio.
    std::string noleggiatore; // chi prende a noleggio.
public:
    Noleggio(const unsigned int i, float p, std::string n, std::string path, std::string description, bool usato = false, std::string noleggiatore = "", std::string noleggiante = "");
    const std::string& getNoleggiante() const; // chi mette a noleggio.
    const std::string& getNoleggiatore() const;
    Noleggio& setNoleggiatore(const std::string& noleggiatore);
    virtual void accept(IVisitor& v);
    virtual void accept(IConstVisitor& v);
};



#endif // NOLEGGIO_H
