#include <stdio.h>
#include <stdlib.h> // Funcões de alocacao

// Estruturas:
typedef struct no // Estrutura de um No
{
    int valor;           // Dados
    struct no* prox;     // Ponteiro para o proximo no
} No;

typedef struct
{
    No *inicio;          // Ponteiro para no
} Lista;
//----------------------------------------------------

enum Opcoes
{
    inserir_no_inicio = 1, // Comeca do 1
    inserir_no_fim, // Vai valer 2!
    inserir_ordem, // Assim por diante!
    remover_primeiro,
    remover_ultimo,
    remover_elemento,
    busca_posicao,
    busca_conteudo,
    tamanho,
    exibir,
    esvaziar,
    sair
};

// Interface:
void Menu(); // Procedimento para exibir um menu de opcoes
void Atraso(); // Procedimento para gerar um atraso de tempo
// Inicializacao de estruturas:
No *Criar_No(const int val); // Funcao para criar um novo no e retornar seu endereco
Lista *Criar_Lista(); // Funcao para criar uma nova lista
// Insercao:
void Inserir_no_Fim(Lista *, const int); // Procedimento para inserir um elemento no fim de uma lista
void Inserir_no_Inicio(Lista *, const int); // Procedimento para inserir um elemento no inicio de uma lista
void Inserir_Ordenadamente(Lista *, const int); // Procedimento para inserir um elemento de maneira ordenada na lista
// Remocao
void Remover_do_Fim(Lista *); // Procedimento para remover o ultimo elemento de uma lista
void Remover_do_Inicio(Lista *); // Procedimento para remover o primeiro elemento de uma lista
int Remover_Elemento(Lista *, int ); // Procedimento para remover um elemento especifico da lista
// Busca:
int Busca_por_Posicao(const Lista *, const int, int *); // Funcao para buscar um elemento por posicao
int Busca_por_Conteudo(const Lista *, int *, const int); // Funcao para buscar um elemento por conteudo
int Tamanho(const Lista *); // Funcao para retornar o tamanho da lista
void Imprimir_Lista(const Lista *); // Procedimento para imprimir uma lista
void Esvaziar_Lista(Lista *l); // Procedimento para liberar os espacos de memoria ocupados
void Destruir_Lista(Lista *l); // Procedimento para Destruir uma lista

int main( void )
{
    Lista *lista = Criar_Lista();
    int op = 0;
    while ( op != sair )
    {
        Menu(); // Exibe o menu
        scanf("%d", &op); // Le a opcao desejada
        int val; // valor
        int pos; // Posicao
        switch (op)
        {
            case inserir_no_inicio:
                printf("Digite o elemento a ser inserido: ");
                scanf("%d", &val); // Le o valor
                Inserir_no_Inicio(lista, val);
                break;
            case inserir_no_fim:
                printf("Digite o elemento a ser inserido: ");
                scanf("%d", &val); // Le o valor
                Inserir_no_Fim(lista, val); // Insere no final da lista
                break;
            case inserir_ordem:
                printf("Digite o elemento a ser inserido: ");
                scanf("%d", &val); // Le o valor
                Inserir_Ordenadamente(lista, val);
                break;
            case remover_primeiro:
                Remover_do_Inicio(lista);
                break;
            case remover_ultimo:
                Remover_do_Fim(lista); // Remove o ultimo elemento
                break;
            case remover_elemento:
                printf("Digite o elemento a ser removido: ");
                scanf("%d", &val); // Le o valor
                if ( Remover_Elemento(lista, val) )
                    printf("Elemento removido\n");
                else
                    printf("Elemento nao encontrado\n");
                break;
            case busca_posicao:
                printf("Digite a posicao do elemento (comecando em zero): ");
                scanf("%d", &pos);
                if ( Busca_por_Posicao(lista, pos, &val) ) // Encontrou
                    printf("Elemento na posicao %d: %d\n", pos, val); // Exibe o encontrado
                else
                    printf("Posicao invalida\n");
                break;
            case busca_conteudo:
                printf("Digite o conteudo a ser buscado: ");
                scanf("%d", &val);
                if ( Busca_por_Conteudo(lista, &pos, val) ) // Encontrou
                    printf("Encontrado na posicao: %d\n", pos); // Exibe a posicao
                else
                    printf("Nao encontrado\n");
                break;
            case tamanho:
                printf("Tamanho da Lista: %d\n", Tamanho(lista)); // Exibe o tamanho da lista
                break;
            case exibir:
                Imprimir_Lista(lista); // Exibe a lista
                break;
            case esvaziar:
                Esvaziar_Lista( lista ); // Destre a lista
                break;
            case sair:
                printf("Saindo...\n");
                break;
            default:
                printf("Comando Invalido\n");
                break;
        }
        Atraso(); // Gera um atraso (delay) de tempo
        //system("cls");
    }
    Destruir_Lista(lista); // Garante que a lista sera destruida
    return 0;
}

