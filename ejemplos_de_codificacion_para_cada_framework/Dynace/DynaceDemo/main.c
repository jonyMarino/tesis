/*
 * main.c
 *
 *  Created on: 22 de mar. de 2018
 *      Author: marino
 */

#include <stdio.h>

#include "generics.h"


int main(int argc, char *argv[])
{
	/*  declare a variable to hold the object  */
	object	myObj;

	InitDynace(&argc);
	printf("Dynace started!!!\n");
	/*  Create an instance of the new class.  Note that the gNew generic
	    is actually running the New method associated with the Object
	    class since Class1 doesn't explicitly define this method.  */

	myObj = gNew(Parent);

	print(myObj);

	/*  If the garbage collector is not being used you must dispose of
	    an object which is no longer needed (unless of course you program
	    is terminating, in which case all the objects will be freed
	    anyway.)  This method is also being inherited from the Object
	    class.  */

	gDispose(myObj);

	myObj = gNew(Child);
	print(myObj);
	gDispose(myObj);

	myObj = gNew(GrandChildren);
	print(myObj);
	gDispose(myObj);

	myObj = gNew(GrandGrandChildren);
	print(myObj);
	gDispose(myObj);

	return 0;
}
