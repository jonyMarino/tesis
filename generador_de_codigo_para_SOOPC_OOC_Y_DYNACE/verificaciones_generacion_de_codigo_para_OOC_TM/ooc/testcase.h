/*
 * testcase.h
 * 
 * Copyright (c) 2011, old_fashioned. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 */


#ifndef TESTCASE_H
#define TESTCASE_H

#include <stdio.h>

#include "exception.h"

DeclareClass( TestCase, Base );

typedef void (*test_method_type)(TestCase);

/** @name Test method definitions.
 * Components defining test methods and execution of them.
 */

/*@{*/
 
/** Test method order table.
 * Table storing the test methods' names and entry points. Must be defined in constant (e.g. @c ROM) memory area.
 * Fill the table with the TEST macro. This table must be the constructor parameter of your TestCase class. 
 * The table must end with a @c NULL pair. \n
 * Use of the table: \n
 * @code
		ROM_ALLOC
		struct TestCaseMethod methods[] =
		{
			TEST(my_first_test_method),
			TEST(my_second_test_method),
			
			{NULL, NULL}
		};
 * @endcode
 * In your main code create your testcase like:
 * @code
		MyTest mytest;
	
		ooc_init_class( MyTest );
		mytest = ooc_new( MyTest, &methods );
 * @endcode
 * @see TEST
 * @nosubgrouping 
  * @hideinitializer
 */
 
struct TestCaseMethod
{
	ROM char *			name;
	test_method_type	method;
};

/** A test method order table entry.
 * This macro places a test method entry point into the test method order table. The test methods will be executed
 * in the order they apper in the table.
 * @param	name	The name of the test method.
 * @see TestCaseMethod
 * @hideinitializer
 */

#define TEST(name) {#name, (test_method_type)name}

/*@}*/

ClassMembers( TestCase, Base )
	ROM struct TestCaseMethod	*	methods;
	int								failed;
	int								run;
EndOfClassMembers;


Virtuals( TestCase, Base )

	void	(* before_class)  	( TestCase );
	void	(* before)  		( TestCase );
	void	(* after)  			( TestCase );
	void	(* after_class)  	( TestCase );

EndOfVirtuals;

 

/* Methods
 */
 
void 	testcase_fail( ROM char * filename, int line, ROM char * message );

int 	testcase_run( TestCase );

int		testcase_run_before_class( TestCase );
void 	testcase_run_test( TestCase, const char *, test_method_type );
int		testcase_run_after_class( TestCase );

/** @name TestCase assertions.
 * These macros can be used in the test methods and in @c before(), @c after(), @c before_class(), @c after_class() methods.
 * If the assertion fails, the unit test run will report a fail message indicating the source file name and 
 * the line number in the source file. The test run will continue with the next statement.
  */

/*@{*/

#define fail()							testcase_fail(__FILE__, __LINE__, NULL)						/**< Unconditional fail. Reports a failed status and continues. @hideinitializer */
#define assertTrue(expr)				if(!(expr)) testcase_fail(__FILE__, __LINE__, NULL)			/**< Fail if not TRUE. Reports a failed status if not TRUE and continues. @hideinitializer */
#define assertFalse(expr)				if(expr) testcase_fail(__FILE__, __LINE__, NULL)			/**< Fail if not FALSE. Reports a failed status if not FALSE and continues. @hideinitializer */
#define assertNull(expr)				if((expr)!=NULL) testcase_fail(__FILE__, __LINE__, NULL)	/**< Fail if not NULL. Reports a failed status if not NULL and continues. @hideinitializer */
#define assertNotNull(expr)				if((expr)==NULL) testcase_fail(__FILE__, __LINE__, NULL)	/**< Fail if NULL. Reports a failed status if NULL and continues. @hideinitializer */
#define assertZero(expr)				if((expr)!=0) testcase_fail(__FILE__, __LINE__, NULL)		/**< Fail if not 0. Reports a failed status if not 0 and continues. @hideinitializer */
#define assertNotZero(expr)				if((expr)==0) testcase_fail(__FILE__, __LINE__, NULL)		/**< Fail if 0L. Reports a failed status if 0 and continues. @hideinitializer */

