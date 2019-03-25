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

#define MAX_OBJECTS 4

int main(int argc, char ** argv)
{
	Child child[MAX_OBJECTS];


	child[0]=  child_new("Ramon");
	child[1]=  child_new("Juan");
	child[2]= (Child) grandchild_new("Pablo");
	child[3]= (Child) ooc_duplicate((Object)child[2]);

	for(int i=0;i<MAX_OBJECTS;i++)
	{
		char * nameFollowedByClassName = ChildVirtual( child[i] )->getNameFollowedByClassName( child[i] );
		Serializable s;

		printf("%s\r\n",nameFollowedByClassName);

		s = ooc_get_interface( child[i] , Serializable);

		if(s)
		{
			char serializeOutput[100];
			s->serialize((Object)child[i] , serializeOutput );
			printf("serialized: %s \r\n", serializeOutput);
		}
		Countable m = ooc_get_interface( child[i] , Countable );
		if(m)
		{
			unsigned int iN = m->getInstanceNum((Object)child[i]);
			printf("Instance Number: %d \r\n",iN);
		}
	}
	return 1;

}
