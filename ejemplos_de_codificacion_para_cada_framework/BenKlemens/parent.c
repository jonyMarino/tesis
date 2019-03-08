/*
 * parent.c
 *
 *  Created on: 8 de mar. de 2019
 *      Author: marino
 */

#include "parent.h"
#include <stdlib.h>
#include <stdio.h>

//parent.c
static void method(parent * self){
	printf("Parent method()\n");
}
parent * parent_new(){
	parent * out = malloc(sizeof(parent));
	*out = (parent){ .method = method, .private_attribute1 = 0,
			.attribute2 = 0};
	return out;
}

parent * parent_copy(parent * in){
	parent *out = malloc(sizeof(parent));
	*out = *in;
	return out;
}

void parent_free(parent * in){
	free(in);
}

