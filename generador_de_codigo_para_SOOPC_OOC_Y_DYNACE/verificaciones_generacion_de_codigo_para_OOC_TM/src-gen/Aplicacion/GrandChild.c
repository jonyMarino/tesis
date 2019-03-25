/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/GrandChild.c
 * Code Management Tool File Version: 
 * SDD Component: GrandChild
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Aplicacion/GrandChild.c
 * \brief GrandChild
 */

/* Dependency with own header */
#include "Aplicacion/GrandChild.h"


/**********************************************************************************
 * Aplicacion/GrandChild.c
 **********************************************************************************/
/*## package Aplicacion */

/*## class TopLevel::GrandChild */



#include "Aplicacion/implement/GrandChild.h"

#include <ooc/exception.h>

struct ConstructorParams_t{
	const char * name;
};





/** \class GrandChild
 *  \brief MyChild class - brief description. 
 * 	\see grandchild.h
 */

/** \file grandchild.h 
 *  \brief GrandChild class - brief description.
 * GrandChild is a .....
 */ 

/* Allocating the class description table and the vtable
 */

InterfaceRegister( GrandChild )
{
};

AllocateClassWithInterface( GrandChild, Child );
/* Class virtual function prototypes
 */


static
char *
GrandChild_getNameFollowedByClassName (GrandChild self){
	//Start of user code for GrandChild_getNameFollowedByClassName
	char * className = "GrandChild";
	const char * name = ((Parent)self)->name;
	char * nameFollowedByClassName= malloc(strlen(className)+strlen(name)+1);
	sprintf(nameFollowedByClassName,"%s%s",name,className);
	return nameFollowedByClassName;
	//End of user code
}




/* Class initializing
 */

static
void
GrandChild_initialize( Class this )
{
	GrandChildVtable vtab = & GrandChildVtableInstance;

	((ChildVtable)vtab)->getNameFollowedByClassName = (char *(*)(Child self))GrandChild_getNameFollowedByClassName;
	

	
	/* Allocate global resources here */
	//Start of user code for GrandChild_initialize
	//TO DO
	//ooc_init_class( !!! Classes that are USED by GrandChild !!! ); Remove if you initialize it other place!
	//End of user code
	
}

/* Class finalizing
 */

#ifndef OOC_NO_FINALIZE
static
void
GrandChild_finalize( Class this )
{
	//Start of user code for GrandChild_finalize
	/* Release global resources! */
	//End of user code
}
#endif


/* Constructor
 */

static
void
GrandChild_constructor( GrandChild self, const void * _params )
{



	assert( ooc_isInitialized( GrandChild ) );
	
	
	
	/*Start of user code for GrandChild_constructor */
	//const struct ConstructorParams_t * params = _params;
	chain_constructor( GrandChild, self,_params ); /*!!! TODO !!! change the third parameter as required! */
	/*End of user code*/
}

/* Destructor
 */

static
void
GrandChild_destructor( GrandChild self, GrandChildVtable vtab )
{
	//Start of user code for GrandChild_destructor
	//TODO
	//End of user code

}

/* Copy constuctor
 */

static
int
GrandChild_copy( GrandChild self, const GrandChild from )
{
	//Start of user code for GrandChild_copy
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


GrandChild grandchild_new( const char * name )
{
	//Start of user code for grandchild_new
	ooc_init_class( GrandChild );// !!! TODO !!! You may want to remove the initialization from here ...
	//End of user code
	struct ConstructorParams_t cp = {
		name
	};
	return (GrandChild) ooc_new( GrandChild, &cp );
}


void
grandchild_GrandChild (GrandChild self, const char * name){
	//Start of user code for GrandChild
	//TO DO
	//End of user code
}
void
grandchild_foo (GrandChild self){
	//Start of user code for foo
	//TO DO
	//End of user code
}
/**********************************************************************************
 * File Path: Aplicacion/GrandChild.c
 **********************************************************************************/
