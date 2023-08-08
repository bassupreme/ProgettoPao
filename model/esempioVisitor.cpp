#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;


class Uomo;
class Donna;

// definizione dell'interfaccia visitor
class IVisitor {
public:
    virtual void VisitUomo(const Uomo*) const = 0;
    virtual void VisitDonna(const Donna*) const = 0;
};

// definizione della gerarchia
class Persona {
private:
    const string nome;
    const string cognome;
    unsigned int eta;
public:
    virtual void Accept(IVisitor* v) const = 0;
};

class Uomo : public Persona {
public:
    virtual void Accept(IVisitor* v) const {
        v->VisitUomo(this);
    }
};

class Donna : public Persona {
public:
    virtual void Accept(IVisitor* v) {
        v->VisitDonna(this);
    }
};

// Definizione di una classe che implementa i metodi dell'interfaccia visitor.
// Come si Riesce a vedere, per ogni tipo della gerarchia vengono definiti dei metodi aventi un comportamento diverso. 

class GUIVisitor : public IVisitor {
public:
    virtual void VisitUomo(const Uomo* m) const {
        cout << "print GUI per uomo!" << endl;
    }
    virtual void VisitDonna(const Donna* w) const {
        cout << "print GUI per uomo!" << endl;
    }
};

int main() {
    // creazione del visitor
    IVisitor* visitor = new GUIVisitor(); 

    // creazione dell'oggetto visitor
    const Persona* p = new Uomo();

    // chiamata del metodo che garantisce un comportamento diverso a seconda del tipo
    p->Accept(visitor);
}