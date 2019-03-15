/*
 * MyInterface1.c
 *
 *  Created on: 3 de feb. de 2019
 *      Author: marino
 */

#include "my_interface1.h"


void my_interface1_method1 (MyInterface1 *self) {
    MYINTERFACE1_GET_IFACE(self)->method1(self);
}

void my_interface1_impl_method1 (MyInterface1 *self) {
    /* default to comparing pointers  */
	g_print("default response\n");
}

static void my_interface1_iface_init (MyInterface1Iface *iface) {
    iface->method1 = my_interface1_impl_method1;
}

GType my_interface1_get_type (void) {
    static GType type = 0;
    if (type) return type;

    static const GTypeInfo info = {
        sizeof (MyInterface1Iface),
        NULL,
        NULL,
        (GClassInitFunc) my_interface1_iface_init
    };

    type = g_type_register_static(
        G_TYPE_INTERFACE,
        "MyInterface1",
        &info,
        0);

    return type;
}
