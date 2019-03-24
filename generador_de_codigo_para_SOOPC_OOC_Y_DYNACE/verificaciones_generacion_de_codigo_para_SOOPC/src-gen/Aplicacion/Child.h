/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/Child.h
 * Code Management Tool File Version: 
 * SDD Component: Child
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Aplicacion/Child.h
 * \brief Child
 */

#ifndef Aplicacion_Child_H
#define Aplicacion_Child_H

/* Dependency with parent package */
#include "Aplicacion/Aplicacion.h"
#include "Aplicacion/Parent.h"


/**********************************************************************************
 * Aplicacion/Child.h
 **********************************************************************************/

/*## package Aplicacion */

/*! 
 * \package Child
 */

/*## class TopLevel::Child */







/*!
 * \brief Type definition of the class Child
 */
//Class Child V-Table
struct ChildVtbl;

//Class Child declaration
typedef struct {
	Parent super;
}Child;


//Class Child V-Table
typedef struct ChildVtbl{
	ParentVtbl superClass;
	char * (*getNameFollowedByClassName)(Child * self); 
}ChildVtbl;




void Child_ctor (Child * self, const char * name);
char * Child_getNameFollowedByClassName (Child * self);

void Child_vPrint_ (Parent * self);
char * Child_getNameFollowedByClassName_ (Child * self);


#endif

/**********************************************************************************
 * File Path: Aplicacion/Child.h
 **********************************************************************************/
