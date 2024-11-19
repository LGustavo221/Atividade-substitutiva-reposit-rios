#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura da Tarefa
typedef struct Tarefa {
    int id;
    char descricao[100];
    int prioridade;
    char data[11];
    struct Tarefa *esquerda, *direita;
    int altura;
} Tarefa;

// Fila com prioridade
typedef struct NodoFila {
    Tarefa *tarefa;
    struct NodoFila *proximo;
} NodoFila;

typedef struct {
    NodoFila *inicio;
    NodoFila *fim;
} Fila;

// Pilha
typedef struct NodoPilha {
    Tarefa *tarefa;
    struct NodoPilha *proximo;
} NodoPilha;

typedef struct {
    NodoPilha *topo;
} Pilha;

// Funções auxiliares de fila e pilha
void inicializarFila(Fila *fila) {
    fila->inicio = fila->fim = NULL;
}

void inicializarPilha(Pilha *pilha) {
    pilha->topo = NULL;
}

// Função inserir na fila
void inserirNaFila(Fila *fila, Tarefa *tarefa) {
    NodoFila *novo = (NodoFila *)malloc(sizeof(NodoFila));
    novo->tarefa = tarefa;
    novo->proximo = NULL;

    if (!fila->inicio) {
        fila->inicio = fila->fim = novo;
    } else {
        NodoFila *anterior = NULL, *atual = fila->inicio;
        while (atual && atual->tarefa->prioridade <= tarefa->prioridade) {
            anterior = atual;
            atual = atual->proximo;
        }

        if (!anterior) {
            novo->proximo = fila->inicio;
            fila->inicio = novo;
        } else {
            anterior->proximo = novo;
            novo->proximo = atual;
            if (!atual)
                fila->fim = novo;
        }
    }
}

// Função remover da fila
void removerDaFila(Fila *fila, Pilha *pilha) {
    if (!fila->inicio) {
        printf("Fila vazia! Nada a remover.\n");
        return;
    }

    NodoFila *removido = fila->inicio;
    fila->inicio = fila->inicio->proximo;

    NodoPilha *novoNodoPilha = (NodoPilha *)malloc(sizeof(NodoPilha));
    novoNodoPilha->tarefa = removido->tarefa;
    novoNodoPilha->proximo = pilha->topo;
    pilha->topo = novoNodoPilha;

    printf("Tarefa removida: %s\n", removido->tarefa->descricao);
    free(removido);

    if (!fila->inicio)
        fila->fim = NULL;
}

// Função para exibir tarefas
void exibirFila(Fila *fila) {
    if (!fila->inicio) {
        printf("A fila está vazia.\n");
        return;
    }

    NodoFila *atual = fila->inicio;
    printf("Tarefas na fila:\n");
    while (atual) {
        Tarefa *t = atual->tarefa;
        printf("ID: %d | Descrição: %s | Prioridade: %d | Data: %s\n",
               t->id, t->descricao, t->prioridade, t->data);
        atual = atual->proximo;
    }
}

// Funções de árvore AVL
int altura(Tarefa *nodo) {
    return nodo ? nodo->altura : -1;
}

Tarefa *rotacionarDireita(Tarefa *y) {
    Tarefa *x = y->esquerda;
    Tarefa *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));
    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));

    return x;
}

Tarefa *rotacionarEsquerda(Tarefa *x) {
    Tarefa *y = x->direita;
    Tarefa *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));
    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));

    return y;
}

int getBalanceamento(Tarefa *nodo) {
    return nodo ? altura(nodo->esquerda) - altura(nodo->direita) : 0;
}

