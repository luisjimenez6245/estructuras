
void modificarPalabra(List diccionario[], char palabra[]){
	definicion candidata;
	strcpy(candidata.palabra, palabra);
	// printf("Clave de List a buscar: %d, Tam: %d\n", hash(palabra), strlen(palabra));
	posicion lugar = Search(&diccionario[hash(palabra)], candidata);
	if(ValidatePosition(&diccionario[hash(palabra)], lugar) == TRUE){	
		char def[251];
		definicion aux = buscarPalabra(diccionario, palabra);
		fflush(stdin);
		printf("\nIngrese la nueva definicion: ");
		scanf("%251[^\n]", def);
		strcpy(aux.significado, def);
		Replace(&diccionario[hash(palabra)],lugar, aux);
		printf("\n\n----------------------------------------\n\n");
		printf("Palabra modificada con exito\n\n");
		printf("----------------------------------------\n\n");
	}else{
		printf("\nError: La palabra que quieres modificar no existe en el diccionario.\n");
	}
	return;
}

void eliminarPalabra(List diccionario[], char palabra[]){
	definicion candidata;
	strcpy(candidata.palabra, palabra);
	// printf("Clave de List a buscar: %d, Tam: %d\n", hash(palabra), strlen(palabra));
	posicion lugar = Search(&diccionario[hash(palabra)], candidata);
	if(ValidatePosition(&diccionario[hash(palabra)], lugar) == TRUE){
		Remove(&diccionario[hash(palabra)], lugar);
		printf("\n\n----------------------------------------\n\n");
		printf("Palabra eliminada con exito\n\n");
		printf("----------------------------------------\n\n");
	}else{
		printf("\nError: La palabra que quieres eliminar no existe en el diccionario\n");
	}
	return;
}

int main(){
	int pos,x=0, tamPal = 51, tamDef = 251, cubeta[100], moda=0, prom=0, vacias=0, max=0;
	char palabra[tamPal], def[tamDef];
	int res[tam],i,j;
	definicion defAct;
	posicion nue;

	for(i=0;i<tam; i++){
		res[i] = 0;
	}

	List diccionario[tam];
	for(i=0; i<tam; i++){
		Initialize(&diccionario[i]);
	}

	while(1){
		switch(menu()){
			case 1:
				
			break;

			case 2:
				
			break;

			case 3:
				printf("\n\n----------------------------------------\n\n");
				printf("BUSQUEDA\n\n");
				printf("----------------------------------------\n\n");
				fflush(stdin);
				printf("\nIngresa la palabra a buscar: ");
				scanf("%51[^\n]", palabra);
				for(i=0; i<strlen(palabra); i++)
					palabra[i] = corregirChar(palabra[i]);
				defAct = buscarPalabra(diccionario, palabra);
				if(defAct.significado[0] == '-' && defAct.significado[1] == '-')
					printf("\n----Palabra no encontrada----\n");
				else{
					printf("\n\t%s: %s\n\n", defAct.palabra, defAct.significado);
				}

				system("pause");
			break;

			case 4:
				fflush(stdin);
				printf("\nIngresa la palabra a modificar: ");
				scanf("%51[^\n]", palabra);
				modificarPalabra(diccionario, palabra);
				system("pause");
			break;

			case 5:
				fflush(stdin);
				printf("\nIngresa la palabra a eliminar: ");
				scanf("%51[^\n]", palabra);
				eliminarPalabra(diccionario, palabra);
				system("pause");
			break;

			case 7:
				for(i=0; i<tam; i++){
					printf("List %d: %d elementos\n", i, Size(&diccionario[i]));
					for(j=0; j<Size(&diccionario[i]); j++){
						if(j==0){
							nue = First(&diccionario[i]);
						}
						else{
							nue = Following(&diccionario[i], nue);
						}
						// printf("\tElemento: %s %s\n", nue->e.palabra, nue->e.significado);
					}
				}
				system("pause");
			break;

			case 6:
				exit(0);
			break;

			case 8:
				for(i=0; i<tam; i++){
					printf("List %d: %d elementos\n", i, Size(&diccionario[i]));
					for(j=0; j<Size(&diccionario[i]); j++){
						if(j==0){
							nue = First(&diccionario[i]);
						}
						else{
							nue = Following(&diccionario[i], nue);
						}
						printf("\tElemento: %s %s\n", nue->e.palabra, nue->e.significado);
					}
				}
				system("pause");

			break;

			case 9:
				moda =0; prom = 0; vacias = 0; max=0;
				for(i=0; i<100; i++)
					cubeta[i] = 0;

				printf("\n\n----------------------------------------\n\n");
				printf("ESTADISTICAS DE DICCIONARIO HASH ABIERTO\n\n");
				printf("----------------------------------------\n\n");

				printf("Tamaño de la tabla: %d\n", tam);

				for(i=0; i<tam; i++){
					// printf("List %d: %d elementos\n", i, Size(&diccionario[i]));
					cubeta[Size(&diccionario[i])]++;
					if(Size(&diccionario[i]) == 0){
						vacias++;
					}
					if(Size(&diccionario[i]) > max){
						max = Size(&diccionario[i]);
					}
				}
				for(i=2; i<100; i++){
					// printf("%d elementos: %d\n", i, cubeta[i]);
					if(cubeta[i] >= moda){
						moda = cubeta[i];
						prom = i;
					}
				}

				printf("El numero promedio de colisiones es de: %d\n", prom);
				printf("El numero de Lists vacias es %d\n", vacias);
				printf("El orden maximo de busqueda es: %d\n", max);
				printf("El numero maximo de pasos para encontrar un elemento es: %d\n", max+1);

				system("pause");
			break;

			case 100:
				for(i=0; i<tam; i++){
					Initialize(&diccionario[i]);
				}
			break;

			default:
				printf("Opcion no reconocida\n");
			break;
		}
	}

	return 0;
}
