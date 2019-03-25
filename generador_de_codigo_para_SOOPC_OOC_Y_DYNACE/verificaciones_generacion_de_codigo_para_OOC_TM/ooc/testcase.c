/*
 * testcase.c
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


/* This is a TestCase class implementation file
 */

#include "testcase.h"
#include "implement/exception.h"

#ifdef OOC_HAS_UNIX_SIGNALS
#include <signal.h>
static void signal_handler( int signum );
#endif

#include <string.h>

#ifndef strlenROM
#define strlenROM(x) strlen(x)
#endif

/** @class TestCase
 *  @brief TestCase class - base class for unit testing.
 * 	@see testcase.h
 */

/** @file testcase.h 
 *  @brief TestCase class - base class for unit testing.
 * TestCase is a base class for unit testing. All of your Unit tests inherits TestCase.
 * The process to create a new unit test in your project:
 * -# Create a new test class with: @code $ ooc --new MyTest --template test @endcode
 * -# Override the necessary virtual methods
 * -# implement your test methods
 * -# create the test methods table
 * -# compile your test file as executable
 * (you can use the makefile template from ooc/template/unit folder)
 * -# run the test file
 * 
 */ 

/* Allocating the class description table and the vtable
 */

AllocateClass( TestCase, Base );

#ifndef OOC_NO_THREADS
static ooc_Mutex	printing;
#endif

/* Class virtual function prototypes
 */

static
void
_testcase_default_virtual( TestCase self )
{
	return;
}


/* Class initializing
 */

static
void
TestCase_initialize( Class this )
{
	TestCaseVtable vtab = & TestCaseVtableInstance;
	
	vtab->before_class	= 	_testcase_default_virtual;
	vtab->before		= 	_testcase_default_virtual;
	vtab->after			= 	_testcase_default_virtual;
	vtab->after_class	= 	_testcase_default_virtual;
	
	ooc_mutex_init( printing );

	ooc_init_class( Exception );

	#ifdef OOC_HAS_UNIX_SIGNALS
	ooc_init_class( SegmentationFault );
	ooc_init_class( ArithmeticFault );
	#endif
}

/* Class finalizing
 */

#ifndef OOC_NO_FINALIZE

static
void
TestCase_finalize( Class this )
{
	ooc_mutex_release( printing );
}
#endif

/* Constructor
 */

static
void
TestCase_constructor( TestCase self, const void * params )
{
	if(!ooc_isInitialized( TestCase )) {
		ooc_throw(exception_new(err_uninitialized));
	}
	
	chain_constructor( TestCase, self, NULL );

	self->methods = (ROM struct TestCaseMethod *) params;

#ifdef OOC_HAS_UNIX_SIGNALS
	signal( SIGSEGV, signal_handler );
	signal( SIGFPE, signal_handler );
#endif
	setbuf(stdout, NULL); /* Unbufferered stdout displays better */
}

/* Destructor
 */

static
void
TestCase_destructor( TestCase self, TestCaseVtable vtab )
{
}

/* Copy constuctor
 */

static
int
TestCase_copy( TestCase self, const TestCase from )
{
	/* makes the default object copying (bit-by-bit) */
	return OOC_COPY_DEFAULT;
}

/* Signal handler prototype
 */
 
#ifdef OOC_HAS_UNIX_SIGNALS
static void signal_handler( int signum );
#endif

/*  =====================================================
	Format strings - if not defined in the port headers already
 */

#ifndef _FMT_Failed_ssu

#define _FMT_Failed_ssu		"\tFailed: %s [%s : %u]\n"
#define _FMT_Func_ss		"%s::%s()"
#define _FMT_Func_dss		"[%d] %s::%s()"
#define _FMT_Func_dsss		"[%d] %s::%s.%s()"
#define _FMT_Name_dss		"[%d] %s::%s"
#define _FMT_Name_dsss		_FMT_Func_dsss
#define _FMT_Exc_sdd		"\tUnexpected exception: %s, code: %d, user code: %d\n"
#define _FMT_Exc_ssdd		"\n\tUnexpected exception %s in %s, code: %d, user code: %d\n"
#define _FMT_Failed_sdd		"Test case %s failed: %d/%d (methods run/failed)\n"

#endif

/*	=====================================================
	Class member functions
 */
 
static int current_test_failed;
static int current_method_fail_count;

/* Marks the current test method as failed.
 */
 
void
testcase_fail( ROM char * filename, int line, ROM char * message )
{
	current_test_failed = TRUE;
	
	ooc_lock( printing );

	if( current_method_fail_count++ == 0 )
		printf( "\n" );
		
	printf( _FMT_Failed_ssu, message ? message : "", filename, line );

	ooc_unlock( printing );
}

