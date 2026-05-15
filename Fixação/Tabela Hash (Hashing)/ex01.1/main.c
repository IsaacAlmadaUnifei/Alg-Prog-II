//tabela hashing - hash = cumprimento da string - 1 
//SEM TRATAMENTO DE COLISÃO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 10 

typedef struct {
    char* chave;
    int valor;
} Item;

typedef struct {
    Item* slots[TAMANHO];
} TabelaHash;

//regra hash: cumprimento da string - 1
int calcularHash(char* chave)
{
    int h = strlen(chave) - 1;
    return abs(h) % TAMANHO; //abs = valor absoluto
}

//inserir na tabela 
void inserir(TabelaHash* tabela, char* chave)
{
    int indice = calcularHash(chave);
   //verifica se a chave já existe
   if (tabela -> slots[indice] != NULL)
   {
    printf("Erro: Colisão em [%d]! '%s' já existe.\n", indice, chave);
    printf("Índice: %d, Chave que tentou inserir: '%s', Chave existente: '%s'\n", indice, chave, tabela -> slots[indice] -> chave);
    // Tratamento de colisão: neste exemplo, apenas exibe uma mensagem de erro
    return;
   } 

   //se estiver vazio, insere o item
    Item* novo = malloc(sizeof(Item)); //aloca memória para o novo item
    novo -> chave = strdup(chave); //duplica a string para armazenar na tabela
    novo -> valor = 0; // valor padrão, já que não estamos passando um valor
    tabela -> slots[indice] = novo;

    printf("Sucesso: '%s' foi inserido na tabela no índice [%d].\n", chave, indice);
}

//imprimir a tabela
void imprimirTabela(TabelaHash* tabela)
{
    printf("\nTabela Hash:\n");
    
    for (int i = 0; i < TAMANHO; i++)
    {
        if(tabela -> slots[i] == NULL) //verifica se o slot não está vazio
        {
            printf("[%d]: (vazio)\n", i);
        }
        else
        {
            printf("[%d]: '%s' -> %d\n", i, tabela -> slots[i] -> chave, tabela -> slots[i] -> valor);
        }
    }
}

int main() {
    // Inicializa a tabela com NULL
    TabelaHash minhaTabela;
    for(int i=0; i<TAMANHO; i++) minhaTabela.slots[i] = NULL;

    char nome[50];
    int opcao, continuar = 1;

    do{
        printf("\nMenu:\n");
        printf("1. Inserir nome\n");
        printf("2. Imprimir tabela\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch(opcao)
        {
            case 1:
                printf("Nome: ");
                scanf("%s", nome);
                inserir(&minhaTabela, nome);
            break;
            case 2:
                imprimirTabela(&minhaTabela);
            break;
            case 0:
                printf("Saindo...\n");
            break;

            default:
                printf("Opção inválida! Tente novamente.\n");
            break;
        }
    }while(opcao != 0);

    for(int i = 0; i < TAMANHO; i++) {
    if(minhaTabela.slots[i] != NULL) {
        free(minhaTabela.slots[i]->chave);
        free(minhaTabela.slots[i]);
    }
    }

    return 0;
}