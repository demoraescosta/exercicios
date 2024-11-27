#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// estrutura para armazenar dados do aluno
typedef struct
{
    int  matricula;
    char nome[50];
    char curso[30];
    int  idade;
} Aluno;

const char* ARQUIVO_ALUNOS = "alunos.txt";

void incluir_aluno()
{
    Aluno a = {0};

    FILE* arquivo = fopen(ARQUIVO_ALUNOS, "a");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o matricula do aluno: ");
    scanf("%d", &a.matricula);
    getchar();

    printf("Digite o nome do aluno: ");
    fgets(a.nome, sizeof(a.nome), stdin);
    a.nome[strcspn(a.nome, "\n")] = 0;  // Remove o '\n'

    printf("Digite o nome do curso: ");
    fgets(a.curso, sizeof(a.curso), stdin);
    a.curso[strcspn(a.curso, "\n")] = 0;

    printf("Digite a idade do aluno: ");
    scanf("%d", &a.idade);

    // Grava os dados no arquivo separados por vírgulas
    fprintf(arquivo, "%d,%s,%s,%d\n", a.matricula, a.nome, a.curso, a.idade);
    fclose(arquivo);

    printf("Aluno incluido com sucesso!\n");
}

void excluir_aluno()
{
    Aluno a = {0};

    int matricula  = 0;
    int encontrado = 0;

    FILE* arquivo = fopen(ARQUIVO_ALUNOS, "r");
    FILE* temp    = fopen("temp.txt", "w");

    if (arquivo == NULL || temp == NULL)
    {
        printf("erro ao abrir o arquivo!\n");
        return;
    }

    printf("digito a matricula do aluno a ser excluido: ");
    scanf("%d", &matricula);

    while (fgets(a.nome, sizeof(a.nome), arquivo))
    {
        sscanf(a.nome, "%d,%49[^,],%30[^,],%d", &a.matricula, a.nome, a.curso, &a.idade);
        if (a.matricula == matricula)
        {
            encontrado = 1;
        }
        else
        {
            fprintf(temp, "%d,%s,%s,%d\n", a.matricula, a.nome, a.curso, a.idade);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO_ALUNOS);
    rename("temp.txt", ARQUIVO_ALUNOS);

    if (encontrado)
    {
        printf("aluno excluido com sucesso\n");
    }
    else
    {
        printf("aluno nao encontrado.\n");
    }
}

void alterar_alunos()
{
    Aluno a = {0};

    int matricula, encontrado = 0;

    FILE* arquivo = fopen(ARQUIVO_ALUNOS, "r");
    FILE* temp    = fopen("temp.txt", "w");

    if (arquivo == NULL || temp == NULL)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }

    printf("digite a matricula do aluno a ser alterado: ");
    scanf("%d", &matricula);
    getchar();

    while (fgets(a.nome, sizeof(a.nome), arquivo))
    {
        sscanf(a.nome, "%d,%49[^,],%30[^,],%d", &a.matricula, a.nome, a.curso, &a.idade);
        if (a.matricula == matricula)
        {
            encontrado = 1;

            printf("digite o novo nome do aluno: ");
            fgets(a.nome, sizeof(a.nome), stdin);
            a.nome[strcspn(a.nome, "\n")] = 0;

            printf("digite o novo nome de curso: ");
            fgets(a.curso, sizeof(a.curso), stdin);
            a.curso[strcspn(a.curso, "\n")] = 0;

            printf("digite a nova idade: ");
            scanf("%d", &a.idade);
            getchar();
        }
        fprintf(temp, "%d,%s,%s,%d\n", a.matricula, a.nome, a.curso, a.idade);
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO_ALUNOS);
    rename("temp.txt", ARQUIVO_ALUNOS);

    if (encontrado)
    {
        printf("aluno alterado com sucesso!\n");
    }
    else
    {
        printf("aluno nao encontrado\n");
    }
}

void consultar_alunos()
{
    Aluno a = {0};

    int   matricula, encontrado = 0;
    FILE* arquivo = fopen(ARQUIVO_ALUNOS, "r");

    if (arquivo == NULL)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }

    printf("digite a matricula do aluno para consulta: ");
    scanf("%d", &matricula);

    while (fgets(a.nome, sizeof(a.nome), arquivo))
    {
        sscanf(a.nome, "%d,%49[^,],%30[^,],%d", &a.matricula, a.nome, a.curso, &a.idade);
        if (a.matricula == matricula)
        {
            printf("aluno encontrado:\n");
            printf("matricula: %d\n", a.matricula);
            printf("nome: %s\n", a.nome);
            printf("curso: %s\n", a.curso);
            printf("idade: %d\n", a.idade);
            encontrado = 1;
            break;
        }
    }

    fclose(arquivo);

    if (!encontrado)
    {
        printf("aluno nao encontrado.\n");
    }
}

void listar_alunos()
{
    Aluno a = {0};

    FILE* arquivo = fopen(ARQUIVO_ALUNOS, "r");

    if (arquivo == NULL)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }

    printf("\nlista de alunos:\n");

    while (fgets(a.nome, sizeof(a.nome), arquivo))
    {
        sscanf(a.nome, "%d,%49[^,],%30[^,],%d", &a.matricula, a.nome, a.curso, &a.idade);
        printf("    matricula: %d | nome: %s | curso: %s | idade: %d\n", a.matricula, a.nome, a.curso, a.idade);
    }

    fclose(arquivo);
}

enum OPCOES
{
    INCLUIR_ALUNO   = 1,
    EXCLUIR_ALUNO   = 2,
    ALTERAR_ALUNO   = 3,
    CONSULTAR_ALUNO = 4,
    LISTAR_ALUNO    = 5,
    SAIR            = 6,
};

void exibir_menu()
{
    printf("%d> incluir alunos\n", INCLUIR_ALUNO);
    printf("%d> excluir alunos\n", EXCLUIR_ALUNO);
    printf("%d> alterar alunos\n", ALTERAR_ALUNO);
    printf("%d> consultar alunos\n", CONSULTAR_ALUNO);
    printf("%d> listar alunos\n", LISTAR_ALUNO);
    printf("%d> sair\n", SAIR);
}

int main()
{
    int opcao = 0;

    printf("sistema de cadastro de alunos:\n\n");

    while (opcao != 6)
    {
        exibir_menu();
        printf("escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer

        switch (opcao)
        {
            case INCLUIR_ALUNO:
                incluir_aluno();
                break;

            case EXCLUIR_ALUNO:
                excluir_aluno();
                break;

            case ALTERAR_ALUNO:
                alterar_alunos();
                break;

            case CONSULTAR_ALUNO:
                consultar_alunos();
                break;

            case LISTAR_ALUNO:
                listar_alunos();
                break;

            case SAIR:
                break;

            default:
                printf("opcao invalida\n");
        }
    };

    return 0;
}
