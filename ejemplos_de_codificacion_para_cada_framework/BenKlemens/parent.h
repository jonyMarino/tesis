/*
 * parent.h
 *
 *  Created on: 8 de mar. de 2019
 *      Author: marino
 */

#ifndef PARENT_H_
#define PARENT_H_

struct parent;

typedef void (*method_p_t)(struct parent*self);

typedef struct parent{
	int private_attribute1;
	int attribute2;
	method_p_t method;
}parent;

parent * parent_new();
parent * parent_copy(parent * parentToCopy);
void parent_free(parent * parentToFree);


#endif /* PARENT_H_ */
