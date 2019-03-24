/*
 * main.c
 *
 *  Created on: 22 de mar. de 2018
 *      Author: marino
 */

#include <stdio.h>
#include "Aplicacion/Parent.h"
#include "Aplicacion/Child.h"
#include "Aplicacion/GrandChild.h"

void printNameFollowedByClassName(Child * child)
{
	char * nameEtc = Child_getNameFollowedByClassName( child );
	printf("%s\r\n",nameEtc);
	free(nameEtc);
}


int main(int argc, char ** argv)
{

	GrandChild grand;
	Child child;
	Child * childs[2]={(Child*)&grand,(Child*)&child};

	GrandChild_ctor(&grand,"Mike");
	Child_ctor(&child,"Junior");

	for(int i = 0 ; i < 2 ; i++ )
	{
		printNameFollowedByClassName(childs[i]);
	}

	return 1;

}
