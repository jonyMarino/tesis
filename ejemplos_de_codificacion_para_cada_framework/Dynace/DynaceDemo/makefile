#  Makefile designed for use by the GNU MAKE utility and		-*-Makefile-*-
#  GCC

ifdef WINE
WINEINCPATH = /usr/include/wine
CC = winegcc -m32
GCC = gcc -m32
else
CC = gcc
GCC = $(CC)
endif

ifdef TCC # target compiler
CC = $(TCC)
GCC = $(TCC)
endif

.SUFFIXES: .d


DYNACE_PATH = /home/marino/Dynace

BINDIR = $(DYNACE_PATH)/bin
LIBDIR = $(DYNACE_PATH)/lib
INCDIR = $(DYNACE_PATH)/include


DEBUG = -g
#DEBUG = -O

ifdef WINE
CFLAGS = -I$(INCDIR) -I$(WINEINCPATH)/windows -D_WINDOWS -D_WIN32 -D__WINE__
GFLAGS = -I$(INCDIR) -I$(WINEINCPATH)/windows -D_WINDOWS -D_WIN32 -D__WINE__ -O -w
else
CFLAGS = -I. -I$(INCDIR) -I./src-gen 
GFLAGS = -I. -I$(INCDIR) -I./src-gen -O -w
endif

TARGET = main
SRC-DIR = src-gen/Aplicacion

CLASSES =  $(SRC-DIR)/Parent.d $(SRC-DIR)/Child.d $(SRC-DIR)/GrandChildren.d $(SRC-DIR)/GrandGrandChildren.d
CFILES = main.c

OBJS = $(CFILES:.c=.o) $(CLASSES:.d=.o)


.SECONDARY: $(CLASSES:.d=.c)

.d.c:
	$(BINDIR)/dpp -g -p $<

.c.o:
	$(CC) -o $@ $(CFLAGS) $(DEBUG) -c $<


$(TARGET) : generics.1 generics.h generics.o $(OBJS)
	$(CC) $(DEBUG) -o $(TARGET) $(OBJS) generics.o $(LIBDIR)/dynace.a -lm
ifdef WINE
	mv $(TARGET).exe $(TARGET)
endif

generics.h : $(CLASSES)
	$(BINDIR)/dpp -g -t -h -p $?

generics.c : generics.h
	$(BINDIR)/dpp -g -c

# generics.c must be compiled with gcc and not winegcc
generics.o : generics.c 
	$(GCC) $(GFLAGS) -c $<

generics.1 newgens:
	$(BINDIR)/dpp -g $(INCDIR)/generics.h -p $(CLASSES) -h
	touch generics.1


clean:
	-rm -f *.obj *.exe generics.* $(TARGET) $(TARGET).exe.so *.o $(CLASSES:.d=.c) *~

