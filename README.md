# TODO

### MODEL
1. aggiungere ad AbstactProduct.h il campo std::string imagePath

### GUI 
1. Guardare il file creato in GoodNotes e cercare la documentazione degli elementi della gerarchia segnati in rosa. 
2. Cercare come far apparire una nuova QWindow in risposta ad un segnale o una QAction.
3. cercare la documentazione della scrollArea all'interno della documentazione di Qt.
4. ~~tudiare come il search engine di Zanella implementa la persistenza dei dati in JSON.~~
5. Risolvere il problema di renderizzare vari itemRenderer utilizzando le classi aggiunte nel commit #4.
6. Studiare come il search engine di Zanella implementa la visualizzazione dei dati 
7. Implementare i seguenti metodi:
    1. createItem()
    2. updateItem()
    3. deleteItem()
    4. showItem()

# IDEE

1. Mio ResultWidget: utilizzare una QScrollArea per poter mostrare i risultati di un filtro 
2. Classe filter: modella un filtro che viene fatto sugli oggetti del contenitore. 
3. Avere tre bottoni diversi per creare un articolo da inserire nel catalogo (fisico, virtuale, noleggio). Quando uno di <br> questi viene clicckato, emette un segnale, il quale triggera l'editor giusto per poter creare un nuovo prodotto <br>
da inserire nel catalogo.