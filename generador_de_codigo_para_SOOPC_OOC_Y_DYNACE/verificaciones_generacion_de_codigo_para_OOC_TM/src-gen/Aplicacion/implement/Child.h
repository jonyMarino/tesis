/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/implement/Child.h
 * Code Management Tool File Version: 
 * SDD Component: Child
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Aplicacion/implement/Child.h
 * \brief Child
 */

/**********************************************************************************
 * Aplicacion/implement/Child.h
 **********************************************************************************/
/*## package Aplicacion */


#ifndef IMPLEMENT_CHILD_H
#define IMPLEMENT_CHILD_H

#ifndef CHILD_H
#error Do #include "child.h" right before doing #include "implement/child.h"
#endif


#include "Aplicacion/implement/Parent.h"


/*! 
 * \package Child
 */

ClassMembers( Child , Parent )
	unsigned int aNumber;
EndOfClassMembers;



#endif

