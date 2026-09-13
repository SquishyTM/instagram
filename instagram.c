#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct vizinho {
    char nome[10];
    struct vizinho *prox;
} TVizinho;

typedef struct grafo {
    char nome[10];
    int idade;
    TVizinho *prim_vizinho;
    struct grafo *prox;
} TGrafo;

TGrafo *insere_vertice(TGrafo *g, char *nome, int idade) {
    TGrafo *vertice = (TGrafo *) malloc(sizeof(TGrafo));
    strcpy(vertice->nome, nome);
    vertice->idade = idade;
    vertice->prox = g;
    vertice->prim_vizinho = NULL;
    return vertice;
}

TGrafo *busca_vertice(TGrafo *vertice, char *nome) {
    while ((vertice != NULL) && (strcmp(vertice->nome, nome) != 0)) {
        vertice = vertice->prox;
    }
    return vertice;
}

TVizinho *busca_vizinho(TVizinho *vizinho, char *nome) {
    while ((vizinho != NULL) && (strcmp(vizinho->nome, nome) != 0)) {
        vizinho = vizinho->prox;
    }
    return vizinho;
}

void insere_aresta(TGrafo *g, char *nome_origem, char *nome_destino) {
    TGrafo *pv1 = busca_vertice(g, nome_origem);
    TGrafo *pv2 = busca_vertice(g, nome_destino);
    if (pv1 != NULL && pv2 != NULL) {
        TVizinho *vizinho = (TVizinho *) malloc(sizeof(TVizinho));
        strcpy(vizinho->nome, nome_destino);
        vizinho->prox = pv1->prim_vizinho;
        pv1->prim_vizinho = vizinho;
    }
}

void imprime(TGrafo *vertice) {
    while (vertice != NULL) {
        printf("Pessoa: %s - %d anos\n", vertice->nome, vertice->idade);
        printf("Segue: ");
        TVizinho *vizinho = vertice->prim_vizinho;
        while (vizinho != NULL) {
            printf("%s ", vizinho->nome);
            vizinho = vizinho->prox;
        }
        printf("\n\n");
        vertice = vertice->prox;
    }
}

int numero_seguidos(TGrafo *g, char *nome) {
    int i = 0;
    TGrafo *achou = busca_vertice(g, nome);
    if (achou != NULL){
        TVizinho *aux = achou->prim_vizinho;
        while (aux != NULL){
            i++;
            aux = aux->prox;
        }
    }
    return i;
}

int seguidores(TGrafo *g, char *nome, int imprime) {
    TGrafo *achou = g;
    TVizinho *aux;
    while (imprime == 1){
        if (achou == NULL){
            imprime = 0;
        } else {
            if (strcmp(achou->nome, nome) != 0){
                aux = achou->prim_vizinho;
                while (aux != NULL && imprime == 1)
                    if (strcmp(aux->nome, nome) == 0){
                        printf("%s ", achou->nome);
                        imprime = 0;
                    } else {
                        aux = aux->prox;
                    }
            }
        achou = achou->prox;
        imprime = 1;
        }
    }
    printf("\n");
    return 0;
}

TGrafo *mais_popular(TGrafo *g) {
    TGrafo *atual = g;
    TGrafo *mais_pop = NULL;
    int max_seguidores = -1;

    while (atual != NULL) {
        int cont_seguidores = 0;
        TGrafo *temp = g;

        while (temp != NULL) {
            TVizinho *viz = temp->prim_vizinho;
            while (viz != NULL) {
                if (strcmp(viz->nome, atual->nome) == 0) {
                    cont_seguidores++;
                    break;
                }
                viz = viz->prox;
            }
            temp = temp->prox;
        }

        if (cont_seguidores > max_seguidores) {
            max_seguidores = cont_seguidores;
            mais_pop = atual;
        }

        atual = atual->prox;
    }

    return mais_pop;
}

int segue_mais_velho(TGrafo *g, int imprime) {
    TGrafo *atual = g;
    int contador = 0;

    while (atual != NULL) {
        TVizinho *viz = atual->prim_vizinho;
        int so_mais_velho = 1;
        int segue_alguem = 0;

        while (viz != NULL) {
            segue_alguem = 1;
            TGrafo *v_destino = busca_vertice(g, viz->nome);

            if (v_destino != NULL && v_destino->idade <= atual->idade) {
                so_mais_velho = 0;
                break;
            }
            viz = viz->prox;
        }

        if (segue_alguem == 1 && so_mais_velho == 1) {
            contador++;
            if (imprime == 1) {
                printf("%s ", atual->nome);
            }
        }
        atual = atual->prox;
    }

    if (imprime == 1) {
        printf("\n");
    }

    return contador;
}

void libera_vizinho(TVizinho *vizinho) {
    if (vizinho != NULL) {
        libera_vizinho(vizinho->prox);
        free(vizinho);
    }
}

void libera_vertice(TGrafo *vertice) {
    if (vertice != NULL) {
        libera_vizinho(vertice->prim_vizinho);
        libera_vertice(vertice->prox);
        free(vertice);
    }
}

int main() {
    /* A função main lê os dados de entrada, cria o grafo e chama as funções solicitadas no problema
    * depois imprime os resultados solicitados
    * ELA NÃO DEVE SER MODIFICADA
    * */
    int num_vertices, num_arestas;
    char nome[30];
    char origem[30], destino[30];
    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int idade;
    int i;
    TGrafo *g = NULL;

    //le numero de vertices
    scanf("%d", &num_vertices);
    //le e cria os vertices
    for (i = 0; i < num_vertices; i++) {
        scanf("%s", l);
        //quebra a string de entrada
        ptr = strtok(l, delimitador);
        strcpy(nome,ptr);
        //printf("%s", nome);
        ptr = strtok(NULL, delimitador);
        idade = atoi(ptr);
        g = insere_vertice(g, nome, idade);
    }

    //Le numero de arestas e depois le os dados de cada aresta
    //Cria as arestas no grafo
    scanf("%d", &num_arestas);
    for (i = 0; i < num_arestas; i++) {
        scanf("%s", l);
        //quebra a string de entrada
        ptr = strtok(l, delimitador);
        strcpy(origem,ptr);
        //printf("%s", nome);
        ptr = strtok(NULL, delimitador);
        strcpy(destino,ptr);
        insere_aresta(g, origem, destino);
    }

    //Le nome de pessoa
    scanf("%s", nome);

    //Encontra o número de seguidos dessa pessoa
    printf("SEGUIDOS por %s: %d\n", nome, numero_seguidos(g, nome));

    //Encontra os seguidores de uma determinada pessoa
    printf("SEGUIDORES de %s:\n", nome);
    seguidores(g, nome, 1);

    TGrafo *p;

    //Encontra mais popular
    p = mais_popular(g);
    printf("MAIS POPULAR: %s\n", p->nome);

    //Encontra as pessoas que seguem apenas pessoas mais velhas
    printf("SEGUEM APENAS PESSOAS MAIS VELHAS:\n");
    segue_mais_velho(g,1);

    libera_vertice(g);
}
