/*
 * main.c
 *
 *  Created on: 22 de mar. de 2018
 *      Author: marino
 */

#include <stdio.h>
#include "Aplicacion/Parent.h"

#define MAX_OBJECTS 4

int main(int argc, char ** argv)
{
	Parent parent = parent_new();

	MyMixin myMixin;

	myMixin = ooc_get_interface( parent , MyMixin);

	if( myMixin )
	{
		myMixin->myMixinMethod((Object)parent);

	}

	MyInterface myInterface;

	myInterface = ooc_get_interface( parent , MyInterface );
	if(myInterface)
	{
		myInterface->myInterfaceMethod((Object)parent);
	}

	return 1;

}