static ROM_ALLOC char before_class[] = "before_class";
static ROM_ALLOC char after_class[] = "after_class";

#ifdef OOC_NO_DYNAMIC_MEM
char print_buffer[PRINT_BUFFER_SIZE];
#endif


static
void
print_func_name( TestCase self, ROM char * func, const char * name, ROM char * suffix )
{
#ifndef OOC_NO_DYNAMIC_MEM
	int			buffer_length;
#endif
	int			display_length;
	static int	previous_display_length = 0;
	char *	volatile display_text = NULL;
	
	/* print_func_name() parameters are distinguished, because of some architectures make difference:
	 * 		func	a name that is stored in ROM
	 * 		name	a name that is stored in RAM
	 * The two parameters are mutually exclusive, at least one of them must be NULL!
	 */
	assert( ! ((func != NULL) && (name != NULL)) );

	try {
		ooc_lock( printing );
		
#ifndef OOC_NO_DYNAMIC_MEM
		buffer_length = 32 /*digit*/ + 1 /*point*/ + strlenROM( ooc_get_type((Object)self)->c.type.name ) + 3 /*double colon */ + 1 /*closing zero*/;
		if( func != NULL )
			buffer_length += strlenROM( func );
		if( name != NULL )
			buffer_length += strlen( name );
		if( suffix != NULL )
			buffer_length += strlenROM( suffix ) + 1;

		if( buffer_length < previous_display_length + 1 )
			buffer_length = previous_display_length + 1;
		
		display_text = ooc_malloc( buffer_length );
#else
		display_text = print_buffer;
#endif
		
		if( func == NULL && name == NULL )
			display_text[0] = '\0';
		else if( func == before_class || func == after_class )
			sprintf( display_text,  _FMT_Func_ss, ooc_get_type((Object)self)->c.type.name, func );
		else if( func != NULL && suffix == NULL )
			sprintf( display_text,  _FMT_Func_dss, self->run , ooc_get_type((Object)self)->c.type.name, func );
		else if( func != NULL && suffix != NULL )
			sprintf( display_text,  _FMT_Func_dsss, self->run , ooc_get_type((Object)self)->c.type.name, func, suffix );
		else if( name != NULL && suffix == NULL )
			sprintf( display_text,  _FMT_Name_dss, self->run , ooc_get_type((Object)self)->c.type.name, name );
		else /* if( name != NULL && suffix != NULL ) */
			sprintf( display_text,  _FMT_Name_dsss, self->run , ooc_get_type((Object)self)->c.type.name, name, suffix );
		
		display_length = strlen( display_text );
		if( display_length < previous_display_length ) {
			memset( &display_text[ display_length ], ' ', previous_display_length - display_length );
			display_text[ previous_display_length ] = '\0';
			}
	
		previous_display_length = strlen( display_text );
			
		printf( "%s\r", display_text );
	}
	finally {
#ifndef OOC_NO_DYNAMIC_MEM
		ooc_free( display_text );
#endif
		ooc_unlock( printing );
	}
	end_try;
}

static
void
testcase_run_before_class_recursive(TestCase self, Class type)
{
	TestCaseVtable vtab = (TestCaseVtable) type->c.vtable;
	
	if( ooc_class_has_parent( type ) )
		testcase_run_before_class_recursive( self, type->parent );
	
	vtab->before_class(self);
}

static
void
testcase_run_after_class_recursive(TestCase self, Class type)
{
	TestCaseVtable vtab = (TestCaseVtable) type->c.vtable;
	
	vtab->after_class( self );
	
	if( ooc_class_has_parent( type ) )
		testcase_run_after_class_recursive( self, type->parent );
}

static
void
testcase_run_before_recursive(TestCase self, Class type)
{
	TestCaseVtable vtab = (TestCaseVtable) type->c.vtable;
	
	if( ooc_class_has_parent( type ) )
		testcase_run_before_recursive( self, type->parent );
	
	vtab->before(self);
}

static
void
testcase_run_after_recursive(TestCase self, Class type)
{
	TestCaseVtable vtab = (TestCaseVtable) type->c.vtable;
	
	vtab->after( self );
	
	if( ooc_class_has_parent( type ) )
		testcase_run_after_recursive( self, type->parent );
}

