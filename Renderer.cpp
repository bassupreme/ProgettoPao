#include "Renderer.h"
#include "Fisico.h"
#include "Virtuale.h"

void Renderer::visit(Virtuale* v) {
    cout << "GUI PER PRODOTTO VIRTUALE\n";
}

void Renderer::visit(Fisico* v) {
    cout << "GUI PER PRODOTTO FISICO\n";
}

void Renderer::visit(Noleggio* v) {
    cout << "GUI PER PRODOTTO A NOLEGGIO\n";
}