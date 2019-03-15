/**********************************************************************************
 * Copyright: 2019 All rights reserved.
 * Project: RootElement
 * File: Aplicacion/Child.h
 * Code Management Tool File Version: 1.0.0
 * Date: $Date$
 * SDD Component: Child
 * Language: C
 * Author: marino
 * Last Change: $Id$
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
}ChildVtbl;




void Child_ctor (Child * self);

void Child_metodo_ (Parent * self);


#endif

/**********************************************************************************
 * File Path: Aplicacion/Child.h
 **********************************************************************************/
