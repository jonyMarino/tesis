/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/GrandChild.h
 * Code Management Tool File Version: 
 * SDD Component: GrandChild
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Aplicacion/GrandChild.h
 * \brief GrandChild
 */

#ifndef Aplicacion_GrandChild_H
#define Aplicacion_GrandChild_H

/* Dependency with parent package */
#include "Aplicacion/Aplicacion.h"
#include "Aplicacion/Child.h"


/**********************************************************************************
 * Aplicacion/GrandChild.h
 **********************************************************************************/

/*## package Aplicacion */

/*! 
 * \package GrandChild
 */

/*## class TopLevel::GrandChild */







/*!
 * \brief Type definition of the class GrandChild
 */
//Class GrandChild V-Table
struct GrandChildVtbl;

//Class GrandChild declaration
typedef struct {
	Child super;
}GrandChild;


//Class GrandChild V-Table
typedef struct GrandChildVtbl{
	ChildVtbl superClass;
}GrandChildVtbl;




void GrandChild_ctor (GrandChild * self, const char * name);
void GrandChild_foo (GrandChild * self);

char * GrandChild_getNameFollowedByClassName_ (Child * self);


#endif

/**********************************************************************************
 * File Path: Aplicacion/GrandChild.h
 **********************************************************************************/
