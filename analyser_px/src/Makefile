################################################################################
## 

##---------------------------------------------------
## NOTE: keep the "/" at the end of all directory names
##
BINDIR   = ../bin/
INCLUDEDIR = ../include/
INCLUDEPATH  = -I/usr/include -I$(INCLUDEDIR)
CC	 = cc
CXX      = g++
#CXXFLAGS = -pipe -Wall -g3 -W -O2 -D_REENTRANT 
CXXFLAGS = -pipe -Wall -g3 -O0 -D_REENTRANT 
#CXXFLAGS = -pipe -W -O2 
#LINK     = g++
LINK     = cc
LFLAGS   = -g3
LIBS     = -lpcap -lpthread
AR       = ar cqs
RANLIB   = 

## commands
QMAKE    = qmake
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY)
COPY_DIR = $(COPY) -r
INSTALL_FILE= $(COPY_FILE)
INSTALL_DIR = $(COPY_DIR)
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p

####### Output directory

OBJECTS_DIR = ./

####### Files

HEADERS = cap.h classifier.h hashtab.h analyserpxAggreg.h analyserpxFile.h analyserpxFlow.h analyserpxTypes.h
ANALYSERPXCAP = analyserpx_cap
ANALYSERPXREAD = analyserpx_read
TARGET   = $(BINDIR)$(ANALYSERPXREAD) $(BINDIR)$(ANALYSERPXCAP)
SOURCES = \
	cap.c \
	classifier.c \
	hashtab.c \
	readBinaryFlow.c \
	analyserpxAggreg.c \
	analyserpxCaptureMain.c \
	analyserpxFile.c \
	analyserpxFlow.c \
	expressions.c
OBJ_ANALYSERPXCAP = \
	cap.o \
	classifier.o \
	hashtab.o \
	analyserpxAggreg.o \
	analyserpxCaptureMain.o \
	analyserpxFile.o \
	analyserpxFlow.o \
	expressions.o
OBJ_ANALYSERPXREAD = \
	cap.o \
	readBinaryFlow.o \
	analyserpxFile.o \
	analyserpxFlow.o 

all: $(TARGET)

####### Implicit rules
.SUFFIXES: .c .o .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDEPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDEPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDEPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDEPATH) -o $@ $<

.c.o:
	$(CC) -c $(CXXFLAGS) $(INCLUDEPATH) -o $@ $<

####### Build rules

OBJECTS = $(OBJ_ANALYSERPXCAP) $(OBJ_ANALYSERPXREAD)

$(BINDIR)$(ANALYSERPXCAP): $(OBJ_ANALYSERPXCAP)
	$(CHK_DIR_EXISTS) $(BINDIR) || $(MKDIR) $(BINDIR)
	$(LINK) $(LFLAGS) -o $(BINDIR)$(ANALYSERPXCAP) $(OBJ_ANALYSERPXCAP) $(LIBS)

$(BINDIR)$(ANALYSERPXREAD): $(OBJ_ANALYSERPXREAD)
	$(CHK_DIR_EXISTS) $(BINDIR) || $(MKDIR) $(BINDIR)
	$(LINK) $(LFLAGS) -o $(BINDIR)$(ANALYSERPXREAD) $(OBJ_ANALYSERPXREAD) $(LIBS)

clean: 
	-$(DEL_FILE) $(OBJECTS) $(TARGET)
	-$(DEL_FILE) *~ core *.core

####### Compile

analyserpxFlow.c: $(INCLUDEDIR)analyserpxTypes.h $(INCLUDEDIR)analyserpxFile.h $(INCLUDEDIR)analyserpxFlow.h

analyserpxFile.c: $(INCLUDEDIR)analyserpxFile.h

analyserpxCaptureMain.c: $(INCLUDEDIR)cap.h $(INCLUDEDIR)analyserpxAggreg.h

analyserpxAgreg.c: $(INCLUDEDIR)analyserpxAggreg.h $(INCLUDEDIR)cap.h $(INCLUDEDIR)analyserpxFlow.h $(INCLUDEDIR)analyserpxFile.h $(INCLUDEDIR)classifier.h

hashtab.c: $(INCLUDEDIR)hashtab.h

classifier.c: $(INCLUDEDIR)classifier.h

cap.c: $(INCLUDEDIR)cap.h

readBinaryFlow.c: $(INCLUDEDIR)analyserpxTypes.h $(INCLUDEDIR)analyserpxFile.h $(INCLUDEDIR)analyserpxFlow.h

expressions.c: $(INCLUDEDIR)expressions.h
