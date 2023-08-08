// direttive di inclusione
#include "AbstractProduct.h"
#include "Fisico.h"
#include "Virtuale.h"
#include "Noleggio.h"
#include "Renderer.h"
#include "JsonVisitor.h"
#include <vector>
#include "Container.h" 

// direttive d'uso
using std::cout;
using std::endl;
using std::vector;
using Service::Container;


AbstractProduct* searchId(const Container<AbstractProduct*>& contenitore, const unsigned int id) {
    
    Container<AbstractProduct*>::Node* aux = contenitore.getHead();

    while(aux != nullptr) {
        if (aux->getData()->getId() == id) return aux->getData();
        aux = aux->getNext();
    }

    return nullptr;
}

vector<Fisico*> searchUsati(const Container<AbstractProduct*>& contenitore) {

    Container<AbstractProduct*>::Node* aux = contenitore.getHead();
    vector<Fisico*> res;

    while(aux != nullptr) {
        Fisico* p = dynamic_cast<Fisico*>(aux->getData());
        if (p) {
            if (p->getUsato()) res.push_back(p);
        }
        aux = aux->getNext();
    }

    return res;
}

vector<AbstractProduct*> searchPrezzo(const Container<AbstractProduct*>& contenitore, unsigned int lower, unsigned int upper) {

    Container<AbstractProduct*>::Node* aux = contenitore.getHead();
    vector<AbstractProduct*> res;

    while(aux != nullptr) {
        AbstractProduct* p = aux->getData();
        if (p->getPrezzo() > lower && p->getPrezzo() < upper) {
            res.push_back(p);
        } 
        aux = aux->getNext();
    }

    return res;
}

int main() {

    Container<AbstractProduct*> contenitore;

    AbstractProduct* p = new Fisico(1, 28, "porcospino", true);
    AbstractProduct* q = new Virtuale(2, 25, "mama");
    AbstractProduct* r = new Noleggio(3, 13, "dio", "leonardo", "anita");


    // TEST visitor
    Renderer v;

    // TEST contenitore
    contenitore.add(p);
    contenitore.add(q);
    contenitore.add(r);

    /*
    AbstractProduct* res = searchId(contenitore, 2);

    if (res) {
        cout << res->getNome() << "\n";
    } else {
        cout << "NON TROVATO" << "\n"
    }
    */

   vector<Fisico*> usati = searchUsati(contenitore);
   if (usati.size() > 0) cout << "sono stati trovati prodotti usati" << "\n";

   vector<AbstractProduct*> prezzi = searchPrezzo(contenitore, 10, 30);

   if (prezzi.size() > 0) cout << "sono stati trovati prodotti che rispettano il range di prezzo introdotto\n";
   
}