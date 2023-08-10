#TODO

### PRIORITARIO
~~1. Provare ad implementare la CustomScrollArea (presente all'interno del file .dia nella cartella doc/).~~

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
CHE COSA: bottone => signal => slot (bottone della toolbar presente nella mainwindow) <br>
DOVE: la funzione che crea il dataset deve essere uno slot della mainWindow <br>
OPZIONALE: questo slot possiamo far si che richiami la funzione di importazione del dataset, cosi' che in automatico la creazione del dataset <br>
ne comporti subito l'importazione.
COSA FA: la funzione crea un nuovo file all'interno della cartella selezionata. Poi esegue questi passi (in ordine):

1. richiama la funzione di importazione del dataset.
2. siccome e' nella mainWindow => ha accesso ai suoi campi privati => mediante i puntatori ai widget richiama i metodi per fornire controllo ad essi, e quindi abilitarli.

#### IMPORTAZIONE DATASET 
quest'azione corrisponde alla serializzazione degli oggetti (scrittura, da oggetti ad un formato scelto, nel file di dataset creato) <br>
nella soluzione di zanella questo risulta abbastanza chiaro come farlo. in ogni caso per farlo bisogna usare le classi che ho implementato per serializzare/deserializzare i dati <br>

#### DESERIALIZZAZIONE (importazione degli oggetti in memoria da uno dei possibili file creati in precedenza).
#### CREAZIONE DI UN PRODOTTO DA AGGIUNGERE AL CATALOGO.
#### VISUALIZZAZIONE DI UN PRODOTTO AGGIUNTO AL CATALOGO.
#### MODIFICA DI UN PRODOTTO AGGIUNTO AL CATALOGO.
#### ELIMINAZIONE DI UN PRODOTTO AGGIUNTO AL CATALOGO.


# IDEE

1. Mio ResultWidget: utilizzare una QScrollArea per poter mostrare i risultati di un filtro 
2. Classe filter: modella un filtro che viene fatto sugli oggetti del contenitore. 
3. Avere tre bottoni diversi per creare un articolo da inserire nel catalogo (fisico, virtuale, noleggio). Quando uno di <br> questi viene clicckato, emette un segnale, il quale triggera l'editor giusto per poter creare un nuovo prodotto <br>
da inserire nel catalogo.
