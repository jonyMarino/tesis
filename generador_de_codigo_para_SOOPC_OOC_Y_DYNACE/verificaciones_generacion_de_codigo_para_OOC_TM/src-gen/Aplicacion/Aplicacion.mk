##################################################################################
 # Copyright: 
 # Project: RootElement
 # File: Aplicacion/Aplicacion.mk
 # Code Management Tool File Version: 
 # SDD Component: Aplicacion
 # Author: 
##################################################################################

###################################
# Directory Definition
###################################

APLICACION_DIR						 = $(SRC_DIR)Aplicacion

###################################
# Slave Sources
###################################
SUBDIRS							+= $(APLICACION_DIR)
SUBDIRS							+= $(BASE_DIR)
APLICACION_SRCS						 =	$(APLICACION_DIR)/GrandChild.c	\
	$(APLICACION_DIR)/Class1.c	\
	$(APLICACION_DIR)/Parent.c	\
	$(APLICACION_DIR)/Child.c	\
	$(APLICACION_DIR)/Countable.c	\
	$(APLICACION_DIR)/Serializable.c	\
													$(APLICACION_DIR)/Aplicacion.c
									


									
SRCS							+=	$(APLICACION_SRCS)

###################################
# Slave Objets
###################################

APLICACION_OBJS						 =	$(subst $(APLICACION_DIR),$(OBJECT_DIR),$(APLICACION_SRCS:.c=.o))
OBJS							+=	$(APLICACION_OBJS)



##################################################################################
 # File Path: Aplicacion.mk
##################################################################################
