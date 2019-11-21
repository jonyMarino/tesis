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
#include <assert.h>




/**********************************************************************************
 * Aplicacion/Parent.c
 **********************************************************************************/
/*## package Aplicacion */

/*## class TopLevel::Parent */






// Virtual Methods 
void Parent_vPrint_ (Parent * self){
	assert(0); /* purely-virtual function should never be called */
}


// Final Methods 
void Parent_ctor (Parent * self, const char * name){
	static ParentVtbl const vtbl={
	
		Parent_vPrint_	
	};

	//Start of user code for calling super constructor
	//End of user code
 	((Parent*)self) -> vptr = (ParentVtbl*)&vtbl; /* override the vptr */		
	//Start of user code for ctor
	self->name = name;
	//End of user code
	
}


// Selectors    
void Parent_vPrint (Parent * self){
	 (**(ParentVtbl**)self).vPrint(self);
}


/**********************************************************************************
 * File Path: Aplicacion/Parent.c
 **********************************************************************************/
