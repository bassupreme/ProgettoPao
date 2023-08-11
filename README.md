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

void EditWidget::apply() {
    int identifier = identifier\_input-\>value();
    QString name = name\_input-\>text();
    QString description = description\_input-\>toPlainText();
    QString image\_path = image\_input-\>text();
    ItemEditor::AbstractItemEditor* editor = editors[stacked\_editor-\>currentIndex()];
    Item::AbstractProduct\* item = editor-\>create(identifier, name, description, image\_path);
    Buffer* buffer = mainWindow-\>getBuffer();
    const std::map\<unsigned int, AbstractProduct\*\>& m = buffer-\>getMap();
    if (m[item.getId() == null) {
        (\*buffer).insert(item);
        mainWindow-\>reloadData();
        mainWindow-\>getSearchWidget()-\>search();
    } else {
        std::cout << "elemento non inserito in quanto l'identificatore esiste già" << std::endl;
    }
}
#### VISUALIZZAZIONE DI UN PRODOTTO AGGIUNTO AL CATALOGO.

#### MODIFICA DI UN PRODOTTO AGGIUNTO AL CATALOGO.

#### ELIMINAZIONE DI UN PRODOTTO AGGIUNTO AL CATALOGO.
CHI LA COMPIE: bottone presente all'interno del ListItem => signal clicked => slot <br>.

Problemi:
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
