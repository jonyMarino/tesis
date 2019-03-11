




/**********************************************************************************
 * .c
 **********************************************************************************/
/*## package invalid */

/*## class TopLevel::Class1 */



#include "implement/.h"

#include <ooc/exception.h>







/** \class 
 *  \brief MyChild class - brief description. 
 * 	\see invalid.h
 */

/** \file invalid.h 
 *  \brief  class - brief description.
 *  is a .....
 */ 

/* Allocating the class description table and the vtable
 */


AllocateClass( ,  );
/* Class virtual function prototypes
 */






/* Class initializing
 */

static
void
_initialize( Class this )
{

	

	
	/* Allocate global resources here */
	//Start of user code for _initialize
	//TO DO
	//ooc_init_class( !!! Classes that are USED by  !!! ); Remove if you initialize it other place!
	//End of user code
	
}

/* Class finalizing
 */

#ifndef OOC_NO_FINALIZE
static
void
_finalize( Class this )
{
	//Start of user code for _finalize
	/* Release global resources! */
	//End of user code
}
#endif


/* Constructor
 */

static
void
_constructor(  self, const void * _params )
{



	assert( ooc_isInitialized(  ) );
	
	
	
	/*Start of user code for _constructor */
	chain_constructor( , self,_params ); /*!!! TODO !!! change the third parameter as required! */
	/*End of user code*/
}

/* Destructor
 */

static
void
_destructor(  self, Vtable vtab )
{
	//Start of user code for _destructor
	//TODO
	//End of user code

}

/* Copy constuctor
 */

static
int
_copy(  self, const  from )
{
	//Start of user code for _copy
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





/**********************************************************************************
 * File Path: .c
 **********************************************************************************/
