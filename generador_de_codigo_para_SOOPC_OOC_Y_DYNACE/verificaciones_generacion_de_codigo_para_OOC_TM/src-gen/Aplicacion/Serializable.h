/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/Serializable.h
 * Code Management Tool File Version: 
 * SDD Component: Serializable
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Aplicacion/Serializable.h
 * \brief Serializable
 */

#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

/* Dependency with parent package */
#include "Aplicacion/Aplicacion.h"

/**********************************************************************************
 * Aplicacion/serializable.h
 **********************************************************************************/

/*## package Aplicacion */

/*! 
 * \package Serializable
 */

#include <ooc/ooc.h>


DeclareInterface( Serializable  )

	void (*serialize)(Object self, char * out);

EndOfInterface;


#endif

/**********************************************************************************
 * File Path: Aplicacion/Serializable.h
 **********************************************************************************/
