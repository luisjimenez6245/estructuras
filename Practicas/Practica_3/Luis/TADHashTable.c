#include "TADHashTable.h"
#include <stdio.h>
#include <string.h>
#include <math.h>


#define ArrayNumber 509
#define AKEY 73571


int aplicarHash(char *palabra,int tamTabla){
	/*
//Esta variante consiste en tomar el valor de cada carácter
//y hacer dos corrimientos de bits
//Uno hacia la izquierda y hacia a derecha con dos valores distintos
//Estos se unen por medio de un or de bits
//El resultado obtenido se utliza como codigo hash

int HashCode(char *palabra, int tamTabla)
{
	int tam=strlen(palabra);
	//declaración de la variable que obtendrá el resultado del hash
	unsigned int h=0;
	int i;
	//Por cada uno lo que se va a hacer es asignar un valor or
	for (i=0; i<tam; i++)
	{
		//utilizamos operadores de desplazamiento
		//<< corrimiento 5 espacios a la izquierda
		//>> corrimiento 27 espacios a la derecha
		
		h=(h<<5)|(h>>27);
		h+=(unsigned int)palabra[i];
	}
	return h;	
}


//Esta basada en el algoritmo de Dan Bernstein
//En esta función hash tenemos dos numeros 33 y 5381
//El número 33 se elige porque es facil de calcular
//Usar 33 hace dos copias de la mayoría de los bits de entrada en el acumulador de hash

    int HashCodee( char *palabra)
    {
        unsigned long hash1 = 5381;
        int c;

        while (c = *palabra++)
        //El desplazamiento de 5 se hace ya que es relativamente
        //primo a 32 lo que ayuda con el avalanchamiento
        //ya que un caracter ascii puede considerarse como un selector de tipo
        //caracteres de 4 bits
            hash1 = ((hash1 << 5) + hash1) + c; // hash * 33 + c 

        return hash1;
    }
    */
	/*
	int index=0,m_posicion,valor_letra,aux;//m_posicion = MÚLTIPLO DE LA POSICIÓN
	for(aux=0;aux<strlen(palabra);aux++){
		m_posicion=pow(2,aux+1);
		valor_letra=(int)palabra[aux];
		index=index+valor_letra*m_posicion;
	}
	if(index<0){
		index=index*-1;
	}
	return index%tamTabla;*/
	
	int aux = 0;
	int i = 0, resultado = 0, tam,  derecha;
	tam = strlen(palabra);
	for (i = 0; i < tam; ++i)
	{
		aux = ((AKEY *  palabra[i]) % ((int) pow(2,i + 13))) >> ((int)(pow(8,i +3)));
		resultado += aux;
	}
	resultado = (resultado % tamTabla);
	if(resultado < 0)
		resultado = tamTabla + resultado;

	return resultado;
}

void InicializarTabla(tablaHash *tabla){
	int aux;
	for(aux=0;aux<tabla->tamTabla;aux++){
		Initialize(&tabla->listas[aux]);
	}
	return;
}

void DestruirTabla(tablaHash *tabla){
	int aux;
	for(aux=0;aux<tabla->tamTabla;aux++){
		Destroy(&tabla->listas[aux]);
	}
	return;
}

void AgregarATabla(tablaHash *tabla, elemento e){
	int index;
	index=aplicarHash(e.palabra,tabla->tamTabla);
	Add(&tabla->listas[index],e);
	return;
}

void EliminarDeTabla(tablaHash *tabla, elemento e){
	int index;
	posicion posEnTabla;
	index=aplicarHash(e.palabra,tabla->tamTabla);
	posEnTabla=Search(&tabla->listas[index],e);
	Remove(&tabla->listas[index],posEnTabla);
	return;
}

elemento BuscarEnTabla(tablaHash *tabla, elemento e){
	elemento encontrada;
	int index;
	posicion posEnTabla;
	index=aplicarHash(e.palabra,tabla->tamTabla);
	posEnTabla=Search(&tabla->listas[index],e);
	if(posEnTabla!=NULL){//COMPROBAMOS QUE EXISTE LA PALABRA DENTRO DE LA LISTA
		encontrada=Position(&tabla->listas[index],posEnTabla);
		printf("Encontrada en %i pasos\n",posEnTabla->pasos);
	}else{
		printf("La palabra solicitada no existe en el diccionario...\n");
		char no_encontrada[4]="NULL";
		strcpy(&encontrada.palabra[0],&no_encontrada[0]);
	}
	return encontrada;
}

void ModificarTabla(tablaHash *tabla, elemento e){
	int index;
	posicion posEnTabla;
	index=aplicarHash(e.palabra,tabla->tamTabla);
	posEnTabla=Search(&tabla->listas[index],e);
	Replace(&tabla->listas[index],posEnTabla,e);
	return;
}

void Estadisticas(tablaHash *tabla){
	printf("Total de listas en la tabla: %i\n",TABLE_SIZE);
	int aux,vacias=0,tamLista,totalElementos=0,noVacias=0;
	for(aux=0;aux<TABLE_SIZE;aux++){
		tamLista=Size(&tabla->listas[aux]);
		totalElementos=totalElementos+tamLista;
		if(tamLista==0){
			vacias++;
		}
		printf("La lista %i contiene %i elemento(s)\n",aux,tamLista);
	}
	printf("Total de listas vacias: %i\n",vacias);
	noVacias=TABLE_SIZE-vacias;
	noVacias!=0?printf("Promedio de colisiones: %i\n",totalElementos/noVacias):printf("No se ha podido determinar el promedio de colisiones\n");
	printf("Total de elementos: %i",totalElementos);
	return;
}

void ExportarTabla(tablaHash *tabla){
	int aux;
	FILE *nuevoArchivo;
	char nombreArchivo[]="Diccionario.txt",palabra[100],definicion[255];
	nuevoArchivo=fopen(nombreArchivo,"w");
	if(nuevoArchivo!=NULL){
		posicion finLista;
		elemento actual;
		for(aux=0;aux<TABLE_SIZE;aux++){
			finLista=tabla->listas[aux].frente;
			while(finLista!=NULL){
				actual=Position(&tabla->listas[aux],finLista);
				strcpy(palabra,actual.palabra);
				strcpy(definicion,actual.definicion);
				strcat(palabra,": ");
				strcat(palabra,definicion);
				fprintf(nuevoArchivo,palabra);
				finLista=finLista->siguiente;
			}
		}
		fclose(nuevoArchivo);
		printf("Exportado exitosamente!\n");
	}else{
		printf("Exportado exitosamente fallido!\n");
	}
	return;
}