#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int  id;
    char titulo[50];
    char genero[20];
    int  ano;
} Funcionario;

const char* ARQUIVO_FILMES = "funcionarios.txt";

void incluir_funcionario()
{
    Funcionario f = {0};

    FILE* arquivo = fopen(ARQUIVO_FILMES, "a");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("digite o id do funcionario: ");
    scanf("%d", &f.id);
    getchar();

    printf("digite o titulo do funcionario: ");
    fgets(f.titulo, sizeof(f.titulo), stdin);
    f.titulo[strcspn(f.titulo, "\n")] = 0;

    printf("digite o genero: ");
    fgets(f.genero, sizeof(f.genero), stdin);
    f.genero[strcspn(f.genero, "\n")] = 0;

    printf("digite o ano do funcionario: ");
    scanf("%d", &f.ano);

    fprintf(arquivo, "%d,%s,%s,%d\n", f.id, f.titulo, f.genero, f.ano);
    fclose(arquivo);

    printf("funcionario incluido com sucesso!\n");
}

void excluir_funcionario()
{
    Funcionario f = {0};

    int id  = 0;
    int encontrado = 0;

    FILE* arquivo = fopen(ARQUIVO_FILMES, "r");
    FILE* temp    = fopen("temp.txt", "w");

    if (arquivo == NULL || temp == NULL)
    {
        printf("erro ao abrir o arquivo!\n");
        return;
    }

    printf("digito a id do funcionario a ser excluido: ");
    scanf("%d", &id);

    while (fgets(f.titulo, sizeof(f.titulo), arquivo))
    {
        sscanf(f.titulo, "%d,%49[^,],%20[^,],%d", &f.id, f.titulo, f.genero, &f.ano);
        if (f.id == id)
        {
            encontrado = 1;
        }
        else
        {
            fprintf(temp, "%d,%s,%s,%d\n", f.id, f.titulo, f.genero, f.ano);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO_FILMES);
    rename("temp.txt", ARQUIVO_FILMES);

    if (encontrado)
    {
        printf("funcionario excluido com sucesso\n");
    }
    else
    {
        printf("funcionario nao encontrado.\n");
    }
}

void alterar_funcionarios()
{
    Funcionario f = {0};

    int id, encontrado = 0;

    FILE* arquivo = fopen(ARQUIVO_FILMES, "r");
    FILE* temp    = fopen("temp.txt", "w");

    if (arquivo == NULL || temp == NULL)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }

    printf("digite a id do funcionario a ser alterado: ");
    scanf("%d", &id);
    getchar();

    while (fgets(f.titulo, sizeof(f.titulo), arquivo))
    {
        sscanf(f.titulo, "%d,%49[^,],%20[^,],%d", &f.id, f.titulo, f.genero, &f.ano);
        if (f.id == id)
        {
            encontrado = 1;

            printf("digite o novo titulo do funcionario: ");
            fgets(f.titulo, sizeof(f.titulo), stdin);
            f.titulo[strcspn(f.titulo, "\n")] = 0;

            printf("digite o novo genero: ");
            fgets(f.genero, sizeof(f.genero), stdin);
            f.genero[strcspn(f.genero, "\n")] = 0;

            printf("digite o nova ano: ");
            scanf("%d", &f.ano);
            getchar();
        }
        fprintf(temp, "%d,%s,%s,%d\n", f.id, f.titulo, f.genero, f.ano);
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO_FILMES);
    rename("temp.txt", ARQUIVO_FILMES);

    if (encontrado)
    {
        printf("funcionario alterado com sucesso!\n");
    }
    else
    {
        printf("funcionario nao encontrado\n");
    }
}

void consultar_funcionarios()
{
    Funcionario f = {0};

    int   id, encontrado = 0;
    FILE* arquivo = fopen(ARQUIVO_FILMES, "r");

    if (arquivo == NULL)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }

    printf("digite o id do funcionario para a consulta: ");
    scanf("%d", &id);

    while (fgets(f.titulo, sizeof(f.titulo), arquivo))
    {
        sscanf(f.titulo, "%d,%49[^,],%20[^,],%d", &f.id, f.titulo, f.genero, &f.ano);
        if (f.id == id)
        {
            printf("funcionario encontrado:\n");
            printf("id: %d\n", f.id);
            printf("titulo: %s\n", f.titulo);
            printf("genero: %s\n", f.genero);
            printf("ano: %d\n", f.ano);
            encontrado = 1;
            break;
        }
    }

    fclose(arquivo);

    if (!encontrado)
    {
        printf("funcionario nao encontrado.\n");
    }
}

void listar_funcionarios()
{
    Funcionario f = {0};

    FILE* arquivo = fopen(ARQUIVO_FILMES, "r");

    if (arquivo == NULL)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }

    printf("\nlista de funcionarios:\n");

    while (fgets(f.titulo, sizeof(f.titulo), arquivo))
    {
        sscanf(f.titulo, "%d,%49[^,],%20[^,],%d", &f.id, f.titulo, f.genero, &f.ano);
        printf("    id: %d | titulo: %s | genero: %s | ano: %d\n", f.id, f.titulo, f.genero, f.ano);
    }

    fclose(arquivo);
}

enum OPCOES
{
    INCLUIR_FILME   = 1,
    EXCLUIR_FILME   = 2,
    ALTERAR_FILME   = 3,
    CONSULTAR_FILME = 4,
    LISTAR_FILME    = 5,
    SAIR            = 6,
};

void exibir_menu()
{
    printf("%d> incluir funcionarios\n", INCLUIR_FILME);
    printf("%d> excluir funcionarios\n", EXCLUIR_FILME);
    printf("%d> alterar funcionarios\n", ALTERAR_FILME);
    printf("%d> consultar funcionarios\n", CONSULTAR_FILME);
    printf("%d> listar funcionarios\n", LISTAR_FILME);
    printf("%d> sair\n", SAIR);
}

int main()
{
    int opcao = 0;

    printf("sistema de cadastro de funcionarios:\n\n");

    while (opcao != 6)
    {
        exibir_menu();
        printf("escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
            case INCLUIR_FILME:
                incluir_funcionario();
                break;

            case EXCLUIR_FILME:
                excluir_funcionario();
                break;

            case ALTERAR_FILME:
                alterar_funcionarios();
                break;

            case CONSULTAR_FILME:
                consultar_funcionarios();
                break;

            case LISTAR_FILME:
                listar_funcionarios();
                break;

            case SAIR:
                break;

            default:
                printf("opcao invalida\n");
        }
    };

    return 0;
}
