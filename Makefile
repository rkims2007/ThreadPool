appname := threadpool
# the compiler: gcc for C program, define as g++ for C++
  CXX = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  CXXFLAGS  = -g3 -Wall -std=c++11
  LDLIBS = -lm -lpthread


  # the build target executable:
  srcfiles := $(shell find . -maxdepth 1 -name "*.cpp")
  objects  := $(patsubst %.cpp, %.o, $(srcfiles))

  all: $(appname)


$(appname): $(objects)
		$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)


