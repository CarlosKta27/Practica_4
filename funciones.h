#ifndef PRACTICA_4_FUNCIONES_H
#define PRACTICA_4_FUNCIONES_H

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct _Nodo{
    int dato;
    char caracter;
    struct _Nodo *L;
    struct _Nodo *R;
    struct _Nodo *sig;
}Nodo;

typedef struct _Binario{
    char caracter;
    long int bits;
    int nbits;
    char *binario;
    struct _Binario *sig;
}Binario;

Nodo* allocateMem(int dato,char caracter) {
    Nodo *dummy = (Nodo *) malloc(sizeof(Nodo));
    dummy->dato = dato;
    dummy->caracter = caracter;
    dummy->sig=NULL;
    dummy->R = NULL;
    dummy->L = NULL;
    return dummy;
}

Binario *allocateMemo(long int bits,char caracter,int nbits) {
    Binario *dummy = (Binario *)malloc(sizeof(Binario));
    dummy->caracter = caracter;
    dummy->bits = bits;
    dummy->nbits=nbits;
    dummy->binario = "";
    dummy->sig =NULL;
}

int binario ( int n ) {
    if(n==0)
        return n;
    else
        return binario(n/2)*10+n%2;
}

void mostrar(Nodo* top) {
    if (top != NULL) {
        while (top != NULL) {
            printf("Caracter %c >> %d\n", top->caracter, top->dato);
            top = top->sig;
        }
    } else {
        printf("No contiene elementos tu Lista\n");
    }
}

void implementarbin(Binario *Arbol) {
    if (Arbol != NULL) {
        int t = strlen(Arbol->binario);
        if (t == (Arbol->nbits - 1)) {
            char *array = "";
            sprintf(array,"0%s",Arbol->binario);
            Arbol->binario = array;
        }
    }
}

void llenarbinario(Binario* top) {
    Binario *aux = top;
    if (top != NULL) {
        char *array = "";
        while (aux->sig != NULL) {
            int codigo = binario(aux->bits);
            sprintf(array, "%d", codigo);
            aux->binario = array;
            implementarbin(aux);
            printf("Caracter %c >> Bits  %s >> Profundidad %d\n", aux->caracter, aux->binario, aux->nbits);
            aux = aux->sig;
        }
    }
}

void imprimirbinariosfile(Binario *Arbol,FILE *out2) {
    Binario *aux =Arbol;
    if (Arbol != NULL) {
        while (aux != NULL) {
            fprintf(out2,"%s", aux->binario);
            aux = aux->sig;
        }
    }
}

void inOrden (Nodo *top) {
    if (top != NULL) {
        inOrden(top->L);
        printf("Elemento %c = %d\n", top->caracter, top->dato);
        inOrden(top->R);
    }
}

void preOrden (Nodo *top) {
    if (top != NULL) {
        printf("%c >> %d\n", top->caracter, top->dato);
        preOrden(top->L);
        preOrden(top->R);
    }
}

void preOrdenimpresion (Nodo *top,FILE *out) {
    if (top != NULL) {
        fprintf(out,"\r%d %c ",top->dato,top->caracter);
        preOrdenimpresion(top->L, out);
        preOrdenimpresion(top->R, out);
    }
}

void postOrden (Nodo *top) {
    if (top != NULL) {
        postOrden(top->L);
        postOrden(top->R);
        printf("Elemento %c = %d\n", top->caracter, top->dato);
    }
}

void alta(Nodo ** top, int dato,char caracter) {
    if (*top == NULL) {
        *top = allocateMem(dato, caracter);
    } else if (dato < (*top)->dato) {
        alta(&(*top)->L, dato, caracter);
    } else {
        alta(&(*top)->R, dato, caracter);
    }
}

void moveleft(Nodo **top) {
    Nodo *a, *p;
    p = (*top);
    a = (*top)->L;
    while (a->R != NULL) {
        p = a;
        a = a->R;
    }
    (*top)->dato = a->dato;
    if (p == (*top)) {
        p->L = a->L;
    } else {
        p->R = a->L;
    }
    (*top) = a;
}

