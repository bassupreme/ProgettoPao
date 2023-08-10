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

* creazione file dataset (la soluzione sta semplicemente nel vedere l'implementazione del boy zanella)
* serializzazione degli oggetti = importazione dataset (scrittura, da oggetti ad un formato scelto, nel file di dataset creato) <br>
nella soluzione di zanella questo risulta abbastanza chiaro come farlo. in ogni caso per farlo bisogna usare le classi che ho implementato per serializzare/deserializzare i dati

* deserializzazione (importazione degli oggetti in memoria da uno dei possibili file creati in precedenza).
* creazione di un prodotto da aggiungere al catalogo.
* visualizzazione di un prodotto aggiunto al catalogo.
* modifica di un prodotto aggiunto al catalogo.
* eliminazione di un prodotto aggiunto al catalogo.


# IDEE

1. Mio ResultWidget: utilizzare una QScrollArea per poter mostrare i risultati di un filtro 
2. Classe filter: modella un filtro che viene fatto sugli oggetti del contenitore. 
3. Avere tre bottoni diversi per creare un articolo da inserire nel catalogo (fisico, virtuale, noleggio). Quando uno di <br> questi viene clicckato, emette un segnale, il quale triggera l'editor giusto per poter creare un nuovo prodotto <br>
da inserire nel catalogo.
