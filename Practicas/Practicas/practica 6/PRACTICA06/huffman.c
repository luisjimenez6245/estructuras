/*AUTORES: Paola Raya Tolentino, 
		 Eduardo Gómez Rodriguez, 
		 Vladimir Azpeitia Hernández.
VERSION: 1.0
DESCRIPCIÓN: Implementacion del algoritmo de huffman, aplicado a documentos de texto. Es solo una 
implementacion didactica.
COMPILACIÓN: gcc -o huffman huffman.c TADArbolBin.o*/

//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADArbolBin.h"
//Constantes
#define SIZE_ASCII 256 //Numero de arboles por cada caracter ASCII
//Prototipos de funciones
void encode(char nameFile[]); //Funcion para codificar un archivo
void orderTrees(arbol_bin charTrees[], int sizeTree); //Funcion para ordenar arboles de manera ascendente, dependidendo de la frecuencia de cada elemento
void decode(char nameCompressFile[], elemento table[], int sizeTable, arbol_bin charTree); //Funcion para descodificar un archivo

/*FUNCION PRINCIPAL*/
int main(){
	char nameFile[50]; //Nombre del archivo a comprimir 
	printf("Ingresa el nombre del archivo:\n\tejemplo(nameFile.txt)\n");
	scanf("%s", nameFile);//Preguntamos al usuario el nombre del archivo
	encode(nameFile); /*Comprimimos el archivo*/
	return 0;
}

