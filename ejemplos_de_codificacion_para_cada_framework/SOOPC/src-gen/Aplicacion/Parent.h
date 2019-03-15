/**********************************************************************************
 * Copyright: 2019 All rights reserved.
 * Project: RootElement
 * File: Aplicacion/Parent.h
 * Code Management Tool File Version: 1.0.0
 * Date: $Date$
 * SDD Component: Parent
 * Language: C
 * Author: marino
 * Last Change: $Id$
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
}Parent;


//Class Parent V-Table
typedef struct ParentVtbl{
	void (*metodo)(Parent * self); 
}ParentVtbl;




void Parent_metodo (Parent * self);
void Parent_ctor (Parent * self);

void Parent_metodo_ (Parent * self);


#endif

/**********************************************************************************
 * File Path: Aplicacion/Parent.h
 **********************************************************************************/
