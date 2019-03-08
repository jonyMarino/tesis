/*
 * child.c
 *
 *  Created on: 8 de mar. de 2019
 *      Author: marino
 */

#include "child.h"
#include <stdio.h>
#include <stdlib.h>


//child.c
static void method(parent * self){
	printf( "Child method()\n" );
}
child * child_new(){
	child * out = (child *) parent_new();
	out -> method = method;
	// other initialization for child
	return out;
}

void child_free(child * in){
	// child release of resources
	parent_free(&in->asParent);
}

child * child_copy(child * in){
	child *out = malloc(sizeof(child));
	*out = *in;
	return out;
}
