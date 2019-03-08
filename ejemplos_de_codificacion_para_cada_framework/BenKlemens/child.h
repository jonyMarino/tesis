/*
 * child.h
 *
 *  Created on: 8 de mar. de 2019
 *      Author: marino
 */


#ifndef CHILD_H_
#define CHILD_H_

#include "parent.h"


//child.h
typedef struct child{
	union{
		struct parent;
		struct parent asParent;
	};
	//new attributes and polymorphic methods...
}child;


child * child_new();
child * child_copy(child * childToCopy);
void child_free(child * in);



#endif

