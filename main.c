#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main() {
    Nodo *lista = NULL, *arbol = NULL;
    Binario *listacod=NULL;
    char abc[29] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                    'u', 'v', 'w', 'x', 'y', 'z', '+','.',','};
    int count[29] = {0}, m;
    char *nombre = "E:\\Escuela\\Estructura_de_datos\\Practica 4\\original.txt", *salida = "E:\\Escuela\\Estructura_de_datos\\Practica 4\\salida.txt";
    char *salida2 = "E:\\Escuela\\Estructura_de_datos\\Practica 4\\codificado.txt", frase[100];
    FILE *archivo = fopen(nombre, "rt"), *out2 = fopen(salida2, "w"),*out = fopen(salida, "w");

    if (archivo == NULL||!out||!out2) {
        puts("Este archivo no existe");
        exit(-1);
    }

    fgets(frase, 100, archivo);
    textoconvertido(frase);
    contador(frase, count);
    for (int j = 0; j < 29; j++) {
        if (count[j] != 0) {
            lista = altainicio(count[j], lista, abc[j]);
        }
    }
    lista = ordenar_seleccion(lista);

    puts("ALGORITMO DE HUFFMAN\n"
         "1 >> Codificar\n"
         "2 >> Decodificar\n"
         "0 >> Salir\n");
    scanf_s("%d", &m);
    switch (m) {
        case 1:
            Nodo *aux = lista/*, *raices[15] = {NULL}, *subarboles[10] = {NULL}, *tree3[5] = {
                    NULL}, *izq = NULL, *der = NULL, *raiz = NULL*/;
            if (aux != NULL) {
                arbol = lista;
                while (arbol && arbol->sig) {
                    int nv = arbol->dato + arbol->sig->dato;
                    aux = allocateMem(nv, '*');
                    aux->L = arbol;
                    aux->R = arbol->sig;
                    arbol = arbol->sig->sig;
                    Buildtree(&arbol, aux);
                }
                //preOrden(arbol);
                preOrdenimpresion(arbol, out);
                Buildbinary(arbol,0,0,&listacod);
                listacod = ordenar_listabinario(listacod);
                llenarbinario(listacod);
                imprimirbinariosfile(listacod,out2);
                fclose(out2);
                fclose(out);
                break;

                case 2:
                    break;

                case 0:
                    puts("CHI CHENOL");
                break;

                default:
                    puts("Inserte una opcion valida");
                break;
            }
            fclose(archivo);

            return 0;
    }
}
/*braices(raices, aux);
                    t = tree(raices);
                    do {
                        if (t == 1 && arbol == NULL) {
                            arbol = raices[0];
                            break;
                        } else
                            comprobador(raices, subarboles);
                        t = tree(subarboles);

                        if (t == 1 && arbol == NULL) {
                            arbol = subarboles[0];
                            break;
                        } else
                            comprobador(subarboles, tree3);
                        t = tree(tree3);

                        if(t==1&&arbol==NULL)
                        {
                            arbol = tree3[0];
                            break;
                        }
                        else
                            comprobador(tree3,raices);

                        t = tree(raices);
                    }while(t!=1);
                }
                preOrden(arbol);

                if(out==NULL && out2 ==NULL)
                {
                    puts("No se puede escribir en el archivo");
                    exit(-1);
                }
                preOrdenimpresion(arbol,out);
                binarios(lista);
                fclose(out);
                fclose(out2);*/