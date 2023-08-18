#include <QCoreApplication>
#include <iostream>

#include "AbstractProduct.h"
#include "Virtuale.h"
#include "Fisico.h"
#include "Noleggio.h"
#include "Buffer.h"
#include "Memory.h"

int main()
{
    // CREAZIONE PRODOTTI NELLA MEMORIA HEAP
    AbstractProduct* p1 = new Fisico(1, 2.0, "Carica batterie", "", "descrizione");
    AbstractProduct* p2 = new Fisico(2, 2.0, "Zaino", "", "descrizione");
    AbstractProduct* p3 = new Fisico(3, 2.0, "Portachiavi", "", "descrizione");
    AbstractProduct* p4 = new Fisico(4, 2.0, "Righello", "", "descrizione");

    // TEST BUFFER
    /*
    // TEST CREAZIONE BUFFER
    Buffer b;

    // TEST AGGIUNTA NEL BUFFER
    b.insert(p1->getId(), p1);
    b.insert(p2->getId(), p2);
    b.insert(p3->getId(), p3);
    b.insert(p4->getId(), p4);

    // TEST EXISTS
    if (b.exists(9)) std::cout << "esiste" << std::endl;
    else std::cout << "non esiste" << std::endl;

    // TEST GET
    const AbstractProduct* res = b.get(1); // nota su res possono essere invocati solamente metodi costanti
    std::cout << "Ritornato: " << res->getId() << std::endl;


    // TEST REMOVE
    b.remove(3);

    // TEST STAMPA DEGLI ELEMENTI e METODO READ ALL
    std::vector<AbstractProduct*> vettore =  b.readAll();

    for(std::vector<AbstractProduct*>::const_iterator it = vettore.begin(); it != vettore.end(); it++) {
        std::cout << (*it)->getId() << " " << (*it)->getNome() << std::endl;
    }

    // TEST CLEAR
    b.clear();

    // TEST EMPTY
    if(b.empty()) std::cout << "vuoto" << std::endl;
    else std::cout << "non vuoto" << std::endl;
    */



    // TEST MEMORIA
    Memory m;

    // TEST INSERIMENTO
    // nota bene: l'inserimento viene fatto in testa alla lista
    m.add(p1);
    m.add(p2);
    m.add(p3);
    m.add(p4);


    // TEST RIMOZIONE
    m.remove(p1);
    m.remove(p4);

    // TEST RICERCA


    // TEST PULIZIA
    m.clear();
}
