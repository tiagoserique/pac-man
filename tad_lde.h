#include <stdio.h>
#include <stdlib.h>

struct nodo {

    int valor;
    struct nodo *prox;
    struct nodo *ante;
};

struct lista {

    struct nodo *inicio;
    struct nodo *final;
    int temNovoNodo;
};


/* cria nodo */
struct nodo *criaNodo(int valor);

/* cria lista */
struct lista *criaLista();

/* insere elemento na lista */
void insereElemento(struct lista *lista, int valor);

/* busca elemento na lista*/
struct nodo *buscaElemento(struct lista *lista, int valor);

/* remove elemento na lista */
void removeElemento(struct lista *lista, int valor);

/* mostra lista */
void mostraLista(struct lista *lista);

/* esvazia lista */
void esvaziaLista(struct lista *lista);

/* destroi lista elemento na lista */
void destroiLista(struct lista *lista);