#define failMsg(msg)					testcase_fail(__FILE__, __LINE__, msg)						/**< Unconditional fail with a specific message.
																										 Reports a failed status with the message and continues.
																										 @note The message must be a @c char* and will not be freed.
																										 @hideinitializer */
#define assertTrueMsg(expr, msg)		if(!(expr)) testcase_fail(__FILE__, __LINE__, msg)			/**< Fail if not TRUE with a specific message.
																										 Reports a failed status with the message if not TRUE and continues.
																										 @note The message must be a @c char* and will not be freed.
																										 @hideinitializer */
#define assertFalseMsg(expr, msg)		if(expr) testcase_fail(__FILE__, __LINE__, msg)				/**< Fail if not FALSE with a specific message.
																										 Reports a failed status with the message if not FALSE and continues.
																										 @note The message must be a @c char* and will not be freed.
																										 @hideinitializer */
#define assertNullMsg(expr, msg)		if((expr)!=NULL) testcase_fail(__FILE__, __LINE__, msg)		/**< Fail if not NULL with a specific message.
																										 Reports a failed status with the message if not NULL and continues.
																										 @note The message must be a @c char* and will not be freed.
																										 @hideinitializer */
#define assertNotNullMsg(expr, msg)		if((expr)==NULL) testcase_fail(__FILE__, __LINE__, msg)		/**< Fail if NULL with a specific message.
																										 Reports a failed status with the message if NULL and continues.
																										 @note The message must be a @c char* and will not be freed.
																										 @hideinitializer */
#define assertZeroMsg(expr, msg)		if((expr)!=0) testcase_fail(__FILE__, __LINE__, msg)		/**< Fail if not 0 with a specific message.
																										 Reports a failed status with the message if not 0 and continues.
																										 @note The message must be a @c char* and will not be freed.
																										 @hideinitializer */
#define assertNotZeroMsg(expr, msg)		if((expr)==0) testcase_fail(__FILE__, __LINE__, msg)		/**< Fail if 0 with a specific message.
																										 Reports a failed status with the message if 0 and continues.
																										 @note The message must be a @c char* and will not be freed.
																										 @hideinitializer */

/*@}*/

/* Exceptions
 */

#ifdef OOC_HAS_UNIX_SIGNALS

/** Segmentation fault exception.
 * SegmentationFault exception is thrown in your testcase if a SIGSEGV unix signal has been arised
 * (e.g. dereferencing a NULL pointer or writing beyond memory borders).
 * TestCase cathes this unix signal and converts it to an ooc Exception, so you can catch and test
 * it in your test methods, or simply let it be reported as a test fail. SegmentationFault is a subclass for Exception.
 * @note Available only on unix-like systems.
 * @hideinitializer
 */
DeclareClass( SegmentationFault, Exception );


/** Arithmetic fault exception.
 * ArithmeticFault exception is thrown in your testcase if a SIGFPE unix signal has been arised (e.g. division by zero).
 * TestCase cathes this unix signal and converts it to an ooc Exception, so you can catch and test
 * it in your test methods, or simply let it be reported as a test fail. ArithmeticFault is a subclass for Exception.
 * @note Available only on unix-like systems.
 * @hideinitializer
 */
DeclareClass( ArithmeticFault, Exception );

#endif /* OOC_HAS_UNIX_SIGNALS */

#ifdef OOC_NO_DYNAMIC_MEM
#define PRINT_BUFFER_SIZE 64
#endif

#ifndef TESTCASE_MAIN
#define TESTCASE_MAIN 	int main( int argc, char * argv[] )
#endif

#endif  /* TESTCASE_H */
