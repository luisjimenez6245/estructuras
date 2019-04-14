#include "TADHashTable.h"
#include <stdio.h>
#include <string.h>
#include <math.h>


#define ArrayNumber 509
#define AKEY 73571


int aplicarHash(char *palabra,int tamTabla){
	int index=0,m_posicion,valor_letra,aux;//m_posicion = MÚLTIPLO DE LA POSICIÓN
	for(aux=0;aux<strlen(palabra);aux++){
		m_posicion=pow(2,aux+1);
		valor_letra=(int)palabra[aux];
		index=index+valor_letra*m_posicion;
	}
	if(index<0){
		index=index*-1;
	}
	return index%tamTabla;
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
	return;
}

void Estadisticas(tablaHash *tabla){
	int vacias = 0, pcolisiones = 0;
	return;
}

void ListarElementos(tablaHash *tabla){
	int i = 0;
	for(i = 0; i < )
	return;
}