void Menu() // Procedimento para exibir um menu de opcoes
{
    printf("%d - Inserir no inicio da lista\n", inserir_no_inicio);
    printf("%d - Inserir no final da lista\n", inserir_no_fim);
    printf("%d - Inserir ordenadamente\n", inserir_ordem);
    printf("%d - Remover primeiro elemento\n", remover_primeiro);
    printf("%d - Remover ultimo elemento\n", remover_ultimo);
    printf("%d - Remover elemento\n", remover_elemento);
    printf("%d - Busca por posicao\n", busca_posicao);
    printf("%d - Busca por conteudo\n", busca_conteudo);
    printf("%d - Tamanho da Lista\n", tamanho);
    printf("%d - Exibir Lista\n", exibir);
    printf("%d - Esvaziar Lista\n", esvaziar);
    printf("%d - Sair\n", sair);
    printf(">> ");
}

void Atraso() // Procedimento para gerar um atraso de tempo
{
    for ( int i = 0; i < 2E8; i++ );
}

No *Criar_No(const int val) // Funcao para criar um novo no e retornar seu endereco
{
    No *novo_no = (No*) malloc(sizeof(No)); // Aloca o espaco necessário para um no
    novo_no->valor = val;  // Atualiza o campo de dado para o valor desejado
    novo_no->prox = NULL;  // Inicialmente, nao aponta para ninguém
    return novo_no;        // Retorna o endereco do novo no (ponteiro)
}

Lista *Criar_Lista() // Funcao para criar uma nova lista
{
    Lista *l = (Lista*) malloc(sizeof(Lista)); // Aloca espaco para a lista
    l->inicio = NULL; // Lista vazia
    return l; // Retorna o endereco da lista
}
//------------------------------------------------------------------------------

// Insercao:
void Inserir_no_Fim(Lista *l, const int val) // Procedimento para inserir um elemento no fim de uma lista
{
    No *novo_no = Criar_No(val); // Cria um novo no
    if (l->inicio == NULL) // Lista vazia
        l->inicio = novo_no; // Aponta para o novo no
    else // Lista tem elementos
    {
        No *aux = l->inicio; // Primeiro no
        while (aux->prox != NULL) // Enquanto houver proximo elemento
        {
            aux = aux->prox; // Aponta para o proximo elemento
        }
        aux->prox = novo_no; // Adiciona o novo no no final
    }
}

void Inserir_no_Inicio(Lista *l, const int val) // Procedimento para inserir um elemento no inicio de uma lista
{
    No *novo_no = Criar_No(val); // Cria um novo no
    if ( l->inicio == NULL )
        l->inicio = novo_no;
    else
    {
        novo_no->prox = l->inicio; // O proximo do novo no e o atual primeiro elemento
        l->inicio = novo_no; // O novo primeiro elemnto e o no recem-criado
    }
}

void Inserir_Ordenadamente(Lista *l, const int val) // Procedimento para inserir um elemento de maneira ordenada na lista
{
    No *novo_no = Criar_No(val); // Cria um novo no
    if ( l->inicio == NULL || l->inicio->valor >= val) // Lista Vazia ou primeiro elemento maior que val
    {
        novo_no->prox = l->inicio; // Novo no aponta para o inicio
        l->inicio = novo_no; // O inicio aponta para o novo no criado
    }
    else
    {
        No *aux = l->inicio; // Primeiro no
        while ( aux->prox != NULL && aux->prox->valor < val ) // Enquanto for menor e houver proximo, cuidado com a ordem das condicoes
            aux = aux->prox; // Atualiza o atual para o proximo no
        // aux --> no anterior ao novo no
        novo_no->prox = aux->prox; // Novo no aponta para No depois de aux
        aux->prox = novo_no; // Anterior aponta para o novo no
    }
}
//------------------------------------------------------------------------

// Remocao:

void Remover_do_Fim(Lista *l) // Procedimento para remover o ultimo elemento de uma lista
{
    if ( l->inicio == NULL)// Lista vazia
        return; // Sai do procedimento
    else if ( l->inicio->prox == NULL ) // um unico elemento
    {
        free(l->inicio); // Libera o espaco
        l->inicio = NULL; // Lista vazia
    }
    else // Tem mais de um elemento
    {
        No *aux = l->inicio; // Primeiro elemento
        No *ant = NULL; // No anterior
        while ( aux-> prox != NULL ) // Tem proximo elemento
        {
            ant = aux; // No anterior
            aux = aux->prox; // Aponta para o proximo
        }
        free(aux); // Libera o espaco do ultimo elemento
        ant->prox = NULL; // Parou no penultimo elemento
    }
}

