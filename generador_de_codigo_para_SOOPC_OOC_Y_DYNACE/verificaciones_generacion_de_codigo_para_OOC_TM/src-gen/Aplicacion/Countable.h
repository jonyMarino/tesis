/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/Countable.h
 * Code Management Tool File Version: 
 * SDD Component: Countable
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Aplicacion/Countable.h
 * \brief Countable
 */

#ifndef COUNTABLE_H
#define COUNTABLE_H

/* Dependency with parent package */
#include "Aplicacion/Aplicacion.h"

/**********************************************************************************
 * Aplicacion/countable.h
 **********************************************************************************/

/*## package Aplicacion */

/*! 
 * \package Countable
 */

#include <ooc/ooc.h>


DeclareMixinInterface( Countable  )

	unsigned int (*getInstanceNum)(Object self);

EndOfInterface;


#endif

/**********************************************************************************
 * File Path: Aplicacion/Countable.h
 **********************************************************************************/
