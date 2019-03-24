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






// Virtual Methods 
char * GrandChild_getNameFollowedByClassName_ (Child * self){
	//Start of user code for getNameFollowedByClassName
	char * className = "GrandChild";
	const char * name = ((Parent*)self)->name;
	char * nameFollowedByClassName= malloc(strlen(className)+strlen(name)+1);
	sprintf(nameFollowedByClassName,"%s%s",name,className);
	return nameFollowedByClassName;
	//End of user code
}


// Final Methods 
void GrandChild_ctor (GrandChild * self, const char * name){
	static GrandChildVtbl const vtbl={
	{{
		Child_vPrint_			},
		GrandChild_getNameFollowedByClassName_			},
	
	};

	//Start of user code for calling super constructor
	Child_ctor ((Child*)self, name);
	//End of user code
 	((Parent*)self) -> vptr = (ParentVtbl*)&vtbl; /* override the vptr */		
	//Start of user code for ctor
	//TO DO
	//End of user code
	
}
void GrandChild_foo (GrandChild * self){

	//Start of user code for foo
	//TO DO
	//End of user code
	
}


// Selectors    


/**********************************************************************************
 * File Path: Aplicacion/GrandChild.c
 **********************************************************************************/
