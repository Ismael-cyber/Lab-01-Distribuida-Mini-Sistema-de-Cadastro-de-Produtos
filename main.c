// Gabriel Lazareti - RA: 10417353
// Hailo Neto - RA: 10416839
// Ismael Sousa - RA: 10410870

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do produto
typedef struct {
    int codigo;
    char *nome;
    float preco;
    int quantidade;
} Produto;

// Estrutura da lista
typedef struct {
    Produto *dados;
    int quantidade;
} Lista;

// ---------------- ADICIONAR PRODUTO ----------------

void adicionar_produto(Lista *lista) {

    lista->quantidade++;

    lista->dados = realloc(lista->dados, lista->quantidade * sizeof(Produto));

    if(lista->dados == NULL){
        printf("Erro de alocacao de memoria\n");
        exit(1);
    }

    Produto *novo = &lista->dados[lista->quantidade - 1];

    novo->codigo = lista->quantidade;

    novo->nome = malloc(50);

    printf("Nome do produto: ");
    scanf("%49s", novo->nome);

    printf("Preco: ");
    scanf("%f", &novo->preco);

    printf("Quantidade: ");
    scanf("%d", &novo->quantidade);

    printf("Produto cadastrado com sucesso!\n");
}

// ---------------- LISTAR PRODUTOS ----------------

void listar_produtos(Lista *lista){

    if(lista->quantidade == 0){
        printf("Nenhum produto cadastrado\n");
        return;
    }

    float total_estoque = 0;

    printf("\n+---------------------------------------------------------------+\n");
    printf("| COD | NOME        | PRECO     | QTD | VALOR EM ESTOQUE        |\n");
    printf("+---------------------------------------------------------------+\n");

    for(int i = 0; i < lista->quantidade; i++){

        float valor = lista->dados[i].preco * lista->dados[i].quantidade;

        total_estoque += valor;

        printf("| %3d | %-11s | %8.2f | %3d | %10.2f |\n",
            lista->dados[i].codigo,
            lista->dados[i].nome,
            lista->dados[i].preco,
            lista->dados[i].quantidade,
            valor);
    }

    printf("+---------------------------------------------------------------+\n");

    printf("Valor total do estoque: %.2f\n", total_estoque);
}

// ---------------- BUSCAR PRODUTO ----------------

Produto* buscar_produto(Lista *lista){

    int codigo;

    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);

    for(int i = 0; i < lista->quantidade; i++){

        if(lista->dados[i].codigo == codigo){

            return &lista->dados[i];

        }
    }

    return NULL;
}

// ---------------- IMPRIMIR PRODUTO ----------------

void imprimirProduto(Produto *p){

    if(p == NULL){
        printf("Produto nao encontrado\n");
        return;
    }

    printf("\n+----------------------------------------+\n");
    printf("| COD | NOME        | PRECO   | QTD      |\n");
    printf("+----------------------------------------+\n");

    printf("| %3d | %-11s | %7.2f | %8d |\n",
        p->codigo,
        p->nome,
        p->preco,
        p->quantidade);

    printf("+----------------------------------------+\n");
}

// ---------------- ATUALIZAR ESTOQUE ----------------

void atualizar_estoque(Lista *lista){

    Produto *produto = buscar_produto(lista);

    if(produto == NULL){
        printf("Produto nao encontrado\n");
        return;
    }

    int nova_qtd;

    printf("Digite a nova quantidade: ");
    scanf("%d", &nova_qtd);

    produto->quantidade = nova_qtd;

    printf("Estoque atualizado!\n");

    imprimirProduto(produto);
}

// ---------------- REMOVER PRODUTO ----------------

void remover_produto(Lista *lista){

    int codigo;

    printf("Digite o codigo do produto que deseja remover: ");
    scanf("%d", &codigo);

    int indice = -1;

    for(int i = 0; i < lista->quantidade; i++){
        if(lista->dados[i].codigo == codigo){
            indice = i;
            break;
        }
    }

    if(indice == -1){
        printf("Produto nao encontrado\n");
        return;
    }

    free(lista->dados[indice].nome);

    for(int i = indice; i < lista->quantidade - 1; i++){
        lista->dados[i] = lista->dados[i + 1];
    }

    lista->quantidade--;

    lista->dados = realloc(lista->dados, lista->quantidade * sizeof(Produto));

    printf("Produto removido com sucesso!\n");
}

// ---------------- LIBERAR MEMORIA ----------------

void liberar_memoria(Lista *lista){

    for(int i = 0; i < lista->quantidade; i++){
        free(lista->dados[i].nome);
    }

    free(lista->dados);

    printf("Memoria liberada com sucesso!\n");
}

// ---------------- MAIN ----------------

int main(){

    Lista lista;

    lista.dados = NULL;
    lista.quantidade = 0;

    int opcao = 0;

    while(opcao != 6){

        printf("\n==============================================\n");
        printf("====== Sistema de Cadastro de Produtos =======\n");
        printf("==============================================\n");

        printf("\n1 - Adicionar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Buscar Produto\n");
        printf("4 - Atualizar Estoque\n");
        printf("5 - Remover Produto\n");
        printf("6 - Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        if(opcao == 1){
            adicionar_produto(&lista);
        }

        if(opcao == 2){
            listar_produtos(&lista);
        }

        if(opcao == 3){
            Produto *p = buscar_produto(&lista);
            imprimirProduto(p);
        }

        if(opcao == 4){
            atualizar_estoque(&lista);
        }

        if(opcao == 5){
            remover_produto(&lista);
        }

        if(opcao == 6){
            liberar_memoria(&lista);
            printf("Encerrando programa...\n");
        }
    }

    return 0;
}
