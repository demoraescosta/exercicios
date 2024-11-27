#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int  codigo;
    char titulo[50];
    char autor[50];
    int  ano;
} Livro;

const char* ARQUIVO_LIVROS = "livros.txt";

void incluir_filme()
{
    Livro l = {0};

    FILE* arquivo = fopen(ARQUIVO_LIVROS, "a");

    if (arquivo == NULL)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }

    printf("digite o codigo do filme: ");
    scanf("%d", &l.codigo);
    getchar();

    printf("digite o titulo do filme: ");
    fgets(l.titulo, sizeof(l.titulo), stdin);
    l.titulo[strcspn(l.titulo, "\n")] = 0;

    printf("digite o autor: ");
    fgets(l.autor, sizeof(l.autor), stdin);
    l.autor[strcspn(l.autor, "\n")] = 0;

    printf("digite o ano do filme: ");
    scanf("%d", &l.ano);

    fprintf(arquivo, "%d,%s,%s,%d\n", l.codigo, l.titulo, l.autor, l.ano);
    fclose(arquivo);

    printf("filme incluido com sucesso!\n");
}

void excluir_filme()
{
    Livro l = {0};

    int codigo         = 0;
    int encontrado = 0;

    FILE* arquivo = fopen(ARQUIVO_LIVROS, "r");
    FILE* temp    = fopen("temp.txt", "w");

    if (arquivo == NULL || temp == NULL)
    {
        printf("erro ao abrir o arquivo!\n");
        return;
    }

    printf("digito a codigo do filme a ser excluido: ");
    scanf("%d", &codigo);

    while (fgets(l.titulo, sizeof(l.titulo), arquivo))
    {
        sscanf(l.titulo, "%d,%49[^,],%49[^,],%d", &l.codigo, l.titulo, l.autor, &l.ano);
        if (l.codigo == codigo)
        {
            encontrado = 1;
        }
        else
        {
            fprintf(temp, "%d,%s,%s,%d\n", l.codigo, l.titulo, l.autor, l.ano);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO_LIVROS);
    rename("temp.txt", ARQUIVO_LIVROS);

    if (encontrado)
    {
        printf("filme excluido com sucesso\n");
    }
    else
    {
        printf("filme nao encontrado.\n");
    }
}

void alterar_livros()
{
    Livro l = {0};

    int codigo, encontrado = 0;

    FILE* arquivo = fopen(ARQUIVO_LIVROS, "r");
    FILE* temp    = fopen("temp.txt", "w");

    if (arquivo == NULL || temp == NULL)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }

    printf("digite a codigo do filme a ser alterado: ");
    scanf("%d", &codigo);
    getchar();

    while (fgets(l.titulo, sizeof(l.titulo), arquivo))
    {
        sscanf(l.titulo, "%d,%49[^,],%49[^,],%d", &l.codigo, l.titulo, l.autor, &l.ano);
        if (l.codigo == codigo)
        {
            encontrado = 1;

            printf("digite o novo titulo do filme: ");
            fgets(l.titulo, sizeof(l.titulo), stdin);
            l.titulo[strcspn(l.titulo, "\n")] = 0;

            printf("digite o novo autor: ");
            fgets(l.autor, sizeof(l.autor), stdin);
            l.autor[strcspn(l.autor, "\n")] = 0;

            printf("digite o nova ano: ");
            scanf("%d", &l.ano);
            getchar();
        }
        fprintf(temp, "%d,%s,%s,%d\n", l.codigo, l.titulo, l.autor, l.ano);
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO_LIVROS);
    rename("temp.txt", ARQUIVO_LIVROS);

    if (encontrado)
    {
        printf("filme alterado com sucesso!\n");
    }
    else
    {
        printf("filme nao encontrado\n");
    }
}

void consultar_livros()
{
    Livro l = {0};

    int codigo = 0;
    int encontrado = 0;
    
    FILE* arquivo = fopen(ARQUIVO_LIVROS, "r");

    if (arquivo == NULL)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }

    printf("digite o codigo do filme para a consulta: ");
    scanf("%d", &codigo);

    while (fgets(l.titulo, sizeof(l.titulo), arquivo))
    {
        sscanf(l.titulo, "%d,%49[^,],%49[^,],%d", &l.codigo, l.titulo, l.autor, &l.ano);
        if (l.codigo == codigo)
        {
            printf("filme encontrado:\n");
            printf("codigo: %d\n", l.codigo);
            printf("titulo: %s\n", l.titulo);
            printf("autor: %s\n", l.autor);
            printf("ano: %d\n", l.ano);
            encontrado = 1;
            break;
        }
    }

    fclose(arquivo);

    if (!encontrado)
    {
        printf("filme nao encontrado.\n");
    }
}

void listar_livros()
{
    Livro l = {0};

    FILE* arquivo = fopen(ARQUIVO_LIVROS, "r");

    if (arquivo == NULL)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }

    printf("\nlista de livros:\n");

    while (fgets(l.titulo, sizeof(l.titulo), arquivo))
    {
        sscanf(l.titulo, "%d,%49[^,],%49[^,],%d", &l.codigo, l.titulo, l.autor, &l.ano);
        printf("    codigo: %d | titulo: %s | autor: %s | ano: %d\n", l.codigo, l.titulo, l.autor, l.ano);
    }

    fclose(arquivo);
}

enum OPCOES
{
    INCLUIR_LIVRO   = 1,
    EXCLUIR_LIVRO   = 2,
    ALTERAR_LIVRO   = 3,
    CONSULTAR_LIVRO = 4,
    LISTAR_LIVRO    = 5,
    SAIR            = 6,
};

void exibir_menu()
{
    printf("%d> incluir livros\n", INCLUIR_LIVRO);
    printf("%d> excluir livros\n", EXCLUIR_LIVRO);
    printf("%d> alterar livros\n", ALTERAR_LIVRO);
    printf("%d> consultar livros\n", CONSULTAR_LIVRO);
    printf("%d> listar livros\n", LISTAR_LIVRO);
    printf("%d> sair\n", SAIR);
}

int main()
{
    int opcao = 0;

    printf("sistema de cadastro de livros:\n\n");

    while (opcao != 6)
    {
        exibir_menu();
        printf("escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
            case INCLUIR_LIVRO:
                incluir_filme();
                break;

            case EXCLUIR_LIVRO:
                excluir_filme();
                break;

            case ALTERAR_LIVRO:
                alterar_livros();
                break;

            case CONSULTAR_LIVRO:
                consultar_livros();
                break;

            case LISTAR_LIVRO:
                listar_livros();
                break;

            case SAIR:
                break;

            default:
                printf("opcao invalida\n");
        }
    };

    return 0;
}
