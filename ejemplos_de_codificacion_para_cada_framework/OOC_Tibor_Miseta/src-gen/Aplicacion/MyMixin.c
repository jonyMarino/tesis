/**********************************************************************************
 * Copyright: 2019 All rights reserved.
 * Project: RootElement
 * File: Aplicacion/MyMixin.c
 * Code Management Tool File Version: 1.0.0
 * Date: $Date$
 * SDD Component: MyMixin
 * Language: C
 * Author: marino
 * Last Change: $Id$
 **********************************************************************************/

/*!
 * \file Aplicacion/MyMixin.c
 * \brief MyMixin
 */

/* Dependency with own header */
#include "Aplicacion/MyMixin.h"

/**********************************************************************************
 * Aplicacion/MyMixin.c
 **********************************************************************************/
/*## package Aplicacion */

/*## class TopLevel::MyMixin */



#include "Aplicacion/implement/MyMixin.h"

AllocateMixin( MyMixin );

/* Initialization, finalization
 */

static
void
MyMixin_initialize(void)
{
	//Start of user code for MyMixin_initialize
	//TO DO
	//End of user code
}

static
void
MyMixin_finalize(void)
{
	//Start of user code for MyMixin_finalize
	//TO DO
	//End of user code
}


/* Construction, destruction
 */

static
void
MyMixin_constructor( MyMixin mymixin, MyMixinData self )
{

	//Start of user code for MyMixin_constructor
	//TO DO
	// Build up your MyMixinDataFields.
	// This method is called ones for every Object, and every field is zeroed at entry.
	//self->data = ?
	//End of user code
	
}

static
int
MyMixin_copy( MyMixin mymixin, MyMixinData self, const MyMixinData from )
{
	//Start of user code for MyMixin_copy
	return OOC_COPY_DEFAULT;
	//return OOC_COPY_DONE;
	//return OOC_NO_COPY;
	//End of user code
}

static
void
MyMixin_destructor( MyMixin mymixin, MyMixinData self )
{
	//Start of user code for MyMixin_destructor
	//TODO
	//End of user code
}


/* Method implementations
 */

static
void
MyMixin_myMixinMethod (Object carrier){
	//Start of user code for invalid_myMixinMethod
	//TODO
	//MyMixinData self = ooc_get_mixin_data( carrier, MyMixin );
	//End of user code
}


/* Populating the interface's virtual table
 */
static
void
MyMixin_populate( MyMixin mymixin )
{
	mymixin->myMixinMethod	=	MyMixin_myMixinMethod;
}


/**********************************************************************************
 * File Path: Aplicacion/MyMixin.c
 **********************************************************************************/
