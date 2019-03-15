/*
 * main.c
 *
 *  Created on: 22 de mar. de 2018
 *      Author: marino
 */

#include <stdio.h>
#include "Aplicacion/Parent.h"
#include "Aplicacion/Child.h"



int main(int argc, char ** argv)
{

	Child child;

	Child_ctor(&child);

	Parent_metodo(&child.super);

	return 1;

}
