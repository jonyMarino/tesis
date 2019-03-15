#include <glib-object.h>
#include "child.h"

#include "my_interface1.h"

enum {
    PROP_0,
    PROP_ATTR
};

enum {
  SIGNAL1,
  LAST_SIGNAL
};

typedef struct _ChildPrivate ChildPrivate;

struct _ChildPrivate {
	int privateAttr;
};

static guint child_signals[LAST_SIGNAL] = {0};

/* virtual print method that calls whatever is in the classes vtable  */
void child_method (Child *self) {
    CHILD_GET_CLASS(self)->method(self);
}

static void child_method_impl (Child *self) {
    g_print("public attribute: %d\n, private attribute", self->publicAttr);
}

static void child_method1_impl (Child *self) {
    g_print("child response!\n");
}

static void child_signal1_process (Child *self) {
    g_object_set(self, "attr", 0, NULL);
}

static void child_get_property (GObject    *obj,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec) {
    Child *child = CHILD(obj);

    switch (prop_id) {
    case PROP_ATTR:
        g_value_set_int(value, child->publicAttr);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
        break;
    }
}

static void child_set_property (GObject      *obj,
                                guint         prop_id,
                                const GValue *value,
                                GParamSpec   *pspec) {
    Child *child = CHILD(obj);

    switch (prop_id) {
    case PROP_ATTR: {
        gint new_attr = g_value_get_int(value);
        child->publicAttr = new_attr;
        break;
    }
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
        break;
    }
}

static void child_class_init (ChildClass *cls) {
    GObjectClass *g_object_class = G_OBJECT_CLASS(cls);
    GParamSpec *attr_param;

    g_type_class_add_private (cls, sizeof (ChildPrivate));


    g_object_class->get_property = child_get_property;
    g_object_class->set_property = child_set_property;

    cls->signal1Process = child_signal1_process;
    cls->method = child_method_impl;

    attr_param = g_param_spec_int(
        "attr", "attr", "attribute of child",
        INT_MIN, INT_MAX,
        0,
        G_PARAM_READWRITE);

    g_object_class_install_property(
        g_object_class,
        PROP_ATTR,
        attr_param);


    child_signals[SIGNAL1] = g_signal_new(
        "signal1",                               /* signal_name */
        TYPE_CHILD,                            /* itype */
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED, /* signal_flags */
        G_STRUCT_OFFSET(ChildClass, signal1Process),    /* class_offset */
        NULL,                                  /* accumulator */
        NULL,                                  /* accu_data */
        g_cclosure_marshal_VOID__VOID,         /* c_marshaller */
        G_TYPE_NONE,                           /* return_type */
        0);                                    /* n_params */
}

static void child_init_my_interface1(MyInterface1Iface* iface, gpointer iface_data) {
    iface->method1 = (void (*)(MyInterface1 *instance))child_method1_impl;
}

GType child_get_type (void) {
    static GType child_type = 0;

    if (!child_type) {
        static const GTypeInfo child_info = {
            sizeof (ChildClass),                /* class_size */
            NULL,                               /* base_init */
            NULL,                               /* base_finalize */
            (GClassInitFunc) child_class_init,  /* class_init */
            NULL,                               /* class_finalize */
            NULL,                               /* class_data */
            sizeof (Child),                     /* instance_size */
            0,                                  /* n_preallocs */
            NULL,                               /* instance_init */
            NULL                                /* value_table */
        };

        child_type = g_type_register_static(
            G_TYPE_OBJECT, /* parent_type */
            "Child",       /* type_name */
            &child_info,   /* info */
            0);            /* flags */

        /* add interface */
		GInterfaceInfo interface_info_my_interface1 = {
			(GInterfaceInitFunc)child_init_my_interface1, /* interface_init */
			NULL,   /* interface_finalize */
			NULL,   /* interface_data */
		};
		g_type_add_interface_static(child_type, TYPE_MYINTERFACE1, &interface_info_my_interface1);

    }

    return child_type;
}

