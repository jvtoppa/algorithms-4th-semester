#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
int main(void)
{
    char input[950000];
 
    while (fgets(input, sizeof(input), stdin))
    {
        int somaNumeros = 0;
 
        char inputCopia[950000];
        strcpy(inputCopia, input);
 
        char* ptra = strtok(input, " ");
        while (ptra != NULL)
        {
            char numero[950000];
            int idxNumero = 0;
 
            for (int i = 0; ptra[i] != '\0'; i++)
            {
                if (isdigit(ptra[i]))
                {
                    numero[idxNumero++] = ptra[i];
                }
                else if (idxNumero > 0)
                {
                    numero[idxNumero] = '\0';
                    somaNumeros += atoi(numero);
                    idxNumero = 0;  
                }
            }
 
            if (idxNumero > 0)
            {
                numero[idxNumero] = '\0';
                somaNumeros += atoi(numero);
            }
 
            ptra = strtok(NULL, " ");
        }
 
        if (somaNumeros == 1)
        {
            printf("%d goat says:", somaNumeros);
        }
        else if (somaNumeros != 1)
        {
            printf("%d goats say:", somaNumeros);
        }
 
        char* ptr = strtok(inputCopia, " ");
        while (ptr != NULL)
        {
            char palavra[950000];
            int idxPalavra = 0;
            int temLetra = 0;
 
            for (int i = 0; ptr[i] != '\0'; i++)
            {
                if (isalpha(ptr[i]))
                {
                    palavra[idxPalavra++] = ptr[i];
                    temLetra = 1;
                }
            }
            palavra[idxPalavra] = '\0';
 
            if (temLetra)
            {
                if (palavra[0] == 'a' || palavra[0] == 'e' || palavra[0] == 'i' || palavra[0] == 'o' || palavra[0] == 'u' ||
                    palavra[0] == 'A' || palavra[0] == 'E' || palavra[0] == 'I' || palavra[0] == 'O' || palavra[0] == 'U')
                {
                    printf(" %sma", palavra);
                }
                else
                {
                    printf(" %s%cma", palavra + 1, palavra[0]);
                }
 
                for (int i = 0; i < idxPalavra; i++)
                {
                    printf("a");
                }
            }
 
            ptr = strtok(NULL, " ");
        }
 
            printf("\n");
    }
 
    return 0;
}