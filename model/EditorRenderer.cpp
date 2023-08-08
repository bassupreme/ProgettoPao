// direttive di inclusione
#include "EditorRenderer.h"
#include "Fisico.h"
#include "Virtuale.h"
#include "Noleggio.h"

void EditorRenderer::visit(Fisico* f) {
    // RENDERING EDITOR PRODOTTO FISICO  
    p = f;
}

void EditorRenderer::visit(Virtuale* v) {
    // RENDERING EDITOR PRODOTTO VIRTUALE  
    p = v;
}

void EditorRenderer::visit(Noleggio* n) {
    // RENDERING EDITOR PRODOTTO A NOLEGGIO
    p = n;
    // connect(buttonApplyNew, clicked, )
}

AbstractProduct* EditorRenderer::getProduct() const {
    return p;
}