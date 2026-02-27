#include <stdio.h>
#include <stdlib.h>

// Tipo do dado que será usado
typedef struct {
    int codigo;
    char *nome[50];
    float preco;
    int quantidade;
} Produto;

// Espaço para armazenar os produtos
Produto *produtos;

//Funções do nosso sistema de cadastro de produtos
void adicionar_produto(Produto *produtos) {
    produtos = malloc(sizeof(Produto));

    if(produtos == NULL) {
        printf("Erro: Falha na alocação de memória!\n");
    }

    int qtd;
    printf("Quantos produtos ira adicionar: ");
    scanf("%d", &qtd);

    for(int i = 0; i < qtd; i++) {
        printf("Nome: ");
        scanf("%s", produtos->nome);
        printf("Preco: ");
        scanf("%f", &produtos->preco);
        printf("Quantidade: ");
        scanf("%d", &produtos->quantidade);
        produtos->codigo++;
        free(produtos);
    }
};
// void listar_produtos();
// Produto* buscar_produto();
// void atualizar_estoque();
// void remover_produto();
// void liberar_memoria();

int main(void) {
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
            adicionar_produto(produtos);
        }
        // //Condição 2
        // if(opcao == 2) {
        //     listar_produtos();
        // }
        // //Condição 3
        // if(opcao == 3) {
        //     buscar_produto();
        // }
        // //Condição 4
        // if(opcao == 4) {
        //     atualizar_estoque();
        // }
        // //Condição 5
        // if(opcao == 5) {
        //     remover_produto();
        // }
        // //Condição 6
        // if(opcao == 6) {
        //     printf("Até Breve!");
        // }
    }
    
    return 0;
}