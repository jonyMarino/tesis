/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/Countable.c
 * Code Management Tool File Version: 
 * SDD Component: Countable
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Aplicacion/Countable.c
 * \brief Countable
 */

/* Dependency with own header */
#include "Aplicacion/Countable.h"

/**********************************************************************************
 * Aplicacion/Countable.c
 **********************************************************************************/
/*## package Aplicacion */

/*## class TopLevel::Countable */



#include "Aplicacion/implement/Countable.h"

AllocateMixin( Countable );

/* Initialization, finalization
 */

static
void
Countable_initialize(void)
{
	//Start of user code for Countable_initialize
	//TO DO
	//End of user code
}

static
void
Countable_finalize(void)
{
	//Start of user code for Countable_finalize
	//TO DO
	//End of user code
}


/* Construction, destruction
 */

static
void
Countable_constructor( Countable countable, CountableData self )
{

	//Start of user code for Countable_constructor
	static unsigned int instances = 0;
	self->instanceNum = instances;
	instances++;
	//End of user code
	
}

static
int
Countable_copy( Countable countable, CountableData self, const CountableData from )
{
	//Start of user code for Countable_copy
	Countable_constructor( countable, self );
	return OOC_COPY_DONE;
	//End of user code
}

static
void
Countable_destructor( Countable countable, CountableData self )
{
	//Start of user code for Countable_destructor
	//TODO
	//End of user code
}


/* Method implementations
 */

static
unsigned int
Countable_getInstanceNum (Object carrier){
	//Start of user code for invalid_getInstanceNum

	CountableData self = ooc_get_mixin_data( carrier, Countable );
	return self->instanceNum;
	//End of user code
}


/* Populating the interface's virtual table
 */
static
void
Countable_populate( Countable countable )
{
	countable->getInstanceNum	=	Countable_getInstanceNum;
}


/**********************************************************************************
 * File Path: Aplicacion/Countable.c
 **********************************************************************************/
