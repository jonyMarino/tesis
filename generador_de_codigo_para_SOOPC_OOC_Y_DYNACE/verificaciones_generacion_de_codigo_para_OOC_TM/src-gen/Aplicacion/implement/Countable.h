/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/implement/Countable.h
 * Code Management Tool File Version: 
 * SDD Component: Countable
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Aplicacion/implement/Countable.h
 * \brief Countable
 */

/**********************************************************************************
 * Aplicacion/implement/Countable.h
 **********************************************************************************/
/*## package Aplicacion */


#ifndef IMPLEMENT_COUNTABLE_H
#define IMPLEMENT_COUNTABLE_H

#ifndef COUNTABLE_H
#error Do #include "countable.h" right before doing #include "implement/countable.h"
#endif

/*! 
 * \package Countable
 */

MixinMembers( Countable )
	unsigned int instanceNum;
EndOfMixinMembers;

#endif

