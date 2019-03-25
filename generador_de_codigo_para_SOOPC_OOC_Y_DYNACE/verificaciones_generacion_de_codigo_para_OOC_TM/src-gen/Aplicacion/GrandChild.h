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

#ifndef GRANDCHILD_H
#define GRANDCHILD_H

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

DeclareClass( GrandChild, Child );




GrandChild grandchild_new( const char * name );

void grandchild_foo (GrandChild self);


/* Virtual function definitions
 */


Virtuals( GrandChild, Child );




EndOfVirtuals;







#endif

/**********************************************************************************
 * File Path: Aplicacion/grandchild.h
 **********************************************************************************/




