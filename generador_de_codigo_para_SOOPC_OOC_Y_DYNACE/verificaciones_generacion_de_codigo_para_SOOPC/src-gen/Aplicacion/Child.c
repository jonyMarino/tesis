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






// Virtual Methods 
void Child_vPrint_ (Parent * self){
	//Start of user code for vPrint
	//TO DO
	//End of user code
}
char * Child_getNameFollowedByClassName_ (Child * self){
	//Start of user code for getNameFollowedByClassName
	char * className = "Child";
	const char * name = ((Parent*)self)->name;
	char * nameFollowedByClassName= malloc(strlen(className)+strlen(name)+1);
	sprintf(nameFollowedByClassName,"%s%s",name,className);
	return nameFollowedByClassName;
	//End of user code
}


// Final Methods 
void Child_ctor (Child * self, const char * name){
	static ChildVtbl const vtbl={
	{
		Child_vPrint_			},
		Child_getNameFollowedByClassName_	
	};

	//Start of user code for calling super constructor
	Parent_ctor ((Parent*)self, name);
	//End of user code
 	((Parent*)self) -> vptr = (ParentVtbl*)&vtbl; /* override the vptr */		
	//Start of user code for ctor
	//TO DO
	//End of user code
	
}


// Selectors    
char * Child_getNameFollowedByClassName (Child * self){
	return  (**(ChildVtbl**)self).getNameFollowedByClassName(self);
}


/**********************************************************************************
 * File Path: Aplicacion/Child.c
 **********************************************************************************/
