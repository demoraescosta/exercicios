/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define NOME_MAX 64

typedef struct Produto
{
    int id;
    char nome[NOME_MAX];
    float valor;
} Produto;

size_t produtos_contar_abaixo(Produto* buffer, size_t len, float valor)
{
    size_t count = 0;
    for (size_t i = 0; i < len; ++i)
    {
        if (buffer[i].valor < valor)
            count += 1;
    }
    
    return count;
}

Produto* produtos_encontrar_id(Produto* buffer, size_t len, int id)
{
    for (size_t i = 0; i < len; ++i)
    {
        if (buffer[i].id == id)
            return &buffer[i];
    }
    
    return NULL;
}

int produtos_atualizar_valor(Produto* buffer, size_t len, int id, float novo_valor)
{
    for (size_t i = 0; i < len; ++i)
    {
        if (buffer[i].id == id)
            buffer[i].id = novo_valor;
        return 1;
    }
    
    return 0;
}

float produtos_media_preco(Produto* buffer, size_t len)
{
    size_t total = len;
    double soma = 0.00;
    
    for (size_t i = 0; i < len; ++i)
    {
        soma += buffer[i].valor;
    }
    
    return (soma / (double)total);
}

size_t produtos_acima_media(Produto* buffer, size_t len)
{
    double media = produtos_media_preco(buffer, len);
    size_t count = 0;
    for (size_t i = 0; i < len; ++i)
    {
        if (buffer[i].valor > media)
        {
            count += 1;   
        }
    }
    printf("Quantidade de produtos acima da media: %llu\n", count);
    return count;
}

typedef struct Clube
{
    int id;
    char nome[NOME_MAX];
    int vitorias;
    int empates;
    int derrotas;
    int gols_pro;
    int gols_contra;
} Clube;

Clube* clubes_cadastrar(void)
{
    size_t qntd = 0;
    printf("Quantidade de clubes a cadastrar: ");
    scanf("%llu", &qntd);
    
    Clube* lista_clubes = calloc(qntd, sizeof(Clube));
    if (lista_clubes == NULL)
        return NULL;
    
    for (int i = 0; i < qntd; i += 1)
    {
        int id = 0;
        printf("ID clube %d: ", i + 1);
        scanf("%d", &id);
        
        lista_clubes[i].id = id;
        
        char nome[NOME_MAX] = { 0 };
        printf("Nome clube %d: ", i + 1);
        scanf("%s", &nome);
        
        memcpy(lista_clubes[i].nome, nome, strnlen(nome, NOME_MAX));

        int vitorias = 0;
        printf("Vitorias do clube %d: ", i + 1);
        scanf("%d", &vitorias);
        
        lista_clubes[i].vitorias = vitorias;
        
        int empates = 0;
        printf("Empates do clube %d: ", i + 1);
        scanf("%d", &empates);
        
        lista_clubes[i].empates = empates;
        
        int derrotas = 0;
        printf("Derrotas do clube %d: ", i + 1);
        scanf("%d", &derrotas);
        
        lista_clubes[i].derrotas = derrotas;
        
        int gols_pro = 0;
        printf("Gols pro do clube %d: ", i + 1);
        scanf("%d", &gols_pro);
        
        lista_clubes[i].gols_pro = gols_pro;
        
        int gols_contra = 0;
        printf("Gols contra do clube %d: ", i + 1);
        scanf("%d", &gols_contra);
        
        lista_clubes[i].gols_contra = gols_contra;
    }
    
    for (int i = 0; i < qntd; i++)
    {
        int pontos = lista_clubes[i].vitorias * 3 + lista_clubes[i].empates;
        printf("O/a %s tem %d pontos\n", lista_clubes[i].nome, pontos);
    }
    
    return lista_clubes;
}

Clube* clubes_encontrar_id(Clube* buffer, size_t len, int id)
{
    for (size_t i = 0; i < len; ++i)
    {
        if (buffer[i].id == id)
            return &buffer[i];
    }
    
    return NULL;
}

size_t clubes_gols_acima(Clube* buffer, size_t len)
{
    size_t total = len;
    double soma = 0.00;
    
    for (size_t i = 0; i < len; ++i)
    {
        soma += buffer[i].gols_pro;
    }
    
    double media = (soma / (double)total);
    
    size_t count = 0;
    
    for (size_t i = 0; i < len; ++i)
    {
        if (buffer[i].gols_pro > media)
            count += 1;
    }
    
    return count;
}

int main()
{
    return 0;
}