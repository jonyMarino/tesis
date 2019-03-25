/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/Parent.c
 * Code Management Tool File Version: 
 * SDD Component: Parent
 * Language: C
 * Author: 
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

struct ConstructorParams_t{
	const char * name;
};





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
	AddMixin( Parent, Countable ),	AddInterface( Parent, Serializable )};

AllocateClassWithInterface( Parent, Base );
/* Class virtual function prototypes
 */


static
void
Parent_serialize (Parent self, char * out){
	//Start of user code for Parent_serialize
	sprintf(out,"<Parent name = \"%s\" hash = %u> </Parent>\r\n",self->name,self->classHash);
	//End of user code
}




/* Class initializing
 */

static
void
Parent_initialize( Class this )
{
	ParentVtable vtab = & ParentVtableInstance;

	((ParentVtable)vtab)->Serializable.serialize = (void(*)(Object self, char * out))Parent_serialize;
	

	
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
	const struct ConstructorParams_t * params = _params;
	chain_constructor( Parent, self,_params ); /*!!! TODO !!! change the third parameter as required! */
	self->name = params->name;
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


Parent parent_new( const char * name )
{
	//Start of user code for parent_new
	ooc_init_class( Parent );// !!! TODO !!! You may want to remove the initialization from here ...
	//End of user code
	struct ConstructorParams_t cp = {
		name
	};
	return (Parent) ooc_new( Parent, &cp );
}


void
parent_Parent (Parent self, const char * name){
	//Start of user code for Parent
	//TO DO
	//End of user code
}
/**********************************************************************************
 * File Path: Aplicacion/Parent.c
 **********************************************************************************/
