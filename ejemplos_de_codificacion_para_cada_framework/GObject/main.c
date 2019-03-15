#include <stdio.h>
#include <glib-object.h>
#include <glib.h>
#include "child.h"
#include "my_interface1.h"


int main(int argc, char ** argv){
	Child * p=g_object_new(TYPE_CHILD,NULL);
    child_method(p);
    g_signal_emit_by_name(p, "signal1");
    child_method(p);
    my_interface1_method1((MyInterface1*)p);
    g_print("...\n");
    return 0;

}