/*FUNCION PARA CODIFICAR EL ARCHIVO*/
void encode(char nameFile[]){
	arbol_bin charTreesALL[SIZE_ASCII];//Arreglo de arboles, uno por cada caracter ASCII
	FILE *file, *fp; //Puntero a los archivos
	char c, finalCodeHuffman[100000], aux[4]; //Strings auxiliares
	int character, sizeTree = 0, i, j; //Contadores
	posicion position, backPosition;	//Posiciones auxiliares
	elemento element, backElement, newElement; //Elementos auxiliare
	arbol_bin newTree, auxTree; //Arbol auxiliar

	/*Inicializamos todos los arboles*/
	for(i=0;i<SIZE_ASCII;i++)
		Initialize(&charTreesALL[i]);

	file = fopen(nameFile,"r"); //Abrimos el archivo a codificar

	if (file == NULL){ /*Verificamos que el archivo exista*/
		printf("\nError de apertura del archivo. \n\n");
		exit(0);
	}
	else{ /*Si el archvio existe*/
		while((character = fgetc(file)) != EOF){ //Leemos caracter por caracter
			/*Contamos las letras asignado la frecuencia a cada arbol*/
			if(Empty(&charTreesALL[character]) == FALSE){//Si ya habiamos guardado la letra solo aumentamos la frecuencia
				element = ReadNode(&charTreesALL[character], Root(&charTreesALL[character]));
				(element.frequency)++;
				ReplaceNode(&charTreesALL[character], Root(&charTreesALL[character]), element);
			}else{ /*Si es la primera vez que guardamos esa letra*/
				element.character = (char)character;
				element.frequency = 1;
				NewRightSon(&charTreesALL[character], position, element);
				sizeTree++;
			}
		}
	}
	/*Ahora separamos los arboles de los caracteres ASCII que se encuentran en el 
	documento*/
	arbol_bin charTrees[sizeTree]; //arreglo de arboles, uno por cada caracter ASCII que aparece en el documento
	elemento valuesTable[sizeTree];//arreglo de elementos, uno por cada caracter ASCII que aparece en el documento
	for(i = 0; i < sizeTree; i++){
		while(Empty(&charTreesALL[j]) == TRUE)
			j++;
		charTrees[i] = charTreesALL[j]; //Guardamos el arbol en el nuevo arreglo
		valuesTable[i] = ReadNode(&charTrees[i], Root(&charTrees[i]));
 		j++;
 		PrepareTreeForHuffman(&charTrees[i]); //Inicializamos las varaibles de cada elemento 
	}
	/*Union de los arboles*/
	for(i = 0;i < (sizeTree-1);i++){
		Initialize(&newTree); //Inicializamos el arbol auxiliar
		orderTrees(charTrees, sizeTree); //ordenamos el arreglo de arboles
		backPosition = Root(&charTrees[i]); //arbol 1
		position = Root(&charTrees[i+1]); //arbol 2
		element = ReadNode(&charTrees[i+1], position); //elemento del arbol 1
		backElement = ReadNode(&charTrees[i], backPosition); //elemento del arbol 2
		newElement.character = '|';
		newElement.frequency = backElement.frequency + element.frequency; //Asigamos la  frecuencia a la nueva raiz
		NewRightSon(&newTree, NULL, newElement); //Creamos la raiz del nuevo arbol
		PrepareTreeForHuffman(&newTree); //Inicilaizamos las variables de la raiz
		if(element.frequency <= backElement.frequency){
			ReplaceCodeALL(&charTrees[i+1], 0, 0);
			linkTrees(&newTree, charTrees[i+1], 0); //Se unen los arboles 
			ReplaceCodeALL(&charTrees[i], 0, 1);
			linkTrees(&newTree, charTrees[i], 1);
		}
		else{
			ReplaceCodeALL(&charTrees[i+1], 0, 1);
			linkTrees(&newTree, charTrees[i+1], 1); //Se unen los arboles
			ReplaceCodeALL(&charTrees[i], 0, 0);
			linkTrees(&newTree, charTrees[i], 0);
		}
		charTrees[i+1] = newTree;//EL nuevo arbol se coloca en la posicion i+1
		Initialize(&newTree); //Reseteamos el arbol auxiliar
	}
	

	//Mostrar tabla de valores	
	for(i = 0;i < sizeTree;++i){
		element = ReadNode(&charTrees[sizeTree-1], Search(&charTrees[sizeTree-1], valuesTable[i].character));
		valuesTable[i].huffmanCode.code = element.huffmanCode.code;//Asignamos el codigo de huffman a cada arbol
		valuesTable[i].huffmanCode.n_bits = element.huffmanCode.n_bits;//Asignamos el codigo de huffman a cada arbol
		printf("character: %c\tfrequency: %d\thuffmancode: ", valuesTable[i].character, valuesTable[i].frequency);
		for(j=valuesTable[i].huffmanCode.n_bits-1; j>=0; j--)
			printf("%2d",CONSULTARBIT(valuesTable[i].huffmanCode.code,j));
		printf("\n");
	} 

	file = fopen(nameFile,"r");
	if (file == NULL){
		printf("\nError de apertura del archivo. \n\n");
		exit(0);
	}
	fp = fopen ("encode_file.txt", "w" ); //parametro para escritura al final y para file tipo texto
 	fflush(stdin);
 	printf("\nEl archivo comprimido se a guardado como encode_file.txt.");
 	while((character = fgetc(file)) != EOF){
 		element = ReadNode(&charTrees[sizeTree-1], Search(&charTrees[sizeTree-1], character));
 		for (i=element.huffmanCode.n_bits-1; i>=0; i--){
 			itoa((int)CONSULTARBIT(element.huffmanCode.code,i), aux, 10);
 			strcat(finalCodeHuffman, aux);
 		}
 	}
	fputs( finalCodeHuffman, fp ); //Agregamos la cadena al archvio codificado
 	fclose(fp); //Cerramos el archivo
 	fclose (file); //Cerramos el archivo
 	char nameFileCompress[] = "encode_file.txt"; //Nombre del archivo codificado
  	decode(nameFileCompress, valuesTable, sizeTree, charTrees[sizeTree-1]); //Llamamos a la funcion descodificar 

 	for(i=0;i<SIZE_ASCII;i++)//Destruimos todos los arboles para liberar memoria
		Destroy(&charTreesALL[i]);
	return;
}
/* 
void decode(char nameCompressFile[], elemento table[], int sizeTable)
Descripción: FUNCION PARA DESCODIFICAR UN ARCHIVO
Devuelve: void
*/
void decode(char nameCompressFile[], elemento table[], int sizeTable, arbol_bin charTree){
	FILE *file, *fp;
	posicion position, backPosition;
	char finalCodeHuffmanDecode[10000];
	unsigned char aux = 0;
	int i = 0;
	char character;
	elemento element;
	file = fopen(nameCompressFile,"r");
	if (file == NULL){
		printf("\nError de apertura del archivo. \n\n");
		exit(0);
	}
	backPosition = Root(&charTree);
	while((character = fgetc(file)) != EOF){
		if(character == '0'){
			position = LeftSon(&charTree, backPosition);
		}else if(character == '1'){
			position = RightSon(&charTree, backPosition);
		}else{printf("\nError: This file is not compress");}

		if(LeftSon(&charTree, position) == NULL && RightSon(&charTree, position) == NULL){
			element = ReadNode(&charTree, position);
			finalCodeHuffmanDecode[i] = element.character;
			i++;
			backPosition = Root(&charTree);
		}else{backPosition = position;}
	}
	fp = fopen ("decode_file.txt", "w" );
 	printf("\nEl archivo descomprimido se a guardado como decode_file.txt.");
	fputs( finalCodeHuffmanDecode, fp );
 	fclose(fp); //Cerraos el archivo 

	return;
}

/*
orderTrees(arbol_bin charTrees[], int sizeTree)
Descripción: Funcion para ordenar arboles
Devuelve: void
*/
void orderTrees(arbol_bin charTrees[], int sizeTree){
	int i, j;
	elemento element, backElement;
	arbol_bin backTree;
	for(j = 1;j<sizeTree;j++){
		for (i = 0;i < sizeTree-1 ;++i){
			backTree = charTrees[i];
			element = ReadNode(&charTrees[i+1], Root(&charTrees[i+1]));
			backElement = ReadNode(&backTree, Root(&backTree));
			if(element.frequency < backElement.frequency){
				charTrees[i] = charTrees[i+1];
				charTrees[i+1] = backTree;
			}
		}
	}
	return;
}