Tarefa *inserirNaArvoreAVL(Tarefa *raiz, Tarefa *novaTarefa) {
    if (!raiz) {
        return novaTarefa;
    }

    if (novaTarefa->id < raiz->id) {
        raiz->esquerda = inserirNaArvoreAVL(raiz->esquerda, novaTarefa);
    } else if (novaTarefa->id > raiz->id) {
        raiz->direita = inserirNaArvoreAVL(raiz->direita, novaTarefa);
    } else {
        return raiz; // ID duplicado
    }

    raiz->altura = 1 + (altura(raiz->esquerda) > altura(raiz->direita) ? altura(raiz->esquerda) : altura(raiz->direita));

    int balance = getBalanceamento(raiz);

    if (balance > 1 && novaTarefa->id < raiz->esquerda->id) {
        return rotacionarDireita(raiz);
    }
    if (balance < -1 && novaTarefa->id > raiz->direita->id) {
        return rotacionarEsquerda(raiz);
    }
    if (balance > 1 && novaTarefa->id > raiz->esquerda->id) {
        raiz->esquerda = rotacionarEsquerda(raiz->esquerda);
        return rotacionarDireita(raiz);
    }
    if (balance < -1 && novaTarefa->id < raiz->direita->id) {
        raiz->direita = rotacionarDireita(raiz->direita);
        return rotacionarEsquerda(raiz);
    }

    return raiz;
}

void exibirArvore(Tarefa *raiz) {
    if (raiz) {
        exibirArvore(raiz->esquerda);
        printf("ID: %d | Descrição: %s | Prioridade: %d | Data: %s\n",
               raiz->id, raiz->descricao, raiz->prioridade, raiz->data);
        exibirArvore(raiz->direita);
    }
}

// Função de busca binária
Tarefa *buscarTarefa(Tarefa *raiz, int id) {
    if (raiz == NULL || raiz->id == id)
        return raiz;

    if (id < raiz->id)
        return buscarTarefa(raiz->esquerda, id);
    else
        return buscarTarefa(raiz->direita, id);
}



// Função principal com menu interativo
int main() {
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    Tarefa *arvore = NULL;
    int opcao;
    Tarefa tarefaTemp;
    int idBuscado;

    while (1) {
        printf("\nMenu de opções:\n");
        printf("1. Inserir tarefa\n");
        printf("2. Remover tarefa\n");
        printf("3. Exibir tarefas na fila\n");
        printf("4. Buscar tarefa por ID\n");
        printf("5. Ordenar tarefas na fila\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer de entrada

        switch (opcao) {
            case 1:
                printf("Insira o ID da tarefa: ");
                scanf("%d", &tarefaTemp.id);
                getchar(); // Limpar o buffer de entrada
                printf("Insira a descrição da tarefa: ");
                fgets(tarefaTemp.descricao, 100, stdin);
                tarefaTemp.descricao[strcspn(tarefaTemp.descricao, "\n")] = '\0'; // Remover nova linha
                printf("Insira a prioridade da tarefa: ");
                scanf("%d", &tarefaTemp.prioridade);
                getchar(); // Limpar o buffer de entrada
                printf("Insira a data da tarefa (DD/MM/AAAA): ");
                fgets(tarefaTemp.data, 11, stdin);
                tarefaTemp.data[strcspn(tarefaTemp.data, "\n")] = '\0'; // Remover nova linha
                inserirNaFila(&fila, &tarefaTemp);
                arvore = inserirNaArvoreAVL(arvore, &tarefaTemp);
                printf("Tarefa inserida com sucesso!\n");
                break;

            case 2:
                removerDaFila(&fila, &pilha);
                break;

            case 3:
                exibirFila(&fila);
                break;

            case 4:
                printf("Digite o ID da tarefa para busca: ");
                scanf("%d", &idBuscado);
                Tarefa *tarefaBuscada = buscarTarefa(arvore, idBuscado);
                if (tarefaBuscada) {
                    printf("Tarefa encontrada: ID: %d | Descrição: %s | Prioridade: %d | Data: %s\n",
                           tarefaBuscada->id, tarefaBuscada->descricao, tarefaBuscada->prioridade, tarefaBuscada->data);
                } else {
                    printf("Tarefa não encontrada!\n");
                }
                break;

            case 5:
                ordenarFila(&fila);
                printf("Fila ordenada por prioridade.\n");
                break;

            case 6:
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
