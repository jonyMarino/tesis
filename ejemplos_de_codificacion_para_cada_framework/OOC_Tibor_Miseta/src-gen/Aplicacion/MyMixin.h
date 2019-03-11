/**********************************************************************************
 * Copyright: 2019 All rights reserved.
 * Project: RootElement
 * File: Aplicacion/MyMixin.h
 * Code Management Tool File Version: 1.0.0
 * Date: $Date$
 * SDD Component: MyMixin
 * Language: C
 * Author: marino
 * Last Change: $Id$
 **********************************************************************************/

/*!
 * \file Aplicacion/MyMixin.h
 * \brief MyMixin
 */

#ifndef MYMIXIN_H
#define MYMIXIN_H

/* Dependency with parent package */
#include "Aplicacion/Aplicacion.h"

/**********************************************************************************
 * Aplicacion/mymixin.h
 **********************************************************************************/

/*## package Aplicacion */

/*! 
 * \package MyMixin
 */

#include <ooc/ooc.h>


DeclareMixinInterface( MyMixin  )

	void (*myMixinMethod)(Object self);

EndOfInterface;


#endif

/**********************************************************************************
 * File Path: Aplicacion/MyMixin.h
 **********************************************************************************/
