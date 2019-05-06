#include <stdlib.h>
#include <stdio.h>

int *cal(int arreglo[], int tamano);
void printArray(int arrTo[], int tam);
void copyArray(int *arrTo, int *arrFrom, int tam);

int main()
{
    int tam =  12;
    int arreglo[tam];
    arreglo[0] = 10;
    arreglo[1] = 11;
    arreglo[2] = 20;
    arreglo[3] = 1;
    arreglo[4] = 5;
    arreglo[5] = 3;
    arreglo[6] = 7;
    arreglo[7] = 0;
    arreglo[8] = 50;
    arreglo[9] = 200;
    arreglo[10] = -550;
    arreglo[11] = 20;
    copyArray(arreglo, cal(arreglo, tam), tam);
    printArray(arreglo, tam);
    return 0;
}

void printArray(int arrTo[], int tam)
{
    int i = 0;
    for (i = 0; i < tam; ++i)
    {
        printf("%i -", arrTo[i]);
    }
    printf("\n");
}

void copyArray(int *arrTo, int *arrFrom, int tam)
{
    int i = 0;
    for (i = 0; i < tam; ++i)
    {
        arrTo[i] = arrFrom[i];
    }
}

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
