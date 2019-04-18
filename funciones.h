#ifndef PRACTICA_4_FUNCIONES_H
#define PRACTICA_4_FUNCIONES_H

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _Nodo{
    int dato;
    char caracter;
    struct _Nodo *L;
    struct _Nodo *R;
}Nodo;

typedef  struct _Arco{
    int dato;
    struct _Arco *R;
}Arco;

Nodo* allocateMem(int dato,char caracter)
{
    Nodo* dummy;
    dummy = (Nodo*)malloc(sizeof(Nodo));
    dummy -> dato = dato;
    dummy -> caracter = caracter;
    dummy -> R = NULL;
    dummy -> L = NULL;
    return dummy;
}

void mostrar(Nodo* top){
    if(top != NULL){
        while(top != NULL){
            printf("Caracter %c aparece = %d\n",top->caracter, top -> dato);
            top = top -> R;
        }
    }else{
        printf("No contiene elementos tu Lista\n");
    }
}

void inOrden (Nodo *top){
    if (top != NULL){
        inOrden (top->L);
        printf("Elemento = %d\n",top->dato);
        inOrden(top->R);
    }
}

void preOrden (Nodo *top){
    if (top != NULL){
        printf("Elemento = %d\n",top->dato);
        preOrden (top->L);
        preOrden(top->R);
    }
}

void postOrden (Nodo *top){
    if (top != NULL){
        preOrden (top->L);
        preOrden(top->R);
        printf("Elemento = %d\n",top->dato);
    }
}

void alta(Nodo ** top, int dato,char caracter)
{
    if(*top == NULL){
        *top = allocateMem(dato,caracter);
    }
    else if(dato < (*top)->dato){
        alta(&(*top)->L,dato,caracter);
    }
    else{
        alta(&(*top)->R,dato,caracter);
    }
}

void moveleft(Nodo **top)
{
    Nodo *a,*p;
    p=(*top);
    a=(*top)->L;
    while(a->R!=NULL)
    {
        p=a;
        a=a->R;
    }
    (*top)->dato=a->dato;
    if(p==(*top))
    {
        p->L=a->L;
    }
    else
    {
        p->R=a->L;
    }
    (*top)=a;
}

void baja(Nodo **top,int dato)
{
    Nodo *aux;
    if(*(top)==NULL)
    {
        puts("El arbol esta vacio");
    }
    else
    {
        if(dato<(*top)->dato)
        {
            baja(&(*top)->L,dato);
        }
        else if(dato>(*top)->dato)
        {
            baja(&(*top)->R,dato);
        }
        if(dato==(*top)->dato)
        {
            aux = (*top);
            if (aux->L==NULL)
            {
                (*top)=aux->dato;
            }
            else if(aux->R==NULL)
            {
                (*top)=aux->L;
            }
            else
            {
                moveleft(&aux);
            }
            free(aux);
        }
    }
}

int size(Nodo *top)
{
    if (top==NULL)
        return 0;
    else
        return(size(top->L) + 1 + size(top->R));
}

int recorrido(Nodo *top) {
    int i = 0;
    if (top != NULL) {
        while (top != NULL) {
            top = top->R;
            i++;
        }
    }
    return i;
}

Nodo* altainicio(int dato, Nodo* top,char caracter)
{
    int t = recorrido(top);
    Nodo *box;
    box = allocateMem(dato,caracter);
    if(top != NULL){
        if(t>0)
        {
            box->R=top;
            top->L=box;
        }
    }
    top = box;
    return top;
}

Nodo* altafinal(int dato, Nodo* top,char caracter) {
    Nodo *box, *aux;
    box = allocateMem(dato,caracter);
    if (top==NULL)
    {
        top = altainicio(dato,top,caracter);
    }
    else{
        aux = top;
        while (aux->R != NULL) {
            aux = aux->R;
        }
        aux->R = box;
        box->L = aux;
        box->R = NULL;
    }
    return top;
}

