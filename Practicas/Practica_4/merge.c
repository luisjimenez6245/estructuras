/*
  MERGESORT
  AUTORES: 
    JIMÉNEZ DELGADO LUIS DIEGO
    SÁNCHEZ CASTRO AARÓN GAMALIEL
    SÁNCHEZ TIRADO CITLALI YASMÍN
  VERSIÓN 1.5
*/
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int *cal(int arreglo[], int tamano);
void printArray(int arrTo[], int tam);
void copyArray(int *arrTo, int *arrFrom, int tam);

int main()
{
    int tam = 25, i;
    int arreglo[tam];
    srand(time(NULL));
    for (i = 0; i < tam; ++i)
    {
        if (i % 2 == 0){
            arreglo[i] = i;
        }
        else
        {
            arreglo[i] = -i + 2;
        }
    }
    printf("\a\n");
    printArray(arreglo, tam);

    copyArray(arreglo, cal(arreglo, tam), tam);
    printf("\resultado\n");
    printArray(arreglo, tam);
    return 0;
}

/*
	FUNCIÓN: printArray(int arrTo[], int tam)
	RECIBE: el arreglo de int a imprimir int arrTo[], el tamaño del arreglo int tam
	DEVUELVE: void;
	DESCRIPCIÓN:
    Funcion que recibe un arreglo de tamaño n, e imprime todos los valores en el separados por un /
	OBSERVACIONES:
*/
void printArray(int arrTo[], int tam)
{
    int i = 0;
    for (i = 0; i < tam; ++i)
    {
        printf("%i \t", arrTo[i]);
    }
    printf("\n");
}

/*
	FUNCIÓN: copyArray(int *arrTo, int *arrFrom, int tam)
	RECIBE: el arreglo al que se le van asignar los numeros int *arrTo,
     el arreglo del que se  van asignar los numeros int *arrFrom,
        el tamaño del arreglo  int tam
	DEVUELVE: void
	DESCRIPCIÓN: copia todos los elementos de un arreglo a otro
*/
void copyArray(int *arrTo, int *arrFrom, int tam)
{
    int i = 0;
    for (i = 0; i < tam; ++i)
    {
        arrTo[i] = arrFrom[i];
    }
}

/*
	FUNCIÓN: *cal(int arreglo[], int tamano)
	RECIBE:  el arreglo a acmodar int arreglo[], el tamaño del arreglo  int tamano
	DEVUELVE: un arreglo de tamño variable int *
	DESCRIPCIÓN: Realiza el proceso de ordenamiento merge por medio de recursividad
*/
int *cal(int arreglo[], int tamano)
{
    printf("\n");
    if (tamano != 1)
    {
        int i, j;
        int tamArr = tamano / 2;
        int tamArr2 = tamArr + (tamano % 2);
        int arr1[tamArr];
        int arr2[tamArr2];
        for (i = 0; i < (tamArr); ++i)
        {
            arr1[i] = arreglo[i];
            arr2[i] = arreglo[tamArr + i];
        }
        arr2[tamArr2 - 1] = arreglo[tamano - 1];
        copyArray(&arr1, cal(arr1, tamArr), tamArr);
        copyArray(&arr2, cal(arr2, tamArr2), tamArr2);
        int res[tamano], k = 0;
        i = 0;
        j = 0;
        while (i <= tamArr && j <= tamArr2 && k < tamano)
        {
            if (i <= tamArr && arr1[i] < arr2[j])
            {
                res[k] = arr1[i];
                ++i;
            }
            else
            {
                if (j < tamArr2)
                {
                    res[k] = arr2[j];
                    ++j;
                }
                else
                {
                    res[k] = arr1[i];
                    ++i;
                }
            }
            ++k;
        }
        return res;
    }
    return arreglo;
}
