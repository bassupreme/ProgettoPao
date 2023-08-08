#include "IProductVisitor.h"
#include "AbstractProduct.h"

class EditorRenderer : public IProductVisitor {
private:
    AbstractProduct* p;
public:
    virtual void visit(Virtuale*);
    virtual void visit(Fisico*);
    virtual void visit(Noleggio*);
    AbstractProduct* getProduct() const;
};