Nodo* Alta_Dato(Nodo *top, int dato_nuevo, int dato_busqueda,char caracter){
    Nodo *aux, *nuevo;
    aux = top;
    nuevo = allocateMem(dato_nuevo,caracter);
    if (top == NULL){
        puts("Lista sin archivos");
        return top;
    } else {
        while(aux->R != NULL){
            if (aux->dato == dato_busqueda){

                /*nuevo->R = aux->R;
                nuevo -> L = aux;
                aux->R = nuevo;
                nuevo -> R -> L = nuevo;
                break;*/
            }else{
                aux = aux->R;
            }
        }
    }
    return top;
}

Nodo *bajainicio(Nodo* top){
    Nodo* aux;
    if(top != NULL){
        aux = top;
        top = aux -> R;
        top->L=NULL;
        free(aux);
    }
    puts("Elmininado\n");
    return top;
}

Nodo *bajainterpos(Nodo *top,int posicion)
{
    Nodo *aux = NULL, *borrar = NULL;
    aux = top;
    int t = recorrido(top);
    if(posicion>t||posicion<0)
    {
        puts("Error en el numero de la posicion introducida");
        return aux;
    }
    if(top!=NULL)
    {
        if(t>1)
        {
            for (int i = 0; i < posicion-2 ; ++i) {
                aux = aux ->R;
            }
            borrar = aux ->R;
            aux ->R = borrar->R;
            borrar->R->L=aux;
            free(borrar);
        }
    }
    return top;
}

Nodo *ordenar_seleccion(Nodo *top) {
    Nodo *aux, *aux2;
    aux = top;

    if(top!=NULL)
    {
        while (aux->R != NULL) {
            aux2 = aux->R;
            while (aux2 != NULL) {
                if (aux->dato>aux2->dato) {
                    int var = aux->dato;
                    aux->dato = aux2->dato;
                    aux2->dato = var;

                    char let = aux->caracter;
                    aux->caracter = aux2->caracter;
                    aux2->caracter = let;
                }
                aux2 = aux2->R;
            }
            aux = aux->R;
        }
    }
    return top;
}

char *textoconvertido(char* letras) {

    int q=0;

    if(letras !=NULL)
    {
        while(letras[q]!='\0')
        {
            letras[q]= tolower(letras[q]);
            if(letras[q]=='\361'||letras[q]=='\321')
                letras[q] = 'n';
            else if(letras[q]=='\300'||letras[q]=='\301'||letras[q]=='\340'||letras[q]=='\341')
                letras[q]= 'a';
            else if(letras[q]=='\310'||letras[q]=='\311'||letras[q]=='\350'||letras[q]=='\351')
                letras[q]='e';
            else if(letras[q]=='\314'||letras[q]=='\315'||letras[q]=='\354'||letras[q]=='\355')
                letras[q]='i';
            else if(letras[q]=='\322'||letras[q]=='\323'||letras[q]=='\326'||letras[q]=='\362'||letras[q]=='\363'||letras[q]=='\366')
                letras[q]='o';
            else if(letras[q]=='\331'||letras[q]=='\332'||letras[q]=='\334'||letras[q]=='\371'||letras[q]=='\372'||letras[q]=='\374')
                letras[q]='u';
            q++;
        }
    }
    puts("normaliza datos\n");

    return letras;
}

Nodo *listapost(char *s) {
    int c=0;
    Nodo *lista=NULL;
    int count[27];
    char abc[27]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','+'};
    for (int i = 0; i < 27; ++i) {
        count[i]=0;
    }

    puts("asies\n");
    while (s[c] != '\0') {
        if (s[c] >= 'a' && s[c] <= 'z' )
            count[s[c]-'a']++;
        else if(s[c]==' ')
            count[26]++;
        c++;
    }
    puts("contabiliza letras\n");

    for (int j = 0; j < 27; j++) {
        if (count[j] != 0) {
            lista = altafinal(count[j], lista, abc[j]);
        }
    }
    puts("crea la lista\n");
    lista = ordenar_seleccion(lista);
    puts("ordena lista\n");
    return lista;
}

/*
Nodo *buildArbol(Nodo *Lista)
{
    Nodo *arbol;



    return arbol;
}*/

#endif