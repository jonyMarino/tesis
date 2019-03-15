/**********************************************************************************
 * Copyright: 2019 All rights reserved.
 * Project: RootElement
 * File: Aplicacion/Child.c
 * Code Management Tool File Version: 1.0.0
 * Date: $Date$
 * SDD Component: Child
 * Language: C
 * Author: marino
 * Last Change: $Id$
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






// Virtual Methods 
void Child_metodo_ (Parent * self){
	//Start of user code for metodo
	//TO DO
	//End of user code
}


// Final Methods 
void Child_ctor (Child * self){
	static ChildVtbl const vtbl={
	{
		Child_metodo_			},
	
	};

	//Start of user code for calling super constructor
	Parent_ctor ((Parent*)self);
	//End of user code
 	((Parent*)self) -> vptr = (ParentVtbl*)&vtbl; /* override the vptr */		
	//Start of user code for ctor
	//TO DO
	//End of user code
	
}


// Selectors    


/**********************************************************************************
 * File Path: Aplicacion/Child.c
 **********************************************************************************/
