/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: lucas
 *
 * Created on April 30, 2019, 10:49 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <time.h>

using namespace std;

/*
 * 
 */

int n = 0;
int m = 0;
int sd = 0;
int ns = 0;

typedef struct dado {
    int id;
} Dado;

typedef struct no {
    Dado dado;
    struct no *proximo;
} No;

typedef struct lista {
    int tamanho;
    No * cabeca;
} Lista;

Lista * criarLista() {
    Lista * lista = (Lista*) malloc(sizeof (Lista));
    lista->tamanho = 0;
    lista->cabeca = NULL;
    return lista;
}

/**
 * Insere dado no início da lista
 * @param lista
 * @param dado
 * @return 
 */
bool inserir(Lista* lista, Dado dado) {
    if (dado.id > 0) {
        No* no = (No*) malloc(sizeof (No));
        no->dado = dado;
        no->proximo = lista->cabeca;
        lista->cabeca = no;
        lista->tamanho++;
        return true;
    }
    return false;
}

/**
 * Exibe lista 
 * @param lista
 * @return 
 */
bool exibirLista(Lista* lista) {
    No* aux = lista->cabeca;

    if (aux == NULL)
        //        printf("Lista vazia\n");
        return false;

    while (aux != NULL) {
        printf("%d\t", aux->dado.id);
        aux = aux->proximo;
    }
    return true;
    printf("\n");

}

/**
 * Excluir da primeira da posição
 * @param lista
 * @return 
 */
bool excluir(Lista* lista) {
    if (lista->tamanho != 0) {
        No* aux = lista->cabeca;
        lista->cabeca = aux->proximo;
        free(aux);
        lista->tamanho--;
        return true;
    }
    return false;
}

/**
 * Retorna um nó baseado no índice passado
 * @param lista
 * @param index
 * @return 
 */
No* indiceNo(Lista* lista, int index) {
    if (index >= 0 && index < lista->tamanho) {
        No* noAux = lista->cabeca;

        for (int i = 0; i < index; i++) {
            noAux = noAux->proximo;
        }
        return noAux;
    }
    return NULL;
}

/**
 * Buscar na lista pelo Nó
 * @param lista
 * @param no
 * @return 
 */
int buscarNo(Lista* lista, No* no) {
    if (no != NULL) {
        No* noAux = lista->cabeca;
        int indice = 0;
        while (noAux != no && noAux != NULL) {
            noAux = noAux->proximo;
            indice++;
        }

        if (noAux != NULL) {
            return indice;
        }
    }
    return -1;
}

/**
 * Buscar na lista por ID - soldado
 * @param lista
 * @param id
 * @return 
 */
int buscarId(Lista* lista, int id) {
    if (id > 0) {
        No* noAux = lista->cabeca;
        int indice = 0;
        while (noAux->dado.id != id && noAux != NULL) {
            noAux = noAux->proximo;
            indice++;
        }

        if (noAux != NULL) {
            return indice;
        }
    }
    return -1;
}

/**
 * Apaga incidência do valor da lista
 * @param lista
 * @param indice
 * @return 
 */
bool apagarIndice(Lista* lista, int indice) {

    if (indice == 0) {
        excluir(lista);
    } else {
        No* noAux = indiceNo(lista, indice);

        if (noAux != NULL) {
            No* noAnterior = indiceNo(lista, indice - 1);
            noAnterior->proximo = noAux->proximo;
            free(noAux);
            lista->tamanho--;
            return true;
        }
    }
    return false;
}

/**
 * Calcula a posição a ser excluida na lista
 * @param lista
 * @param sd
 * @param m
 * @return 
 */
int posicaoSair(Lista* lista, int sd, int m) {
    ns = (buscarId(lista, sd) + m) - 1;
    while (ns >= lista->tamanho) {
        ns = ns - lista->tamanho;
    }
    return ns;
}

int random_number(int min_num, int max_num) {
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num) {
        low_num = min_num;
        hi_num = max_num + 1;
    } else {
        low_num = max_num + 1;
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

int main(int argc, char** argv) {
    Lista* lista = criarLista();
    Dado dado;

    printf("Número de soldados: ");
    scanf("%d", &n);
    for (int i = n; i > 0; i--) {
        dado.id = i;
        inserir(lista, dado);
    }

    exibirLista(lista);
    printf("\n");

    do {

        int valor = random_number(0, lista->tamanho - 1);
        No* no = indiceNo(lista, valor);
        sd = no->dado.id;

        printf("Soldado sorteado: %d\t", sd);
        srand(time(NULL));
        m = random_number(1, lista->tamanho * 6);
        printf("M-ésimo soldado: %d\n", m);
        //        scanf("%d", &m);
        int sairPosicao = posicaoSair(lista, sd, m);
        printf("Posicao sair: %d\t", sairPosicao);
        printf("Posicao SD: %d\n\n", buscarId(lista, sd));
        apagarIndice(lista, sairPosicao);
        //        printf("Size lista: %d\n", lista->tamanho);
        
        exibirLista(lista);
        printf("\n");
    } while (lista->tamanho > 1);


    return 0;
}