static void
testcase_run_selected( TestCase self, ROM char * ROMname, const char * RAMname, test_method_type method )
{
	current_test_failed = FALSE;
	++self->run;
	current_method_fail_count = 0;

	try {
		print_func_name( self, ROMname, RAMname, "before" );
		testcase_run_before_recursive( self, ooc_get_type( (Object) self ) );

		print_func_name( self, ROMname, RAMname, NULL );
		method(self);
	}
	catch_any {
		ooc_lock( printing );

		if( ! current_test_failed )
			printf("\n");
		printf( _FMT_Exc_sdd,
						ooc_get_type((Object)exception)->c.type.name,
						exception_get_error_code(exception),
						exception_get_user_code(exception));
		current_test_failed = TRUE;
		ooc_unlock( printing );
	}
	end_try;

	if( current_test_failed )
		self->failed++;

	try {
		print_func_name( self, ROMname, RAMname, "after" );
		testcase_run_after_recursive( self, ooc_get_type( (Object) self ) );
	}
	catch_any {
		self->failed++;
		ooc_lock( printing );
		printf( _FMT_Exc_ssdd,
						ooc_get_type((Object)exception)->c.type.name,
						ooc_get_type((Object)self)->c.type.name,
						exception_get_error_code(exception),
						exception_get_user_code(exception));
		ooc_unlock( printing );
	}
	end_try;
}

/** Start the execution of a test series.
 * Prepares the TestCase for subsequent tests.\n
 * Actually calls the before_class() virtua methods recursively.
 * @param	self	The TestCase
 * @return 	0 if successful, non-zero if failed.
 * @note	Do not use, if test method table is used!
 */

int
testcase_run_before_class( TestCase self )
{

	if( ! ooc_isInstanceOf(self, TestCase) )
		ooc_throw( exception_new(err_bad_cast) );

	try {
		print_func_name( self, before_class, NULL, "" );
		testcase_run_before_class_recursive( self, ooc_get_type( (Object) self ) );
	}
	catch_any {
		self->failed++;
		ooc_lock( printing );
		printf( _FMT_Exc_ssdd,
						ooc_get_type((Object)exception)->c.type.name,
						ooc_get_type((Object)self)->c.type.name,
						exception_get_error_code(exception),
						exception_get_user_code(exception));
		ooc_unlock( printing );
	}
	end_try;

	return 	(self->failed == 0 ) ? 0 : 1;
}

/** Finishes the execution of a test series.
 * Close the TestCase for subsequent tests.\n
 * Actually calls the after_class() virtual methods recursively.
 * @param	self	The TestCase
 * @return 	0 if the whole test series was successful, non-zero if failed.
 * @note	Do not use, if test method table is used!
 */

int
testcase_run_after_class( TestCase self )
{
	if( ! ooc_isInstanceOf(self, TestCase) )
		ooc_throw( exception_new(err_bad_cast) );

	try {
		print_func_name( self, after_class, NULL, "" );
		testcase_run_after_class_recursive( self, ooc_get_type( (Object) self ) );

		print_func_name( self, NULL, NULL, NULL ); /* cleans the last function name */
	}
	catch_any {
		self->failed++;
		ooc_lock( printing );
		printf( _FMT_Exc_ssdd,
						ooc_get_type((Object)exception)->c.type.name,
						ooc_get_type((Object)self)->c.type.name,
						exception_get_error_code(exception),
						exception_get_user_code(exception));
		ooc_unlock( printing );
	}
	end_try;

	if( self->failed != 0 ) {
		ooc_lock( printing );
		printf( _FMT_Failed_sdd, ooc_get_type((Object)self)->c.type.name, self->run, self->failed );
		ooc_unlock( printing );
	}

	return 	(self->failed == 0 ) ? 0 : 1;
}

/** Run the whole TestCase.
 * If the testcase was constructed with a method order table then this function runs all methods defined in the table.\n
 * It also runs the before_class() end after_class() methods.\n
 * This is the convenient way of running test methods and suites for the most cases.\n
 * This is equvivalent with the following pseudo code:\n
@verbatim
		if( testcase_run_before_class(self) == 0)
			testcase_run_all_methods(self);
		return testcase_run_after_class(self);
@endverbatim
 * @param	self	The TestCase to be run. The method order table must exist!
 * @return			0 if the was no error, 1 if any error occurs
 */

int
testcase_run( TestCase self )
{
	if( ! ooc_isInstanceOf(self, TestCase) )
		ooc_throw( exception_new(err_bad_cast) );

	if( testcase_run_before_class(self) == 0)
	{
		ROM struct TestCaseMethod * method_table = self->methods;

		if( method_table != NULL )
			while( method_table->method )
			{
				testcase_run_selected( self, method_table->name, NULL, method_table->method );
				method_table++;
			};
	}
	return testcase_run_after_class(self);
}

/** Run a single test.
 * Runs a single test method with the given display name.
 * The testcase_run_before_class() function must be called before, and testcase_run_after_class() must be called
 * at the end.\n
 * The testcase_run_test() can be called any times between testcase_run_before_class() and testcase_run_after_class().\n
 * The before() and after() methods are called automatically.
 * @param	self	The test case
 * @param	name	The display name of the test
 * @param	method	The test function to invoke
 * @return			Nothing
 * @note	Do not use, if test method table is used!
 */

