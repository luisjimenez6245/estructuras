#include "TADHashTable.h"
#include <stdio.h>
#include <string.h>
#include <math.h>


#define ArrayNumber 509
#define AKEY 73571


int aplicarHash(char *palabra,int tamTabla){
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