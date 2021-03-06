#
# Created by gmakemake (Ubuntu Jul 25 2014) on Sun May 14 18:26:02 2017
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
CXXFLAGS = $(CCFLAGS) --std=c++11
LIBFLAGS = -g -L$(BASE)/lib/$(SYS_TYPE) -l$(ARCHVER)
CCLIBFLAGS = $(LIBFLAGS)

########## End of flags from header.mak


CPP_FILES =	CPU.cpp execute.cpp fetch.cpp hardware.cpp hazards.cpp hw_exec.cpp hw_fetch.cpp hw_issue.cpp hw_mem.cpp hw_read.cpp issue.cpp make_connections.cpp memory.cpp pipeline.cpp read.cpp run_simulation.cpp
C_FILES =	
PS_FILES =	
S_FILES =	
H_FILES =	hardware.h hazards.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	execute.o fetch.o hardware.o hazards.o hw_exec.o hw_fetch.o hw_issue.o hw_mem.o hw_read.o issue.o make_connections.o memory.o pipeline.o read.o run_simulation.o 

#
# Main targets
#

all:	CPU 

CPU:	CPU.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o CPU CPU.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

CPU.o:	hardware.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
execute.o:	hardware.h hazards.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
fetch.o:	hardware.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
hardware.o:	hardware.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
hazards.o:	hardware.h hazards.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
hw_exec.o:	hardware.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
hw_fetch.o:	hardware.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
hw_issue.o:	hardware.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
hw_mem.o:	hardware.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
hw_read.o:	hardware.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
issue.o:	hardware.h hazards.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
make_connections.o:	hardware.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
memory.o:	hardware.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
pipeline.o:	hardware.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
read.o:	hardware.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h
run_simulation.o:	hardware.h hw_exec.h hw_fetch.h hw_issue.h hw_mem.h hw_read.h includes.h prototypes.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) CPU.o core

realclean:        clean
	-/bin/rm -f CPU 
