#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *appendString(char *cadena, char caracter);
void algoritmoMoneda(char *cadena, int veces);
int algoritmoEuclides(int mayor, int menor);
int algoritmoEuclidesIteraciones(int mayor, int menor);
int mcd(int mayor, int menor, int aux);
int mcdIteraciones(int mayor, int menor);
int monedas(int cantidad, int *denominaciones, int *contadores, int index);

int main()
{
    algoritmoMoneda("", 2);
    printf("minimo común divisor : %i\n", algoritmoEuclides(51, 50));
    printf("minimo común divisor : %i\n", algoritmoEuclidesIteraciones(51, 50));
    printf("minimo común divisor : %i\n", mcd(51, 50, 50));
    printf("minimo común divisor : %i\n", mcdIteraciones(51, 50));

    int cantidad = 25, aux;
    int denominaciones[] = {10, 5, 2, 1};
    int contadores[] = {0, 0, 0, 0};
    int magia = monedas(cantidad, denominaciones, contadores, 0);
    for (aux = 0; aux < 4; aux++)
    {
        printf("%i monedas de %i\n", contadores[aux], denominaciones[aux]);
    }
    return 0;

    return EXIT_SUCCESS;
}

int mcdIteraciones(int mayor, int menor)
{
    int aux = menor;
MCDI:
    if (mayor % aux != 0 || menor % aux != 0)
    {
        --aux;
        goto MCDI;
    }
    return aux;
}

int mcd(int mayor, int menor, int aux)
{
    if (mayor % aux == 0 && menor % aux == 0)
    {
        return aux;
    }
    else
    {
        return mcd(mayor, menor, aux - 1);
    }
}

int algoritmoEuclidesIteraciones(int mayor, int menor)
{
    int aux;
    aux = mayor % menor;
AEI:
    if (aux != 0)
    {
        mayor = menor;
        menor = aux;
        aux = mayor % menor;
        goto AEI;
    }

    return menor;
}

int algoritmoEuclides(int mayor, int menor)
{
    mayor = mayor % menor;
    if (mayor == 0)
    {
        return menor;
    }
    else
    {
        return algoritmoEuclides(menor, mayor);
    }
}

void algoritmoMoneda(char *cadena, int veces)
{
    if (veces == 0)
    {
        printf("%s\n", cadena);
    }
    else
    {
        algoritmoMoneda(appendString(cadena, 'S'), veces - 1);
        algoritmoMoneda(appendString(cadena, 'A'), veces - 1);
    }
}

int monedas(int cantidad, int *denominaciones, int *contadores, int index)
{
    if (cantidad % denominaciones[index] == 0)
    {
        contadores[index] = cantidad / denominaciones[index];
        return 0;
    }
    else
    {
        contadores[index] = cantidad / denominaciones[index];
        return monedas(cantidad % denominaciones[index++], denominaciones, contadores, index);
    }
}

char *appendString(char *cadena, char caracter)
{
    size_t tam = strlen(cadena);
    char *res = malloc(tam + 1 + 1);
    strcpy(res, cadena);
    res[tam] = caracter;
    res[tam + 1] = '\0';
    cadena = malloc(strlen(res));
    strcpy(cadena, res);
    free(res);
    return cadena;
}