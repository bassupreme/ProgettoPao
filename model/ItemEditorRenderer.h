#ifndef ITEMDEDITORRENDERER_H
#define ITEMDEDITORRENDERER_H

#include "IConstVisitor.h"

class ItemEditorRenderer : public IConstVisitor {
private:
	QWidget* widget;
public:
	virtual void visit(const Virtuale*);
	virtual void visit(const Fisico*);
	virtual void visit(const Noleggio*);	
	QWidget* getRenderedWidget() const;
};

#endif