void baja(Nodo **top,int dato) {
    Nodo *aux;
    if (*(top) == NULL) {
        puts("El arbol esta vacio");
    } else {
        if (dato < (*top)->dato) {
            baja(&(*top)->L, dato);
        } else if (dato > (*top)->dato) {
            baja(&(*top)->R, dato);
        }
        if (dato == (*top)->dato) {
            aux = (*top);
            if (aux->L == NULL) {
                (*top) = aux->R;
            } else if (aux->R == NULL) {
                (*top) = aux->L;
            } else {
                moveleft(&aux);
            }
            free(aux);
        }
    }
}

void textoconvertido(char* letras) {
    int q = 0;
    if (letras != NULL) {
        while (letras[q] != '\0') {
            letras[q] = tolower(letras[q]);
            if (letras[q] == '\361' || letras[q] == '\321')
                letras[q] = 'n';
            else if (letras[q] == '\300' || letras[q] == '\301' || letras[q] == '\340' || letras[q] == '\341')
                letras[q] = 'a';
            else if (letras[q] == '\310' || letras[q] == '\311' || letras[q] == '\350' || letras[q] == '\351')
                letras[q] = 'e';
            else if (letras[q] == '\314' || letras[q] == '\315' || letras[q] == '\354' || letras[q] == '\355')
                letras[q] = 'i';
            else if (letras[q] == '\322' || letras[q] == '\323' || letras[q] == '\326' || letras[q] == '\362' ||
                     letras[q] == '\363' || letras[q] == '\366')
                letras[q] = 'o';
            else if (letras[q] == '\331' || letras[q] == '\332' || letras[q] == '\334' || letras[q] == '\371' ||
                     letras[q] == '\372' || letras[q] == '\374')
                letras[q] = 'u';
            q++;
        }
    }
}

void contador(char s[],int count[]) {
    int c = 0;
    while (s[c] != '\0') {
        if (s[c] >= 'a' && s[c] <= 'z')
            count[s[c] - 'a']++;
        else if (s[c] == ' ')
            count[26]++;
        else if(s[c] == '.')
            count[27]++;
        else if(s[c] == ',')
            count[28]++;
        c++;
    }
}

void Buildtree(Nodo** arbol, Nodo *raiz) {
    Nodo *aux, *aux2;
    if (*arbol==NULL) {
        *arbol = raiz;
        (*arbol)->sig = NULL;
    } else {
        aux = *arbol;
        aux2 = NULL;
        while (aux && aux->dato < raiz->dato) {
            aux2 = aux;
            aux = aux->sig;
        }
        raiz->sig = aux;
        if (aux2!=NULL)
            aux2->sig = raiz;
        else
            *arbol = raiz;
    }
}

void Makelist(Binario **Listabin,char caracter,int longitud,int binarios) {
    Binario *aux, *aux2, *aux3;
    aux = allocateMemo(binarios, caracter, longitud);
    if (*Listabin == NULL) {
        *Listabin = aux;
        (*Listabin)->sig = NULL;
    } else
    {
        aux2 = *Listabin;
        aux3 = NULL;
        while (aux2 && aux2->caracter<aux->caracter)
        {
                aux3 = aux2;
                aux2 = aux2->sig;
        }
        aux ->sig=aux2;
        if(aux3!=NULL)
            aux3->sig = aux;
        else
            *Listabin = aux;
    }
}

void Buildbinary(Nodo *Arbol,int longitud,int binarios,Binario **Listabin)
{
    if(Arbol->L!=NULL)
        Buildbinary(Arbol->L,longitud+1,binarios<<1,Listabin);

    if(Arbol->R!=NULL)
        Buildbinary(Arbol->R,longitud+1,binarios<<1|1,Listabin);

    if(Arbol->L==NULL&&Arbol->R==NULL)
        Makelist(Listabin,Arbol->caracter,longitud,binarios);
}

