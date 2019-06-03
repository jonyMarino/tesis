/*
 * test_gen_parent.c
 *
 *  Created on: 17 de may. de 2018
 *      Author: marino
 */


/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/

//-- unity: unit test framework
#include "unity.h"

#include <stdlib.h>
#include "Aplicacion/Parent.h"
#include "Aplicacion/Child.h"

//-- module being tested
#include "Aplicacion/GrandChild.h"


#include "Aplicacion/Countable.h"
#include "Aplicacion/Serializable.h"
#include "ooc.h"
#include "exception.h"




/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
GrandChild aGrandChild;
/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/


/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/

void setUp(void)
{
	aGrandChild = grandchild_new("Simon");
}

void tearDown(void)
{
	ooc_delete((Object)aGrandChild);
}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/

void test_grandchild_redefinicion(void)
{

    char * str = GrandChildVirtual(aGrandChild)->Child.getNameFollowedByClassName((Child)aGrandChild);
	TEST_ASSERT_EQUAL_STRING("SimonGrandChild",str);

}


