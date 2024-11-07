/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

void exercicio1(char* string)
{
    int len = strlen(string);
    printf("%.*s (%d)\n", len, string, len);
}

void exercicio2(char* s1, char* s2)
{
    int res = strcmp(s1, s2) == 0 ? 1 : 0;
    if (res)
    {
        printf("As strings sao iguais\n");
    }
    else
    {
        printf("As strings nao sao iguais\n");
    }
}

void exercicio3(void)
{
    char string[256] = { 0 };
    fgets(string, 256, stdin);
    
    int len = strlen(string);
    for (int i = 0; i < len; ++i)
    {
        printf("%c\n", string[i]);
    }
}

void exercicio4(void)
{
    char string[256] = { 0 };
    fgets(string, 256, stdin);
    
    int len = strlen(string);
    uint32_t count = 0;
    for (int i = 0; i < len; ++i)
    {
        if (string[i] == 'c')
            count += 1;
    }
    
    printf("A string tem %d letras 'A'", count);
}

void exercicio5()
{
    char string1[256] = { 0 };
    fgets(string1, 256, stdin);
    
    char string2[256] = { 0 };
    
    strcpy(string2, string1);
    
    printf("%s\n", string1);
    printf("%s\n", string2);
}

void exercicio6()
{
    char string1[256] = { 0 };
    fgets(string1, 256, stdin);
    string1[strcspn(string1, "\n")] = 0;
    
    char string2[512] = { 0 };
    fgets(string2, 256, stdin);
    string2[strcspn(string2, "\n")] = 0;

    strcat(string1, string2);
    
    printf("%s\n", string1);
}

void exercicio7()
{
    char string[256] = { 0 };
    fgets(string, 256, stdin);
    string[strcspn(string, "\n")] = 0;
    
    int len = strlen(string);
    for (int i = 0; i < len; ++i)
    {
        string[i] = tolower(string[i]);
    }
    
    printf("%s\n", string);
}

void exercicio8()
{
    char string[256] = { 0 };
    fgets(string, 256, stdin);
    string[strcspn(string, "\n")] = 0;
    
    int len = strlen(string);
    unsigned int count = 0;
    for (int i = 0; i < len; ++i)
    {
        switch (string[i])
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                count += 1;
                break;
                
            default:
                break;
        }
    }
    
    printf("%d\n", count);
}

void exercicio9()
{
    char string[256] = { 0 };
    fgets(string, 256, stdin);
    
    int len = strlen(string);
    uint32_t count = 0;
    for (int i = 0; i < len; ++i)
    {
        if (!isalpha(string[i]) && !isdigit(string[i]))
        {
            count += 1;
        }
    }
    
    count -= 1; // remover /0
    
    printf("A string tem %d espaços vazios\n", count);
}

void exercicio10()
{
    char string[256] = { 0 };
    fgets(string, 256, stdin);
    
    int len = strlen(string);
    uint32_t alpha_count = 0;
    uint32_t digit_count = 0;
    uint32_t special_count = 0;
    
    for (int i = 0; i < len; ++i)
    {
        if (isalpha(string[i]))
        {
            alpha_count += 1;
        }
        else if (isdigit(string[i]))
        {
            digit_count += 1;
        }
        else
        {
            special_count += 1;
        }
    }
    
    printf("A string tem %d digitos, %d letras, %d caracteres especiais\n", 
            digit_count, alpha_count, special_count);
}

int main()
{
    // exercicio1("Exercicio 1");
    // exercicio2("1234", "1234");
    // exercicio3();
    // exercicio4();
    // exercicio5();
    // exercicio6();
    // exercicio7();
    // exercicio8();
    // exercicio9();
    exercicio10();
    

    return 0;
}