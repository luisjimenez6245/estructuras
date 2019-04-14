#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define size 299
#define AKEY 73571


int arr[size];
int choques = 0;
typedef struct elemento
{
	char palabra[25];
} elemento;

int corregirChar(int c)
{
	switch (c)
	{
	case 177:
		return 164; //ñ
		break;

	case 145:
		return 165; //Ñ
		break;

	case 193:
		return 181; //Á
		break;

	case 201:
		return 144; //É
		break;

	case 205:
		return 214; //Í
		break;

	case 211:
		return 224; //Ó
		break;

	case 218:
		return 233; //Ú
		break;

	case 225:
		return 160; //á
		break;

	case 233:
		return 130; //é
		break;

	case 237:
		return 161; //í
		break;

	case 243:
		return 162; //ó
		break;

	case 250:
		return 163; //ú
		break;

	case 241:
		return 164; //ñ
		break;

	case 209:
		return 165; //Ñ
		break;

	case 252:
		return 129; //ü
		break;

	default:
		return c;
		break;
	}
}

void hashFunc(char palabra[25], int numero)
{
	int aux = 0;
	int i = 0, resultado = 0, tam,  derecha;
	tam = strlen(palabra);
	for (i = 0; i < tam; ++i)
	{
		aux = ((AKEY *  palabra[i]) % ((int) pow(2,i + 13))) >> ((int)(pow(8,i +3)));
		resultado += aux;
	}
	resultado = (resultado % size);
	if(resultado < 0)
		resultado = size - 1 + resultado;
	
	if (arr[resultado] == 1)
	{
		printf("valio verga %i\n ", choques);
		++choques;
	}
	else
	{
		arr[resultado] = 1;
	}
	printf("palabra %i  hash: %i  : %s  \n", numero, resultado, palabra);
}

int main()
{
	elemento dic[size];
	elemento e;
	int car, i = 0, j = 0;

	//int size = 4, i, resultado, aux, j, tam;
	char pal[100];

	for (i = 0; i < size; ++i)
	{
		arr[i] = 0;
	}
	i = 0;

	FILE *pArch;
	char nomArchivo[30], palabraAlt[25], definicion[251], estado = 'p';						  //Declaracion de las variables
	printf("Ingresa el nombre del diccionario \n\tEjemplo: diccionario.txt \nDiccionario: "); //Usuario ingresa el documento .txt
	scanf("%s", nomArchivo);																  //Se guarda en la variable nomArchivo ya declarado anteriormente

	pArch = fopen(nomArchivo, "r"); //Se va a leer el archivo
	palabraAlt[0] = '#';

	while ((car = getc(pArch)) != EOF)
	{ //Este while lo que hace es recorrer todo el archivo ya que termina hasta que sea igual a End of file
		//lee caracter por caracter
		car = corregirChar(car); //se manda a llamar a la funcion corregir char

		if (car == ':')
		{
			estado = 'd';
		}
		else
		{
			if (car == '\n')
			{
				estado = 'p';
				++i;
				j = 0;
				fflush(stdout);
				hashFunc(palabraAlt, i);
				memset(palabraAlt, 0, 25);
			}
			else
			{
				if (estado == 'p')
				{
					palabraAlt[j] = car;
					++j;
				}
			}
		}

		// printf("%d ", i);
	}

	printf("\nchoques: %i", choques);

	int vacios  = 0;

	for (i = 0; i < size; ++i)
	{
		if(arr[i] == 0)
		 ++vacios;
	}

	printf("\nvacios: %i\n", vacios);
	/*
    for(j = 0; j< 20; ++j){
        scanf("%s", palabra);
        		int tam = strlen(palabra);
        resultado = 0;
        for(i = 0; i < tam; ++i){
            if(palabra[i]%2 == 0){
                aux =  ((palabra[i] << (5 * i) ));
            }
            else{
                aux = ((palabra[i] >> (3 * i)));
            }   
            if(aux < 0){
                aux = (-1*aux);
            }
            resultado += aux;
        }
        e.palabra =  palabra;
        printf("numero %i \n", (resultado%257));
    }
*/
}