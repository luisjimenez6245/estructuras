#include <stdio.h>
#include "milibreria.h"
int main(void)
{
	float lado;
	scanf("%f",&lado);
	printf("\nCuadrado de lado %f\tEl área es: %f\tEl perímetro es: %f",lado,AreaCuadrado(lado),PerimetroCuadrado(lado));	
	return 0;
}