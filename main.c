/****************************

Questão 1

#include<stdio.h>
#include<stdlib.h>

int Fibo(int y){
    if(y <= 1)
        return y;

    return Fibo(y - 1) + Fibo(y - 2);
}

int main()
{
    int x = 6, i;

    for(i = 0; i < x; i++){
        printf("%d",Fibo(i));
    }

    return 0;
}
***********************/

/****************************

Questão 2

#include <stdio.h>
#include <stdlib.h>


int Soma(int v[], int n) {
    if (n == 0)
        return 0;

    return v[n - 1] + Soma(v, n - 1);
}

int main() {
    int tamanho, i;


    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);

    int vetor[tamanho];


    printf("Digite os valores do vetor:\n");
    for (i = 0; i < tamanho; i++) {
        printf("Elemento %d: ", i + 1);
        scanf("%d", &vetor[i]);
    }


    printf("A soma dos valores do vetor é: %d\n", Soma(vetor, tamanho));

    return 0;
}
***********************/

/****************************

Quetão 3

#include <stdio.h>
#include <stdlib.h>

int Pot(int b, int e){
    if(e == 0)
        return 1;

    return b * Pot(b, e - 1);
}

int main(){
    int x, y, i;

    printf("Digite a base e o expoente: ");
    scanf("%d", &x);
    scanf("%d", &y);
    printf("%d ", Pot(x, y));


    return 0;
}
***********************/

/****************************

Questão 4

#include <stdio.h>
#include <stdlib.h>

int* aloca(int x){

    int* vetor = (int*)malloc (x * sizeof(int));

    if(vetor == NULL){
        printf("ERRO");
        return NULL;
    }

    for(int i = 0; i< x; i++){
        vetor[i] = i + 1;
    }

    return vetor;
}

int* realoca(int* vetor, int x, int y){

    vetor = (int*)realloc (vetor, y * sizeof(int));

    if(vetor == NULL){
        printf("ERRO");
        return NULL;
    }

    for(int i = x; i < y; i++){
        vetor[i] = i + 1;
    }

    return vetor;
}

int main() {

    int n, m, t;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    int* vetor = aloca(n);

    printf("Elementos do vetor:\n");

    for(int i = 0; i < n; i++){
        printf("%d", vetor[i]);
    }

    printf("\n Voce quer aumentar o tamanho do vetor? \n Digite 1 para sim e 0 para nao: ");
    scanf("%d", &m);

    if(m == 1){

        printf("Digite o novo tamanho: ");
        scanf("%d", &t);

        vetor = realoca(vetor, n, t);

        printf("Elementos do vetor:\n");

        for(int j = 0; j < t; j++){
            printf("%d", vetor[j]);
        }

        free(vetor);
        vetor = NULL;
    }

    return 0;
}

***********************/

/****************************

#include<stdio.h>
#include<stdlib.h>

struct lista {
    int info;
    struct lista* prox;
};

typedef struct lista Lista;

Lista* lst_cria(void){
    return NULL;
}

int main()
{
    Lista* lista = lst_cria();
    printf("%p", (void*)lista);
    return 0;
}

***********************/

/****************************
#include<stdio.h>
#include<stdlib.h>

static int incr(int i){

if(i == N-1)
    return 0;
else
    return i + 1;
}

struct fila {
    int n;
    int ini;
};

typedef struct fila Fila;

Fila* fila_cria(void){

    Fila* f = (Fila*) malloc(sizeof(Fila));
    f -> = 0;
    f -> ini = 0;

    return f;
}
***********************/

/****************************
#include<stdio.h>
#include<stdlib.h>

struct no {

    char conteudo;
    struct no* prox;

};

struct Pilha{

struct no* topo;

};

struct Pilha* cria(){

    struct Pilha* pilha = (struct Pilha*)malloc(sizeof(struct Pilha));

    pilha -> topo = NULL;

    return pilha;
};

void push(struct Pilha* pilha, char letra){

    struct no* temp = (struct no*)malloc(sizeof(struct no));

    temp -> conteudo = letra;
    temp -> prox = pilha -> topo;
    pilha -> topo = temp;

}

int pop(struct Pilha* pilha){

    if(pilha -> topo == NULL){

        printf("Pilha vazia");

        return -1;

    }

    struct no* temp = pilha -> topo;

    char letra = temp -> conteudo;

    pilha -> topo = pilha -> topo -> prox;

    free(temp);

    return letra;

}

int main(){

    char L;

    printf("Digite as letras para formar a palavra: \n");

    for( int i = 0; i < 11; i++){

        scanf("%c", &L);


    }


return 0;
}

struct No* Remocao(struct No* raiz, int valor){

    if(raiz == NULL)
        return -1;






};






***********************/

#include<stdio.h>
#include<stdlib.h>

struct No {

    int conteudo;
    int alt;
    struct No* esq;
    struct No* dir;

};

int altura(struct No* n){

    if(n == NULL)

        return 0;

    return n->alt;
}

int max(int a, int b) {

    return (a > b) ? a : b;
}

struct No* Criar(int valor) {

    struct No* Novo = (struct No*)malloc(sizeof(struct No));

    Novo->conteudo = valor;
    Novo->esq = NULL;
    Novo->dir = NULL;
    Novo->alt = 1;

    return Novo;
}

