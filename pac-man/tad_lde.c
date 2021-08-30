#include "tad_lde.h"



struct nodo *criaNodo(int valor){

    struct nodo *temp;

    temp = malloc(sizeof(struct nodo));
    temp->valor = valor;
    temp->prox  = NULL;
    temp->ante  = NULL;

    return temp;
}


struct lista *criaLista(){

    struct lista *temp;

    temp = malloc(sizeof(struct lista));
    temp->inicio = NULL;
    temp->final  = NULL;
    temp->temNovoNodo = 0;

    return temp;
}


void insereElemento(struct lista *lista, int valor){

    if ( lista->inicio == NULL && lista->final == NULL ){
        lista->inicio = lista->final = criaNodo(valor);
        lista->temNovoNodo = 1;
    }
    else {
        struct nodo *temp = buscaElemento(lista, valor);

        if ( temp == NULL ){
            temp = criaNodo(valor);
            lista->final->prox = temp;
            temp->ante = lista->final; 
            lista->final = temp;
            lista->temNovoNodo = 1;
        }
    }

    return;
}


struct nodo *buscaElemento(struct lista *lista, int valor){

    struct nodo *aux = lista->inicio; 

    while ( aux != NULL && aux->valor != valor ){
        if ( aux->valor == valor )
            return aux;

        aux = aux->prox;
    }

    return aux;
}


void removeElemento(struct lista *lista, int valor){

    struct nodo *temp = buscaElemento(lista, valor);

    if ( temp != NULL ){
        if ( temp == lista->inicio && temp == lista->final ){
            lista->inicio = lista->final = NULL;
        }
        else if ( temp == lista->inicio ){
            lista->inicio       = lista->inicio->prox;
            lista->inicio->ante = NULL;
        }
        else if ( temp == lista->final ){
            lista->final       = lista->final->ante;
            lista->final->prox = NULL;
        }
        else {
            struct nodo *aux; 

            aux       = temp->ante;
            aux->prox = temp->prox;
            aux       = temp->prox;
            aux->ante = temp->ante; 
        }

        free(temp);
    }

    return;
}


void mostraLista(struct lista *lista){

    struct nodo *aux = lista->inicio; 

    while ( aux != NULL ){
        printf(" %d\n", aux->valor);
        aux = aux->prox;
    }

    printf("\n");
    return;
}


void esvaziaLista(struct lista *lista){

    if ( lista->inicio != NULL && lista->final != NULL ){
        struct nodo* aux;

        while ( lista->inicio != NULL ){
            aux = lista->inicio;
            lista->inicio = lista->inicio->prox;
            free(aux);
        }

        lista->final = NULL;
    }

    return;
}


void destroiLista(struct lista *lista){

    esvaziaLista(lista);
    free(lista);
    return;
}