void Remover_do_Inicio(Lista *l) // Procedimento para remover o primeiro elemento de uma lista
{
    if ( l->inicio == NULL) // Lista Vazia
        return; // Forca a saida
    else
    {
        No *aux = l->inicio;
        l->inicio = l->inicio->prox; // Novo inicio e o segundo elemento
        free(aux); // Libera o espaco alocado para o antigo primeiro no
    }
}

int Remover_Elemento(Lista *l, int elemento) // Funcao para remover um elemento especifico da lista
{
    if ( l->inicio == NULL ) // Lista vazia
        return 0; // Ninguem removido
    No *aux = l->inicio; // Primeiro No
    No *ant = NULL; // No anterior
    while ( aux!=NULL && aux->valor != elemento ) // Percorre a lista ate encotrar ou chegar no final
    {
        ant = aux; // Atualiza o no anterior
        aux = aux->prox; // Aponta para o proximo no
    }
    if ( aux == NULL ) // Elemento nao encontrado
        return 0; // Ninguem removido
    if ( aux == l->inicio ) // Primeiro elemento
        l->inicio = l->inicio->prox; // Pula o primeiro no
    else // Se nao
        ant->prox = aux->prox; // Anterior pula um no
    free(aux); // Libera o espaco do no removido
    return 1; // Elemento removido
}
//-------------------------------------------------------------

// Buscas:
int Busca_por_Posicao(const Lista *l, const int pos, int *val) // Funcao para buscar um elemento por posicao
{
   No *aux = l->inicio; // Primeiro No
   int i = 0; // Contador
   while ( aux!= NULL && i < pos ) // Enquanto tiver no antes de pos
   {
       aux = aux->prox; // Apoonta para o proximo No
       i++; // Incrementa o contador
   }
   if ( aux != NULL ) // Encontrou
   {
       *val = aux->valor;  // Atualiza para o valor do elemento na posicao pos
       return 1; // Retorna 1 (sucesso)
   }
   return 0; // Nao encontrou

}

int Busca_por_Conteudo(const Lista *l, int *pos, const int val) // Funcao para buscar um elemento por conteudo
{
   No *aux = l->inicio; // Primeiro No
   int i = 0; // Contador
   while ( aux!= NULL && aux->valor!=val ) // Enquanto tiver no com conteudo diferente de val
   {
       aux = aux->prox; // Apoonta para o proximo No
       i++; // Incrementa o contador
   }
   if ( aux != NULL ) // Encontrou
   {
       *pos = i;  // Atualiza para o valor do elemento na posicao pos
       return 1; // Retorna 1 (sucesso)
   }
   return 0; // Nao encontrou

}

//------------------------------------------------
int Tamanho(const Lista *l) // Funcao para retornar o tamanho da lista
{
    int tam = 0; // Tamanho da lista
    No *aux = l->inicio; // Primeiro No
    while ( aux != NULL ) // Enquanto houver No
    {
        aux = aux->prox; // Proximo No
        tam++; // Mais um elemento
    }
    return tam; // Retorna o tamanho da lista (numero de elementos)
}

void Imprimir_Lista(const Lista *l) // Procedimento para imprimir uma lista
{
    No *aux = l->inicio;
    if (aux == NULL) // Lista vazia
        printf("Lista vazia\n");
    else // Tem elemento
    {
        while (aux != NULL) // Enquanto houver proximo elemento
        {
            printf("%d -> ", aux->valor); // Exibe o elemento
            aux = aux->prox; // Aponta para o proximo elemento
        }
        printf("NULL\n"); // Indica o final da lista
    }
}

void Esvaziar_Lista(Lista *l) // Procedimento para liberar os espacos de memoria ocupados pelos nos
{
    No *aux = l->inicio; // Auxiliar
    while ( aux != NULL )
    {
        No *proximo = aux->prox; // Proximo no
        free(aux); // Libera o espaco ocupado por esse no
        aux = proximo; // Aux recebe o proximo no
    }
    l->inicio = NULL; // Atualiza o ponteiro inicial da lista para NULL
}

void Destruir_Lista(Lista *l) // Procedimento para Destruir uma lista
{
    No *aux = l->inicio; // Auxiliar
    while ( aux != NULL )
    {
        No *proximo = aux->prox; // Proximo no
        free(aux); // Libera o espaco ocupado por esse no
        aux = proximo; // Aux recebe o proximo no
    }
    free(l); // Libera o espaco de memoria
}
