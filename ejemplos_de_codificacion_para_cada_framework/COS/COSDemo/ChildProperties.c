/*
 * attribute.c
 *
 *  Created on: 18 de feb. de 2019
 *      Author: marino
 */


#include "Child.h"
#include "value.h"
#include <cos/Number.h>
#include <cos/gen/value.h>


static OBJ int2OBJ(int val) { // no receiver: cannot be a method
return  aInt(val); // boxing
}


defproperty(Child, (attribute)value,int2OBJ,gint);



