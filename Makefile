SRCS = src/library.cpp
EXE = a.out
SUBMITTY_CXXFLAGS = -I.

ifeq ($(DRIVER),)
	# Code.CS student settings (default)
	SRCS += src/main.cpp
else
	# Alternate driver supplied (likely for testing)
	SRCS += $(DRIVER)
endif

# Everything below that should not have to change ever.
CXX = g++

TARGET = all 

OBJS = $(SRCS:.cpp=.o)

CXXFLAGS = -g -std=c++17 -Wall $(SUBMITTY_CXXFLAGS)

LDFLAGS = -g 
LIBS =

SHELL = /bin/bash

$(EXE): $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(LDFLAGS) $(LIBS)

.SUFFIXES: .cpp

.cpp.o:  
	$(CXX) $(CXXFLAGS) -c $< -o $@

all : $(EXE)

clean:
	-rm -f $(OBJS)
	-rm -f *.o
	-rm -f $(EXE)
	