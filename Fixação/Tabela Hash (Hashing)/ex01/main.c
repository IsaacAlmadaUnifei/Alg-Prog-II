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
void inserir(TabelaHash* tabela, char* chave, int valor)
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
    novo -> valor = valor;
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

    // Teste 1: Nomes com tamanhos diferentes
    inserir(&minhaTabela, "Ana", 10);      // 3 letras -> índice 2
    inserir(&minhaTabela, "Carlos", 30);   // 6 letras -> índice 5
    
    // Teste 2: Causando a colisão propositalmente
    inserir(&minhaTabela, "Bob", 20);      // 3 letras -> índice 2 (Opa!)
    inserir(&minhaTabela, "Bia", 50);      // 3 letras -> índice 2 (Opa de novo!)

    imprimirTabela(&minhaTabela);

    return 0;
}