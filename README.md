# TODO

### PRIORITARIO
1. Provare ad implementare la CustomScrollArea (presente all'interno del file .dia nella cartella doc/).

### MODEL
1. aggiungere ad AbstactProduct.h il campo std::string imagePath
2. aggiungere ad AbstactProduct.h il campo std::string description 
3. Rinominare le interfacce appartenenti alla persistenza dei dati in quanto non sono proprio delle interfacce pure. <br>
    In particolare queste sono delle classi astratte (ex: IFile -> AbstractFile, IReader -> AbstractReader).

2. ### GUI 
1. Guardare il file creato in GoodNotes e cercare la documentazione degli elementi della gerarchia segnati in rosa. 
2. Cercare come far apparire una nuova QWindow in risposta ad un segnale o una QAction.
3. ~~cercare la documentazione della scrollArea all'interno della documentazione di Qt.~~
4. ~~Studiare come il search engine di Zanella implementa la persistenza dei dati in JSON.~~
5. Risolvere il problema di renderizzare vari itemRenderer utilizzando le classi aggiunte nel commit #4.
6. Studiare come il search engine di Zanella implementa la visualizzazione dei dati. 
7. Implementare i seguenti metodi:
    1. createItem()
    2. updateItem()
    3. showItem()
    4. deleteItem()
8. Pianificare la GUI

# IDEE

1. Mio ResultWidget: utilizzare una QScrollArea per poter mostrare i risultati di un filtro 
2. Classe filter: modella un filtro che viene fatto sugli oggetti del contenitore. 
3. Avere tre bottoni diversi per creare un articolo da inserire nel catalogo (fisico, virtuale, noleggio). Quando uno di <br> questi viene clicckato, emette un segnale, il quale triggera l'editor giusto per poter creare un nuovo prodotto <br>
da inserire nel catalogo.