void
testcase_run_test( TestCase self, const char * name, test_method_type method )
{
	if( ! ooc_isInstanceOf(self, TestCase) )
		ooc_throw( exception_new(err_bad_cast) );

	testcase_run_selected( self, NULL, name, method );
}

#ifdef OOC_HAS_UNIX_SIGNALS

/* Segmentation fault exception.
*/

ClassMembers( SegmentationFault, Exception )
EndOfClassMembers;

Virtuals( SegmentationFault, Exception )
EndOfVirtuals;

AllocateClass( SegmentationFault, Exception );

static	void	SegmentationFault_initialize( Class this ) {}
#ifndef OOC_NO_FINALIZE
static	void	SegmentationFault_finalize( Class this ) {}
#endif

static	void	SegmentationFault_constructor( SegmentationFault self, const void * params )
{
	assert( ooc_isInitialized( SegmentationFault ) );
	
	chain_constructor( SegmentationFault, self, NULL );
}

static	void	SegmentationFault_destructor( SegmentationFault self, SegmentationFaultVtable vtab ) {}
static	int		SegmentationFault_copy( SegmentationFault self, const SegmentationFault from ) { return OOC_COPY_DEFAULT; }

/* Arithmetic fault exception.
*/

ClassMembers( ArithmeticFault, Exception )
EndOfClassMembers;

Virtuals( ArithmeticFault, Exception )
EndOfVirtuals;

AllocateClass( ArithmeticFault, Exception );

static	void	ArithmeticFault_initialize( Class this ) {}
#ifndef OOC_NO_FINALIZE
static	void	ArithmeticFault_finalize( Class this ) {}
#endif

static	void	ArithmeticFault_constructor( ArithmeticFault self, const void * params )
{
	assert( ooc_isInitialized( ArithmeticFault ) );
	
	chain_constructor( ArithmeticFault, self, NULL );
}

static	void	ArithmeticFault_destructor( ArithmeticFault self, ArithmeticFaultVtable vtab ) {}
static	int		ArithmeticFault_copy( ArithmeticFault self, const ArithmeticFault from ) { return OOC_COPY_DEFAULT; }

/* Unix Signal handler
 */
 
static
void
signal_handler( int signum )
{
	switch( signum ) {
		case SIGSEGV :	ooc_throw( (Exception) ooc_new( SegmentationFault, NULL ) );
		case SIGFPE	 :	ooc_throw( (Exception) ooc_new( ArithmeticFault, NULL ) );
		default 	 :	break;
	}
}

#endif /* OOC_HAS_UNIX_SIGNALS */


/** TestCase virtual functions.
 * These virtual functions run before and after your test methods. You can override them as needed. \n
 * The execution order of the virtual functions are: \n
	@verbatim
	For each instantiation of your test case:
	{
		Your testcase's parents' constructors
		Your testcase's constructor
		For each testcase_run( TestCase ):
		{
			Your test's parents' before_class() methods
			Your test's before_class() method
			For each test method in the test method table:
			{
				Your test's parents' before() methods
				Your test's  before() method
				Yor test method
				Your test's  after() method
				Your test's parents' after() methods
			}
			Your test's after_class() method
			Your test's parents' after_class() methods
		}
		Your testcase's destructor
		Your testcase's parents' destructors
	}
	@endverbatim
  */

/*@{*/

/** \struct TestCaseVtable_stru
 * \brief Virtual functions.
 */

/** \fn void (*TestCaseVtable_stru::before_class) ( TestCase testcase )
 * Prepares the testcase.
 * In this virtual function should the testcase be prepared for execution. \n
 * Implement this function according to your needs. \n
 * It runs only ones for each testcase_run() function call.
 * @param	The testcase.
  * \nosubgrouping
 */
 
/** \fn void (*TestCaseVtable_stru::before) ( TestCase testcase )
 * Prepares the test method.
 * In this virtual function should the test method be prepared for execution. \n
 * Implement this function according to your needs. \n
 * Runs before each test methods.
 * @param	The testcase.
 */
 
/** \fn void (*TestCaseVtable_stru::after) ( TestCase testcase )
 * Finishes the test method.
 * In this virtual function should the test method be finished. \n
 * Implement this function according to your needs: free, delete or release all resources
 * that were aquired in before(). \n
 * Runs after each test methods.
 * @param	The testcase.
 */
 
/** \fn void (*TestCaseVtable_stru::after_class) ( TestCase testcase )
 * Finishes the testcase.
 * In this virtual function should the testcase be finished. \n
 * Implement this function according to your needs: free, delete or release all resources
 * that were aquired in before_class().\n
 * It runs only ones for each testcase_run() function call.
 * @param	The testcase.
 */
 
/*@}*/
