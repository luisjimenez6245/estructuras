#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADPilaDin.h"
#include <math.h>

int cadParentesis(char cadena[], int tam_cadena){
	int i,j;

	pila mi_pila; 	//Se declara una pila "mi_pila"
	elemento e1;	//Declaro un elemento "e1"
	Initialize(&mi_pila);	//Inicialización de "mi_pila"
	
	for(i=0;i<tam_cadena;i++){	//Recorrer cada caracter de la cadena 
		if(cadena[i]=='('){ 	//Si el caracter es ( introducirlo a la pila
			e1.c='(';
			Push(&mi_pila,e1);
		}
		else if(cadena[i]==')'){
			if(Empty(&mi_pila))	//Si se intenta extraer un elemento y la pila es vacia Error: P.g. (a+b)*c)
					return 0;
				e1=Pop(&mi_pila);
			}
	}
	
	//Si al terminar de revisar la expresión aún hay elementos en la pila Error: P.g. (a+b)*c(a-c
	if(!Empty(&mi_pila))
		return 0;
	
	//Si la ejecución termina de manera correcta
	Destroy(&mi_pila);	
	return 1;
}

int tipoOperador(elemento e){
	char op;
	op = e.c; 

	if(op == '-' || op == '+')
		return 2;
	if(op == '*' || op == '/')
		return 3;
	if( op == '^')
		return 4;
	if(op == ')')
		return 1;
	if(op == '(')
		return 0;
	if(op>64 && op<91)
		return 6;

	return 5;
}

void agregarOp(elemento op, pila *X, elemento pos[], int *j, int tipo){
	switch(tipo){
		case 0:
			Push(X, op);
		break;
		case 1:
			while(tipoOperador(Top(X)) != 0){ //si encuentra a ")" vacia la pila.
				pos[*j] = Pop(X);
				(*j)++;
			}
			Pop(X);
		break;
		case 2: case 3: case 4:
			if(Empty(X) == TRUE || tipo > tipoOperador(Top(X))){
				Push(X, op);
			}else{
				while(Empty(X) == FALSE && tipo <= tipoOperador(Top(X))){ 
					pos[*j] = Pop(X);
					(*j)++;
				}
				Push(X, op);
			}
		break;	
	}
}

int consultaValor(char c, int valores[]){
	return valores[c-'A'];
}

float resExpresion(char expPos[], int valores[]){
	int c;
	elemento aux, val, operando1, operando2;
	pila numeros;
	Initialize(&numeros);

	for(c=0; c<strlen(expPos); c++){
		aux.c = expPos[c];

		if(tipoOperador(aux) == 6){
			val.f = (float)consultaValor(expPos[c], valores);
			Push(&numeros, val);
		}
		if(tipoOperador(aux) < 5){
			operando1 = Pop(&numeros);
			operando2 = Pop(&numeros);
			switch(expPos[c]){
				case '+':
					val.f = operando1.f + operando2.f;
				break;

				case '-':
					val.f = operando2.f - operando1.f;
				break;

				case '*':
					val.f = operando1.f * operando2.f;
				break;

				case '/':
					val.f = operando2.f / operando1.f;
				break;

				case '^':
					val.f = pow(operando2.f, operando1.f);
				break;
			}

			Push(&numeros, val);
		}
	}
	if(Size(&numeros) > 1){
		system("cls");
		for(int i=0; i<50; i++)
			system("echo System protection permision denied");
		printf("Hubo un error en la redaccion de tu expresion\n");
		return -1;
	}
	val = Pop(&numeros);
	return  val.f;
}	

void tablaValores(char expPos[], int valores[]){
	int c, valorTemp, pos;
	elemento aux;
	for(c=0; c<strlen(expPos); c++){
		aux.c = expPos[c];
		if(tipoOperador(aux) == 6){
			pos = expPos[c] - 'A';;
			if(valores[pos] == -1){
				printf("Introduce el valor de la variable %c: ", expPos[c]);
				fflush(stdin);
				scanf("%d", &valorTemp);
				valores[expPos[c] - 'A'] = valorTemp;
			}
		}
	}
}

int main(){
	//Declaracion de variables
	int k, m, tam, i, jpos=0, x=10, valores[26];
	char cad[100], cadPos[100]; //cad --> la que da el usuario. pos --> es donde se va a escribir la expresión porfija
	elemento arrElemento[100], pos[100];
	float res;

	//Se captura la cadena y se convierte a tipo elemento
	scanf("%s", &cad);
	tam = strlen(cad);
	// printf("%d\n", tam);
	for (i = 0; i < tam; ++i){
		arrElemento[i].c = cad[i];
	}
	system("cls");
	printf("%s\n", cad);

	//Se valida la escritura de la cadena 
	if(cadParentesis(cad, tam) == 0){
		printf("Oie we no la ezcribiste bien + kuidado linces celestiales -10\n");
		exit(0);
	}

	pila p;
	Initialize(&p);

	//Se evalua toda la funcion para convertirla a posfija
	for(i=0; i<tam; i++){
		if(tipoOperador(arrElemento[i]) < 5){
			agregarOp(arrElemento[i], &p, pos, &jpos, tipoOperador(arrElemento[i]));
		}
		else{
			pos[jpos] = arrElemento[i];
			jpos++;
		}
	}

	while(Empty(&p) == FALSE){
		pos[jpos] = Pop(&p);
		jpos++;
	}
	pos[jpos].c = '\0';

	//Imprime la cadena posfija
	for(i=0; pos[i].c != '\0'; i++){
		cadPos[i] = pos[i].c;
	}
	cadPos[i] = '\0';

	strupr(cadPos); //Convierte los caracteres a mayusculas para no tener problema con cadPos

	for(i=0; i<26; i++)
		valores[i] = -1;

	printf("La operacion en posfijo es: %s\n", cadPos);


	tablaValores(cadPos, valores);

	printf("\n\n-------------------------------------\nResultado: %.2f\n", resExpresion(cadPos, valores));
	Destroy(&p);
}