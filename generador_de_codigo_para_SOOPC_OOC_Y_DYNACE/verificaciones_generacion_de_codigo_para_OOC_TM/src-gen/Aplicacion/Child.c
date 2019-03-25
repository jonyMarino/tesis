/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/Child.c
 * Code Management Tool File Version: 
 * SDD Component: Child
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Aplicacion/Child.c
 * \brief Child
 */

/* Dependency with own header */
#include "Aplicacion/Child.h"


/**********************************************************************************
 * Aplicacion/Child.c
 **********************************************************************************/
/*## package Aplicacion */

/*## class TopLevel::Child */



#include "Aplicacion/implement/Child.h"

#include <ooc/exception.h>

struct ConstructorParams_t{
	const char * name;
};





/** \class Child
 *  \brief MyChild class - brief description. 
 * 	\see child.h
 */

/** \file child.h 
 *  \brief Child class - brief description.
 * Child is a .....
 */ 

/* Allocating the class description table and the vtable
 */

InterfaceRegister( Child )
{
};

AllocateClassWithInterface( Child, Parent );
/* Class virtual function prototypes
 */


static
void
Child_vPrint (Child self){
	//Start of user code for Child_vPrint
	//TO DO
	//End of user code
}
static
char *
Child_getNameFollowedByClassName (Child self){
	//Start of user code for Child_getNameFollowedByClassName
	char * className = "Child";
	const char * name = ((Parent)self)->name;
	char * nameFollowedByClassName= malloc(strlen(className)+strlen(name)+1);
	sprintf(nameFollowedByClassName,"%s%s",name,className);
	return nameFollowedByClassName;
	//End of user code
}
static
void
Child_serialize (Child self, char * out){
	//Start of user code for Child_serialize
	sprintf(out,"<Child aNumber = %u >\r\n",self->aNumber);
	out += strlen(out);
	ChildParentVirtual(self)->Serializable.serialize((Object)self,out);
	out += strlen(out);
	sprintf(out,"</Child>");
	//End of user code
}




/* Class initializing
 */

static
void
Child_initialize( Class this )
{
	ChildVtable vtab = & ChildVtableInstance;

	((ParentVtable)vtab)->vPrint = (void(*)(Parent self))Child_vPrint;
	((ParentVtable)vtab)->Serializable.serialize = (void(*)(Object self, char * out))Child_serialize;
	((ChildVtable)vtab)->getNameFollowedByClassName = (char *(*)(Child self))Child_getNameFollowedByClassName;
	

	
	/* Allocate global resources here */
	//Start of user code for Child_initialize
	//TO DO
	//ooc_init_class( !!! Classes that are USED by Child !!! ); Remove if you initialize it other place!
	//End of user code
	
}

/* Class finalizing
 */

#ifndef OOC_NO_FINALIZE
static
void
Child_finalize( Class this )
{
	//Start of user code for Child_finalize
	/* Release global resources! */
	//End of user code
}
#endif


/* Constructor
 */

static
void
Child_constructor( Child self, const void * _params )
{



	assert( ooc_isInitialized( Child ) );
	
	
	
	/*Start of user code for Child_constructor */
	//const struct ConstructorParams_t * params = _params;
	chain_constructor( Child, self,_params ); /*!!! TODO !!! change the third parameter as required! */
	/*End of user code*/
}

/* Destructor
 */

static
void
Child_destructor( Child self, ChildVtable vtab )
{
	//Start of user code for Child_destructor
	//TODO
	//End of user code

}

/* Copy constuctor
 */

static
int
Child_copy( Child self, const Child from )
{
	//Start of user code for Child_copy
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


Child child_new( const char * name )
{
	//Start of user code for child_new
	ooc_init_class( Child );// !!! TODO !!! You may want to remove the initialization from here ...
	//End of user code
	struct ConstructorParams_t cp = {
		name
	};
	return (Child) ooc_new( Child, &cp );
}


void
child_Child (Child self, const char * name){
	//Start of user code for Child
	//TO DO
	//End of user code
}
/**********************************************************************************
 * File Path: Aplicacion/Child.c
 **********************************************************************************/
