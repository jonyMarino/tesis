/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/Parent.h
 * Code Management Tool File Version: 
 * SDD Component: Parent
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Aplicacion/Parent.h
 * \brief Parent
 */

#ifndef Aplicacion_Parent_H
#define Aplicacion_Parent_H

/* Dependency with parent package */
#include "Aplicacion/Aplicacion.h"


/**********************************************************************************
 * Aplicacion/Parent.h
 **********************************************************************************/

/*## package Aplicacion */

/*! 
 * \package Parent
 * \brief This is the first class in this class hierarchy
 */

/*## class TopLevel::Parent */







/*!
 * \brief Type definition of the class Parent
 */
//Class Parent V-Table
struct ParentVtbl;

//Class Parent declaration
typedef struct {
	struct ParentVtbl const *vptr;
	const char * name;
}Parent;


//Class Parent V-Table
typedef struct ParentVtbl{
	void (*vPrint)(Parent * self); 
}ParentVtbl;




void Parent_vPrint (Parent * self);
void Parent_ctor (Parent * self, const char * name);

void Parent_vPrint_ (Parent * self);


#endif

/**********************************************************************************
 * File Path: Aplicacion/Parent.h
 **********************************************************************************/
