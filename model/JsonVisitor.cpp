// direttive di inclusione
#include "JsonVisitor.h"
#include "Fisico.h"
#include "Virtuale.h"
#include "Noleggio.h"

void JsonVisitor::visit(const Fisico* f) {
    // codice per la serializzazione dell'oggetto puntato da f.
    cout << "LOGICA per serializzazione di oggetto di tipo FISICO in JSON\n";
}

void JsonVisitor::visit(const Virtuale* f) {
    // codice per la serializzazione dell'oggetto puntato da f.
    cout << "LOGICA per serializzazione di oggetto di tipo FISICO in JSON\n";
}

void JsonVisitor::visit(const Noleggio* f) {
    // codice per la serializzazione dell'oggetto puntato da f.
    cout << "LOGICA per serializzazione di oggetto di tipo FISICO in JSON\n";
}