/*void braices(Nodo *raices[],Nodo *lista) {
    Nodo *aux = lista, *izq = NULL, *der = NULL, *raiz = NULL;
    int i = 0;
    if (aux != NULL) {
        while (aux != NULL) {
            if (aux->R != NULL) {
                int nv = aux->dato + aux->R->dato;
                raiz = allocateMem(nv, '*');
                izq = allocateMem(aux->dato, aux->caracter);
                der = allocateMem(aux->R->dato, aux->R->caracter);
                raiz->L = izq;
                raiz->R = der;
                raices[i] = raiz;
            } else {
                raiz = allocateMem(aux->dato, '*');
                izq = allocateMem(aux->dato, aux->caracter);
                raiz->L = izq;
                raices[i] = raiz;
                break;
            }
            aux = aux->R->R;
            i++;
        }
    }
}

void bsubtreesp(Nodo *raices[],Nodo *subarboles[]) {
    Nodo *raiz = NULL;
    int j = 0, i = 0;
    while (raices[j + 1] != NULL) {
        if (raices[j + 1] != NULL) {
            int nv = raices[j]->dato + raices[j + 1]->dato;
            raiz = allocateMem(nv, '*');
            raiz->L = raices[j];
            raiz->R = raices[j + 1];
            subarboles[i] = raiz;
        }
        j += 2;
        i++;
    }
}

void bsubtreesi(Nodo *raices[],Nodo *subarboles[]) {
    Nodo *raiz = NULL;
    int j = 0, i = 0;
    while (raices[j + 1] != NULL) {
        if (raices[j + 1] != NULL) {
            int nv = raices[j]->dato + raices[j + 1]->dato;
            raiz = allocateMem(nv, '*');
            raiz->L = raices[j];
            raiz->R = raices[j + 1];
            subarboles[i] = raiz;
        }
        j += 2;
        i++;
    }
    raiz = allocateMem(raices[j]->dato, '*');
    raiz->L = raices[j];
    subarboles[i] = raiz;
}

int tree(Nodo *top[]) {
    int i = 0;
    if (top[i] != NULL) {
        while (top[i] != NULL) {
            i++;
        }
    }
    return i;
}

void comprobador(Nodo *raices[],Nodo *guardadito[]) {
    int tamanio = tree(raices);
    if (guardadito != NULL) {
        for (int i = 0; guardadito[i] != NULL; i++) {
            guardadito[i] = NULL;
        }
    }
    if (tamanio != 1) {
        if (tamanio % 2 != 0) {
            bsubtreesi(raices, guardadito);
        } else {
            bsubtreesp(raices, guardadito);
        }
    }
}*/

int sizetree(Nodo *top) {
    if (top == NULL)
        return 0;
    else
        return (sizetree(top->L) + 1 + sizetree(top->R));
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

Nodo* altainicio(int dato, Nodo* top,char caracter) {
    Nodo *box;
    box = allocateMem(dato, caracter);
    if (top != NULL) {
        box->sig = top;
    }
    top = box;
    return top;
}

Nodo *altadato(Nodo *top,int dato,int posicion,char caracter) {
    Nodo *aux, *nuevo;
    aux = top;
    nuevo = allocateMem(dato, caracter);
    if (aux != NULL) {
        while (aux->sig != NULL) {
            if (aux->dato == posicion) {
                nuevo->sig = aux->sig;
                aux->sig = nuevo;
                break;
            } else {
                aux = aux->sig;
            }
        }
    }
    return top;
}

Nodo *ordenar_seleccion(Nodo *top) {
    Nodo *aux, *aux2;
    aux = top;

    if (top != NULL) {
        while (aux->sig != NULL) {
            aux2 = aux->sig;
            while (aux2 != NULL) {
                if (aux->dato > aux2->dato) {
                    int var = aux->dato;
                    aux->dato = aux2->dato;
                    aux2->dato = var;

                    char let = aux->caracter;
                    aux->caracter = aux2->caracter;
                    aux2->caracter = let;
                }
                aux2 = aux2->sig;
            }
            aux = aux->sig;
        }
    }
    return top;
}

Binario *ordenar_listabinario(Binario *top) {
    Binario *aux, *aux2;
    aux = top;
    if (top != NULL) {
        while (aux->sig != NULL) {
            aux2 = aux->sig;
            while (aux2 != NULL) {
                if (aux->nbits > aux2->nbits) {
                    int var = aux->bits;
                    aux->bits = aux2->bits;
                    aux2->bits = var;

                    char let = aux->caracter;
                    aux->caracter = aux2->caracter;
                    aux2->caracter = let;

                    int nbit = aux->nbits;
                    aux->nbits = aux2->nbits;
                    aux2->nbits = nbit;

                    char *array = aux->binario;
                    aux->binario = aux2->binario;
                    aux2->binario = array;
                }
                aux2 = aux2->sig;
            }
            aux = aux->sig;
        }
    }
    return top;
}

#endif