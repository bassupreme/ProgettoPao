# TODO

### PRIORITARIO
~~1. Provare ad implementare la CustomScrollArea (presente all'interno del file .dia nella cartella doc/).~~ <br>
2. Finire la pianificazione delle AZIONI. <br>
    1. Leggere documentazione di QStackedWidget per capire come aggiungere i vari Widget. <br>
    2. definire i vari widget da poter aggiungere alla stack di widget e dove inserire (in quale parte della mainWindow) la 
        stack di widget. <br>

### MODEL
1. aggiungere ad AbstactProduct.h il campo std::string imagePath
2. aggiungere ad AbstactProduct.h il campo std::string description 
3. Rinominare le interfacce appartenenti alla persistenza dei dati in quanto non sono proprio delle interfacce pure. <br>
    In particolare queste sono delle classi astratte (ex: IFile -> AbstractFile, IReader -> AbstractReader).

### GUI 
~~1. Guardare il file creato in GoodNotes e cercare la documentazione degli elementi della gerarchia segnati in rosa.~~
2. ~~cercare la documentazione della scrollArea all'interno della documentazione di Qt.~~
3. ~~Studiare come il search engine di Zanella implementa la persistenza dei dati in JSON.~~
4. Risolvere il problema di renderizzare vari itemRenderer utilizzando le classi aggiunte nel commit #4.
5. Studiare come il search engine di Zanella implementa la visualizzazione dei dati. 
6. Pianificare la GUI per passi: ogni passo corrisponde all'implementazione di un'azione che si vuole ottenere.

### AZIONI

#### CREAZIONE FILE DATASET 
(la soluzione sta semplicemente nel vedere l'implementazione del boy zanella) <br>
CHI LA COMPIE: bottone => signal => slot (bottone della toolbar presente nella mainwindow) <br>
DOVE: la funzione che crea il dataset deve essere uno slot della mainWindow <br>
OPZIONALE: questo slot possiamo far si che richiami la funzione di importazione del dataset, cosi' che in automatico la creazione del dataset <br>
ne comporti subito l'importazione.
COSA FA: la funzione crea un nuovo file all'interno della cartella selezionata. Poi esegue questi passi (in ordine):

1. richiama la funzione di importazione del dataset.
2. siccome e' nella mainWindow => ha accesso ai suoi campi privati => mediante i puntatori ai widget richiama i metodi per fornire controllo ad essi, e quindi abilitarli.

#### IMPORTAZIONE DATASET 
Quest'azione corrisponde alla serializzazione degli oggetti (scrittura, da oggetti ad un formato scelto, nel file di dataset creato) <br>
Nella soluzione di Zanella questo risulta abbastanza chiaro come farlo. in ogni caso per farlo bisogna usare le classi che ho implementato per serializzare/deserializzare i dati <br>

CHI LA COMPIE: bottone => signal => slot (bottone della toolbar presente nella mainwindow) <br>
DOVE: la funzione slot nella main window chiamata loadFromDataset();
COSA FA: la funzione serializza i dati in questo modo:

1. Tramite il puntatore a file, legge il contenuto del file => ritorna un std::vector<AbstractProduct*>. <br>
2. Inserire nel buffer tutti i prodotti. questo torna poi utile per molti tipi di controlli che possono essere fatti sull'inserimento di un nuovo prodotto. 

#### ESPORTAZIONE DATASET (importazione degli oggetti in memoria da uno dei possibili file creati in precedenza).
CHI LA COMPIE: bottone => signal => slot (bottone della toolbar presente nella mainwindow) <br>.
DOVE: la funzione slot nella main window chiamata writeToFile();
COSA FA: tramite puntatore al file all'interno del widget MainWindow, si hanno a disposizione i metodi di file. 
=>   virtual IFile& WriteTo(const vector<AbstractProduct*>&, const IConverter&) = 0;

1. Prendere il contenuto del buffer (tramite il puntatore presente nella MainWindow) e mettere tutti i valori all'interno di un <br>
std::vector<AbstractProduct*> x.
2. Passare x alla funzione virtual IFile& WriteTo. Questa garantisce di scrivere all'interno del file che si trova al percorso <br>
specificato dall'oggetto puntato dal puntatore AbstractFile* presente nella MainWindow.
Questa funzione lascia intatto il buffer.

#### CREAZIONE DI UN PRODOTTO DA AGGIUNGERE AL CATALOGO.
CHI LA COMPIE: bottone presente all'interno della toolbar nella mainWindow => signal clicked => slot <br>.
DOVE: lo slot è all'interno della MainWindow chiamato createItem().
COSA FA: la funzione slot esegue questo. 

1. Pulisce la stack di widget all'interno della MainWindow per poi far comparire un widget chiamato ItemCreator. 
2. Una volta creato l'item all'intern del widget, questo ritorna un AbstractProduct\*.
3. All'interno del signal apply() controllo che l'identificatore dell' AbstractProduct\* passato mediante signal() dall'itemCreator non sia già presente all'interno del buffer. Siccome il puntatore al buffer è contenuto nella mainWindow, mi serve che vi sia un puntatore alla mainWindow all'interno dell'ItemEditor. 

il buffer internamente è una map\<unsigned int, AbstractProduct\*\>; => la verifica di ciò può essere fatta in questo modo: 
<br>
<br>

if (buffer[(\*AbstractProduct).getId()] == null) then OK.
else NOT OK.

4. se OK => il prodotto appena creato può essere inserito all'interno del catalogo. In particolare deve essere inserito all'interno del buffer, all'interno del contenitore di AbstractProduct* e deve essere creato un listItem all'interno della scrollArea per poter rappresentare l'oggetto appena creato.
5. se NOT OK => il prodotto non puà essere inserito. Di conseguenza quello che si può fare è far apparire una finestra di dialogo che dice che il seguente prodotto non può essere inserito.

Il codice è più o meno questo.
```cpp
void ItemCreatorWidget::apply() {
    int identifier = identifier_input->value();
    QString name = name_input->text();
    QString description = description_input->toPlainText();
    QString image_path = image_input->text();
    ItemEditor::AbstractItemEditor* editor = editors[stacked_editor->currentIndex()];
    Item::AbstractProduct* item = editor->create(identifier, name, description, image_path);
    Buffer* buffer = mainWindow->getBuffer();
    const std::map<unsigned int, AbstractProduct*>& m = buffer->getMap();
    if (m[item.getId() == null) {
        (*buffer).insert(item);
        mainWindow->reloadData();
        mainWindow->getSearchWidget()->search();
    } else {
        std::cout << "elemento non inserito in quanto l'identificatore esiste già" << std::endl;
    }
}
```
#### VISUALIZZAZIONE DI UN PRODOTTO AGGIUNTO AL CATALOGO.
Questo in realtà è abbastanza opzionale in quanto una visualizzazione (lista di ListItem nella scrollbar) la si ha già.  

#### MODIFICA DI UN PRODOTTO AGGIUNTO AL CATALOGO.
CHI LA COMPIE: bottone presente all'interno del ListItem => signal clicked => slot <br>.
DOVE: lo slot è all'interno della mainWindow.

PROBLEMI: praticamente sono le stesse problematiche dell'eliminazione di un prodotto in termini di segnali e slot con qualche complicazione aggiuntiva.

1. La modifica dipende dal tipo del prodotto che si vuole modificare.
2. dopo la modifica del prodotto, bisogna renderla visibile all'interno del resultsWidget.

SOLUZIONE 1: Dato che ogni listItem ha un bottone modifica prodotto => signal. <br>
Questo signal deve essere connesso ad uno slot presente nella mainWindow chiamato updateItem(AbstractProduct\*).
Per la propagazione del segnale vedere la soluzione descritta nel problema dell'eliminazione. <br>

Siamo ora all'interno della funzione updateItem():

```cpp
void MainWindow::updateItem(AbstractProduct\* item) {
    stackedWidget->clearstack(); // copiare questo metodo da Zanella. 
}
```
Ora, in base al tipo dinamico di item, dobbiamo renderizzare e mettere all'interno sullo stackedWidget un widget diverso per ognuno dei tipi (Fisico, Virtuale e Noleggio). <br>
Questo lo si può fare tramite il Visitor design pattern (in particolare sfruttiamo la versione IConstVisitor di questo).

```cpp
class Virtuale;
class Fisico;
class Noleggio;

class IConstProductVisitor {
public:
    virtual ~IConstProductVisitor() {};
    virtual void visit(const Virtuale*) = 0;
    virtual void visit(const Fisico*) = 0;
    virtual void visit(const Noleggio*) = 0;
};
```
Quindi possiamo creare una classe ItemEditorRender che implementa quest'interfaccia. la classe è fatta in questo modo:

```cpp
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
```
Ognuno di questi metodi ha un implementazione analoga al seguente esempio: 

```cpp
virtual void visit(const Fisico*) {
    // render EditorFisico* di tipo QWidget.
    new EditorFisico* editor = new EditorFisico(...);
    widget = editor;
}
```
di conseguenza, per ognuno dei tipi, si devono implementare degli editor appositi: EditorFisico, EditorVirtuale e EditorNoleggio. <br>
A questo punto, il signal updateItem() diventa così.

```cpp
void MainWindow::updateItem(AbstractProduct\* item) {
    stackedWidget->clearstack(); // copiare questo metodo da Zanella. 
    IConstVisitor* editorRenderer = new ItemEditorRenderer(item);
    item.accept(editorRenderer);
    QWidget* editor = editorRenderer.getRenderedWidget();
    stackedWidget->addWidget(editor);
}
```

#### ELIMINAZIONE DI UN PRODOTTO AGGIUNTO AL CATALOGO.
CHI LA COMPIE: bottone presente all'interno del ListItem => signal clicked => slot <br>.

PROBLEMI:
1. All'interno della MainWindow: ho solamente i puntatori ai seguenti widget: SearchWidget e FilterWidget. <br>
2. Lo slot deleteItem() all'interno della MainWindow deve essere connesso ad un segnle affinché possa essere eseguito. <br>

PRIMA SOLUZIONE
1. ListItem connette il segnale clicked() di QPushButton ad uno slot (privato in quanto serve solamente a questo widget per poter emettere il segnale) che emette a sua volta un segnale del tipo signal( AbstractProduct* ).
2. All'interno del SearchWidget aggiungere il medesimo slot che fa esattamente la stessa cosa. 
3. Collegare il segnale emesso dal SearchWidget allo slot deleteItem() tramite il puntatore SearchWidget presente nella <br>
MainWindow.

SECONDA SOLUZIONE (scartata)

Si basa sull'utilizzo del campo parent del widget ListItem.
1. Ogni qual volta che inizializzo un ListItem e lo aggiungo alla lista presente all'interno del searchWidget, inizializzo <br>
il suo campo parent con il puntatore al searchWidget.
2. Creo un slot privato all'interno del widget chiamato callForDeleteItem() (il nome è solo un esempio). Questo slot emette un segnale del tipo signal( AbstractProduct* ).


# IDEE

1. Mio ResultWidget: utilizzare una QScrollArea per poter mostrare i risultati di un filtro 
2. Classe filter: modella un filtro che viene fatto sugli oggetti del contenitore. 
3. Avere tre bottoni diversi per creare un articolo da inserire nel catalogo (fisico, virtuale, noleggio). Quando uno di <br> questi viene clicckato, emette un segnale, il quale triggera l'editor giusto per poter creare un nuovo prodotto <br>
da inserire nel catalogo.
4. Utilizzare la classe StackedWidget per poter disporre al posto del resultWidget i vari itemEditor. 
5. Provare a vedere se eliminando degli elementi programmaticamente dalla QScrollarea questi mantengano una disposizione "senza buchi".  


### LINK UTILI

https://doc.qt.io/qt-6/qstackedwidget.html#count-prop
