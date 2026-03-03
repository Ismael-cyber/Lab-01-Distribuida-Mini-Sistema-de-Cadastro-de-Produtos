#include <stdio.h>
#include <stdlib.h>

// Tipo do dado que será usado
typedef struct {
    int codigo;
    char *nome;
    float preco;
    int quantidade;
} Produto;

typedef struct {
    Produto *dados;
    int quantidade;
} Lista;

//Funções do nosso sistema de cadastro de produtos
void adicionar_produto(Lista *lista) {    
    printf("Quantos produtos ira adicionar: ");
    scanf("%d", &lista->quantidade);

    lista->dados = malloc(lista->quantidade * sizeof(Produto));
    
    if(lista->dados == NULL) {
        printf("Erro: Falha na alocação de memória!\n");
    }
    
    for(int i = 0; i < lista->quantidade; i++) {
        lista->dados[i].nome = malloc(50);

        printf("Nome: ");
        scanf("%49s", lista->dados[i].nome);
        printf("Preco: ");
        scanf("%f", &lista->dados[i].preco);
        printf("Quantidade: ");
        scanf("%d", &lista->dados[i].quantidade);
        lista->dados[i].codigo = i + 1;
    }
};

void listar_produtos(Lista *lista) {
    if(lista->dados == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("+--------------------------------------------+\n");
    printf("----------- LISTAGEM DOS PRODUTOS ------------\n");
    printf("+--------------------------------------------+\n");
    for(int i = 0; i < lista->quantidade; i++) {
        printf("|  %3d  |  %-10s  |  %8.2f  |  %4d  |\n",
            lista->dados[i].codigo, 
            lista->dados[i].nome, 
            lista->dados[i].preco, 
            lista->dados[i].quantidade); 
        }
    printf("+--------------------------------------------+\n");
};

Produto* buscar_produto(Lista *lista) {
    int codigo_produto;
    printf("Digite o codigo do produto cadastro em nosso sistema: ");
    scanf(" %d", &codigo_produto);

    for(int i = 0; i < lista->quantidade; i++) {
        if(codigo_produto == lista->dados[i].codigo) {
            return &lista->dados[i];
        }
    }   

    return NULL;
};

void imprimirProduto(Produto *p) {
    if(p == NULL) {
        printf("Produto nao encontrado.\n");
    }

    printf("+-----------------------------------------+\n");
    printf("| Cod    | Nome        | Preco   | Qtd    |\n");
    printf("+-----------------------------------------+\n");
    printf("| %6d | %-11s | %-7.2f | %-6d |\n",
           p->codigo,
           p->nome,
           p->preco,
           p->quantidade);
    printf("+-----------------------------------------+\n");
}

void atualizar_estoque(Lista *lista) {
    int novo_valor_estoque;

    Produto *atualiza_produto = buscar_produto(lista);
    
    printf("\nDigite o novo valor existente no estoque: ");
    scanf(" %d", &novo_valor_estoque);
    
    atualiza_produto->quantidade = novo_valor_estoque;

    imprimirProduto(atualiza_produto);
};

void remover_produto(Lista *lista) {
    Produto *produto_removido = buscar_produto(lista);

    free(produto_removido->nome); //Liberando a memória alocada para o nome do produto no vetor

    for(int i = produto_removido->codigo; i < lista->quantidade - 1; i++) {
        lista->dados[i] = lista->dados[i + 1]; //Deslocando os elementos no vetor
    }

    lista->quantidade--; //Diminuindo a quantidade de produtos no vetor
    lista->dados = realloc(lista->dados, lista->quantidade * sizeof(Produto)); // Realocando tamanho do vetor
};

void liberar_memoria(Lista *lista) {
    free(lista->dados);
    printf("Memoria liberada, forte abraco!\n");
};

int main(void) {
    // Declarar vetor de Produtos
    Lista lista;
    lista.dados = NULL;
    lista.quantidade = 0;

    //Loop para rodar sistema enquanto usuário não quer sair do programa
    int opcao;
    while(opcao != 6) {
        // Aparicao do MENU
        printf("\n==============================================\n");
        printf("====== Sistema de Cadastro de Produtos =======\n");
        printf("==============================================\n");
        printf("\nMenu\n");
        printf("1. Adicionar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Buscar Produto\n");
        printf("4. Atualizar Estoque\n");
        printf("5. Remover Produto\n");
        printf("6. Sair\n");

        // Escolha das opcoes
        printf("\nEscolha uma das opcoes: ");
        scanf("%d", &opcao);

        //Condição 1
        if(opcao == 1) {
            adicionar_produto(&lista);
        }
        // //Condição 2
        if(opcao == 2) {
            listar_produtos(&lista);
        }
        //Condição 3
        if(opcao == 3) {
            Produto *resultado = buscar_produto(&lista);
            imprimirProduto(resultado);
        }
        //Condição 4
        if(opcao == 4) {
            atualizar_estoque(&lista);
        }
        //Condição 5
        if(opcao == 5) {
            remover_produto(&lista);
        }
        //Condição 6
        if(opcao == 6) {
            liberar_memoria(&lista);
            printf("VOCE FOI DESCONECTADO!");
            exit(0);
        }
    }
    return 0;
}