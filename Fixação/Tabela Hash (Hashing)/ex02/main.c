//Tabela Hash => Hash: cumprimento da string - 1
//Tratamento de colisão => Encadeamento

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Item{
    char* nome;
    int valor;
    struct Item* prox;
} Item;

typedef struct{
    Item* tabela[MAX];
} TabelaHash;

int calcularHash(char* chave)
{
    int h = strlen(chave) - 1;
    return abs(h) % MAX;
}

//inserir o elemento
void inserir(TabelaHash* tabela, char* chave)
{
    int indice = calcularHash(chave);

    //verifica se já existe 
    Item* atual = tabela -> tabela[indice];

    while(atual != NULL)
    {
        if(strcmp(atual -> nome, chave) == 0)
        {
            printf("Erro: '%s' já existe na tabela.\n");
            return;
        }
        
        atual = atual -> prox; // Move para o próximo item na lista encadeada
    }

    Item* novoItem = (Item*) malloc(sizeof(Item));
    novoItem -> nome = strdup(chave); // Aloca memória e copia a string
    novoItem -> valor = 0; // Valor padrão
    novoItem -> prox = tabela -> tabela[indice]; // Insere no início da lista
    tabela -> tabela[indice] = novoItem; // Atualiza o início da lista

    printf("'%s' inserido com sucesso.\n", chave);
}

//buscar item
void buscar(TabelaHash* tabela, char* chave)
{
    int indice = calcularHash(chave);

    Item* atual = tabela->tabela[indice];

    while(atual != NULL)
    {
        if(strcmp(atual->nome, chave) == 0)
        {
            printf("'%s' encontrado no índice [%d].\n", chave, indice);
            return;
        }

        atual = atual->prox;
    }

    printf("'%s' não encontrado.\n", chave);
}

//remover item
void remover(TabelaHash* tabela, char* chave)
{
    int indice = calcularHash(chave);

    Item* atual = tabela -> tabela[indice];
    Item* anterior = NULL;

    while(atual != NULL) //se tiver o item 
    {
        if(strcmp(atual -> nome, chave) == 0)
        {
            //se for o primeiro da lista
            if(anterior == NULL)
            {
                tabela -> tabela[indice] = atual -> prox;
            }
            else{
                anterior -> prox = atual -> prox;
            }

            free(atual -> nome);
            free(atual);

            printf("'%s' removido com sucesso.\n", chave);
            return;
        }

        anterior = atual;
        atual = atual -> prox; // Move para o próximo item na lista encadeada
    }

    printf("'%s' não encontrado para remoção.\n", chave);
}

//imprimir a Tabela
void imprimir(TabelaHash* tabela)
{
    printf("=== TABELA HASH ===\n");

    for(int i = 0; i < MAX; i ++)
    {
        printf("[%d]: ", i);
        Item* atual = tabela -> tabela[i];

        if(atual == NULL)
        {
            printf("(vazio)");
        }
        
        while(atual != NULL)
        {
            printf("'%s' -> ", atual -> nome);
            atual = atual -> prox; // Move para o próximo item na lista encadeada
        }

        printf("NULL\n");
    }
}

//liberar memória
void liberarMemoria(TabelaHash* tabela)
{
    for(int i = 0; i < MAX; i++)
    {
        Item* atual = tabela -> tabela[i];

        while(atual != NULL)
        {
            Item* temp = atual;
            atual = atual -> prox;

            free(temp -> nome);
            free(temp);
        }
    }
}

int main()
{
    TabelaHash minhaTabela;

    // inicializa tudo com NULL
    for(int i = 0; i < MAX; i++)
    {
        minhaTabela.tabela[i] = NULL;
    }

    int opcao;
    char nome[50];

    do {
        printf("\n===== MENU =====\n");
        printf("1. Inserir\n");
        printf("2. Buscar\n");
        printf("3. Remover\n");
        printf("4. Imprimir tabela\n");
        printf("0. Sair\n");
        printf("Escolha: ");

        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                printf("Nome: ");
                scanf("%49s", nome);

                inserir(&minhaTabela, nome);
            break;

            case 2:
                printf("Nome para buscar: ");
                scanf("%49s", nome);

                buscar(&minhaTabela, nome);
            break;

            case 3:
                printf("Nome para remover: ");
                scanf("%49s", nome);

                remover(&minhaTabela, nome);
            break;

            case 4:
                imprimir(&minhaTabela);
            break;

            case 0:
                printf("Saindo...\n");
            break;

            default:
                printf("Opção inválida.\n");
        }

    } while(opcao != 0);

    liberarMemoria(&minhaTabela);

    return 0;
}
