/* Template for an INTERFACE implementation
   - replace interface_example by the interface name
   - add default interface_example methods implementation
   - add default interface_example methods initialization
   - remove this comment
 */
#include "interface_example.h"

#define TYPE      struct interface_example
#define INTERFACE struct interface_example_interface

/* put INTERFACE default methods implementation here, if any */
static void method2(TYPE*arg){}

INTERFACE interface_example_interface=
 {method2 }
;
