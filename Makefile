#
# Created by gmakemake (Ubuntu Jul 25 2014) on Sat Apr 29 20:02:54 2017
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

BASE = /home/course/csci453
ARCHVER = arch2-5a
CXX = g++
CCFLAGS = -g -I$(BASE)/include/$(ARCHVER)
CXXFLAGS = $(CCFLAGS)
LIBFLAGS = -g -L$(BASE)/lib/$(SYS_TYPE) -l$(ARCHVER)
CCLIBFLAGS = $(LIBFLAGS)

########## End of flags from header.mak


CPP_FILES =	alpha.cpp execute.cpp fetch.cpp hardware.cpp issue.cpp make_connections.cpp memory.cpp memory_ops.cpp read.cpp run_simulation.cpp
C_FILES =	
PS_FILES =	
S_FILES =	
H_FILES =	hardware.h includes.h prototypes.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	execute.o fetch.o hardware.o issue.o make_connections.o memory.o memory_ops.o read.o run_simulation.o 

#
# Main targets
#

all:	alpha 

alpha:	alpha.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o alpha alpha.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

alpha.o:	hardware.h includes.h prototypes.h
execute.o:	
fetch.o:	hardware.h includes.h prototypes.h
hardware.o:	hardware.h includes.h prototypes.h
issue.o:	hardware.h includes.h prototypes.h
make_connections.o:	hardware.h includes.h prototypes.h
memory.o:	hardware.h includes.h prototypes.h
memory_ops.o:	hardware.h includes.h prototypes.h
read.o:	hardware.h includes.h prototypes.h
run_simulation.o:	hardware.h includes.h prototypes.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) alpha.o core

realclean:        clean
	-/bin/rm -f alpha 