# TODO

### PRIORITARIO
~~1. Provare ad implementare la CustomScrollArea (presente all'interno del file .dia nella cartella doc/).~~ <br>
~~2. Finire la pianificazione delle AZIONI.~~ <br>
    1. ~~Leggere documentazione di QStackedWidget per capire come aggiungere i vari Widget.~~<br>
    2. ~~definire i vari widget da poter aggiungere alla stack di widget e dove inserire (in quale parte della mainWindow) la 
        stack di widget.~~ <br>
3. Riguardare tutte le azioni.
4. Implementare tutto.
5. Testare e debuggare (in particolare allocazione e deallocazione della memoria dinamica).

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
DOVE: la funzione che crea il dataset deve essere uno slot della mainWindow `void createDataset()`. <br>
COSA FA: la funzione crea un nuovo file all'interno della cartella selezionata.

```cpp
#include <>
MainWindow::createDataset() {
    // copiare l'implementazione di zanella
    QString path = QFileDialog::getSaveFileName(
        this,
        "Creates new Dataset",
        "./",
        "JSON files *.json"
    ); 
    if (path.isEmpty()) { // questo serve in caso l'utente non abbia creato alcun file
        return;
    }
    if (buffer != nullptr) { // controllo che serve per controllare se nel buffer vi siano oggetti. 
        delete buffer;
    }
    buffer = new Buffer();
    memoria.clear();
    create_item->setEnabled(true);
    showStatus("New dataset created.")
}
```
`showStatus()` è un metodo dell `mainWindow`.

```cpp
MainWindow::showStatus(const QString& status) {
    statusBar()->showMessage(status, 5000);
    // 5000 specifica per millisecondi il messagio rimane attivo nella status bar. 
}

```

#### IMPORTAZIONE DATASET 
Quest'azione corrisponde alla serializzazione degli oggetti (scrittura, da oggetti ad un formato scelto, nel file di dataset creato). <br>
Nella soluzione di Zanella questo risulta abbastanza chiaro come farlo. in ogni caso per farlo bisogna usare le classi che ho implementato per serializzare/deserializzare i dati. <br>

CHI LA COMPIE: bottone => signal => slot (bottone della toolbar presente nella mainwindow) <br>
DOVE: la funzione slot nella main window chiamata loadFromDataset(); <br>
COSA FA: la funzione serializza i dati in questo modo:

1. Tramite il puntatore a file, legge il contenuto del file => ritorna un std::vector<AbstractProduct*>. <br>
2. Inserire sia nel buffer che nella memoria tutti i prodotti. Questo torna poi utile per molti tipi di controlli che possono essere fatti sull'inserimento di un nuovo prodotto. 
3. Chiama la funzione render all'interno del resultWidget.

L'ultimo punto permette di renderizzare tutti i risultati all'interno del result widget non appena si voglia importare un nuovo dataset. <br>

Il codice dovrebbe essere una cosa di questo tipo:
```cpp
void loadDataset() {
    JsonReader reader()
    JsonConverter converter(reader);
    std::vector<AbstractProduct*> aux = fileHandle->ReadFrom(converter);

    // Bisogna tenere a mente che il metodo fileHandle->ReadFrom(converter)
    // Crea degli abstractProduct all'interno della memoria dinamica (guardare l'implementazione). 
    // Quindi bisogna aggiungere questi elementi sia al buffer sia alla memoria. 

 
    for(auto it = aux.begin(); it != aux.end(); it++) {
        buffer.insert((*aux).getId(), aux); // inserimento buffer
        contenitore->insert(aux); // inserimento memoria
    }
    
    resultsWidget->renderResults(aux);
}
```

#### ESPORTAZIONE DATASET (importazione degli oggetti in memoria da uno dei possibili file creati in precedenza).

CHI LA COMPIE: bottone => signal => slot (bottone della toolbar presente nella mainwindow) writeToFile(). <br>
DOVE: la funzione slot nella main window chiamata `writeToFile();` <br>
COSA FA: tramite puntatore al file `jsonFile JsonFile*`  nella MainWindow, si utilizza il metodo WriteTo(const vector<AbstractProduct*>&, const JsonConverter&); <br>
All'interno del signal `writeToFile()`: 

1. Prendere il contenuto del buffer tramite il puntatore presente nella MainWindow; questo lo si fa con il metodo ReadAll() presente all'interno del buffer.<br>
2. Passare il vettore alla funzione JsonFile& WriteTo. Questa garantisce di scrivere gli oggetti in formato json all'interno del file che si trova al percorso <br>
specificato dall'oggetto puntato dal puntatore AbstractFile* presente nella MainWindow. <br>
NOTA BENE: Questa funzione lascia intatto il buffer. 

```cpp
void writeDataset() {
    std::vector<AbstractProduct*> aux = buffer->readAll(); // readAll

    JsonReader reader();
    JsonConverter converter(reader);
    fileHandle->writeToFile(aux, converter);

    std::cout << "Dataset Salvato" << std::endl;
    unsavedChanges = false;
}
```

ATTENZIONE: nella funzione writeToFile viene creato un QJsonArray; questo contiene dei QJsonObject. <br>
I `QJsonObject` vengono creati diversamente in base al tipo dinamico del puntatore ad `AbstractProduct*`, il che suggerisce che si debba usare il visitor pattern
per generare diversi QJsonObject. <br>

Questo lo si risolve creando la seguente classe, che implementa l'interfaccia IConstVisitor. <br>
Viene implementata questa in quanto i puntatori agli oggetti sono soplamente utili in lettura. 

```cpp
#include <QJsonObject>
#include "IConstProductVisitor.h"

class JsonVisitor: public IConstProductVisitor {
private:
    QJsonObject jsonObject;
public:
    virtual void visit(const Virtuale&);
    virtual void visit(const Fisico&);
    virtual void visit(const Noleggio&);
    QJsonObject getJsonObject();
};

```

#### CREAZIONE DI UN PRODOTTO DA AGGIUNGERE AL CATALOGO.

CHI LA COMPIE: bottone presente all'interno della toolbar nella mainWindow => signal clicked() => slot. <br>
DOVE: lo slot è all'interno della MainWindow chiamato `createItem()`. <br>
COSA FA: la funzione slot esegue il seguente codice. <br>

1. Pulisce la stack di widget all'interno della MainWindow tramite il puntatore `QStackedWidget* stackedWidget` per poi far comparire un widget chiamato `ItemCreator`. <br>
La soluzione di Zanella riadattata al mio modello della GUI è il seguente:

```cpp
void MainWindow::createItem() {
    clearStack(); // da implementare
    QScrollArea* scrollArea = new QScrollArea(); 
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll_area->setWidgetResizable(true);
    ItemCreator* createWidget = new ItemCreator(this); // puntatore alla mainwindow
    scroll_area->setWidget(createWidget);
    stacked_widget->addWidget(scrollArea);
    stacked_widget->setCurrentIndex(1); // I Widgget aventi come indice 1 sono quelli che si possono elminare all'interno del metodo clearStack().
    has_unsaved_changes = true;
    showStatus("Creating a new item.", 0);
}
```

2. All'interno dello `SLOT(apply())`, triggerato dal `QPushButton* buttonCreate` appartenente all' `ItemCreator` controllo che l'identificatore dell' `AbstractProduct*` non sia già presente all'interno del buffer. Siccome il puntatore al buffer è contenuto nella mainWindow, `ItemCreator` deve avere un puntatore alla mainWindow. 
Il buffer internamente è una `std::map<unsigned int, AbstractProduct*>` => la verifica di ciò può essere fatta in questo modo: 

`if (buffer[(*AbstractProduct).getId()] == null) then OK, else NOT OK.`

4. se OK => il prodotto appena creato può essere inserito all'interno del catalogo. In particolare deve essere inserito all'interno del buffer, all'interno di `Contenitore* memoria` di `AbstractProduct*`.
5. se NOT OK => il prodotto non puà essere inserito. Di conseguenza quello che si può fare è far apparire una finestra di dialogo che dice che il seguente prodotto non può essere inserito.

Il codice è più o meno questo.

```cpp
void ItemCreator::apply() { 
    // uno degli editor crea un prodotto e lo allooca nello HEAP
    Item::AbstractProduct* item = editor->create(); 

    // setup oggetti che servono per i controlli. 
    Buffer* buffer = mainWindow->getBuffer();
    Memory* memoria = mainWindow->getMemoria();
    const std::map<unsigned int, AbstractProduct*>& m = buffer->getMap(); // const in quanto serve solo in lettura la mappa

    if (m[item->getId()) {
        std::cout << "elemento non inserito in quanto l'identificatore esiste già" << std::endl;
        delete item; // questo in quanto, nel caso sia gia' presente un item avente lo stesso id
                     // non serve piu' questo item in memoria.
    } else {
        (*buffer).insert(item->getId(), item); // inserimento all'interno del buffer
        (*memoria).add(item); // inserimento all'interno della memoria
        mainWindow->search(nullptr); 
    }
}
```

OSSERVAZIONI
1. metodo `ItemEditor::create()`: secondo la struttura riadattata degli oggetti grafici per la creazione e modifica del prodotto, nella classe `AbstractEditor` deve esserci un metodo create, in quanto ogni editor deve poter creare un AbstractProduct* avente tipo dinamico diverso. <br>
Il metodo create di un determinato prodotto implementa la logica seguente; prendiamo, per esempio la creazione di un prodotto fisico a noleggio: <br>

```cpp
AbstractProduct* EditorNoleggio::create() {
    // prendere i valori dagli elementi grafici
    int identifier = boxId->value();
    QString name = boxName->text();
    QString prezzo = boxPrezzo->value();
    QString imagePath = boxImagePath->text();
    QString noleggiatore = boxNoleggiatore->text();
    QString noleggiante = boxNoleggiante->text();

    // passare alla creazione di AbstractProduct*
    Item::AbstractProduct* item = new Noleggio(identifier, name, description, imagePath, noleggiatore, noleggiante);
    return item;
}
```
2. metodo `MainWindow::search(Filter* filtro)`: per capire come funziona fare riferimento alla sezione [ricerca di un prodotto](#ricerca-di-un-prodotto-aggiunto-al-catalogo-mediante-filter-widget)

#### VISUALIZZAZIONE DI UN PRODOTTO AGGIUNTO AL CATALOGO.
Questo in realtà è abbastanza opzionale in quanto una visualizzazione (lista di ListItem nella scrollbar) la si ha già.  

#### MODIFICA DI UN PRODOTTO AGGIUNTO AL CATALOGO.

CHI LA COMPIE: bottone presente all'interno del ListItem => signal clicked => slot. <br>
DOVE: lo slot è all'interno della mainWindow: `void editItem(AbstractProduct*)`. <br>
PROBLEMI: praticamente sono le stesse problematiche dell'eliminazione di un prodotto in termini di segnali e slot con qualche complicazione aggiuntiva. <br>

1. La modifica dipende dal tipo del prodotto che si vuole modificare.
2. L'editor di un prodotto deve poter modificare il prodotto "giusto", nel senso che deve modificare il prodotto puntato dal listItem che ha segnalato <br> 
il click del pulsante edit.
3. dopo la modifica del prodotto, bisogna renderla visibile all'interno del resultsWidget.

SOLUZIONE 1: Dato che ogni listItem ha un bottone modifica prodotto => signal. <br>
Questo signal deve essere connesso ad uno slot presente nella mainWindow chiamato `updateItem(AbstractProduct*)`.
Per vedere la propagazione di `AbstractProduct*` alla mainwindow, andare alla sezione di [eliminazione](#eliminazione-di-un-prodotto-aggiunto-al-catalogo)

Siamo ora all'interno della funzione `updateItem(AbstractProduct*)`:

```cpp
void MainWindow::updateItem(const AbstractProduct* item) {
    stackedWidget->clearstack(); // copiare questo metodo da Zanella. 
}
```
In base al tipo dinamico di item, si puo' renderizzare e mettere all'interno dello stackedWidget uno degli editor per ognuno dei tipi (EditorFisico, EditorVirtuale e EditorNoleggio). <br>
Questo lo si può fare tramite il Visitor design pattern (in particolare sfruttiamo la versione IConstVisitor di questo).

```cpp
class Virtuale;
class Fisico;
class Noleggio;

class IConstProductVisitor {
public:
    virtual ~IConstProductVisitor() {};
    virtual void visit(const Virtuale&) = 0;
    virtual void visit(const Fisico&) = 0;
    virtual void visit(const Noleggio&) = 0;
};
```
Quindi possiamo creare una classe ItemEditorRender che implementa quest'interfaccia. la classe è fatta in questo modo:

```cpp
#include "IConstVisitor.h"

class ItemEditorRenderer : public IConstVisitor {
private:
	QWidget* widget;
public:
	virtual void visit(const Virtuale&);
	virtual void visit(const Fisico&);
	virtual void visit(const Noleggio&);	
	QWidget* getRenderedWidget() const;
};
```
Ognuno di questi metodi ha un implementazione diversa, analoga al seguente esempio: 

```cpp
virtual void visit(const Fisico& element) {
    // render EditorFisico* di tipo QWidget.
    EditorFisico* editor = new EditorFisico(nullptr, &element);
    widget = editor;
}
```
Di conseguenza, per ognuno dei tipi, si devono implementare degli editor appositi: EditorFisico, EditorVirtuale e EditorNoleggio. <br>
A questo punto, il signal updateItem() diventa così.

```cpp
void MainWindow::updateItem(AbstractProduct* item) {
    stackedWidget->clearstack(); // copiare questo metodo da Zanella. 
    IConstVisitor* editorRenderer = new ItemEditorRenderer();
    item.accept(editorRenderer);
    QWidget* editor = editorRenderer.getRenderedWidget();
    stackedWidget->addWidget(editor);
}
```

SOLUZIONE 2
Sappiamo che ogni listItem ha un puntatore al prodotto che vuole rappresentare; <br>
Questo viene propagto al signal editItem(AbstractProduct\*) presente nella mainWindow.
La soluzione in realtà è nella struttura dell'AbstractEditor, in quanto, quando viene invocato il metodo visit, si crea un editor ad hoc passandogli il puntatore 
al prodotto da modificare. <br>
Una volta modificato questo prodotto, si può propagare il cambiamento alla MainWindow. <br>
La struttura della classe Editor è la seguente:

```cpp
class AbstractEditor : public QWidget {
private:
	AbstractProduct* subject;
    QLineEdit* boxId;
    QSpinBox* boxPrezzo;
    QLineEdit* boxNamel;
    QLineEdit* boxImagePath;
public:
	virtual ~AbstractEditor() {};
	AbstractEditor(AbstractProduct* item, QWidget* parent = nullptr) : QWidget(parent), subject(item) {} // costruttore di default.
			
public slots:
    void update(); // da collegare al bottone apply changes 
    void create(); // da collegare al bottone apply
signals:
	// SIGNALS
};
```

SOLUZIONE 3

Per propagare la modifica dell'item si possono adottare diverse strategie. la più semplice nel mio caso potrebbe essere la seguente. 
Modificare la classe AbstractEditor in questo modo.

```cpp
class AbstractEditor : public QWidget {
private:
	AbstractProduct* subject;
	MainWindow* mainWindow; // AGGIUNTO
    QLineEdit* boxId;
    QSpinBox* boxPrezzo;
    QLineEdit* boxNamel;
    QLineEdit* boxImagePath;   
    QPushButton* applyChangesButton; // AGGIUNTO
public:
	virtual ~AbstractEditor() {};
	AbstractEditor(QMainWindow* window, AbstractProduct* item, QWidget* parent = nullptr) : QWidget(parent), mainWindow(window), subject(item) {} // costruttore di default.
public slots:
    void update();  
    void create(); 
};
```

Il metodo setMainWindow(MainWindow* w) è definito così:

```cpp
void setMainWindow(MainWindow* w) {
    mainWindow = w;    
};
```

All'interno del metodo update posso fare tutto quello che c'è da fare in quanto ho il puntatore alla mainWindow:
1. Controllare se l'update che si vuole applicare sia fattibile oppure no; in caso lo fosse:
    1. Richiamare l'update dell'item all'interno dela mainWindow tramite l'api della memoria.
    2. Richiamare l'update del buffer tramite la sua API.
    3. fare il refresh degli elementi grafici.

Il metodo update è piu' o meno il seguente.

```cpp
void AbstractEditor::update() {
    // prendere valori da oggetti grafici.
    

    unsigned int previousId = subject->getIdentifier();
    unsigned int currentId  = boxId->getText();
        
    if (previousId == currentId) {
        // ok modifico tutto  
        subject->setId(currentId);
        // prendo gli oggetti grafici e setto quello che c'e da settare.
        
        // ...
        (mainWindow->getMemoria())->update(subject);
        (mainWindow->getBuffer())->modify(currentId, subject);
        mainWindow->setUnsavedChanges(true);
    } else  { // vuol dire che ho un id che non corrisponde piu' al prodotto
        if (!(mainWindow->getBuffer()->exists(currentId))) {
        // rimuovere l'elemento precedente dalla map
        (mainWindow->getBuffer())->erase(previosId);
        // effettuare la modifica all'elemento in memoria
        (mainWindow->getBuffer())->modify(currentId, subject);
        // aggiungerlo al buffer
        (mainWindow->getMemoria())->update(subject);
        // settare cambiamenti non salvati
        mainWindow->setUnsavedChanges(true);
        } else {
            // errore. l'item non puo' essere modificat in quanto l'id è stato modificato in modo poco opportuno
            std::cout << "errore durante la modifica del prodotto" << std::endl;
        }
    }
    // In ogni caso
    mainWindow->clearStack(); // importante 
    mainWindow->search(nullptr); // importante
}
```
REFRESH ELEMENTI GRAFICI
All'interno del ResultsWidget, ho un `std::vector<ListItem*>`.  <br>
Dato che, nella MainWindow vi è un puntatore all'oggetto resultsWidget, quello che posso fare è creare <br>
un metodo refresh(), da porre all'interno della MainWindow.

Questo metodo scorre il buffer di elementi e, per ogni elemento (\*) aggiorna il contenuto. <br>
Siccome `std::vector<ListItem*>` può contenere dei ListItem Diversi, allora ogni ListItem deve poter implementare la sua logica di refresh. 
Questo tuttavia risulta problematico in quanto la rappresentazione di ListItem ha solamente un puntatore ad un QWidget generato al momento del rendering.

SOLUZIONE 3.1
è veramente necessario fare il refresh di ogni elemento grafico? d'altra parte, se modifico un prodotto, modifico solo quel prodotto. <br>
è naturale domandarsi come possa modificare solamente l'oggetto grafico che lo rappresenta.

#### ELIMINAZIONE DI UN PRODOTTO AGGIUNTO AL CATALOGO
CHI LA COMPIE: bottone presente all'interno del ListItem => signal clicked => slot. <br>

PROBLEMI:
1. All'interno della MainWindow: ho solamente i puntatori ai seguenti widget: SearchWidget e FilterWidget. <br>
2. Lo slot `deleteItem(AbstractProduct*)` all'interno della MainWindow deve essere connesso ad un segnle affinché possa essere eseguito. <br>

PRIMA SOLUZIONE
1. ListItem connette il segnale clicked() di QPushButton ad uno slot (privato in quanto serve solamente a questo widget per poter emettere il segnale) che emette un segnale del tipo `signal(AbstractProduct*)`.
2. All'interno del SearchWidget aggiungere il medesimo slot privato che fa esattamente la stessa cosa. 
3. Collegare il segnale emesso dal SearchWidget allo slot deleteItem() tramite il puntatore SearchWidget presente nella MainWindow. <br>

Il segnale che viene emesso sia da listItem che dallo slot può chiamarsi `itemDeleted(AbstractProduct*)`. <br>
Questo slot privato deve essere connesso al tasto eslimina durante la costruzione di `ListItem`. <br>
Essa avviene circa in questo modo:

```cpp
ListItem::ListItem(QWidget* parent) : QWidget(parent) {
    //... inizializzazine oggetti grafici per rappresentare un AbstractProduct*

    connect(editButton, SIGNAL(clicked()), this, SLOT(slotItemSelected()));         
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(slotItemDeleted()));         
}
```
Lo slot `slotItemDeleted()` all'interno di `ListItem` implementa la seguente logica:

```cpp
ListItem::slotItemSelected() {
    emit signalDeletedItem(item);
}

```
Per quanto riguarda la connessione con il resultWidget, questa viene fatta nel momento della costruzione

```cpp
ResultsWidget::ResultsWidget(QWidget* parent) : QWidget(parent) {
    
    // dal puntatore alla mainwindow prendiamo il contenitore, nel quale dobbiamo inserire un metodo getData() che ritorna un std::vector<AbstractProduct*>
    std::vector<AbstractProduct*> vettore = (mainWindow->getContenitore())->getData();

    // inizializzazione std::vector<ListItem*> 
    for(auto it = vettore.begin(); it != vettore.end(); it++) {
        ListItem* listItem = new ListItem(this, *it);        
        connect(listItem, SIGNAL(signalDeltedItem(AbstractProduct*), mainWindow, SLOT(deleteItem(AbstractProduct*)));
    }
}
```

La soluzione più semplice per l'implementazione di `void deleteItem(AbstractProduct*)` all'interno della mainWindow è la seguente.

```cpp
void MainWindow::deleteItem(AbstractProduct* item) {
    // pulire la stack dei widget
    clearstack();

    // deallocare la memoria del prodotto
    buffer->delete(item);
    memoria->delete(item);

    // refreshare il resultWidget
    search(nullptr);
}
```

Questa logica si può riutilizzare per la propagazione di `AbstractProduct*` durante la'operazione di modifica, la quale scatta tramite il `SIGNAL(clicked())` di editButton all'interno di `ListItem`.

SECONDA SOLUZIONE (scartata)

Si basa sull'utilizzo del campo parent del widget ListItem.
1. Ogni qual volta che inizializzo un ListItem e lo aggiungo alla lista presente all'interno del searchWidget, inizializzo <br>
il suo campo parent con il puntatore al searchWidget.
2. Creo un slot privato all'interno del widget chiamato callForDeleteItem() (il nome è solo un esempio). Questo slot emette un segnale del tipo signal( AbstractProduct* ).

#### RICERCA DI UN PRODOTTO AGGIUNTO AL CATALOGO MEDIANTE FILTER WIDGET

1. bisogna progettare questo widget. L'idea è quella di avere un form layout che cntiene tutti gli elementi grafici per poter applicare il filtro.
quindi bisogna andare a guardare la ducoumentazione di QFormLayout.


SETUP INIZIALE 
All'interno del costruttore della main window, viene invocato il metodo connect che connette, tramite il puntatore al filterwidget, il segnale `signalFilter(Filter*)` allo slot `search(Filter*)`.

COMPORTAMENTE DI QUESTO WIDGET:

1. Prima di caricare un dataset, questo widget non ha controllo, quindi bisogna fare un metodo che si occupi di disabilitare tutti i widget all'interno di esso.
2. dopo l'importazione di un dataset, questo widget ha controllo, quindi bisogna fare un metodo che si occupi di abilitare tutti i widget all'interno di esso. <br>
    Sarà la mainwindow il widget responsabile di abilitare/disabilitare questo widget a seconda dell'avvenuto caricamento di un dataset. 
3. Setup:
    1. scorrere la memoria e trovare il prezzo minimo e massimo dei prodotti all'interno del dataset.
    2. inizializzare le spinbox del prezzo con questi due valori.
4. Una volta ottenuto controllo, il widget accetta valori all'interno del suo valore
5. una volta presi i valori, questo è quello che dovrebbe succedere nello slot `slotEmitSignalFilter()`.

```cpp
#include "SubstringMatcher.h"
#include "PriceMatcher.h"
void FilterWidget::slotEmitSignalFilter() {
    if (currentFilter != nullptr) { // vuol dire che è già stato applicato un filtro precedentemente 
        delete currentFilter; // richiama il distruttore di Filter.
    }
    Filter* aux = new Filter(); 

    // setup dei vari matcher a seconda di quali checkbox spuntate
    if (boxPrezzo->spuntata()) { // esempio con il filtro del prezzo
        const unsigned int lb = lbbox->getValore();
        const unsigned int ub = ubbox->getValore();
        IMatcher* m = new PriceMatcher(lb, ub);
        aux->addMatcher(m);
    }
    // ... e via dicendo ...

    // settare il currentFilter come aux
    currentFilter = aux;
    emit signalFilter(aux); 
}

```

Quello che deve succedere all'interno dello slot `search(Filter*)` nella mainWindow lo si vede qui:

```cpp
#include "SubstringMatcher.h"
#include "PriceMatcher.h"

void MainWindow::search(Filter* filter) {

    // setup oggetti grafici
    clearstack(); // pulisce la stack da vari elementi che non siano il resultWidget
    stackedWidget->addWidget(resultsWidget); // aggiunge il result widget alla stack.
    stackedWidget->setCurrentIndex(0); // setta il result widget come quello principale (indice 0).
    
    // SETUP RICERCA
    std::vector<AbstractProduct*> filteredProducts; 

    if (filter == nullptr) { // nel caso in cui non siano stati fatti alcuni filtri.
        filteredProducts = getBuffer()->readAll(); 
    } else {
    // scorrere il contenitre e fare questo
        if (filter.matchesAll(contenitore[i]) {
            filteredProducts.pushBack(contenitore[i]);
        }
    }
    render(filteredProducts); // necessità di un metodo render all'interno della mainWindow.

}
```

COSA SUCCEDE SE 
1. Si vuole applicare un nuovo filtro.
2. Si vuol resettare il filterWidget con nessun filtro

In tutti e due i casi si deve eliminare dalla memoria dinamica il contenuto puntato dal puntatore `Filter* currentFilter`. <br>
Per fare questo, tuttava, non basta il distruttore standard di Filter. <br>
Questo, in quanto, gli ogggeti contenuti in `std::vector<IMatcher*>` sono puntatori che puntano ad aree di memoria dinamica. <br>
Di conseguenza, invocare il costruttore standard di `Filter` eliminerebbe solamente la memoria di `std::vector<IMatcher*>`, ma non il contenuto puntato dagli oggetti del vettore. <br>
Il distruttore di `Filter` deve quindi avere la seguente implementazione:

```cpp
class FilterWidget {
private:
// ...
static void destroy() {
    for (auto it = matchers.begin(); it != matchers.end(); it++) {
        delete matchers[it];
    }
}

public:
FilterWidget::~FilterWidget() {
    destroy();    
}

```

MODELLAZIONE DELLA CLASSE FILTRO
Tutto questo è disponibile nell'uml del progetto.

#### RENDERIZZARE GLI ELEMENTI GRAFICI
Le azioni che vanno ad usare il rendere degli elementi grafici sono:
1. [importazione dataset](#importazione-dataset)
2. [ricerda di un prodotto](#ricerca-di-un-prodotto-aggiunto-al-catalogo-mediante-filter-widget)
3. [modifica di un prodotto](#modifica-di-un-prodotto-aggiunto-al-catalogo)

Nel resultWidget è disponibile un metodo `renderResults(std::vector<AbstractProcut*>)`. <br>

# IDEE

1. ~~Mio ResultWidget: utilizzare una QScrollArea per poter mostrare i risultati di un filtro~~
2. Classe filter: modella un filtro che viene fatto sugli oggetti del contenitore. 
3. Avere tre bottoni diversi per creare un articolo da inserire nel catalogo (fisico, virtuale, noleggio). Quando uno di <br> questi viene clicckato, emette un segnale, il quale triggera l'editor giusto per poter creare un nuovo prodotto <br>
da inserire nel catalogo.
4. ~~Utilizzare la classe StackedWidget per poter disporre al posto del resultWidget i vari itemEditor.~~
5. ~~Provare a vedere se eliminando degli elementi programmaticamente dalla QScrollarea questi mantengano una disposizione "senza buchi".~~


NOTA: gli elementi barrati sono  idee che si possono implementare.

### LINK UTILI

https://doc.qt.io/qt-6/qstackedwidget.html#count-prop
