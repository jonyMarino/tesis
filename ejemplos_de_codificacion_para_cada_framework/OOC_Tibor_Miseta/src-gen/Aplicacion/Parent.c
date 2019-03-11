/**********************************************************************************
 * Copyright: 2019 All rights reserved.
 * Project: RootElement
 * File: Aplicacion/Parent.c
 * Code Management Tool File Version: 1.0.0
 * Date: $Date$
 * SDD Component: Parent
 * Language: C
 * Author: marino
 * Last Change: $Id$
 **********************************************************************************/

/*!
 * \file Aplicacion/Parent.c
 * \brief Parent
 */

/* Dependency with own header */
#include "Aplicacion/Parent.h"


/**********************************************************************************
 * Aplicacion/Parent.c
 **********************************************************************************/
/*## package Aplicacion */

/*## class TopLevel::Parent */



#include "Aplicacion/implement/Parent.h"

#include <ooc/exception.h>







/** \class Parent
 *  \brief MyChild class - brief description. 
 * 	\see parent.h
 */

/** \file parent.h 
 *  \brief Parent class - brief description.
 * Parent is a .....
 */ 

/* Allocating the class description table and the vtable
 */

InterfaceRegister( Parent )
{
	AddInterface( Parent, MyInterface ),	AddMixin( Parent, MyMixin )};

AllocateClassWithInterface( Parent, Base );
/* Class virtual function prototypes
 */


static
void
Parent_method (Parent self){
	//Start of user code for Parent_method
	//TO DO
	//End of user code
}
static
void
Parent_serialize (Parent self, char * out){
	//Start of user code for Parent_serialize
	//TO DO
	//End of user code
}
static
void
Parent_myInterfaceMethod (Parent self){
	//Start of user code for Parent_myInterfaceMethod
	//TO DO
	//End of user code
}




/* Class initializing
 */

static
void
Parent_initialize( Class this )
{
	ParentVtable vtab = & ParentVtableInstance;

	((ParentVtable)vtab)->method = (void(*)(Parent self))Parent_method;
	((ParentVtable)vtab)->serialize = (void(*)(Parent self, char * out))Parent_serialize;
	((ParentVtable)vtab)->MyInterface.myInterfaceMethod = (void(*)(Object self))Parent_myInterfaceMethod;
	

	
	/* Allocate global resources here */
	//Start of user code for Parent_initialize
	//TO DO
	//ooc_init_class( !!! Classes that are USED by Parent !!! ); Remove if you initialize it other place!
	//End of user code
	
}

/* Class finalizing
 */

#ifndef OOC_NO_FINALIZE
static
void
Parent_finalize( Class this )
{
	//Start of user code for Parent_finalize
	/* Release global resources! */
	//End of user code
}
#endif


/* Constructor
 */

static
void
Parent_constructor( Parent self, const void * _params )
{



	assert( ooc_isInitialized( Parent ) );
	
	
	
	/*Start of user code for Parent_constructor */
	chain_constructor( Parent, self,_params ); /*!!! TODO !!! change the third parameter as required! */
	/*End of user code*/
}

/* Destructor
 */

static
void
Parent_destructor( Parent self, ParentVtable vtab )
{
	//Start of user code for Parent_destructor
	//TODO
	//End of user code

}

/* Copy constuctor
 */

static
int
Parent_copy( Parent self, const Parent from )
{
	//Start of user code for Parent_copy
	/* makes the default object copying (bit-by-bit) */
	return OOC_COPY_DEFAULT;
	
	/*Other alternatives:*/

	/* Copies data by hand */
	//self->data = from->data;
	//...
	//return OOC_COPY_DONE;
	
	/* Prevent object duplication */
	//return OOC_NO_COPY;
	//End of user code
}

/*	=====================================================
	Class member functions
 */


Parent parent_new( void )
{
	//Start of user code for parent_new
	ooc_init_class( Parent );// !!! TODO !!! You may want to remove the initialization from here ...
	//End of user code
	return (Parent) ooc_new( Parent, NULL );
}


/**********************************************************************************
 * File Path: Aplicacion/Parent.c
 **********************************************************************************/
