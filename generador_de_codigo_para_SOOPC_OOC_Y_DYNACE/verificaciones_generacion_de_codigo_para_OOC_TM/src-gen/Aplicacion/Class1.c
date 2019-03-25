/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/Class1.c
 * Code Management Tool File Version: 
 * SDD Component: Class1
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Aplicacion/Class1.c
 * \brief Class1
 */

/* Dependency with own header */
#include "Aplicacion/Class1.h"


/**********************************************************************************
 * Aplicacion/Class1.c
 **********************************************************************************/
/*## package Aplicacion */

/*## class TopLevel::Class1 */



#include "Aplicacion/implement/Class1.h"

#include <ooc/exception.h>







/** \class Class1
 *  \brief MyChild class - brief description. 
 * 	\see class1.h
 */

/** \file class1.h 
 *  \brief Class1 class - brief description.
 * Class1 is a .....
 */ 

/* Allocating the class description table and the vtable
 */


AllocateClass( Class1, Base );
/* Class virtual function prototypes
 */


static
void
Class1_Class1 (Class1 self){
	//Start of user code for Class1_Class1
	//TO DO
	//End of user code
}




/* Class initializing
 */

static
void
Class1_initialize( Class this )
{
	Class1Vtable vtab = & Class1VtableInstance;

	((Class1Vtable)vtab)->Class1 = (void(*)(Class1 self))Class1_Class1;
	

	
	/* Allocate global resources here */
	//Start of user code for Class1_initialize
	//TO DO
	//ooc_init_class( !!! Classes that are USED by Class1 !!! ); Remove if you initialize it other place!
	//End of user code
	
}

/* Class finalizing
 */

#ifndef OOC_NO_FINALIZE
static
void
Class1_finalize( Class this )
{
	//Start of user code for Class1_finalize
	/* Release global resources! */
	//End of user code
}
#endif


/* Constructor
 */

static
void
Class1_constructor( Class1 self, const void * _params )
{



	assert( ooc_isInitialized( Class1 ) );
	
	
	
	/*Start of user code for Class1_constructor */
	chain_constructor( Class1, self,_params ); /*!!! TODO !!! change the third parameter as required! */
	/*End of user code*/
}

/* Destructor
 */

static
void
Class1_destructor( Class1 self, Class1Vtable vtab )
{
	//Start of user code for Class1_destructor
	//TODO
	//End of user code

}

/* Copy constuctor
 */

static
int
Class1_copy( Class1 self, const Class1 from )
{
	//Start of user code for Class1_copy
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


Class1 class1_new( void )
{
	//Start of user code for class1_new
	ooc_init_class( Class1 );// !!! TODO !!! You may want to remove the initialization from here ...
	//End of user code
	return (Class1) ooc_new( Class1, NULL );
}


/**********************************************************************************
 * File Path: Aplicacion/Class1.c
 **********************************************************************************/
