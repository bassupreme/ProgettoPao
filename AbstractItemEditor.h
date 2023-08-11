#include <QWidget>
#include "AbstractProduct.h" 


class AbstractEditor : public QWidget {
private:
	AbstractProduct* subject;
public:
	virtual ~AbstractEditor() {};
	AbstractEditor(AbstractProduct* item, QWidget* parent) : QWidget(parent), subject(item) {} // costruttore di default.
			
public slots:
	// SLOTS
signals:
	// SIGNALS
};