int get_balance(struct No* n){

    if(n == NULL)

        return 0;

    return altura(n->esq) - altura(n->dir);
}

struct No* rot_dir(struct No* y){

    struct No* x = y->esq;
    struct No* z = x->dir;

    x->dir = y;
    y->esq = z;
    y->alt = max(altura(y->esq), altura(y->dir)) + 1;
    x->alt = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

struct No* rot_esq(struct No* x){

    struct No* y = x->dir;
    struct No* z = y->esq;

    y->esq = x;
    x->dir = z;
    x->alt = max(altura(x->esq), altura(x->dir)) + 1;
    y->alt = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

struct No* Inserir(struct No* raiz, int valor) {

    if (raiz == NULL)

        return Criar(valor);

    if (valor < raiz->conteudo)

        raiz->esq = Inserir(raiz->esq, valor);

    else if (valor > raiz->conteudo)

        raiz->dir = Inserir(raiz->dir, valor);

    else

        return raiz;

    raiz->alt = 1 + max(altura(raiz->esq), altura(raiz->dir));

    int balance = get_balance(raiz);

    if(balance > 1 && valor < raiz->esq->conteudo)

        return rot_dir(raiz);

    if(balance < -1 && valor > raiz->dir->conteudo)

        return rot_esq(raiz);

    if(balance > 1 && valor > raiz->esq->conteudo) {

        raiz->esq = rot_esq(raiz->esq);

        return rot_dir(raiz);
    }

    if(balance < -1 && valor < raiz->dir->conteudo) {

        raiz->dir = rot_dir(raiz->dir);

        return rot_esq(raiz);
    }

    return raiz;
}

struct No* Buscar(struct No* raiz, int valor) {

    if (raiz == NULL || raiz->conteudo == valor)

        return raiz;

    if (valor < raiz->conteudo)

        return Buscar(raiz->esq, valor);

    return Buscar(raiz->dir, valor);
}

struct No* Remocao(struct No* raiz, int valor) {

    if (raiz == NULL)

        return raiz;

    if (valor < raiz->conteudo)

        raiz->esq = Remocao(raiz->esq, valor);

    else if (valor > raiz->conteudo)

        raiz->dir = Remocao(raiz->dir, valor);

    else {
        if (raiz->esq == NULL) {

            struct No* temp = raiz->dir;

            free(raiz);

            return temp;

        } else if (raiz->dir == NULL) {

            struct No* temp = raiz->esq;

            free(raiz);

            return temp;
        }

        struct No* maior = raiz->esq;
        struct No* paiMaior = raiz;

        while (maior->dir != NULL) {

            paiMaior = maior;
            maior = maior->dir;
        }

        raiz->conteudo = maior->conteudo;

        if (paiMaior == raiz)

            paiMaior->esq = maior->esq;

        else

            paiMaior->dir = maior->esq;

        free(maior);
    }

    if (raiz == NULL)

        return raiz;

    raiz->alt = 1 + max(altura(raiz->esq), altura(raiz->dir));

    int balance = get_balance(raiz);

    if (balance > 1 && get_balance(raiz->esq) >= 0)

        return rot_dir(raiz);

    if (balance < -1 && get_balance(raiz->dir) <= 0)

        return rot_esq(raiz);

    if (balance > 1 && get_balance(raiz->esq) < 0) {

        raiz->esq = rot_esq(raiz->esq);

        return rot_dir(raiz);
    }

    if (balance < -1 && get_balance(raiz->dir) > 0) {

        raiz->dir = rot_dir(raiz->dir);

        return rot_esq(raiz);
    }

    return raiz;
}

void Percorrer(struct No* raiz){

    if(raiz != NULL){

        printf("%d", raiz->conteudo);
        Percorrer(raiz->esq);
        Percorrer(raiz->dir);

    }

}

int main() {

    struct No* raiz = NULL;
    int valor, opcao;

    do {

        printf("Escolha uma opcao:\n");
        printf("1 - Inserir valor na arvore\n");
        printf("2 - Buscar valor na arvore\n");
        printf("3 - Remover valor da arvore\n");
        printf("4 - Percorrendo arvore\n");
        printf("5 - Sair\n");
        scanf("%d", &opcao);

        if (opcao == 1) {

            printf("Digite o valor para adicionar na arvore:\n");
            scanf("%d", &valor);

            raiz = Inserir(raiz, valor);

            printf("Valor %d inserido!\n", valor);

        } else if (opcao == 2) {

            printf("Digite o valor a ser buscado:\n");
            scanf("%d", &valor);

            struct No* resultado = Buscar(raiz, valor);

            if (resultado != NULL)

                printf("Valor %d encontrado!\n", valor);

            else

                printf("Valor %d nao encontrado!\n", valor);

        } else if (opcao == 3) {

            printf("Digite o valor a ser removido:\n");
            scanf("%d", &valor);

            raiz = Remocao(raiz, valor);

            printf("Valor %d removido (se existente)!\n", valor);

        } else if (opcao == 4) {

            printf("Percorrendo arvore\n");

            Percorrer(raiz);

            printf("\n");

        } else if (opcao == 5) {

            printf("Saindo do programa...\n");

            break;
        }

        else {

            printf("Opcao invalida. Tente novamente.\n");

        }

    } while (opcao != 5);

    return 0;
}