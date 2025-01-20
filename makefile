# The following just specifies some variables for "flexibility".

# Specify the C++ compiler
CXX     = g++

# Specify options to pass to the compiler. Here it sets the optimisation
# level, outputs debugging info for gdb, and C++ version to use.
CXXFLAGS = -O0 -g3 -std=c++17

All: all
all: main JumpListTesterMain

# These are the two executables to be produced
main: main.cpp JumpList.o
	$(CXX) $(CXXFLAGS) main.cpp JumpList.o -o main

JumpListTesterMain: JumpListTesterMain.cpp JumpList.o JumpListTester.o
	$(CXX) $(CXXFLAGS) JumpListTesterMain.cpp JumpList.o JumpListTester.o -o JumpListTesterMain

# These are the "intermediate" object files
# The -c command produces them
JumpList.o: JumpList.cpp JumpList.h
	$(CXX) $(CXXFLAGS) -c JumpList.cpp -o JumpList.o

JumpListTester.o: JumpListTester.cpp JumpListTester.h JumpList.h
	$(CXX) $(CXXFLAGS) -c JumpListTester.cpp -o JumpListTester.o

# Some cleanup functions, invoked by typing "make clean" or "make deepclean"
deepclean:
	rm -f *~ *.o JumpListTesterMain main main.exe *.stackdump

clean:
	rm -f *~ *.o *.stackdump