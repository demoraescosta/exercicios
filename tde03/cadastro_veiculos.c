#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int  id;
    char modelo[50];
    char placa[50];
    int  ano;
} Veiculo;

const char* ARQUIVO_VEICULOS = "veiculos.txt";

void incluir_filme()
{
    Veiculo v = {0};

    FILE* arquivo = fopen(ARQUIVO_VEICULOS, "a");

    if (arquivo == NULL)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }

    printf("digite o id do veiculo: ");
    scanf("%d", &v.id);
    getchar();

    printf("digite o modelo do veiculo: ");
    fgets(v.modelo, sizeof(v.modelo), stdin);
    v.modelo[strcspn(v.modelo, "\n")] = 0;

    printf("digite a placa: ");
    fgets(v.placa, sizeof(v.placa), stdin);
    v.placa[strcspn(v.placa, "\n")] = 0;

    printf("digite o ano do veiculo: ");
    scanf("%d", &v.ano);

    fprintf(arquivo, "%d,%s,%s,%d\n", v.id, v.modelo, v.placa, v.ano);
    fclose(arquivo);

    printf("veiculo incluido com sucesso!\n");
}

void excluir_filme()
{
    Veiculo v = {0};

    int id     = 0;
    int encontrado = 0;

    FILE* arquivo = fopen(ARQUIVO_VEICULOS, "r");
    FILE* temp    = fopen("temp.txt", "w");

    if (arquivo == NULL || temp == NULL)
    {
        printf("erro ao abrir o arquivo!\n");
        return;
    }

    printf("digito a id do veiculo a ser excluido: ");
    scanf("%d", &id);

    while (fgets(v.modelo, sizeof(v.modelo), arquivo))
    {
        sscanf(v.modelo, "%d,%49[^,],%10[^,],%d", &v.id, v.modelo, v.placa, &v.ano);
        if (v.id == id)
        {
            encontrado = 1;
        }
        else
        {
            fprintf(temp, "%d,%s,%s,%d\n", v.id, v.modelo, v.placa, v.ano);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO_VEICULOS);
    rename("temp.txt", ARQUIVO_VEICULOS);

    if (encontrado)
    {
        printf("veiculo excluido com sucesso\n");
    }
    else
    {
        printf("veiculo nao encontrado.\n");
    }
}

void alterar_livros()
{
    Veiculo v = {0};

    int id, encontrado = 0;

    FILE* arquivo = fopen(ARQUIVO_VEICULOS, "r");
    FILE* temp    = fopen("temp.txt", "w");

    if (arquivo == NULL || temp == NULL)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }

    printf("digite a id do veiculo a ser alterado: ");
    scanf("%d", &id);
    getchar();

    while (fgets(v.modelo, sizeof(v.modelo), arquivo))
    {
        sscanf(v.modelo, "%d,%49[^,],%10[^,],%d", &v.id, v.modelo, v.placa, &v.ano);
        if (v.id == id)
        {
            encontrado = 1;

            printf("digite o novo modelo do veiculo: ");
            fgets(v.modelo, sizeof(v.modelo), stdin);
            v.modelo[strcspn(v.modelo, "\n")] = 0;

            printf("digite o nova placa: ");
            fgets(v.placa, sizeof(v.placa), stdin);
            v.placa[strcspn(v.placa, "\n")] = 0;

            printf("digite o nova ano: ");
            scanf("%d", &v.ano);
            getchar();
        }
        fprintf(temp, "%d,%s,%s,%d\n", v.id, v.modelo, v.placa, v.ano);
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO_VEICULOS);
    rename("temp.txt", ARQUIVO_VEICULOS);

    if (encontrado)
    {
        printf("veiculo alterado com sucesso!\n");
    }
    else
    {
        printf("veiculo nao encontrado\n");
    }
}

void consultar_livros()
{
    Veiculo v = {0};

    int id     = 0;
    int encontrado = 0;

    FILE* arquivo = fopen(ARQUIVO_VEICULOS, "r");

    if (arquivo == NULL)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }

    printf("digite o id do veiculo para a consulta: ");
    scanf("%d", &id);

    while (fgets(v.modelo, sizeof(v.modelo), arquivo))
    {
        sscanf(v.modelo, "%d,%49[^,],%10[^,],%d", &v.id, v.modelo, v.placa, &v.ano);
        if (v.id == id)
        {
            printf("veiculo encontrado:\n");
            printf("id: %d\n", v.id);
            printf("modelo: %s\n", v.modelo);
            printf("placa: %s\n", v.placa);
            printf("ano: %d\n", v.ano);
            encontrado = 1;
            break;
        }
    }

    fclose(arquivo);

    if (!encontrado)
    {
        printf("veiculo nao encontrado.\n");
    }
}

void listar_livros()
{
    Veiculo v = {0};

    FILE* arquivo = fopen(ARQUIVO_VEICULOS, "r");

    if (arquivo == NULL)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }

    printf("\nlista de veiculos:\n");

    while (fgets(v.modelo, sizeof(v.modelo), arquivo))
    {
        sscanf(v.modelo, "%d,%49[^,],%10[^,],%d", &v.id, v.modelo, v.placa, &v.ano);
        printf("    id: %d | modelo: %s | placa: %s | ano: %d\n", v.id, v.modelo, v.placa, v.ano);
    }

    fclose(arquivo);
}

enum OPCOES
{
    INCLUIR_VEICULO   = 1,
    EXCLUIR_VEICULO   = 2,
    ALTERAR_VEICULO   = 3,
    CONSULTAR_VEICULO = 4,
    LISTAR_VEICULO    = 5,
    SAIR            = 6,
};

void exibir_menu()
{
    printf("%d> incluir veiculos\n", INCLUIR_VEICULO);
    printf("%d> excluir veiculos\n", EXCLUIR_VEICULO);
    printf("%d> alterar veiculos\n", ALTERAR_VEICULO);
    printf("%d> consultar veiculos\n", CONSULTAR_VEICULO);
    printf("%d> listar veiculos\n", LISTAR_VEICULO);
    printf("%d> sair\n", SAIR);
}

int main()
{
    int opcao = 0;

    printf("sistema de cadastro de veiculos:\n\n");

    while (opcao != 6)
    {
        exibir_menu();
        printf("escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
            case INCLUIR_VEICULO:
                incluir_filme();
                break;

            case EXCLUIR_VEICULO:
                excluir_filme();
                break;

            case ALTERAR_VEICULO:
                alterar_livros();
                break;

            case CONSULTAR_VEICULO:
                consultar_livros();
                break;

            case LISTAR_VEICULO:
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
