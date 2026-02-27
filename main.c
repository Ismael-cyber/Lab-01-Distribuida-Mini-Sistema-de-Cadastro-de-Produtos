#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void buscar_produto(Lista *lista) {
    char nome_produto[50];
    printf("Qual produto esta buscando em nosso sistema: ");
    scanf("%49s", nome_produto);

    for(int i = 0; i < lista->quantidade; i++) {
        if(strcmp(nome_produto, lista->dados[i].nome) == 0) {
            printf("\nProduto encontrado: \n");
            printf("|  %3d  |  %-10s  |  %8.2f  |  %4d  |\n",
                lista->dados[i].codigo, 
                lista->dados[i].nome, 
                lista->dados[i].preco, 
                lista->dados[i].quantidade);
            break; 
        }
        else {
            printf("Nenhum produto com este nome foi encontrado.\n");
            break;
        }
    }
};
// void atualizar_estoque();
// void remover_produto();
// void liberar_memoria();

int main(void) {
    // Declarar vetor de Produtos
    Lista lista;
    lista.dados = NULL;
    lista.quantidade = 0;

    //Loop para rodar sistema enquanto usuário não quer sair do programa
    int opcao;
    while(opcao != 6) {
        // Aparicao do MENU
        printf("==============================================\n");
        printf("====== Sistema de Cadastro de Produtos =======\n");
        printf("==============================================\n");
        printf("Menu\n");
        printf("1. Adicionar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Buscar Produto\n");
        printf("4. Atualizar Estoque\n");
        printf("5. Remover Produto\n");
        printf("6. Sair\n");

        // Escolha das opcoes
        printf("Escolha uma das opcoes: ");
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
            buscar_produto(&lista);
        }
        // //Condição 4
        // if(opcao == 4) {
        //     atualizar_estoque();
        // }
        // //Condição 5
        // if(opcao == 5) {
        //     remover_produto();
        // }
        //Condição 6
        if(opcao == 6) {
            printf("VOCE FOI DESCONECTADO!");
            exit;
        }
    }
    return 0;
}