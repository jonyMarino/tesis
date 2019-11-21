##################################################################################
 # Copyright: 2019 All rights reserved.
 # Project: RootElement
 # File: Aplicacion/Aplicacion.mk
 # Code Management Tool File Version: 1.0.0
 # Date: $Date$
 # SDD Component: Aplicacion
 # Author: marino
 # Last Change: $Id$
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
APLICACION_SRCS						 =	$(APLICACION_DIR)/Parent.c	\
	$(APLICACION_DIR)/GrandChildren.c	\
	$(APLICACION_DIR)/<stdio.h>.c	\
	$(APLICACION_DIR)/GrandGrandChildren.c	\
	$(APLICACION_DIR)/Child.c	\
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
